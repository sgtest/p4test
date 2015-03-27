/*
 * Copyright 1995, 2003 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * fileiozip.cc - FileIOGzip/FileIOGunzip methods
 */

# include <stdhdrs.h>

# include <error.h>
# include <strbuf.h>
# include <gzip.h>

# include "filesys.h"
# include "fileio.h"

FileIOGzip::~FileIOGzip()
{
	Cleanup();
	delete gzip;
}

void
FileIOGzip::Open( FileOpenMode mode, Error *e )
{
	gzip = new Gzip;

	// Read expects is/ie; write os/oe.

	gzip->is = iobuf.Text();
	gzip->ie = iobuf.Text();
	gzip->os = iobuf.Text();
	gzip->oe = iobuf.Text() + iobuf.Length();

	FileIOBinary::Open( mode, e );

	if( e->Test() )
	{
	    delete gzip;
	    gzip = 0;
	}
}

void
FileIOGzip::Write( const char *buf, int len, Error *e )
{
	// Write( 0, 0 ) means flush (from Close()).
	// Don't be fooled by buf, 0.

	if( buf && !len ) 
	    return;

	gzip->is = buf;
	gzip->ie = buf + len;

	// Flush output if full and Compress input
	// util Compress() indicates input exhausted

	do if( gzip->OutputFull() )
	{
	    FileIOBinary::Write( iobuf.Text(), gzip->os - iobuf.Text(), e );
	    gzip->os = iobuf.Text();
	}
	while( !e->Test() && gzip->Compress( e ) && !gzip->InputEmpty() );
}

int
FileIOGzip::Read( char *buf, int len, Error *e )
{
	gzip->os = buf;
	gzip->oe = buf + len;

	do if( gzip->InputEmpty() )
	{
	    int l = FileIOBinary::Read( iobuf.Text(), iobuf.Length(), e );
	    if( !l )
	        e->Set( E_FAILED, "Unexpected end of file" );
	    gzip->is = iobuf.Text();
	    gzip->ie = iobuf.Text() + l;
	}
	while( !e->Test() && gzip->Uncompress( e ) && !gzip->OutputFull() );

	return gzip->os - buf;
}

void
FileIOGzip::Close( Error *e )
{
	// Flush & clear gzip 

	if( gzip && mode == FOM_WRITE && GetFd() != -1 )
	{
	    Write( 0, 0, e );
	    FileIOBinary::Write( iobuf.Text(), gzip->os - iobuf.Text(), e );
	}

	delete gzip;
	gzip = 0;

	// Rest of normal close

	FileIOBinary::Close( e );
}

FileIOGunzip::~FileIOGunzip()
{
	Cleanup();
	delete gzip;
}

void
FileIOGunzip::Open( FileOpenMode mode, Error *e )
{
	gzip = new Gzip;

	// Read expects is/ie; write os/oe.

	gzip->is = iobuf.Text();
	gzip->ie = iobuf.Text();
	gzip->os = iobuf.Text();
	gzip->oe = iobuf.Text() + iobuf.Length();

	FileIOBinary::Open( mode, e );

	if( e->Test() )
	{
	    delete gzip;
	    gzip = 0;
	}
}

void
FileIOGunzip::Write( const char *buf, int len, Error *e )
{
	gzip->is = buf;
	gzip->ie = buf + len;

	// Flush output if full and Compress input
	// util Compress() indicates input exhausted

	do if( gzip->OutputFull() )
	{
	    FileIOBinary::Write( iobuf.Text(), gzip->os - iobuf.Text(), e );
	    gzip->os = iobuf.Text();
	}
	while( !e->Test() && gzip->Uncompress( e ) && !gzip->InputEmpty() );
}

int
FileIOGunzip::Read( char *buf, int len, Error *e )
{
	gzip->os = buf;
	gzip->oe = buf + len;
	int done = 0;

	do if( gzip->InputEmpty() && !done )
	{
	    int l = FileIOBinary::Read( iobuf.Text(), iobuf.Length(), e );
	    gzip->is = l ? iobuf.Text() : 0;
	    gzip->ie = iobuf.Text() + l;
	    done |= !l;
	}
	while( !e->Test() && gzip->Compress( e ) && !gzip->OutputFull() );

	return gzip->os - buf;
}

void
FileIOGunzip::Close( Error *e )
{
	// Flush & clear gzip 

	if( gzip && mode == FOM_WRITE && gzip->os - iobuf.Text() )
	    FileIOBinary::Write( iobuf.Text(), gzip->os - iobuf.Text(), e );

	delete gzip;
	gzip = 0;

	// Rest of normal close

	FileIOBinary::Close( e );
}
