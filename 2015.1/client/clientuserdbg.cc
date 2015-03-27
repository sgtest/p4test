/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <stdhdrs.h>

# include <strbuf.h>
# include <strops.h>
# include <enviro.h>
# include <error.h>

# include <filesys.h>

# include "clientuser.h"
# include "clientuserdbg.h"

/*
 * ClientUserDebug -- version of output that always to stdout
 */

void
ClientUserDebug::OutputError( const char *errBuf )
{
	OutputTag( "error", errBuf, strlen( errBuf ) );
}

void
ClientUserDebug::OutputInfo( char level, const char *data )
{
	switch( level )
	{
	default: OutputTag( "info", data, strlen( data ) ); break;
	case '1': OutputTag( "info1", data, strlen( data ) ); break;
	case '2': OutputTag( "info2", data, strlen( data ) ); break;
	}
}

void
ClientUserDebug::OutputText( const char *data, int length )
{
	OutputTag( "text", data, length );
}

void
ClientUserDebug::OutputTag( const char *tag, const char *data, int length )
{
	char *p;

	while( p = (char *)memchr( data, '\n', length ) )
	{
	    printf( "%s: ", tag );
	    fwrite( data, 1, p + 1 - data, stdout );
	    length -= p + 1 - data;
	    data = p + 1;
	}

	if( length )
	{
	    printf( "%s: ", tag );
	    fwrite( data, 1, length, stdout );
	    printf( "\n" );
	}
}

/*
 * ClientUserDebugMsg -- message debugging ("-e" global opt)
 */

void
ClientUserDebugMsg::Message( Error *err )
{
	ClientUserDebug::Message( err );

	// print error subcodes for each ErrorId

	ErrorId* id;
	for ( int i = 0 ; id = err->GetId( i ) ; i++ )
	    printf( "code%d %d (sub %d sys %d gen %d args %d sev %d uniq %d)\n",
		i,
		id->code,
		id->SubCode(),
		id->Subsystem(),
		id->Generic(),
		id->ArgCount(),
		id->Severity(),
		id->UniqueCode() );

	// use base ClientUser OutputStat/Info() to print dict

	ClientUser ui;
	if ( err->GetDict() )
	    ui.OutputStat( err->GetDict() );
}

/*
 * ClientUserFmt -- user-specified formatting ("-F" global opt)
 */

void
ClientUserFmt::Message( Error *err )
{
	OutputStat( err->GetDict() );
}

void
ClientUserFmt::OutputStat( StrDict *dict )
{
	if( !dict )
	    return;

	StrBuf out;
	StrOps::Expand2( out, *fmt, *dict );
	if( out.Length() )
	    printf( "%s\n", out.Text() );
}
