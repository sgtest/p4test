/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# define NEED_FCNTL
# define NEED_FILE
# define NEED_STAT
# define NEED_UTIME
# define NEED_ERRNO
# define NEED_SLEEP
# define NEED_CHDIR

# include <stdhdrs.h>

# include <error.h>
# include <errornum.h>
# include <strbuf.h>
# include <debug.h>
# include <tunable.h>
# include <datetime.h>
# include <i18napi.h>
# include <charcvt.h>
# include <lockfile.h>
# include <largefile.h>

# include "filesys.h"
# include "pathsys.h"
# include "fileio.h"

extern int global_umask;

# define utimbufL _utimbuf

# define DOUNICODE	( CharSetApi::isUnicode((CharSetApi::CharSet)GetCharSetPriv()) )

// The REPARSE_DATA_BUFFER is part of the "Windows Driver Kit" according to
// the MSDN docs, so for the time being we just copy the structure here:
//
# ifndef OS_MINGW
typedef struct _REPARSE_DATA_BUFFER {
	ULONG  ReparseTag;
	USHORT ReparseDataLength;
	USHORT Reserved;
	union {
		// if ReparseTag == IO_REPARSE_TAG_SYMLINK:
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			ULONG  Flags;
			WCHAR  PathBuffer[1];
		} SymbolicLinkReparseBuffer;

		// if ReparseTag == IO_REPARSE_TAG_MOUNT_POINT:
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			WCHAR  PathBuffer[1];
		} MountPointReparseBuffer;
		
		// Just bulks up the structure so I can allocate it on the stack
		struct {
			UCHAR DataBuffer[MAX_PATH * 4];
		} GenericReparseBuffer;
	} ;
} REPARSE_DATA_BUFFER, *PREPARSE_DATA_BUFFER;
# endif

// We also include a handful of relevant magic constants from the device
// driver development kit here:
//
#ifndef FSCTL_GET_REPARSE_POINT
// define FSCTL_GET_REPARSE_POINT     CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 42, METHOD_BUFFERED, FILE_ANY_ACCESS)
# define FSCTL_GET_REPARSE_POINT 0x000900A8
# endif
# ifndef IO_REPARSE_TAG_SYMLINK
# define IO_REPARSE_TAG_SYMLINK 0xA000000CL
# endif
# ifndef S_ISDIR
# define S_ISDIR(m) (((m)&S_IFMT)==S_IFDIR)
# endif
# ifndef SYMBOLIC_LINK_FLAG_DIRECTORY 
# define SYMBOLIC_LINK_FLAG_DIRECTORY 1
# endif

typedef BOOLEAN (WINAPI *CreateSymbolicLinkProc)(LPCSTR,LPCSTR,DWORD);

static CreateSymbolicLinkProc CreateSymbolicLink_func = 0;
static int functionHandlesLoaded = 0;

int
nt_makelink( const char *target, const char *name )
{
	int result = -1;

	if( !FileSys::SymlinksSupported() )
	    return result;
	char tgt[MAX_PATH];
	char *p = tgt;
	while( *target )
	{
	    *p = *target == '/' ? '\\' : *target;
	    p++;
	    target++;
	}
	*p = '\0';

	// Since the target may be relative, cd to the source's directory
	char curDir[1024];
	_getcwd( curDir, sizeof( curDir ) );
	PathSys *pth = PathSys::Create();
	pth->Set( StrRef( name ) );
	pth->ToParent();
	_chdir( pth->Text() );

	struct stat sb;
	DWORD dwFlags = 0;
	if( stat( tgt, &sb ) >= 0 )
	{
	    if( S_ISDIR( sb.st_mode ) )
	        dwFlags = SYMBOLIC_LINK_FLAG_DIRECTORY;
	}
	if( (*CreateSymbolicLink_func)( name, tgt, (DWORD)dwFlags ) )
	    result = 0;
	_chdir( curDir );
	delete pth;

	return result;
}

int
nt_islink( const char *fname )
{
	DWORD fileAttributes = GetFileAttributes( fname );
	if( fileAttributes == INVALID_FILE_ATTRIBUTES )
	    return -1;
	if( fileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
	{
	    WIN32_FIND_DATA findFileData;
	    HANDLE fH = FindFirstFile( fname, &findFileData );
	    if( fH == INVALID_HANDLE_VALUE )
	        return -1;
	    FindClose( fH );
	    if( findFileData.dwReserved0 == IO_REPARSE_TAG_SYMLINK     ||
	        findFileData.dwReserved0 == IO_REPARSE_TAG_MOUNT_POINT )
	        return 1;
	}
	return 0;
}

// Reads what the symlink points to, puts the data into targetBuf.
// Returns the number of bytes read.
//
int
nt_readlink( const char *name, char *targetBuf, int bufSize )
{
	HANDLE fH = CreateFile( name, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING,
		(FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OPEN_REPARSE_POINT), 0);
	if( fH == INVALID_HANDLE_VALUE )
	    return -1;
	REPARSE_DATA_BUFFER reparseBuffer;
	DWORD returnedLength;
	DWORD result = DeviceIoControl( fH, FSCTL_GET_REPARSE_POINT, 0, 0,
			&reparseBuffer, sizeof(reparseBuffer),
			&returnedLength, 0 );
	CloseHandle( fH );
	if( !result )
	    return -1;

	int len, off;
	WCHAR *wp;

	// This is low-level device driver and file system filter data
	// structures, so we tread gently. By observation, the substitute
	// name and the print name are similar, but the substitute name,
	// particularly for junctions, seems to often point to the so-called
	// "non-parsed string", which starts "\??\". I haven't found any
	// docs about that magic string prefix, and have been successfully
	// using the PrintName representation instead.
	//
	if( reparseBuffer.ReparseTag == IO_REPARSE_TAG_SYMLINK )
	{
	    len = reparseBuffer.SymbolicLinkReparseBuffer.PrintNameLength;
	    off = reparseBuffer.SymbolicLinkReparseBuffer.PrintNameOffset;
	    wp  = reparseBuffer.SymbolicLinkReparseBuffer.PathBuffer;
	}
	else if( reparseBuffer.ReparseTag == IO_REPARSE_TAG_MOUNT_POINT )
	{
	    len = reparseBuffer.MountPointReparseBuffer.PrintNameLength;
	    off = reparseBuffer.MountPointReparseBuffer.PrintNameOffset;
	    wp  = reparseBuffer.MountPointReparseBuffer.PathBuffer;
	}
	else
	{
	    return -1;
	}

	len = len / sizeof(WCHAR);
	off = off / sizeof(WCHAR);
	wp += off;

	int retlen = len;
	char *o = targetBuf;
	while( len-- )
	{
	    char c = *wp++;
	    *o++ = c == '\\' ? '/' : c;
	}
	*o = 0;
	return retlen;
}


static int
nt_open( const char *fname, int flags, int mode, int dounicode )
{
# ifdef O_NOINHERIT
	// All files on Windows are set to no inherit.
	//
	flags |= O_NOINHERIT;
# endif

	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    int newlen = 0;

	    const char *wname = cvt.FastCvt( fname, strlen( fname ), &newlen );

	    if( newlen > ( MAX_PATH * 2 ) )
	    {
		SetLastError( ERROR_BUFFER_OVERFLOW );
		return -1;
	    }

	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		return _wopen( (const wchar_t *)wname, flags, mode );
	    }
	}

	if( strlen( fname ) > MAX_PATH )
	{
	    SetLastError( ERROR_BUFFER_OVERFLOW );
	    return -1;
	}

	return ::open(fname, flags, mode);
}

static int
nt_stat( const char *fname, struct statbL *sb, int dounicode )
{
	int ret;

	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    int newlen = 0;

	    const char *wname = cvt.FastCvt( fname, strlen( fname ), &newlen );

	    if( newlen > ( MAX_PATH * 2 ) )
	    {
		SetLastError( ERROR_BUFFER_OVERFLOW );
		return -1;
	    }

	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		ret = _wstati64( (const wchar_t *)wname, sb );
		if ( ret >= 0 || errno != ENOENT )
		    return ret;
	    }
	}

	if( strlen( fname ) > MAX_PATH )
	{
	    SetLastError( ERROR_BUFFER_OVERFLOW );
	    return -1;
	}

	return ::_stati64( fname, sb );
}

static int
nt_unlink( const char *fname, int dounicode )
{
	int ret;

	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    const char *wname = cvt.FastCvt( fname, strlen( fname ) );
	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		ret = _wunlink( (const wchar_t *)wname );
		if ( ret >= 0 || errno != ENOENT )
		    return ret;
	    }
	}
	if( nt_islink( fname ) > 0 && RemoveDirectory( fname ) )
	        return 0;

	return ::_unlink( fname );
}

static HANDLE nt_openHandleW( const wchar_t *wname)
{
	return CreateFileW( wname,
	        FILE_WRITE_ATTRIBUTES,
	        ( FILE_SHARE_READ | FILE_SHARE_WRITE ),
	        NULL,
	        OPEN_EXISTING,
	        FILE_ATTRIBUTE_NORMAL,
	        NULL);
}
static HANDLE nt_openDirOrFileHandle( const char *fname, DWORD flags )
{
	return CreateFile( fname,
	        FILE_WRITE_ATTRIBUTES,
	        ( FILE_SHARE_READ | FILE_SHARE_WRITE ),
	        NULL,
	        OPEN_EXISTING,
	        flags,
	        NULL);
}
static HANDLE nt_openHandle( const char *fname )
{
	return nt_openDirOrFileHandle( fname, FILE_ATTRIBUTE_NORMAL );
}
static HANDLE nt_openDirHandle( const char *fname )
{
	return nt_openDirOrFileHandle( fname,
		( FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL ) );
}

static int nt_convertToFileTime( time_t t32, FILETIME *ft)
{
	SYSTEMTIME st;
	struct tm *u_tm;

	u_tm = ::gmtime( &t32 );

	if( !u_tm )
	    return -1;

	st.wMilliseconds = 0;
	st.wDayOfWeek = 0;
	st.wSecond = u_tm->tm_sec;
	st.wMinute = u_tm->tm_min;
	st.wHour   = u_tm->tm_hour;
	st.wDay    = u_tm->tm_mday;
	st.wMonth  = u_tm->tm_mon + 1;
	st.wYear   = u_tm->tm_year + 1900;

	SystemTimeToFileTime( &st, ft );

	return 0;
}

static int
nt_setFileTimes( HANDLE hFile, time_t t32 )
{
	FILETIME ft;
	int result;

	if( hFile == INVALID_HANDLE_VALUE || t32 == -1 ||
		nt_convertToFileTime( t32, &ft ) )
	    return -1;
	result = SetFileTime( hFile, (LPFILETIME)0, (LPFILETIME)0, &ft ) != 0
		? 0 : -1 ;
	CloseHandle( hFile );
	return result;
}

static int
nt_utime( const char *fname, struct utimbufL *ut, int dounicode )
{
	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    const char *wname = cvt.FastCvt( fname, strlen( fname ) );
	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
	        return nt_setFileTimes(
	            nt_openHandleW( (const wchar_t *)wname ),
	            ut->modtime );
	    }
	}
	return nt_setFileTimes( nt_openHandle( fname ), ut->modtime );
}

static int
nt_chmod( const char *fname, int m, int dounicode )
{
	int ret;

	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    const char *wname = cvt.FastCvt( fname, strlen( fname ) );
	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		ret = _wchmod( (const wchar_t *)wname, m );
		if ( ret >= 0 || errno != ENOENT )
		    return ret;
	    }
	}
	return ::_chmod( fname, m );
}

static int
nt_rename( const char *fname, const char *nname, int dounicode )
{
	int ret;

	if ( dounicode )
	{
	    CharSetCvtUTF816 cvt;
	    const char *wname = cvt.FastCvt( fname, strlen( fname ) );
	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		wchar_t *wnname = FileIO::UnicodeName( nname, strlen( nname ) );
		if ( wnname )
		{
		    ret = _wrename( (const wchar_t *)wname, wnname );
		    delete [] (char *)wnname;
		    if ( ret >= 0 || errno != ENOENT )
			return ret;
		}
	    }
	}
	return ::rename( fname, nname );
}

void
FileIO::Rename( FileSys *target, Error *e )
{
	// On VMS and Novelle, the source must be writable (deletable, 
	// actually) for the rename() to unlink it.  So we give it write 
	// perm first and then revert it to original perms after.

	Chmod( FPM_RW, e );

	// Don't unlink the target unless the source exists,
	// as our rename isn't atomic (like on UNIX) and some
	// stumblebum user may have removed the source file.

	if( e->Test() )
	    return;

	// Remember original perms of target so we can reset on failure.

	FilePerm oldPerms = Stat() | FSF_WRITEABLE ? FPM_RW : FPM_RO;

	// One customer (in Iceland) wanted this for IRIX as well.
	// You need if you are you running NFS aginst NT as well
	// if you are running on NT.  Gag me!
	//
	// To support case-changing a file,  rename needs to NOT
	// unlink the file in this case, this is mainly client support.
	
	const StrPtr *targetPath = target->Path();

	if( ( Path()->Length() != targetPath->Length() ) ||
	      Path()->Compare( *targetPath ) )
	{
	    target->Unlink( 0 ); // yeech - must not exist to rename
	}

	if( nt_rename( Name(), target->Name(), DOUNICODE ) < 0 )
	{
	    // nasty hack coming up.
	    // one customer is suffering from a rename() problem
	    // that requires more diagnostics,  so we will retry 
	    // the rename() 10 times with 1 second interval and
	    // log any failure.

	    int ret;
	    int renameMax  = p4tunable.Get( P4TUNE_SYS_RENAME_MAX );
	    int renameWait = p4tunable.Get( P4TUNE_SYS_RENAME_WAIT );

	    for( int i=0; i < renameMax; ++i )
	    {
	        msleep( renameWait );

	        target->Unlink( 0 );

	        ret = nt_rename( Name(), target->Name(), DOUNICODE );

	        if( ret >= 0 )
	            break;
	    }

	    if( ret < 0 )
	    {
	        StrBuf b;
	        b << "failed to rename " << target->Name()
	          << " after " << StrNum( renameMax ) << " attempts";
	        e->Sys( "rename", b.Text() );

	        // failed, restore original target perms. 

	        target->Perms( oldPerms );
	        target->Chmod( e );
	        return;
	    }
	}

	// reset the target to our perms

	target->Perms( perms );
	target->Chmod( e );

	// source file has been deleted,  clear the flag
	ClearDeleteOnClose();
}

/*
 * FileIO::Unlink() - remove single file (error optional)
 */

void
FileIO::Unlink( Error *e )
{
	// yeech - must be writable to remove

	if( *Name() )
	    nt_chmod( Name(), PERM_0666  & ~global_umask, DOUNICODE );

	if( *Name() && nt_unlink( Name(), DOUNICODE ) < 0 && e )
	    e->Sys( "unlink", Name() );
}

wchar_t *
FileIO::UnicodeName( const char* fname, int flen )
{
	wchar_t *ret;

	CharSetCvtUTF816 cvt;

	ret = (wchar_t *) cvt.CvtBuffer( fname, flen );

	if ( cvt.LastErr() != CharSetCvt::NONE )
	{
	    delete [] (char *)ret;
	    ret = NULL;
	}

	return ret;
}

void
FileIO::ChmodTime( int modTime, Error *e )
{
	struct utimbufL t;

	t.actime = 0; // This is ignored by nt_utime
	t.modtime = DateTime::Localize( modTime );

	if( nt_utime( Name(), &t, DOUNICODE ) < 0 )
	    e->Sys( "utime", Name() );
}

void
FileIO::Truncate( Error *e )
{
	// Don't bother if non-existent.

	if( !( Stat() & FSF_EXISTS ) )
	    return;

	// Try truncate first; if that fails (as it will on secure NCR's),
	// then open O_TRUNC.
	
	int fd;

	if( ( fd = nt_open( Name(), O_WRONLY|O_TRUNC, PERM_0666, DOUNICODE ) ) >= 0 )
	{
	    close( fd );
	    return;
	}

	e->Sys( "truncate", Name() );
}

/*
 * FileIO::Stat() - return flags if file exists
 */

int
FileIO::Stat()
{
	// Stat & check for missing, special

	int flags = 0;
	struct statbL sb;

	if( FileSys::SymlinksSupported() && nt_islink( Name() ) > 0 )
	{
	    char linkTarget[ MAX_PATH ];
	    if( nt_readlink( Name(), linkTarget, sizeof( linkTarget ) ) < 0 )
	        return flags;
	    flags = FSF_SYMLINK;
	    if( nt_stat( linkTarget, &sb, DOUNICODE ) >= 0 )
	        flags |= FSF_EXISTS;
	    return flags;
	}

	if( nt_stat( Name(), &sb, DOUNICODE ) < 0 )
	    return flags;

	flags |= FSF_EXISTS;

	if( sb.st_mode & S_IWUSR ) flags |= FSF_WRITEABLE;
	if( sb.st_mode & S_IXUSR ) flags |= FSF_EXECUTABLE;
	if( S_ISDIR( sb.st_mode ) ) flags |= FSF_DIRECTORY;
	if( !S_ISREG( sb.st_mode ) ) flags |= FSF_SPECIAL;
	if( !sb.st_size ) flags |= FSF_EMPTY;

	return flags;
}

int
FileIO::GetOwner()
{
	int uid = 0;
	struct statbL sb;

	if( FileSys::SymlinksSupported() && nt_islink( Name() ) > 0 )
	{
	    char linkTarget[ MAX_PATH ];
	    if( nt_readlink( Name(), linkTarget, sizeof( linkTarget ) ) < 0 )
	        return uid;

	    if( nt_stat( linkTarget, &sb, DOUNICODE ) >= 0 )
	        uid = sb.st_uid;
	    return uid;
	}

	if( nt_stat( Name(), &sb, DOUNICODE ) >= 0 )
	    uid = sb.st_uid;
	return uid;
}

bool
FileIO::HasOnlyPerm( FilePerm perms )
{
# ifdef false
	/*
	 * This code does not work on windows since the
	 * windows does not handle the notion of group and world
	 * permissions in the same way unix does.  Brent is looking
	 * into seeing if there is a way to assure security on
	 * the credentials directory and file.  For now commented out.
	 */
	struct statbL sb;
	int modeBits = 0;

	if( nt_stat( Name(), &sb, DOUNICODE ) < 0 )
	    return false;

	switch (perms)
	{
	case FPM_RO:
	    modeBits = PERM_0222;
	    break;
	case FPM_RW:
	    modeBits = PERM_0666;
	    break;
	case FPM_ROO:
	    modeBits = PERM_0400;
	    break;
	case FPM_RXO:
	    modeBits = PERM_0500;
	    break;
	case FPM_RWO:
	    modeBits = PERM_0600;
	    break;
	case FPM_RWXO:
	    modeBits = PERM_0700;
	    break;
	}
	/*
	 * In this case we want an exact match of permissions
	 * We don't want to "and" to a mask, since we also want
	 * to verify that the other bits are off.
	 */
	if( (sb.st_mode & PERMSMASK) == modeBits )
		return true;

	return false;
# else
	return true;
# endif //ifdef 0
}

# ifdef OS_MINGW

static int nt_getLastModifiedTime( HANDLE hFile )
{
	// Convert file timestamp to local time, then to time_t.
	// This is because MINGW doesn't have _mkgmtime, but does have mktime.
	SYSTEMTIME st;
	SYSTEMTIME stUTC;
	struct tm u_tm;
	FILETIME cTime, aTime, mTime;

	if (hFile == INVALID_HANDLE_VALUE)
	    return -1;
	if( !GetFileTime( hFile, &cTime, &aTime, &mTime ) )
	    return -1;
	CloseHandle( hFile );

	FileTimeToSystemTime( &mTime, &stUTC );
	SystemTimeToTzSpecificLocalTime( NULL, &stUTC, &st );

	u_tm.tm_sec   = st.wSecond;
	u_tm.tm_min   = st.wMinute;
	u_tm.tm_hour  = st.wHour;
	u_tm.tm_mday  = st.wDay;
	u_tm.tm_mon   = st.wMonth - 1;
	u_tm.tm_year  = st.wYear - 1900;
	u_tm.tm_wday  = 0;
	u_tm.tm_yday  = 0;
	u_tm.tm_isdst = 0;

	return (int)( DateTime::Centralize( ::mktime( &u_tm ) ) );
}

# else

static int nt_getLastModifiedTime( HANDLE hFile )
{
	SYSTEMTIME st;
	struct tm u_tm;
	FILETIME cTime, aTime, mTime;

	if (hFile == INVALID_HANDLE_VALUE)
	    return -1;
	if( !GetFileTime( hFile, &cTime, &aTime, &mTime ) )
	    return -1;
	CloseHandle( hFile );

	FileTimeToSystemTime( &mTime, &st );

	u_tm.tm_sec   = st.wSecond;
	u_tm.tm_min   = st.wMinute;
	u_tm.tm_hour  = st.wHour;
	u_tm.tm_mday  = st.wDay;
	u_tm.tm_mon   = st.wMonth - 1;
	u_tm.tm_year  = st.wYear - 1900;
	u_tm.tm_wday  = 0;
	u_tm.tm_yday  = 0;
	u_tm.tm_isdst = 0;

	return (int)( DateTime::Centralize( ::_mkgmtime( &u_tm ) ) );
}

# endif

int
FileIO::StatModTime()
{
	const char *fname = Name();

	if ( DOUNICODE )
	{
	    CharSetCvtUTF816 cvt;
	    const char *wname = cvt.FastCvt( fname, strlen( fname ) );
	    if ( cvt.LastErr() == CharSetCvt::NONE )
	        return nt_getLastModifiedTime(
				nt_openHandleW( (const wchar_t *)wname ) );
	}
	if( nt_islink( fname ) > 0 )
	    return nt_getLastModifiedTime( nt_openDirHandle( fname ) );
	return nt_getLastModifiedTime( nt_openHandle( fname ) );
}

void
FileIO::Chmod( FilePerm perms, Error *e )
{
	// Don't set perms on symlinks

	if( ( GetType() & FST_MASK ) == FST_SYMLINK )
	    return;

	// Permissions for readonly/readwrite, exec vs no exec

	int bits = IsExec() ? PERM_0777 : PERM_0666;

	switch( perms )
	{
	case FPM_RO: bits &= ~PERM_0222; break;
	case FPM_ROO: bits &= ~PERM_0266; break;
	case FPM_RWO: bits = PERM_0600; break; // for key file, set exactly to rwo
	case FPM_RXO: bits = PERM_0500; break;
	}

	if( nt_chmod( Name(), bits & ~global_umask, DOUNICODE ) >= 0 )
	    return;

	// Can be called with e==0 to ignore error.

	if( e )
	    e->Sys( "chmod", Name() );
}

void
FileIOBinary::Open( FileOpenMode mode, Error *e )
{
	// Save mode for write, close

	this->mode = mode;

	// Get bits for (binary) open

	int bits = openModes[ mode ].bflags;

	// Handle exclusive open (must not already exist)

# ifdef O_EXCL
	// Set O_EXCL to ensure we create the file when we open it.

	if( GetType() & FST_M_EXCL )
	    bits |= O_EXCL;
# else
	// No O_EXCL: we'll manually check if file already exists.
	// Not atomic, but what can one do?

	if( GetType() & FST_M_EXCL && Stat() & FSF_EXISTS )
	{
	    e->Set( E_FAILED, "file exists" );

	    // if file is set delete on close unset that because we
	    // didn't create the file...
	    ClearDeleteOnClose();
	    return;
	}
# endif

	// open stdin/stdout or real file

	if( Name()[0] == '-' && !Name()[1] )
	{
	    // we do raw output: flush stdout
	    // for nice mixing of messages.

	    if( mode == FOM_WRITE )
		fflush( stdout );

	    fd = openModes[ mode ].standard;
	}
	else if( ( fd = nt_open( Name(), bits, PERM_0666, DOUNICODE ) ) < 0 )
	{
	    e->Sys( openModes[ mode ].modeName, Name() );
# ifdef O_EXCL
	    // if we failed to create the file probably due to the
	    // file already existing (O_EXCL)
	    // then unset delete on close because we didn't create it...
	    if( ( bits & (O_EXCL|O_CREAT) ) == (O_EXCL|O_CREAT) )
		ClearDeleteOnClose();
# endif
	}


	if( e->Test() )
	    return;

	// Do we need to preallocate (fragmentation ?)

	offL_t sizeOffSet = GetSizeHint();

	if( sizeOffSet )
	{
	    FileIOBinary::Seek( sizeOffSet - (offL_t)1, e );

	    if( !e->Test() )
	    {
	        char endFile = 0;
	        FileIOBinary::Write( &endFile, 1, e );
	        FileIOBinary::Seek( (offL_t)0, e );
	    }
	}
}

offL_t
FileIOBinary::GetSize()
{
	struct _stati64 sb;

	if ( DOUNICODE )
	{
	    CharSetCvtUTF816 cvt;
	    int newlen = 0;

	    const char *wname = cvt.FastCvt( Name(), strlen(Name()), &newlen );

	    if ( cvt.LastErr() == CharSetCvt::NONE )
	    {
		if( _wstati64( (const wchar_t *)wname, &sb ) < 0 )
		    return -1;
	    }

	    if( newlen > ( MAX_PATH * 2 ) )
	    {
		SetLastError( ERROR_BUFFER_OVERFLOW );
		return -1;
	    }

	    return sb.st_size;
	}

	if( _stati64( Name(), &sb ) < 0 )
	    return -1;

	return sb.st_size;
}

void
FileIOBinary::Seek( offL_t offset, Error *e )
{
	if( _lseeki64( fd, offset, 0 ) == -1 && e )
		e->Sys( "Seek", Name() );
	tellpos = offset;
}

void
FileIOAppend::Open( FileOpenMode mode, Error *e )
{
	// Save mode for write, close

	this->mode = mode;

	// open stdin/stdout or real file

	if( Name()[0] == '-' && !Name()[1] )
	{
	    fd = openModes[ mode ].standard;
	}
	else if( ( fd = nt_open( Name(), openModes[ mode ].aflags,
				 PERM_0666, DOUNICODE ) ) < 0 )
	{
	    e->Sys( openModes[ mode ].modeName, Name() );
	}
}

offL_t
FileIOAppend::GetSize()
{
	offL_t s = 0;

	if( !lockFile( fd, LOCKF_SH ) )
	{
	    BY_HANDLE_FILE_INFORMATION bhfi;

	    if( GetFileInformationByHandle(
	                    (HANDLE)_get_osfhandle( fd ), &bhfi ) )
	        s = ((offL_t)(bhfi.nFileSizeHigh)) * (0x100000000LL) +
	            (offL_t)(bhfi.nFileSizeLow);

	    lockFile( fd, LOCKF_UN );
	}
	else
	    s = FileIOBinary::GetSize();

	return s;
}

void
FileIOAppend::Write( const char *buf, int len, Error *e )
{
	// We do an unbuffered write here to guarantee the atomicity
	// of the write.  Stdio might break it up into chunks, whereas
	// write() is supposed to keep it whole.

	if( lockFile( fd, LOCKF_EX ) < 0 )
	{
	    e->Sys( "lock", Name() );
	    return;
	}

	FileIOBinary::Write( buf, len, e );

	if( lockFile( fd, LOCKF_UN ) < 0 )
	{
	    e->Sys( "unlock", Name() );
	    return;
	}
}

void
FileIOAppend::Rename( FileSys *target, Error *e )
{
	// File may be open, so to rename we copy 
	// and truncate FileIOAppend files on NT.

	Copy( target, FPM_RO, e );

	if( e->Test() )
	    return;

	Truncate( e );
}

int
FileSys::SymlinksSupported()
{
	if( !functionHandlesLoaded)
	{
	    functionHandlesLoaded = 1;

	    CreateSymbolicLink_func = (CreateSymbolicLinkProc)
		    GetProcAddress(
	                GetModuleHandle("kernel32.dll"),
	                "CreateSymbolicLinkA");

	    if( CreateSymbolicLink_func != 0 )
	    {
		const char *tempdir = getenv("TEMP");
		if( !tempdir )
		{
	            CreateSymbolicLink_func = 0;
		    return 0;
		}
		StrBuf testLink;
		StrBuf testTarget;
		testLink << tempdir << "\\p4_test_symlink";
		testTarget << tempdir << "\\p4_test_target";
	        nt_chmod( testLink.Text(), PERM_0666  & ~global_umask, 0 );
		nt_unlink( testLink.Text(), 0 );
		int result = nt_makelink( testTarget.Text(), testLink.Text() );
		nt_unlink( testLink.Text(), 0 );
		if( result < 0 )
	            CreateSymbolicLink_func = 0;
	    }
	}
	return CreateSymbolicLink_func != 0;
}


