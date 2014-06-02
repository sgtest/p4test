/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# define NEED_ACCESS
# define NEED_ERRNO
# define NEED_STAT

# include <stdhdrs.h>
# include <charman.h>

# include <i18napi.h>
# include <charcvt.h>

# ifdef OS_VMS
# include <unistd.h>
# include <dirent.h>
# endif

# include <error.h>
# include <strbuf.h>
# include <strarray.h>

# include "pathsys.h"
# include "filesys.h"
# include "macfile.h"
# include "fileio.h"
# include "signaler.h"

# ifdef OS_NT
# include "windows.h"
extern int nt_islink( const char *fname );
# endif

// We can encounter .DS_Store files on *any* platform
// and we should remove them if we've been directed to
// RmDir().
//
// http://en.wikipedia.org/wiki/.DS_Store
//
StrRef DS_STORE_NAME(".DS_Store");


/*
 * filemkdir.cc -- mkdir and rmdir operations
 */

/*
 * FileSys::MkDir() - make directory, recursively if necessary
 */

void
FileSys::MkDir( const StrPtr &path, Error *e )
{
	PathSys *p = PathSys::Create();
	p->SetCharSet( GetCharSetPriv() );

	p->Set( path );

	// Bail if there is no parent, or the parent is "" (current dir)

	if( !p->ToParent() || !p->Length() )
	{
	    delete p;
	    return;
	}

	// BEOS and VMS:
	// Blinkin' thing's access() returns -1 for all directories,
        // so we use stat() instead.
	// Now we always use stat(), just 'cause it works.

# ifdef OS_NT
	wchar_t *wp;

	if( CharSetApi::isUnicode( (CharSetApi::CharSet)GetCharSetPriv() ) &&
	    ( wp = FileIO::UnicodeName( p->Text(), p->Length() ) ) )
	{
	    struct _stat sb;

	    if( _wstat( wp, &sb ) < 0 )
	    {
		MkDir( *p, e );

		if( !e->Test() )
		{
		    if( _wmkdir( wp ) < 0 && _wstat( wp, &sb ) < 0 )
			if( errno != EEXIST )
			    e->Sys( "mkdir", p->Text() );
		}
	    }

	    delete [] wp;
	    delete p;
	    return;
	}	
	if( nt_islink( p->Text() ) > 0 )
	{
	    delete p;
	    return;
	}
# endif

	// Ensure it is a dir.  On cygwin (at least) we can create
	// a directory with the same apparent name as a file (on
	// cygwin only if that file is a .exe).

	struct stat sb;

	if( stat( p->Text(), &sb ) >= 0 && S_ISDIR( sb.st_mode ) )
	{
	    delete p;
	    return;
	}

	// Recursively make the directory, but not on VMS, where
	// you can just mkdir() the whole path.

# ifndef OS_VMS
	MkDir( *p, e );

	if( e->Test() )
	{
	    delete p;
	    return;
	}
# endif

	// It seems that some versions of the MSVC runtime have a mangled
	// mkdir that succeeds but returns failure on our "foo,d" directories.

# if defined(OS_OS2) || defined(OS_NT)
	if( mkdir( p->Text() ) < 0 && stat( p->Text(), &sb ) < 0 )
	    if( errno != EEXIST )
		e->Sys( "mkdir", p->Text() );
# elif defined ( OS_MACOSX )
	if( mkdir( p->Text(), PERM_0777) < 0 )
		e->Sys( "mkdir", p->Text() );
# else
	if( mkdir( p->Text(), PERM_0777 ) < 0 )
	    if( errno != EEXIST )
		e->Sys( "mkdir", p->Text() );
# endif

	delete p;
}

void
FileSys::RmDir( const StrPtr &path, Error *e )
{
	PathSys *p = PathSys::Create();
	p->SetCharSet( GetCharSetPriv() );  

	p->Set( path );

	// Bail if there is no parent, or the parent is "" (current dir)

	if( !p->ToParent() || !p->Length() )
	{
	    delete p;
	    return;
	}

// Remove the directory.
	// Bail on failure.

# ifdef OS_CYGWIN
	// cygwin 1.3.12: rmdir() exits(!) if passwd CWD.

	char cwd[ 1024 ];
	getcwd( cwd, sizeof( cwd ) );

	if( !StrPtr::SCompare( p->Text(), cwd ) )
	{
	    delete p;
	    return;
	}
# endif

# ifdef OS_NT
	DWORD attr;
	wchar_t *wp = NULL;

	if( CharSetApi::isUnicode( (CharSetApi::CharSet)GetCharSetPriv() ) &&
	    ( wp = FileIO::UnicodeName( p->Text(), p->Length() ) ) )
	    attr = GetFileAttributesW( wp );
	else	
	    attr = GetFileAttributesA( p->Text() );

	// for windows bail if the directory is a 'junction'

	if( attr & FILE_ATTRIBUTE_REPARSE_POINT )
	{
	    delete [] wp;
	    delete p;
	    return;  
	}

	if( wp )
	{
	    if( _wrmdir( wp ) < 0 )
	    {

		delete [] wp;
		delete p;
		return; 
	    }
	    delete [] wp;
	}
	else
# endif
	if( rmdir( p->Text() ) < 0 )
	{
	    // It's possible we may have encountered a .DS_Store file
	    // These are created by the Finder on Mac OS X.
	    //
	    // http://en.wikipedia.org/wiki/.DS_Store
	    //
	    // These can be deleted with no harm.
	  
	    // First make a path for the .DS_Store file
	    //
	    PathSys * dsp = PathSys::Create();
	    dsp->SetCharSet( GetCharSetPriv() );
	    dsp->SetLocal( *p, DS_STORE_NAME );

	    FileSys * fs = FileSys::Create( FST_BINARY );
	    fs->Set( *dsp );

	    delete dsp;
	    
	    // If there doesn't exist a .DS_Store file, rmdir() failed for
	    // "legitimate" reasons. We bail.
	    //
	    if ( !(fs->Stat() & FSF_EXISTS) )
	    {
	        delete fs;
	        delete p;
	        return;
	    }
	    
	    // If the file exists, we need to make sure it is the *only* file
	    // in the directory.
	    //
	    FileSys * dir = FileSys::Create( FST_BINARY );

	    if ( !dir )
	    {
	        delete fs;
	        delete p;
	        return;
	    }
	    dir->Set( *p );
	    
	    StrArray * files = dir->ScanDir( e );
	    
	    if ( files && files->Count() == 1 )
	        fs->Unlink( e );

	    delete fs;
	    delete dir;
	    delete files;

	    // Try again
	    //
	    if( rmdir( p->Text() ) < 0 )
	    {
	        delete p;
	        return;
	    }
	}

	// Hey -- it worked.  Try to get the parent.

	RmDir( *p, e );

	delete p;
}
