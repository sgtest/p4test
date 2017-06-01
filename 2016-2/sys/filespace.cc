/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# define NEED_SLEEP
# define NEED_STATFS
# define NEED_STATVFS

# ifdef OS_NT
# undef _WIN32_WINNT
# define _WIN32_WINNT 0x0600
# include <windows.h>
# if (_MSC_VER >= 1800)
# include <fileapi.h>
# endif
# endif
# include <stdhdrs.h>

# include <error.h>
# include <strbuf.h>
# include <i18napi.h>
# include <charcvt.h>
# include <debug.h>
# include <tunable.h>

# include "filesys.h"
# include "pathsys.h"
# include "fileio.h"

extern void nt_free_wname( const wchar_t *wname );

/*
 * FileSys::GetDiskSpace -- fill in details about disk space usage.
 */

DiskSpaceInfo::DiskSpaceInfo()
{
	this->fsType = new StrBuf();
	blockSize = totalBytes = usedBytes = freeBytes = 0;
	pctUsed = 0;
}

DiskSpaceInfo::~DiskSpaceInfo()
{
	delete this->fsType;
}

void
FileSys::GetDiskSpace( DiskSpaceInfo *info, Error *e )
{
	info->fsType->Set( "unknown" );
# ifdef OS_NT

	// Setup for a file or a directory.
	FileSys *fs = FileSys::Create( FST_TEXT );
	fs->Set( Name() );
	int is_dir = ( fs->Stat() & (FSF_EXISTS|FSF_DIRECTORY)) ==
			(FSF_EXISTS|FSF_DIRECTORY);
	delete fs;

	if( !is_dir )
	{
	    PathSys *ps = PathSys::Create();
	    ps->Set( Name() );
	    ps->ToParent();
	    Set( ps->Text() );
	    delete ps;
	}

	// Force LFN on.
	LFN = LFN_ENABLED;
	if( IsUNC( *Path() ) )
	    LFN |= LFN_UNCPATH;
	if( DOUNICODE )
	    LFN |= LFN_UTF8;

	const wchar_t *wname = NULL;
	if( ( wname = FileIO::UnicodeName( (StrBuf *)Path(), LFN ) ) == NULL )
	{
	    e->Sys( "UnicodeName", Name() );
	    return;
	}

	ULARGE_INTEGER freeBytesAvailable;
	ULARGE_INTEGER totalNumberOfBytes;
	ULARGE_INTEGER totalNumberOfFreeBytes;

	BOOL bRet = GetDiskFreeSpaceExW( wname,
				&freeBytesAvailable,
				&totalNumberOfBytes,
				&totalNumberOfFreeBytes );
	if( !bRet )
	{
	    if( wname )
		nt_free_wname( wname );
	    e->Sys( "GetDiskFreeSpaceExW", Name() );
	    return;
	}

	info->blockSize = -1;
	info->freeBytes = freeBytesAvailable.QuadPart;
	info->totalBytes= totalNumberOfBytes.QuadPart;

	// Open the directory so we can use the wide GetVolumeInformation
	HANDLE fH;
	fH = CreateFileW( wname,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);
	if( wname )
	    nt_free_wname( wname );
	if( fH == INVALID_HANDLE_VALUE )
	{
	    e->Sys( "CreateFileW", Name() );
	    return;
	}

# if !defined( OS_MINGW )
	wchar_t vName[MAX_PATH+1];
	wchar_t wfsType[MAX_PATH+1];
	char fsType[MAX_PATH+1];

	bRet = GetVolumeInformationByHandleW( fH, 
				vName, (DWORD)MAX_PATH,
				(LPDWORD)0, (LPDWORD)0, (LPDWORD)0,
				wfsType, (DWORD)MAX_PATH );
	CloseHandle( fH );
	if( bRet == 0 )
	{
	    e->Sys( "GetVolumeInformationByHandleW", Name() );
	    return;
	}

	// Convert unicode to multibyte.
	bRet = WideCharToMultiByte (
		CP_ACP,
		(DWORD)0,	// Use default flags
		wfsType,
		-1,		// wfsType is NULL terminated
		fsType,
		MAX_PATH,
		NULL,
		NULL
		);
	if ( bRet == 0 )
	{
	    e->Sys( "WideCharToMultiByte", Name() );
	    return;
	}

	info->fsType->Set( fsType );
# else
	info->fsType->Set( "NTFS" );
# endif
	info->usedBytes = info->totalBytes - info->freeBytes;
	double usage = 1.0;
	if( info->totalBytes > 0 )
	    usage = (double)info->usedBytes / (double)info->totalBytes;
	info->pctUsed = (int)( usage * 100 );
# else
	if( !strchr( Name(), '/' ) )
	{
	    StrBuf nm;
	    nm << "./" << Name();
	    Set( nm );
	}
	PathSys *ps = PathSys::Create();
	ps->Set( Name() );
	ps->ToParent();
	Set( ps->Text() );
	delete ps;

	struct statvfs df;

	if( statvfs( Name(), &df ) == -1 )
	{
	    e->Sys( "statvfs", Name() );
	    return;
	}

	info->blockSize = df.f_frsize;
	info->freeBytes  = (P4INT64) ( (double) df.f_frsize * df.f_bfree  );
	info->totalBytes = (P4INT64) ( (double) df.f_frsize * df.f_blocks );
	info->usedBytes  = info->totalBytes - info->freeBytes;
	info->freeBytes  = (P4INT64) ( (double) df.f_frsize * df.f_bavail );
	double usage = 1.0;
	if( info->totalBytes > 0 )
	    usage = (double)info->usedBytes /
	            (double)(info->usedBytes + info->freeBytes);
	info->pctUsed = (int)( usage * 100 );

	// Note that used + free may not equal total, and also note that
	// used/total does not match pctUsed. This is because
	// the filesystem may also have 'reserved' space, which is
	// available only to privileged users, and we are attemptint
	// to return the non-privileged information, like df does.

# ifdef HAVE_STATVFS_BASETYPE
	info->fsType->Set( df.f_basetype );
# endif

# endif

# ifdef HAVE_STATFS
	struct statfs sys_fs;

	if( statfs( Name(), &sys_fs ) == -1 )
	{
	    e->Sys( "statfs", Name() );
	    return;
	}

# ifdef HAVE_STATFS_FSTYPENAME
	info->fsType->Set( sys_fs.f_fstypename );
# else
	switch( sys_fs.f_type )
	{
	case 0x6969: 
	    info->fsType->Set( "nfs" );
	    break;
	case 0xEF53: 
	    info->fsType->Set( "ext2" );
	    break;
	case 0x58465342: 
	    info->fsType->Set( "xfs" );
	    break;
	case 0x1021994: 
	    info->fsType->Set( "tmpfs" );
	    break;
	case 0x858458f6: 
	    info->fsType->Set( "ramfs" );
	    break;
	case 0x00011954: 
	    info->fsType->Set( "ufs" );
	    break;
	case 0x52654973: 
	    info->fsType->Set( "reiserfs" );
	    break;
	default:
	    info->fsType->Set( StrNum( (P4INT64) sys_fs.f_type ) );
	    break;
	}
# endif

# endif
}
