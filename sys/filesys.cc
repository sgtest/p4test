/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <stdhdrs.h>
# include <charman.h>

# include <i18napi.h>
# include <charcvt.h>
# include <charset.h>

# include <error.h>
# include <debug.h>
# include <tunable.h>
# include <strbuf.h>
# include <strops.h>
# include <md5.h>

# include "pathsys.h"
# include "filesys.h"
# include "macfile.h"
# include "fileio.h"
# include "signaler.h"
# include "enviro.h"
# include "errno.h"
# include "hostenv.h"
# define USE_ERRNO

void
FileSysCleanup( FileSys *f )
{
	if( f->IsDeleteOnClose() )
	    f->Cleanup();
}

FileSys *
FileSys::Create( FileSysType t )
{
	FileSys *f;
	LineType lt;

	// Pull the LineType out of the FileSysType.

	switch( t & FST_L_MASK )
	{
	case FST_L_LOCAL: 	lt = LineTypeLocal; break;
	case FST_L_LF:		lt = LineTypeRaw; break;
	case FST_L_CR:		lt = LineTypeCr; break;
	case FST_L_CRLF:	lt = LineTypeCrLf; break;
	case FST_L_LFCRLF:	lt = LineTypeLfcrlf; break;
	default: 		lt = LineTypeLocal; 
	}

	// Apple's an odd mod: it's a mod, but totally supplants
	// the text/binary type.  So include it in the switch.
	// The other mods don't affect the base type.

	switch( t & ( FST_MASK | FST_M_APPLE | FST_M_APPEND ) )
	{
	case FST_TEXT:		
		f = new FileIOBuffer( lt ); 
		break;
	case FST_UNICODE:
		f = new FileIOUnicode( lt ); 
		break;

	case FST_BINARY:
		f = new FileIOBinary;
		break;

	case FST_RESOURCE:
		f = new FileIOResource;
		break;

	case FST_APPLETEXT:
	case FST_APPLEFILE:
		f = new FileIOApple;
		break;

	case FST_SYMLINK:
	        if( SymlinksSupported() )
	            f = new FileIOSymlink;
	        else
	            f = new FileIOBinary;
		break;

	case FST_ATEXT:
		f = new FileIOAppend;
		break;

	case FST_GZIP:
		f = new FileIOGzip;
		break;

	case FST_GUNZIP:
		f = new FileIOGunzip;
		break;
	
	case FST_UTF16:
		f = new FileIOUTF16( lt );
		break;

	case FST_EMPTY:
	        f = new FileIOEmpty;
	        break;
	
	default:
		return NULL;
	}

	// Replace the type.

	f->type = t;

	// Arrange for temps to blow on exit.

	signaler.OnIntr( (SignalFunc)FileSysCleanup, f );

	return f;
}

FileSys::FileSys()
{
	// start off with permission bits as the umask;

	mode = FOM_READ;
	perms = FPM_RO;
	modTime = 0;
	sizeHint = 0;
	checksum = 0;
	cacheHint = 0;
	charSet = GlobalCharSet::Get();
	content_charSet = GlobalCharSet::Get();

	type = FST_TEXT;

	isTemp = 0;
}

FileSys::~FileSys()
{
	// Once gone, we don't need to delete it
	// on interrupt anymore.

	signaler.DeleteOnIntr( this );
}

int
FileSys::BufferSize()
{
	return p4tunable.Get( P4TUNE_FILESYS_BUFSIZE );
}

void
FileSys::Cleanup()
{
	Error e;
	Close( &e );
	if( IsDeleteOnClose() )
	    Unlink();
}

void
FileSys::Set( const StrPtr &name )
{
	path.Set( name );
}

void
FileSys::SetDigest( MD5 *m )
{
	checksum = m;
}

int
FileSys::DoIndirectWrites()
{
# if defined( OS_MACOSX )
	return ( ( type & FST_MASK ) == FST_SYMLINK );
# else
	return 1;
# endif
}

void
FileSys::Translator( CharSetCvt * )
{
}

void
FileSys::LowerCasePath()
{
	if( CharSetApi::isUnicode( (CharSetApi::CharSet)GetCharSetPriv()) )
	{
	    StrBuf res;

	    if( CharSetCvt::Utf8Fold( &path, &res ) == 0 )
	    {
		path = res;
		return;
	    }
	    // if Utf8 fold failed... fall through...
	}
	StrOps::Lower( path );
}

/*
 * FileSys::GetFd()
 * FileSys::GetSize()
 * FileSys::Seek()
 *
 * Non-functional stubs.
 */

int
FileSys::GetFd()
{
	return -1;
}

int
FileSys::GetOwner()
{
	return 0;
}

bool
FileSys::HasOnlyPerm( FilePerm perms )
{
	return true;
}

offL_t
FileSys::GetSize()
{
	return 0;
}

void
FileSys::Seek( offL_t offset, Error * )
{
}

int
FileSys::Readlink( StrBuf &linkPath, Error *e )
{
	linkPath.Clear();
	return EINVAL;
}

int
FileSys::Writelink( const StrPtr &linkPath, Error *e )
{
	return EINVAL;
}

offL_t
FileSys::Tell()
{
	return 0;
}

/*
 * FileSys::Perms() - translate permission
 */

FilePerm
FileSys::Perm( const char *perms )
{
	return strcmp( perms, "rw" ) ? FPM_RO : FPM_RW;
}

static int ContainsTraversal( const char *p )
{
	while( p && *p )
	{
	    if( p[0] == '.' && p[1] == '.' )
	        return 1;
	    p++;
	}
	return 0;
}


bool
FileSys::IsRelative( const StrPtr &path )
{
	const char *p = path.Text();

	if( *p == '/' )
	    return false;
#ifdef OS_NT
	if( *p == '\\' )
	    return false;
	if( p[0] && p[1] == ':' )
	    return false;
#endif
	return true;
}

static int UnderRootCheck( const char *name, const char *root, int rootLen )
{
	int result;
	PathSys *p = PathSys::Create();
	p->Set( name );
	StrBuf r;
	if( *root == '.' )
	{
	    HostEnv h;
	    Enviro e;
	    StrBuf b;
	    h.GetCwd( b, &e );
	    r << b << StrRef( root + 1, rootLen - 1 );
	}
	else
	    r.Set( root, rootLen );

	result = p->IsUnderRoot( r );

	delete p;

	return result;
}

/**
 * FileExists
 *
 * @brief Verify that the file exists
 *
 * @param  filepath
 * @return boolean true if exists false otherwise
 * @throws
 */
bool
FileSys::FileExists( const char *filepath )
{
	if( !filepath )
	    return false;

	FileSys *f = FileSys::Create( FST_BINARY );
	f->Set( filepath );
	if( f->Stat() & FSF_EXISTS )
	{
	    delete f;
	    return true;
	}
	delete f;
	return false;
}


// Enforces P4CLIENTPATH restrictions
int
FileSys::IsUnderPath( const StrPtr &roots )
{
	if( roots.Length() == 0 )
	    return 1;

	HostEnv h;
	Enviro e;
	StrBuf b;
	const char *n = Name();
	if( ContainsTraversal( n ) )
	    return 0;
	if( IsRelative( StrRef( n ) ) )
	{
	    h.GetCwd( b, &e );
	    n = b.Text();
	}

	char listSep = ';';
	const char *p = roots.Text();
	const char *s = p;
	while( *p )
	{
	    if( *p == listSep )
	    {
	        if( p != s )
	        {
	            if( UnderRootCheck( n, s, p - s ) )
	                return 1;
	        }
	        s = p + 1;
	    }
	    p++;
	}
	if( p != s )
	    return UnderRootCheck( n, s, p - s );
	return 0;
}
