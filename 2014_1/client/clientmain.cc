/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * clientmain() - Perforce client program
 *
 * See below for usage.
 */

# include <stdhdrs.h>

# include <debug.h>
# include <strbuf.h>
# include <strdict.h>
# include <strtable.h>
# include <strops.h>
# include <error.h>
# include <errornum.h>
# include <options.h>
# include <handler.h>
# include <rpc.h>

# include <pathsys.h>
# include <filesys.h>

# include <ident.h>
# include <ticket.h>
# include <enviro.h>
# include <i18napi.h>
# include <charcvt.h>
# include <charset.h>
# include <diff.h>
# include <diffmerge.h>
# include <hostenv.h>
# include <errorlog.h>
# include <p4tags.h>
# include <md5.h>

# include <msgclient.h>
# include <msgsupp.h>

# include "client.h"
# include "clientmerge.h"
# include "clientuser.h"
# include "clientuserdbg.h"
# include "clientusermsh.h"

/* Ident strings */

Ident ident = { 
	IdentMagic "P4" "/" ID_OS "/" ID_REL "/" ID_PATCH,
	 ID_Y "/" ID_M "/" ID_D 
};

/* Usage info */

ErrorId usage = { ErrorOf( 0, 0, E_FAILED, 0, 0 ), "p4 -h for usage." };

static const char long_usage[] =
"Usage:\n"
"\n"
"    p4 [ options ] command [ arg ... ]\n"
"\n"
"    Options:\n"
"	-b batchsize	specify a batchsize to use with -x (default 128)\n"
"	-h -?		print this message\n"
"	-s		prepend message type to each line of server output\n"
"	-v level	debug modes\n"
"	-V		print client version\n"
"	-x file		read named files as xargs\n"
"	-G		format input/output as marshalled Python objects\n"
"	-z tag		format output as 'tagged' (like fstat)\n"
"	-I		show progress indicators\n"
"\n"
"	-c client	set client name (default $P4CLIENT)\n"
"	-C charset	set character set (default $P4CHARSET)\n"
"	-d dir		set current directory for relative paths\n"
"	-H host		set host name (default $P4HOST)\n"
"	-L language	set message language (default $P4LANGUAGE)\n"
"	-p port		set server port (default $P4PORT)\n"
"	-P password	set user's password (default $P4PASSWD)\n"
"	-q 		suppress all info messages\n"
"	-r retries	Retry command if network times out\n"
"	-Q charset	set command character set (default $P4COMMANDCHARSET)\n"
"	-u user		set user's username (default $P4USER)\n"
"\n"
"    The Perforce client 'p4' requires a valid Perforce server network\n"
"    address 'P4PORT' for most operations, including its help system.\n"
"    Without an explicit P4PORT, the Perforce client will use a default\n"
"    P4PORT of 'perforce:1666'.  That is to say, the host is named 'perforce'\n"
"    and the port number is '1666'.\n"
"\n"
"    The Perforce client accepts configuration via command-line options,\n"
"    P4CONFIG files, environmental variables and on Windows, the registry.\n"
"    Run 'p4 set' to list the client's current settings.\n"
"\n"
"    Run 'p4 help' to ask the Perforce server for information on commands.\n"
"\n"
"    For administrators, see the Perforce server's help output in 'p4d -h'.\n"
"\n"
"    For further information, visit the documentation at www.perforce.com.\n"
"\n";

/* Some forwards */

int clientMain( int argc, char **argv, int &uidebug, Error *e );
int clientMerger( int argc, char **argv, Error *e );
static int clientSet( int argc, char **argv, Options &, Error *e );
static int clientTickets( int argc, char **argv, Options &, Error *e );
int clientReplicate( int argc, char **argv, Options & );
int jtail( int, char **, Options &, Options &, const char * );
extern int commandChaining;

static char argv0[ 1024 ];

/* And now main... */

int
main( int argc, char **argv )
{
	/* Error reporting handle */

	Error e;

	AssertLog.SetTag( "Perforce client" );

	strncpy( argv0, argv[0], sizeof( argv0 ) - 1 );

	int uidebug = 0;
	int ret = clientMain( --argc, ++argv, uidebug, &e );

	AssertLog.Report( &e );

	if( uidebug )
	    printf( "exit: %d\n", ret );

# ifdef OS_VMS
	exit( ret );
# endif

	return ret;
}

void
setVarsAndArgs( Client &client, int argc, char **argv, Options &opts)
{
	StrPtr *s;

	// Set any special -z var=value's, for debug
	// Use -zfunc=something to override default func

	for( int i = 0; s = opts.GetValue( 'z', i ); i++ )
	    client.SetVarV( s->Text() );

	// Set the client program name
	client.SetVar( P4Tag::v_prog, "p4" );
	
	// Set the version used in server log and monitor output
	StrBuf v;
	v << ID_REL "/" << ID_OS << "/" << ID_PATCH;
	client.SetVar( P4Tag::v_version, v.Text() );

	client.SetArgv( argc - 1, argv + 1 );
}

static int
ErrorIncludesRPCSubsystem( Error *e )
{
	for( int eno = e->GetErrorCount(); eno > 0; eno-- )
	{
	    if( e->GetId( eno - 1 )->Subsystem() == ES_RPC )
	        return 1;
	}
	return 0;
}

int
clientMain( int argc, char **argv, int &uidebug, Error *e )
{
	int result;
	int restarted = 0;

	/* Arg processing */

	StrPtr *s;

	// Parse up options

	Options opts;
	int longOpts[] = { Options::Client, Options::Batchsize, Options::User,
	                   Options::Host, Options::Charset, Options::Host,
	                   Options::Help, Options::Port, Options::Password,
	                   Options::CmdCharset, Options::Retries,
	                   Options::Quiet, Options::Progress,
	                   Options::Variable, Options::Xargs, 0 };
	opts.ParseLong( argc, argv,
	        "?b:c:C:d:eE:F:GRhH:M:p:P:l:L:qQ:r#sIu:v:Vx:z:Z:", 
		longOpts, OPT_ANY, usage, e );

	if( e->Test() )
	    return 1;

	// Blast out message.

	if( opts[ 'h' ] || opts[ '?' ] )
	{
	    printf( "%s", long_usage );
	    return 0;
	}

	if( opts[ 'V' ] )
	{
	    StrBuf s;
	    ident.GetMessage( &s );
	    printf( "%s", s.Text() );
	    return 0;
	}

	// Debugging 

	for( int i = 0; s = opts.GetValue( 'v', i ); i++ )
	    p4debug.SetLevel( s->Text() );

	if( opts[ 's' ] || opts[ 'e' ] )
	    ++uidebug;

	// If we recognize the command (merge3, set), do it now */

	if( argc && !strcmp( argv[0], "merge3" ) )
	{
	    return clientMerger( argc - 1, argv + 1, e );
	}
	else if( argc && !strcmp( argv[0], "set" ) )
	{
	    return clientSet( argc - 1, argv + 1, opts, e );
	}
	else if( argc && !strcmp( argv[0], "tickets" ) )
	{
	    return clientTickets( argc - 1, argv + 1, opts, e );
	}
	else if( argc && !strcmp( argv[0], "replicate" ) )
	{
	    return clientReplicate( argc - 1, argv + 1, opts );
	}

	// Misc -E environment updates

	StrBufDict envList;
	StrRef var, val;
	for ( int i = 0 ; s = opts.GetValue( 'E', i ) ; i++ )
	    envList.SetVarV( s->Text() );

	// Apply these updates before and after each Config().
	// Before to make sure we read the right P4CONFIG, and after
	// to make sure that -E vars override P4CONFIG vars.

	// Create client rpc handle.

	Client client;
	for ( int i = 0 ; envList.GetVar( i, var, val ) ; i++ )
	    client.GetEnviro()->Update( var.Text(), val.Text() );

	// Locale setting

	// Early setting of cwd to find right P4CONFIG file...
	if( s = opts[ 'd' ] ) client.SetCwd( s );
	for ( int i = 0 ; envList.GetVar( i, var, val ) ; i++ )
	    client.GetEnviro()->Update( var.Text(), val.Text() );

	Enviro enviro;
	for ( int i = 0 ; envList.GetVar( i, var, val ) ; i++ )
	    enviro.Update( var.Text(), val.Text() );

	const char *lc;

	enviro.Config( client.GetCwd() );
	for ( int i = 0 ; envList.GetVar( i, var, val ) ; i++ )
	    enviro.Update( var.Text(), val.Text() );

	if( ( s = opts[ 'l' ] ) || ( s = opts[ 'C' ] ) )
	{
	    lc = s->Text();
	}
	else
	{
	    lc = enviro.Get( "P4CHARSET" );
	}

	if( lc )
	{
	    CharSetCvt::CharSet cs = CharSetCvt::Lookup( lc );

	    if( (int)cs == -1 )
	    {
		// bad charset specification
		printf( "Character set must be one of:\n"
		        "none, utf8, utf8-bom, iso8859-1, shiftjis, eucjp, iso8859-15,\n"
		        "iso8859-5, macosroman, winansi, koi8-r, cp949, cp1251,\n"
		        "utf16, utf16-nobom, utf16le, utf16le-bom, utf16be,\n"
		        "utf16be-bom, utf32, utf32-nobom, utf32le, utf32le-bom, utf32be,\n"
			"cp936, cp950, cp850, cp858, cp1253, \n"
			"iso8859-7 or utf32be-bom\n"
		        "Check P4CHARSET and your '-C' option.\n" );
		return 1;
	    }
	    else
	    {
		CharSetCvt::CharSet ws = cs;

		if( ( s = opts[ 'Q' ] ) ||
		    ( lc = enviro.Get( "P4COMMANDCHARSET" ) ) )
		{
		    if( s )
			lc = s->Text();
		    cs = CharSetCvt::Lookup( lc );
		    if( (int)cs == -1 )
		    {
			printf( "P4COMMANDCHARSET unknown\n" );
			return 1;
		    }
		}
		if( CharSetApi::Granularity( cs ) != 1 )
		{
		    printf( "p4 can not support a wide charset unless\n"
			    "P4COMMANDCHARSET is set to another charset.\n" );
		    return 1;
		}
		client.SetTrans( cs, ws, cs, cs );

		for ( int i = 0 ; envList.GetVar( i, var, val ) ; i++ )
		     client.GetEnviro()->Update( var.Text(), val.Text() );
	    }
	}

	// Get command line overrides of user, client, cwd, port
	
	if( s = opts[ 'c' ] ) client.SetClient( s );
	if( s = opts[ 'H' ] ) client.SetHost( s );
	if( s = opts[ 'L' ] ) client.SetLanguage( s );
	if( s = opts[ 'd' ] ) client.SetCwd( s );
	if( s = opts[ 'u' ] ) client.SetUser( s );
	if( s = opts[ 'p' ] ) client.SetPort( s );
	if( s = opts[ 'P' ] )
	{
	    client.SetPassword( s );
	    memset( s->Text(), '\0', s->Length() );
	}
	client.SetExecutable( argv0 );

	// Specify a batch size

	int batchSize = opts[ 'b' ] ? opts[ 'b' ]->Atoi() : 128;
	if( batchSize < 1 ) 
	    batchSize = 1;

	// Any protocol settings?

	for( int i = 0; s = opts.GetValue( 'Z', i ); i++ )
	    client.SetProtocolV( s->Text() );

	// -G or -R implies -Z tag -Z sendspec

	if( opts[ 'G' ] || opts[ 'R' ] )
	{
	    client.SetProtocol( P4Tag::v_tag );
	    client.SetProtocol( P4Tag::v_specstring );
	}

	// -M implies -Z sendspec
	if( opts[ 'M' ] )
	    client.SetProtocol( P4Tag::v_specstring );

	// Set default api value high,  client floats with server output
	// This high value also lets the server know that the client can 
	// handle streams (i.e. don't change this).
	// Ignore above,  unfortunately there are other api's using the
	// magic 99999,  although there is server support to prevent this
	// we shall enable streams here for future gratification.

	client.SetProtocol( P4Tag::v_api, "99999" );
	client.SetProtocol( P4Tag::v_enableStreams );

    restart:

	// Connect.

	client.Init( e );

	if( e->Test() )
	    return 1;

	// Normal client -- will connect to server.
	// -s means use debug display mode.

	ClientUser *ui;

	if( opts[ 's' ] )
	    ui = new ClientUserDebug;
	else if( opts[ 'e' ] )
	    ui = new ClientUserDebugMsg;
	else if( opts[ 'F' ] )
	    ui = new ClientUserFmt( opts[ 'F' ] );
	else if( opts[ 'G' ] )
	    ui = new ClientUserPython;
	else if( opts[ 'R' ] )
	    ui = new ClientUserRuby;
	else if( ( s = opts[ 'M' ] ) && ( *s == "g" ) )
	    ui = new ClientUserPython;
	else if( ( s = opts[ 'M' ] ) && ( *s == "r" ) )
	    ui = new ClientUserRuby;
	else if( ( s = opts[ 'M' ] ) && ( *s == "p" ) )
	    ui = new ClientUserPhp;
	else if( opts[ 'I' ] )
	    ui = new ClientUserProgress;
	else
	    ui = new ClientUser;

	if( opts[ 'q' ] )
	    ui->SetQuiet();

	// Invoke operation in server:
	//	if not -x, bundle up argv and send it on down.
	//	if -x, bundle up argv and a few lines from the file.

	StrPtr *xargsName;

	if( !( xargsName = opts[ 'x' ] ) )
	{
	    // Normal invocation.

	    setVarsAndArgs( client, argc, argv, opts );
	    client.Run( argv[0], ui );
	}
	else if( argc == 1 && !strcmp( argv[0], "run" ) )
	{
	    // p4 -x cmdfile run: serially run multiple commands, same client
	    commandChaining = 1;
	    StrBuf s;
	    FileSys *xf = FileSys::Create( FST_TEXT );

	    xf->Set( *xargsName );
	    xf->Open( FOM_READ, e );

	    if( e->Test() )
	    {
		delete xf;
		return 1;
	    }

	    while( !e->Test() && !client.Dropped() && !client.GetFatals() )
	    {
		int eof = xf->ReadLine( &s, e );
		if( eof < 0 )
		{
	            e->Set( MsgClient::LineTooLong ) << xf->BufferSize();
		    break;
		}
		else if ( eof > 0 )
		{
	            StrBuf	wordBuffer;
	            char	*words[2048];
		    int 	nwords;
		    
		    nwords = StrOps::Words( wordBuffer, s.Text(), words,
				    ( sizeof( words ) / sizeof( words[0] ) ) );
		    
		    if( !nwords )
	                continue; //blank line in file

	            setVarsAndArgs( client, argc, argv, opts );

	            for( int i = 1; i < nwords; i++ )
		        client.translated->SetVar( "", words[ i ] );

		    client.Run( words[0], ui );
		    fflush( stdout );
		    fflush( stderr );
		}
		else
		{
		    break;
		}
	    }

	    xf->Close( e );
	    delete xf;
	}
	else
	{
	    // -x invocation

	    StrBuf s;
	    FileSys *xf = FileSys::Create( FST_TEXT );
	    int eof = 0;
	    int count = 0;

	    // Open -x file

	    xf->Set( *xargsName );
	    xf->Open( FOM_READ, e );

	    if( e->Test() )
	    {
		delete xf;
		return 1;
	    }

	    // In blocks of batchSize args.

	    while( !e->Test() && !client.Dropped() && !eof )
	    {
		// If more...

		if( !( eof = !xf->ReadLine( &s, e ) ) )
		{
		    // Set user's (constant) args at beginning of block

		    if( !count )
			setVarsAndArgs( client, argc, argv, opts );

		    // Set this arg.

		    client.translated->SetVar( "", &s );
		}

		// Dispatch

		if( eof ? count : ++count == batchSize )
		{
		    client.Run( argv[0], ui );
		    count = 0;
		}
	    }

	    // Seal off xargs file.

	    xf->Close( e );
	    delete xf;
	}

	// Since we only did sync Client::Run() calls, the ui should
	// no longer be necessary.

	delete ui;

	// Close and clean.

	result = client.Final( e );

	if( result && ErrorIncludesRPCSubsystem( e ) &&
	    opts[ 'r' ] && ( restarted++ < opts[ 'r' ]->Atoi() ) )
	{
	    e->Clear();
	    goto restart;
	}

	return result;
}

int
clientMerger( int argc, char **argv, Error *e )
{
	// Parse up options

	Options opts;
	int longOpts[] = { Options::DiffFlags, Options::BinaryAsText,
	                   Options::Verbose, 0 };
	opts.ParseLong( argc, argv, "d:rtvx:", longOpts, OPT_THREE, usage, e );

	if( e->Test() )
	    return 1;

	int rcsstyle = opts[ 'r' ] != 0;
	int showall = opts[ 'v' ] != 0;
        StrPtr *checkMerge = opts[ 'x' ];

	/* Run as 3-way diff for merging */

	FileSys *f1 = FileSys::Create( FST_BINARY );
	FileSys *f2 = FileSys::Create( FST_BINARY );
	FileSys *f3 = FileSys::Create( FST_BINARY );

	f1->Set( argv[0] );
	f2->Set( argv[1] );
	f3->Set( argv[2] );

	StrBuf baseDigest;
	StrBuf l1Digest;
	StrBuf l2Digest;

	MD5 baseMD5;
	MD5 resultMD5;
	MD5 l1MD5;
	MD5 l2MD5;
	
	if( checkMerge )
	{
	    f1->Digest( &baseDigest, e );
	    f2->Digest( &l1Digest, e );
	    f3->Digest( &l2Digest, e );

	    e->Clear();
	}

	DiffFlags flags( opts[ 'd' ] );
	LineType lineType = opts[ 't' ] ? LineTypeRaw : LineTypeLocal;

	DiffMerge *m = new DiffMerge( f1, f2, f3, flags, lineType, e );
	AssertLog.Abort( e );

	StrBuf sBuf;
	char buf[4096];
	int oldbits = 0, bits;
	int len;

	for( ; bits = m->Read( buf, sizeof( buf ), &len ); oldbits = bits )
	{
	    /* Merge check */

	    if( checkMerge )
	    {
	        sBuf.Clear();
	        sBuf << buf;
	        sBuf.SetLength( len );

		if( bits & SEL_BASE )
	        {
	            if( *checkMerge == "base" ) 
		        fwrite( buf, 1, len, stdout );
	            baseMD5.Update( sBuf );
	        }
		if( bits & SEL_LEG1)
	        {
	            if( *checkMerge == "leg1" ) 
		        fwrite( buf, 1, len, stdout );
	            l1MD5.Update( sBuf );
	        }
		if( bits & SEL_LEG2 )
		{
	            if( *checkMerge == "leg2" ) 
		        fwrite( buf, 1, len, stdout );
	            l2MD5.Update( sBuf );
		}
	        if( bits & SEL_RSLT || bits == ( SEL_BASE | SEL_CONF ) )
	        {
	            if( *checkMerge == "result" ) 
		        fwrite( buf, 1, len, stdout );
	           resultMD5.Update( sBuf );
	        }

	        continue; 
	    }

	    /* Display tag */

	    if( !oldbits || oldbits == bits )
	    {
		/* OK */;
	    }
	    else if( !rcsstyle )
	    {
		printf( ">>>> %s\n", m->BitNames( bits ) );
	    }
	    else if( showall || 
		     bits & SEL_CONF || 
		     bits == SEL_ALL && oldbits & SEL_CONF )
	    {
		switch( bits )
		{
		case SEL_ALL:
		    printf( "<<<<\n" );
		    break;

		case SEL_BASE:
		case SEL_BASE|SEL_CONF:
		case SEL_BASE|SEL_LEG1:
		case SEL_BASE|SEL_LEG2:
		    printf( ">>>> %s\n", m->BitNames( bits ) );
		    break;

		case SEL_LEG1|SEL_RSLT|SEL_CONF:
		    /* fall through */

		case SEL_LEG2|SEL_RSLT|SEL_CONF:
		case SEL_LEG1|SEL_RSLT:
		case SEL_LEG2|SEL_RSLT:
		case SEL_LEG1|SEL_LEG2|SEL_RSLT:
		    printf( "==== %s\n", m->BitNames( bits ) );
		    break;
		}
	    }

	    /* Display data */

	    if( !rcsstyle || showall || 
	        bits & SEL_RSLT || 
		bits == ( SEL_BASE | SEL_CONF ) )
	    {
		fwrite( buf, 1, len, stdout );
	    }
	}

	if( checkMerge && *checkMerge == "check" )
	{
	    StrBuf baseFinal;
	    StrBuf l1Final;
	    StrBuf l2Final;
	    StrBuf resultFinal;

	    resultMD5.Final( resultFinal );
	    baseMD5.Final( baseFinal );
	    l1MD5.Final( l1Final );
	    l2MD5.Final( l2Final );

	    if( baseDigest.Compare( baseFinal ) )
	        printf("BAD (base)\n");
	    if( l1Digest.Compare( l1Final ) )
	        printf("BAD (leg1)\n");
	    if( l2Digest.Compare( l2Final ) )
	        printf("BAD (leg2)\n");

	    if( ( !baseDigest.Compare( l1Digest ) &&
	           l2Digest.Compare( resultFinal ) )
	      ||( !baseDigest.Compare( l2Digest ) &&
	           l1Digest.Compare( resultFinal ) ) )
	        printf("BAD (safe-merge)\n");
	}

	delete m;
	delete f1;
	delete f2;
	delete f3;

	return 0;
}

int
clientTickets( int argc, char **argv, Options &global_opts, Error *e )
{
	const char *c;
	HostEnv h;
	StrBuf cwd;
	StrBuf ticketfile;
	StrBuf output;

	// Parse up options

	Options opts;
	int longOpts[] = { Options::Charset, Options::CmdCharset, 0 };
	opts.ParseLong( argc, argv, "C:l:Q:", longOpts, OPT_ANY, usage, e );

	if( e->Test() )
	    return 1;

	if( global_opts[ 'd' ] )
	    cwd.Set( global_opts[ 'd' ] );
	else
	    h.GetCwd( cwd );
	Enviro enviro;
	enviro.Config( cwd );
	const char *lc;
	StrPtr *s;
	CharSetCvt::CharSet cs = CharSetCvt::NOCONV;

	if( ( s = opts[ 'l' ] ) || ( s = opts[ 'C' ] ) )
	{
	    lc = s->Text();
	}
	else
	{
	    lc = enviro.Get( "P4CHARSET" );
	}

	if( lc )
	{
	    cs = CharSetCvt::Lookup( lc );

	    if( (int)cs == -1 )
	    {
		// bad charset specification
		printf( "Character set must be one of:\n"
		        "none, utf8, utf8-bom, iso8859-1, shiftjis, eucjp, iso8859-15,\n"
		        "iso8859-5, macosroman, winansi, koi8-r, cp949, cp1251,\n"
		        "utf16, utf16-nobom, utf16le, utf16le-bom, utf16be,\n"
		        "utf16be-bom, utf32, utf32-nobom, utf32le, utf32le-bom, utf32be,\n"
			"cp936, cp950, cp850, cp858, or utf32be-bom\n"
		        "Check P4CHARSET and your '-C' option.\n" );
		return 1;
	    }
	    else
	    {
		if( ( s = opts[ 'Q' ] ) ||
		    ( lc = enviro.Get( "P4COMMANDCHARSET" ) ) )
		{
		    if( s )
			lc = s->Text();
		    cs = CharSetCvt::Lookup( lc );
		    if( (int)cs == -1 )
		    {
			printf( "P4COMMANDCHARSET unknown\n" );
			return 1;
		    }
		}
		if( CharSetApi::Granularity( cs ) != 1 )
		{
		    printf( "p4 can not support a wide charset unless\n"
			    "P4COMMANDCHARSET is set to another charset.\n" );
		    return 1;
		}
		if( cs )
		{
		    GlobalCharSet::Set( cs );
		    enviro.SetCharSet( cs );
	            if( !global_opts[ 'd' ] )
		        h.GetCwd( cwd, &enviro );
		    enviro.Config( cwd );
		}
	    }
	}

	if( c = enviro.Get( "P4TICKETS" ) )
	    ticketfile.Set( c );
	else
	    h.GetTicketFile( ticketfile );

	Ticket t( &ticketfile );
	t.List( output );

	if( cs )
	{
	    // i18n mode - need to translate from utf8 to P4CHARSET

	    CharSetCvt *converter = CharSetCvt::FindCvt( CharSetCvt::UTF_8, cs );
	    if( converter )
	    {
		c = converter->FastCvtQues( output.Text(), output.Length() );
		printf( "%s", c ? c : output.Text() );
		delete converter;
	    }
	}
	else
	    printf( "%s", output.Text() );
	
	return 0;
}

int
clientSet( int argc, char **argv, Options &global_opts, Error *e )
{
	/* p4 set - manipulate env vars */

	StrBuf var;

	// Parse up options

	Options opts;
	int longOpts[] = { Options::System, Options::Service,
	                   Options::Charset, Options::CmdCharset, 0 };
	opts.ParseLong( argc, argv, "sS:C:l:Q:", longOpts, OPT_ANY, usage, e );

	if( e->Test() )
	    return 1;

	// Blast out message.

	HostEnv h;
	StrBuf cwd;
	if( global_opts[ 'd' ] )
	    cwd.Set( global_opts[ 'd' ] );
	else
	    h.GetCwd( cwd );
	Enviro enviro;
	const char *lc;
	StrPtr *s;
	enviro.LoadConfig( cwd, argc == 0 );

	if( ( s = opts[ 'l' ] ) || ( s = opts[ 'C' ] ) )
	{
	    lc = s->Text();
	}
	else
	{
	    lc = enviro.Get( "P4CHARSET" );
	}

	if( lc )
	{
	    CharSetCvt::CharSet cs = CharSetCvt::Lookup( lc );

	    if( (int)cs == -1 )
	    {
		// bad charset specification
		printf( "Character set must be one of:\n"
		        "none, utf8, utf8-bom, iso8859-1, shiftjis, eucjp, iso8859-15,\n"
		        "iso8859-5, macosroman, winansi, koi8-r, cp949, cp1251,\n"
		        "utf16, utf16-nobom, utf16le, utf16le-bom, utf16be,\n"
		        "utf16be-bom, utf32, utf32-nobom, utf32le, utf32le-bom, utf32be,\n"
			"cp936, cp950, cp850, cp858, or utf32be-bom\n"
		        "Check P4CHARSET and your '-C' option.\n"
			"Continuing as if not set.\n" );
	    }
	    else
	    {
		if( ( s = opts[ 'Q' ] ) ||
		    ( lc = enviro.Get( "P4COMMANDCHARSET" ) ) )
		{
		    if( s )
			lc = s->Text();
		    cs = CharSetCvt::Lookup( lc );
		    if( (int)cs == -1 )
		    {
			printf( "P4COMMANDCHARSET unknown\n" );
			return 1;
		    }
		}
		if( CharSetApi::Granularity( cs ) != 1 )
		{
		    printf( "p4 can not support a wide charset unless\n"
			    "P4COMMANDCHARSET is set to another charset.\n" );
		    return 1;
		}
		if( cs )
		{
		    GlobalCharSet::Set( cs );
		    enviro.SetCharSet( cs );
	            if( !global_opts[ 'd' ] )
		        h.GetCwd( cwd, &enviro );
		    enviro.Config( cwd );
		}
	    }
	}

	if( opts[ 's' ] )
	    enviro.BeServer();

	if( opts[ 'S' ] )
	{
	    int serviceExists = enviro.BeServer( opts[ 'S'], !argc );
	    if( !serviceExists )
	    {
	        printf( "Perforce service '%s' does not exist.\n",
	                opts[ 'S' ]->Text() );
	        return 1;
	    }
	}
	    
	if( !argc )
	{
	    enviro.List();
	    int o = 0;
	    while( p4tunable.GetName( o ) )
	    {
	        if( p4tunable.IsSet( o ) )
	            printf( "%s: %d\n",
	                    p4tunable.GetName( o ), p4tunable.Get( o ) );
	        o++;
	    }
	}
	else for( ; argc; argc--, argv++ )
	{
	    char *equals;

	    if( equals = strchr( *argv, '=' ) )
	    {
		var.Set( *argv, equals - *argv );
		++equals;
		if( var == "P4CHARSET" && *equals )
		{
		    CharSetApi::CharSet cs = CharSetCvt::Lookup( equals );
		    if( (int)cs == -1 )
		    {
			printf("Will not set P4CHARSET to an invalid value.\n");
			continue;
		    }
		    if( CharSetApi::Granularity( cs ) != 1 )
		    {
			lc = enviro.Get( "P4COMMANDCHARSET" );

			if( !lc || 
			    -1 == (int)( cs = CharSetCvt::Lookup( lc ) ) ||
			    CharSetApi::Granularity( cs ) != 1 )
			    printf( "p4 can not support a wide charset unless\n"
			        "P4COMMANDCHARSET is set to another charset.\n" );
			return 1;
		    }
		}
		enviro.Set( var.Text(), equals, e );
		AssertLog.Report( e );
		e->Clear();
	    }
	    else
	    {
		enviro.Print( *argv );
	    }
	}

	return 0;
}

static ErrorId replicateUsage = { ErrorOf( 0, 0, 0, 0, 0),
	"p4 [ -p port ][ -u user ][ -P password ][ -C charset ] replicate\n"
	"\t   [ -j token ][ -s statefile ][ -i interval ][ -k -x -R ]\n"
	"\t   [ -J prefix ][ -T tables excluded ][ -o output ][ command ]\n"
};

int
clientReplicate( int ac, char **av, Options &preops )
{
	Error e;

	AssertLog.SetTag( "replicate" );

	Options opts;

	int longOpts[] = { Options::JournalPrefix, Options::Repeat,
	                   Options::OutputFile, 0 };
	opts.ParseLong( ac, av, "xkj:i:J:s:o:T:R", longOpts,
	                OPT_ANY, replicateUsage, &e );

	if( e.Test() )
	{
	    AssertLog.Report( &e );
	    return 1;
	}

	return jtail( ac, av, preops, opts, "replicate" );
}
