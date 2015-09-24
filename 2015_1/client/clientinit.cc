/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * clientinit() - Perforce client DVCS init
 *
 */

# define NEED_CHDIR
# define NEED_TYPES
# define NEED_STAT
# define NEED_FLOCK

# include <stdhdrs.h>

# include <debug.h>
# include <strbuf.h>
# include <strdict.h>
# include <strtable.h>
# include <error.h>
# include <options.h>
# include <rpc.h>
# include <datetime.h>
# include <strops.h>

# include <pathsys.h>
# include <filesys.h>
# include <lockfile.h>
# include <signaler.h>

# include <enviro.h>
# include <handler.h>
# include <runcmd.h>

# include <msgclient.h>
# include <p4tags.h>

# include "client.h"
# include "clientuser.h"

# ifdef OS_NT
# define INIT_CONFIG "p4config.txt"
# define INIT_IGNORE "p4ignore.txt"
# else
# define INIT_CONFIG ".p4config"
# define INIT_IGNORE ".p4ignore"
# endif

# define INIT_ROOT ".p4root"
# define INIT_SERVERID ".p4root/server.id"

static ErrorId initClone = { ErrorOf( 0, 0, E_INFO, 0, 0),
"\n"
"	clone -- Clone a new private local Perforce repository from a remote.\n"
"\n"
"	p4 [-u user][-d dir][-c client] clone [-m depth -v] -p port -r remote\n"
"	p4 [-u user][-d dir][-c client] clone [-m depth -v] -p port -f filespec\n"
"\n"
"	This command initializes a new Perforce repository in the current\n"
"	directory (or the directory specified by the -d flag).\n"
"\n"
"	In order to run 'p4 clone', you must have up-to-date and matching\n"
"	versions of the 'p4' and 'p4d' executables in your operating system\n"
"	path. You can download these executables from http://www.perforce.com\n"
"\n"
"	Perforce database files will be stored in the directory named\n"
"	\".p4root\". Perforce configuration settings will be stored in\n"
"	P4CONFIG and P4IGNORE files in the top level of your directory.\n"
"	It is not necessary to view or update these files, but you should\n"
"	be aware that they exist.\n"
"\n"
"	The -m flag performs a shallow fetch; only the last number of\n"
"	specified revisions of each file are fetched.\n"
"\n"
"	The -p flag specifies the address of the target server you wish\n"
"	to clone from.\n"
"\n"
"	The -r flag specifies a remote spec installed on the remote server\n"
"	to use as a template for the clone and stream setup. See 'p4 help\n"
"	remote' for more information about how the clone command interprets\n"
"	the remote spec during the setup steps.\n"
"\n"
"	The -f flag specifies a filepath in the remote server to use as the\n"
"	path to clone; this path will also be used to determine the stream\n"
"	setup in the local server.\n"
"\n"
"	The -v flag specifies verbose mode.\n"
"\n"
"	When the clone completes, a default remote spec will be created,\n"
"	called origin. To update your local repository with the latest\n"
"	changes from the target server, run 'p4 fetch'.\n"
"\n"
"	For more information about using Perforce, run 'p4 help' after you\n"
"	have run 'p4 clone', or visit http://www.perforce.com.\n"
};

static ErrorId initHelp = { ErrorOf( 0, 0, E_INFO, 0, 0),
"\n"
"	init -- Initialize a new private local Perforce repository.\n"
"\n"
"	p4 [-u user][-d dir][-c client] init [-hq][-c stream][-p port]\n"
"	p4 [-u user][-d dir][-c client] init [-hq][-c stream][-Cx -xi -n]\n"
"\n"
"	This command initializes a new Perforce repository in the current\n"
"	directory (or the directory specified by the -d flag).\n"
"\n"
"	In order to run 'p4 init', you must have up-to-date and matching\n"
"	versions of the 'p4' and 'p4d' executables in your operating system\n"
"	path. You can download these executables from http://www.perforce.com\n"
"\n"
"	Perforce database files will be stored in the directory named\n"
"	\".p4root\". Perforce configuration settings will be stored in\n"
"	P4CONFIG and P4IGNORE files in the top level of your directory.\n"
"	It is not necessary to view or update these files, but you should\n"
"	be aware that they exist.\n"
"\n"
"	After initializing your new repository, run 'p4 reconcile' to mark\n"
"	all of your source files to be added to Perforce, then 'p4 submit'\n"
"	to submit them.\n"
"\n"
"	The -c flag configures the installation to create the specified stream\n"
"	as the mainline stream rather than the default '//stream/main'.\n"
"\n"
"	The -p flag specifies the address of a target server you wish to\n"
"	discover the case sensitivity and unicode settings from. This will\n"
"	make your local repository compatible with that server.\n"
"\n"
"	The -q flag suppresses informational messages (including if\n"
"	p4 init has already been run.)\n"
"\n"
"	The -Cx flag sets the case sensitivity of the new Perforce\n"
"	installation. You may specify either -C0 or -C1. The -C0 flag\n"
"	specifies case-sensitive operation; the -C1 flag specifies\n"
"	case-insensitive operation. (see discovery note below).\n"
"\n"
"	The -n flag configures the installation without unicode support.\n"
"	The -xi flag configures the installation with unicode support.\n"
"	Without -n or -xi, the installation will decide on unicode support\n"
"	based on the P4CHARSET enviroment being set.\n"
"\n"
"	Note: If neither -Cx, -xi or -n flags are set, init will try and\n"
"	discover the correct settings from a server already set in your\n"
"	environment.  If init cannot find a server then it will fail\n"
"	initialization.\n"
"\n"
"	For more information about using Perforce, run 'p4 help' after you\n"
"	have run 'p4 init', or visit http://www.perforce.com.\n"
};

static ErrorId initUsage = { ErrorOf( 0, 0, E_FAILED, 0, 0),
	"Usage: p4 [-u user][-d dir][-c client] init [-hq][-c stream][-p port | -Cx -xi -n]\n"
	"\tUse p4 init -h for detailed help."
};

static ErrorId cloneUsage = { ErrorOf( 0, 0, E_FAILED, 0, 0),
	"Usage: p4 [-u user][-d dir][-c client] clone -p <port> [-m depth -v][-r <remote> | -f filespec]\n"
	"\tUse p4 clone -h for detailed help."
};

static ErrorId initUnicodeMixup = { ErrorOf( 0, 0, E_FAILED, 0, 0),
	"p4 init does not allow '-n' and '-xi' to be used together"
};

static ErrorId initCaseFlagMixup = { ErrorOf( 0, 0, E_FAILED, 0, 0),
	"Specify either -C0 or -C1."
};

static ErrorId initServerFail = { ErrorOf( 0, 0, E_FAILED, 0, 0),
	"\np4d server failed to initialize.  A 2015.1 or later p4d server\n"
	"must be in your path and runable."
};

class CloneUser : public ClientUserProgress {

	public:
	        CloneUser(){
	            commandError = 0;
	            needLogin = 0;
	            gotRemote = 0;
	            quiet = 1;
		}

	// implement user callbacks

	void		OutputStat( StrDict *varList ); 
	void		OutputError( const char *errBuf );
	void		OutputText( const char *data, int length );
	void		OutputInfo( char level, const char *data );
	void		InputData( StrBuf *strbuf, Error *e );

	// what command is running ?

	void		SetCommand( const char *p ) { command.Set( p ); }
	StrPtr		&GetCommand() { return command; }

	// fun stuff

	void		GetStreamName( StrBuf *filePath, StrPtr &val );
	int		StreamExists( StrPtr &filePath );
	int		TooWide( const char *s );
	const char	*Trim( StrPtr &filePath, StrPtr &val );
	int		Unicode() { return unicode; }
	int		MaxChange() { return maxCommitChange; }
	int		Security() { return security; }
	int		GotError() { return commandError; }
	void		SetError() { commandError = 1; }
	void		ClearError() { commandError = 0; }
	int		GotRemote(){ return gotRemote; }
	int		NeedLogin(){ return needLogin; }
	StrPtr		CaseFlag() { return caseFlag; }
	StrPtr		Server()   { return serverAddress; }
	StrPtr		Description() { return description; }
	void		SetDescription( const char *d ) 
			              { description.Set( d ); }
	StrPtr		GetUser() { return user; }
	void		SetUser   ( const char *u )
			          { user.Set( u ); }
	StrPtr		UserName()    { return userName; }
	void		DoDebug()  { quiet = 0; }
	StrBuf		*GetData() { return &inputData; }
	StrBufDict	*GetStreams() { return &mainlines; }
	StrBufDict	*Dict() { return &remoteMap; }

	private:

	// p4 info
	int		unicode;
	int		security;
	StrBuf		caseFlag;

	// p4 remote
	StrBufDict	remoteMap;
	StrBuf		depotName;
	StrBuf		description;
	StrBuf		serverAddress;
	StrBuf		inputData;
	StrBuf		userName;
	StrBuf		user;
	int		gotRemote;
	int		needLogin;

	// p4 counter
	int		maxCommitChange;
	
	// streams
	StrBufDict	mainlines;

	// command tracking
	StrBuf		command;
	int		commandError;
	int		quiet;

} ;

void cloneSetup( StrPtr *, StrPtr *, StrPtr *, StrPtr *, CloneUser *, Enviro *, Error * );
void cloneFetch( StrPtr *, StrPtr *, StrPtr *, StrPtr *, StrPtr *, CloneUser *, StrPtr *, Enviro *, Error * );
void initService( StrPtr *, CloneUser *, StrPtr *, Enviro *, Error * );
void initDiscover( StrPtr *, StrPtr *, CloneUser *, Enviro *, Error * );
int  initValidate( StrPtr * );
static void WriteIgnore( StrPtr *, StrPtr *, int, Error * );
static void LockCheck( Error * );

int
clientInitHelp( int doClone, Error *e )
{
	ClientUser cuser;
	e->Set( doClone ? initClone : initHelp );
	cuser.Message( e );
	e->Clear();
	return 0;
}

int
clientInit( int ac, char **av, Options &preops, int doClone, Error *e )
{
	Options opts;
	ClientUser cuser;
	CloneUser ruser;
	int doUnicode = 0;
	int doDiscover = 0;
	StrBuf remote;
# ifndef OS_NT
	int oldumask;
# endif

	int longOpts[] = { Options::Help, Options::Quiet, 0 };

	if( doClone )
	    opts.ParseLong( ac, av, "hf:m#p:r:v", longOpts, OPT_NONE, cloneUsage, e );
	else
	    opts.ParseLong( ac, av, "c:hnp:qC#x:", longOpts, OPT_NONE, initUsage, e );

	if( e->Test() )
	    return 1;


	StrPtr *sp;
	StrRef fileref( "file" );
	Client *client = NULL;
	Enviro *enviro = NULL;
	RunCommand rc;
	RunArgs ra;
	StrBuf clientname;
	StrBuf user;
	FileSys *fsys = NULL;
	FileSys* rootDir = NULL;
	PathSys *curdir = NULL;
	StrBuf config( INIT_CONFIG );
	StrBuf ignore( INIT_IGNORE );
	StrBuf serverID( INIT_SERVERID );
	const char *s;
	int ecode = 0;

	// turn-off quiet mode
	if( preops[ 'v' ] )
	    ruser.DoDebug();

	if( !doClone && opts[ 'h' ] )
	    return clientInitHelp( 0, e );

	if( opts[ 'C' ] )
	{
	    int caseVal = opts[ 'C' ]->Atoi();
	    if( caseVal != 0 && caseVal != 1 )
	    {
	        e->Set( initCaseFlagMixup );
	        goto finish;
	    }
	}
	enviro = new Enviro;

	if( s = enviro->Get( "P4CONFIG" ) )
	    config.Set( s );
	else
	{
	    enviro->Set( "P4CONFIG", config.Text(), e );
	    delete enviro;
	    enviro = new Enviro;
	}

	fsys = FileSys::Create( FST_TEXT );
	rootDir = FileSys::Create( FST_TEXT );

	// Load config/enviro

	// check if already initialized
	// P4INITROOT and .p4root dir

	curdir = PathSys::Create();

	client = new Client( enviro );

	curdir->Set( client->GetCwd() );
	if( ( sp = preops[ 'd' ] ) )
	{
	    curdir->SetLocal( *curdir, *sp );
	    curdir->SetLocal( *curdir, fileref );
	    fsys->MkDir( *curdir, e );
	    if( e->Test() )
	    {
		ecode = 1;
		goto finish;
	    }
	    curdir->ToParent();
	    if( chdir( curdir->Text() ) < 0 )
	    {
		ecode = 1;
		goto finish;
	    }
	    delete client;
	    delete enviro;
	    enviro = new Enviro;
	    enviro->Update( "PWD", curdir->Text() );
	    client = new Client( enviro );
	}

	s = enviro->Get( "P4INITROOT" );
	fsys->Set( INIT_ROOT );

	if( s || ( fsys->Stat() & FSF_EXISTS ) )
	{
	    if( !opts[ 'q' ] )
		printf( "Nothing to do - existing dvcs tree at %s\n", 
	                s ? s : INIT_ROOT );
	    ecode = 1;
	    goto finish;
	}

	// check for locking issues

	LockCheck( e );

	if( e->Test() )
	{
	    // add a user polite error about locking
	    e->Set( MsgClient::LockCheckFail );
	    goto finish;
	}

	if( doClone )
	{
	    if( opts[ 'h' ] )
	        return clientInitHelp( 1, e );

	    if( (  opts[ 'r' ] &&  opts[ 'f' ] ) ||
	        ( !opts[ 'f' ] && !opts[ 'r' ] ) ||
	        ( !opts[ 'p' ] ) )
	    {
	        e->Set( cloneUsage );
	        goto finish;
	    }

	    // Pull down all the clone info & stash it

	    cloneSetup( opts[ 'p' ], opts[ 'r' ], opts[ 'f' ], preops[ 'u' ],
			 &ruser, enviro, e );
	    doUnicode = ruser.Unicode();

	    if( e->Test() )
	        goto finish;

	    if( ruser.GotError() )
	        goto finish;

	    if( opts[ 'f' ] )
	        remote << "origin";
	    else
	        remote = *opts[ 'r' ];
	}
	else
	{
	    if( initValidate( opts[ 'c' ] ) )
	        goto finish;

	    if( opts[ 'p' ] && 
	      ( opts[ 'x' ] || opts [ 'n' ] || opts[ 'C' ] ) )
	    {
	        e->Set( initUsage );
	        goto finish;
	    }

	    s = enviro->Get( "P4CHARSET" );
	    doUnicode = ( s && StrPtr::CCompare( s, "none" ) );

	    sp = opts[ 'x' ];
	    if( sp && sp->Text()[0] == 'i' )
	    {
		doUnicode = 1;
		if( opts[ 'n' ] )
		{
		    e->Set( initUnicodeMixup );
	            goto finish;
		}
	    }
	    if( opts[ 'n' ] )
		doUnicode = 0;

	    if( opts[ 'p' ] || 
	     !( opts[ 'x' ] || opts [ 'n' ] || opts[ 'C' ] ) )
	    {
	        initDiscover( opts[ 'p' ], preops[ 'u' ], &ruser, enviro, e );

	        if( opts[ 'p' ] && e->Test() )
	            goto finish;

	        if( opts[ 'p' ] && ruser.GotError() )
	            goto finish;

	        if( e->Test() || ruser.GotError() )
	        {
	            // passive discovery failed, require options
	            ruser.ClearError();
	            e->Clear();

	            printf("No available server to discover configuration, needs flags:\n");
	            printf("p4 init -C0     (case-sensitive)\n");
	            printf("p4 init -C1     (case-insensitive)\n");
	            printf("Note, it is important to initialize with the same case sensitivity\n");
	            printf("as the server you wish to push/fetch from.\n");
	            goto finish;
	        }

	        doDiscover = 1;
	        doUnicode = ruser.Unicode();
	    }
	}

	if( ( sp = preops[ 'u' ] ) )
	    user.Set( sp );
	else
	    user = client->GetUser();

	if( ( sp = preops[ 'c' ] ) )
	    clientname.Set( sp );
	else
	{
	    DateTime dt;

	    dt.SetNow();
	    StrNum dn( dt.Value() );
	    clientname.Set( user );
	    clientname.UAppend( "-dvcs-" );
	    clientname.UAppend( &dn );
	}

	// Make it happen...

	// Get P4CONFIG, set if needed

	// Look for P4CONFIG file...
	fsys->Set( config );
	if( ( fsys->Stat() & ( FSF_EXISTS|FSF_EMPTY ) ) == FSF_EXISTS )
	{
	    delete fsys;
	    fsys = FileSys::Create( FST_ATEXT );
	    fsys->Set( config );
	}

	// Add values
	fsys->Perms( FPM_RW );
	fsys->Open( FOM_WRITE, e );

	if( e->Test() )
	    goto finish;

	s = enviro->Get( "P4IGNORE" );
	if( s )
	    ignore.Set( s );
	fsys->Write( StrRef( "P4IGNORE=" ), e );
	fsys->Write( ignore, e );

	fsys->Write( StrRef( "\nP4CHARSET=" ), e );
	fsys->Write( StrRef( doUnicode ? "auto" : "none" ), e );

	fsys->Write( StrRef("\n"
	    "P4INITROOT=$configdir\n"
	    "P4USER=" ), e );
	fsys->Write( user, e );
# ifdef OS_NT
	fsys->Write( StrRef( "\nP4PORT=rsh:p4d.exe -i " ), e );
# else
	fsys->Write( StrRef( "\nP4PORT=rsh:/bin/sh -c \"umask 077 && exec p4d -i " ), e );
# endif
	if( preops[ 'v' ]  ) { fsys->Write( StrRef( "-v" ), e );
	                       fsys->Write( preops[ 'v' ], e ); }
	                else { fsys->Write( StrRef( "-J off" ), e ); }
# ifdef OS_NT
	fsys->Write( StrRef( " -r \"$configdir\\" INIT_ROOT "\"\n" ), e );
# else
	fsys->Write( StrRef( " -r '$configdir/" INIT_ROOT "'\"\n" ), e );
# endif
	fsys->Write( StrRef( "P4CLIENT=" ), e );
	fsys->Write( clientname, e );
	fsys->Write( "\n", 1, e );

	fsys->Close( e );

	curdir->SetLocal( *curdir, StrRef( INIT_ROOT ) );

	ra << "p4d";

	// Handle unicode

	if( doUnicode ) ra << "-xn";
	           else ra << "-xnn";

	ra << "-r" << *curdir;

	ra << "-u" << user;

	// Handle case flags

	if( opts[ 'C' ] )
	{
	    StrBuf caseflag( "-C" );
	    caseflag.UAppend( opts[ 'C' ] );
	    ra << caseflag;
	}
	else if( doClone || doDiscover )
	    ra << ruser.CaseFlag();

	// quiet
	ra << "-q";

	curdir->SetLocal( *curdir, fileref );
	fsys->Set( *curdir );

# ifndef OS_NT
	oldumask = umask( 077 );
# endif

	fsys->MkDir( e );

	// Make the .p4 root directory hidden

	curdir->ToParent();
	rootDir->Set( curdir->Text() );
	rootDir->SetAttribute( FSA_HIDDEN, e );

	fsys->Set( serverID );
	fsys->Perms( FPM_RW );
	fsys->Open( FOM_WRITE, e );

	if( e->Test() )
	    goto finish;

	fsys->Write( clientname, e );
	fsys->Write( "\n", 1, e );
	fsys->Close( e );

	if( e->Test() )
	    goto finish;

	ecode = rc.Run( ra, e );

	if( ecode )
	{
	    // server failed to initialize

	    fsys->Set( config );
	    fsys->Unlink( e );

	    fsys->Set( serverID );
	    fsys->Unlink( e );
	    fsys->RmDir( e );

	    e->Set( initServerFail );
	    goto finish;
	}

	if( e->Test() )
	    goto finish;

# ifndef OS_NT
	umask( oldumask );
# endif

	if( !ecode )
	{
	    if( doClone )
	    {
	        cloneFetch( opts[ 'p' ], opts[ 'm' ], opts[ 'v' ], &remote, 
	                    &user, &ruser, &clientname, enviro, e );
	    }
	    else
	    {
	        if( doDiscover )
	        {
	            printf("Matching server configuration from '%s':\n", 
	                   ruser.Server().Text());
	            printf("%s, %s\n",
	                   ruser.CaseFlag() == "-C0" ? "case-sensitive (-C0)"
	                                             : "case-insensitive (-C1)",
	                   ruser.Unicode() ? "unicode (-xi)"
	                                   : "non-unicode (-n)" );
	            if( ruser.UserName() == "*unknown*" )
		        printf("warning: your user '%s' unknown at this server!\n",
		               ruser.GetUser().Text() );
	                
	        }
	        initService( &clientname, &ruser, opts[ 'c' ], enviro, e );
	    }

	    if( !e->Test() )
	        WriteIgnore( &ignore, &config, doClone, e );
	}

finish:
	if( e->Test() )
	{
	    cuser.Message( e );
	    ecode = 1;
	    e->Clear();
	}

	delete fsys;
	delete rootDir;
	delete curdir;
	delete client;
	delete enviro;

	return ecode;
}

void
initService( 
	StrPtr *clientname, 
	CloneUser *ruser, 
	StrPtr *branch, 
	Enviro *env,
	Error *e )
{
	Client client( env );
	char *args[2];
	ruser->GetData()->Clear();

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.Init( e );

	if( e->Test() )
	    return;

	*ruser->GetData() << "\nServerID: " << clientname;
	*ruser->GetData() << "\nType: server";
	*ruser->GetData() << "\nServices: local";
	*ruser->GetData() << "\nDescription:\n\tDVCS local personal repo\n";

	args[0] = (char *) "-i";
	ruser->SetCommand( "server-in" );
	client.SetArgv( 1, args );
	client.Run( "server", ruser );
	client.Final( e );

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.Init( e );

	if( e->Test() )
	    return;

	args[0] = (char *) "-i";
	if( branch )
	    args[1] = (char *) branch->Text();
	ruser->GetData()->Clear();
	ruser->SetCommand( "switch" );
	client.SetArgv( branch ? 2 : 1, args );
	client.Run( "switch", ruser );
	client.Final( e );
}

int
initValidate( StrPtr *branch )
{
	if( !branch )
	    return 0;

	char *p = branch->Text();
	int invalid = 0;

	if( strstr( p, "/" ) )
	{
	    // Must look like a stream
	    // e.g.   //depot/mainline

	    if( ( *p != '/' || *(p+1) != '/' || *(p+2) == '/' ) ||
	        !( p = strchr( p+2, '/' ) ) ||
	         ( strchr( p+1, '/' ) ) ||
	         ( *++p == 0 ) ) 
	        invalid = 1;
	}

	if( !invalid )
	    for( p = branch->Text(); !invalid && *p != 0; p++ )
	        invalid = ( *p == '@' || *p == '%' || *p == '#' || *p == '*' )
	                    || ( *p == '.' && *(p+1) == '.' && *(p+2) == '.' );
	if( !invalid )
	    return 0;

	printf("'%s' is not a valid mainline stream name.\n", branch->Text() );
	return 1;
}

void
initDiscover(
	StrPtr *port,
	StrPtr *user, 
	CloneUser *ruser, 
	Enviro *env,
	Error *e )
{
	Client client( env );
	char *args[2];

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );

	if( port )
	    client.SetPort( port );
	if( user )
	    client.SetUser( user );

	ruser->SetUser( client.GetUser().Text() );

	client.Init( e );

	if( e->Test() )
	    return;

	// Run info command, no crypto required (yet)

	ruser->SetCommand( "info-init" );
	client.Run( "info", ruser );
	client.Final( e );
}

void
cloneSetup( 
	StrPtr *port, 
	StrPtr *remote, 
	StrPtr *filepath, 
	StrPtr *user, 
	CloneUser *ruser, 
	Enviro *env,
	Error *e )
{
	Client client( env );
	char *args[2];

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.SetPort( port );
	if( user )
	    client.SetUser( user );
	client.Init( e );

	if( e->Test() )
	    return;

	// Run info command, no crypto required (yet)

	ruser->SetCommand( "info" );
	client.Run( "info", ruser );

	if( ruser->GotError() )
	{
	    // Only error is that push/fetch not allowed
	    printf("server '%s' not configured to clone (server.allowfetch).\n",
	           port->Text() );
	    client.Final( e );
	    return;
	}

	// Run remote command, crypto required

	if( remote )
	{
	    // Check remote exists

	    args[0] = (char *) "-E";
	    args[1] = remote->Text();
	    ruser->SetCommand( "remotes" );
	    client.SetArgv( 2, args );
	    client.Run( "remotes", ruser );

	    if( ruser->NeedLogin() )
	    {
	        printf("'%s' is not currently logged in to '%s'\n", 
	               client.GetUser().Text(), port->Text() );
	        printf("run 'p4 -u %s -p %s login' to authenticate\n",
	               client.GetUser().Text(), port->Text() );
	        client.Final( e );
	        ruser->SetError();
	        return;
	    }

	    if( !ruser->GotRemote() )
	    {
	        if( !ruser->GotError() )
	            printf("server '%s' does not have a remote spec '%s'\n",
	                   port->Text(), remote->Text() );
	        client.Final( e );
	        ruser->SetError();
	        return;
	    }

	    args[0] = (char *) "-o";
	    args[1] = remote->Text();
	    ruser->SetCommand( "remote-out" );
	    client.SetArgv( 2, args );
	    client.Run( "remote", ruser );
	    client.Final( e );
	}
	else if( filepath )
	{
	    // Fakeup a remote map called origin
	    // We can only map a filepath if its only wildcards are
	    // trailing ellipses.

	    StrBuf depotMap;
	    int cannotMap = 0;
	    int reMap = 0;
	    const char *s = filepath->Text();
	    const char *x = s + strlen( s );
	    const char *p = strstr( s, "/..." );
	    const char *newPath;

	    if( !p || p != ( x - 4 ) )
	        cannotMap = 1;

	    if( ruser->TooWide( s ) && cannotMap )
	    {
	        if( *s == '/' && *(s+1) == '/'  && strstr( (s+2), "/" ) 
	                      && *(x-1) != '/'  )
	        {
	            reMap = 1;
	            newPath = x;
	            while( *newPath != '/' ) 
	                newPath--;
	        }
	        else
	        {
	            printf( "filepath '%s' cannot be mapped.\n", 
	                    filepath->Text() );
	            client.Final( e );
	            ruser->SetError();
	            return;
	        }
	        
	    }
	    else if( ruser->TooWide( s ) )
	    {
	        printf( "filepath '%s' is too wide open.\n", filepath->Text() );
	        client.Final( e );
	        ruser->SetError();
	        return;
	    }

	    for( p = s; p < (x - 4); p++ )
	    {
                if( ( *p == '@' || *p == '%' || *p == '#' || *p == '*' )
                 || ( *p == '.' && *(p+1) == '.' && *(p+2) == '.' ) )
	        {
	            printf( "filepath '%s' contains %s.\n", filepath->Text(),
	                  (*p == '.') ? "embedded wildcards"
	                              : "illegal characters [@%#*]" );
	            client.Final( e );
	            ruser->SetError();
	            return;
	        }
	    }

	    args[0] = (char *) "-s";
	    ruser->SetCommand( "login-s" );
	    client.SetArgv( 1, args );
	    client.Run( "login", ruser );

	    if( ruser->NeedLogin() )
	    {
	        printf("'%s' is not currently logged in to '%s'\n", 
	               client.GetUser().Text(), port->Text() );
	        printf("run 'p4 -u %s -p %s login' to authenticate\n",
	               client.GetUser().Text(), port->Text() );
	        client.Final( e );
	        ruser->SetError();
	        return;
	    }

	    client.Final( e );

	    if( reMap )
	        depotMap << "//stream/main" << newPath << " " << filepath;
	    else if( cannotMap )
	        depotMap << filepath << " " << filepath;
	    else
	        depotMap << "//stream/main/..." << " " << filepath;

	    ruser->Dict()->SetVar( StrRef( "depotMap" ), depotMap );
	    ruser->SetDescription( "auto-generated from clone command" );
	}
}

void
cloneFetch( 
	StrPtr *port, 
	StrPtr *depth,
	StrPtr *debug,
	StrPtr *remote, 
	StrPtr *user, 
	CloneUser *ruser, 
	StrPtr *clientname,
	Enviro *env,
	Error *e )
{
	// save cloned remote map

	int i, j;
	StrRef var, val;
	Client client( env );
	char *args[1000];
	ruser->GetData()->Clear();

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.Init( e );

	if( e->Test() )
	{
	    client.Final( e );
	    return;
	}

	*ruser->GetData() << "\nServerID: " << clientname;
	*ruser->GetData() << "\nType: server";
	*ruser->GetData() << "\nServices: local";
	*ruser->GetData() << "\nDescription:\n\tDVCS local personal repo\n";

	args[0] = (char *) "-i";
	ruser->SetCommand( "server-in" );
	client.SetArgv( 1, args );
	client.Run( "server", ruser );
	client.Final( e );

	if( e->Test() || ruser->GotError() )
	    return;

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.Init( e );

	if( e->Test() )
	{
	    client.Final( e );
	    return;
	}

	ruser->GetData()->Clear();
	*ruser->GetData() << "\nRemoteID: origin";
	*ruser->GetData() << "\nAddress: " << port;
	*ruser->GetData() << "\nOwner: " << user;
	*ruser->GetData() << "\nOptions: unlocked nocompress";
	*ruser->GetData() << "\nDescription: ";

	char *ptr = ruser->Description().Text();

	while( *ptr != '\0' )
	{
	    ruser->GetData()->Append( ptr, 1 );
	    if( *ptr++ == '\n' && *ptr != '\0' )
	        *ruser->GetData() << "\t";
	}

	*ruser->GetData() << "\nDepotMap:\n";

	for( i = 0; ruser->Dict()->GetVar( i, var, val ); i++ )
	    *ruser->GetData() << "\t" << val.Text() << "\n";

	args[0] = (char *) "-i";

	ruser->SetCommand( "remote-in" );
	client.SetArgv( 1, args );
	client.Run( "remote", ruser );

	if( ruser->GotError() )
	{
	    client.Final( e );
	    return;
	}

	// Initialize depot, build mainline streams
	// Use the first map entry to create the first mainline

	int index = 0;
	int initDone = 0;
	int argsCount;
	StrBuf filePath;

	for( i = 0; ruser->Dict()->GetVar( i, var, val ); i++ )
	{
	    ruser->GetStreamName( &filePath, val );

	    if( ruser->StreamExists( filePath ) )
	        continue;

	    argsCount = 0;

	    if( initDone )
	    {
	        args[argsCount++] = (char *) "-m";
	        args[argsCount++] = (char *) "-c";
	    }
	    else
	    {
	        args[argsCount++] = (char *) "-i";
	        initDone++;
	    }

	    args[argsCount++] = (char *) "-s";
	    args[argsCount++] = (char *) ruser->Trim( filePath, val );

	    for( j = (i+1); ruser->Dict()->GetVar( j, var, val ); j++ )
	    {
	        if( !filePath.XCompareN( val ) )
	        {
	            args[argsCount++] = (char *) "-s";
	            args[argsCount++] = (char *) ruser->Trim( filePath, val );
	        }
	    }

	    args[argsCount++] = filePath.Text();
	    
	    ruser->SetCommand( "switch" );
	    client.SetArgv( argsCount, args );
	    client.Run( "switch", ruser );

	    // cleanup allocated trimmed paths

	    for( int x = 0; x < argsCount; ++x )
	    {
	        if( !strcmp( args[ x ], "-s" ) )
	            delete args[ ++x ];
	    }

	    if( ruser->GotError() )
	        break;
	}

	// Might have created an alternate depot,  need to
	// fire up a new connection

	client.Final( e );

	if( ruser->GotError() )
	    return;

	client.SetProtocol( P4Tag::v_tag );
	client.SetProtocol( P4Tag::v_enableStreams );
	client.Init( e );

	if( e->Test() )
	{
	    client.Final( e );
	    return;
	}

	printf("Cloning from '%s'...\n", port->Text());

	// Issue fetch command
	int argc = 0;

	if( debug )
	{
	    args[argc++] = (char *) "-v";
	}

	if( depth )
	{
	    args[argc++] = (char *) "-m";
	    args[argc++] = (char *) depth->Text();
	}

	ruser->SetCommand( "fetch" );
	client.SetArgv( argc, args );
	client.Run( "fetch", ruser );

	// Get MaxCommitChange.

	args[0] = (char *) "maxCommitChange";
	
	ruser->SetCommand( "counter" );
	client.SetArgv( 1, args );
	client.Run( "counter", ruser );

	// Only update LastPush if data was pulled

	if( !ruser->MaxChange() )
	{
	    client.Final( e );
	    return;
	}

	// Reload origin remote map.

	args[0] = (char *) "-o";
	args[1] = (char *) "origin";

	ruser->SetCommand( "remote-out2" );
	client.SetArgv( 2, args );
	client.Run( "remote", ruser );

	// Alter last push value

	ruser->GetData()->Clear();

	StrBuf map;
	map.Set( "DepotMap" );
	int mapCount = 0;

	for( i = 0; ruser->Dict()->GetVar( i, var, val ); i++ )
	{
	    // extra vars not in form

	    if( var == "specFormatted" || var == "func" )
	        continue; 
	    else if( var == "Description" )
	    {
	        char *ptr = val.Text();
	        *ruser->GetData() << var << ": ";

	        while( *ptr != '\0' )
	        {
	            ruser->GetData()->Append( ptr, 1 );
	            if( *ptr++ == '\n' && *ptr != '\0' )
	                *ruser->GetData() << "\t";
	        }
	    }
	    else if( !map.XCompareN( var ) )
	    {
	        if( !mapCount++ )
	            *ruser->GetData() << "DepotMap:\n";
	        *ruser->GetData() << "\t" << val << "\n";
	    }
	    else
	    {
	        *ruser->GetData() << var << ":\n\t";
	        if( var == "LastPush" )
	            *ruser->GetData() << ruser->MaxChange() << "\n";
	        else
	            *ruser->GetData() << val << "\n";
	    }
	}

	args[0] = (char *) "-i";

	ruser->SetCommand( "remote-in" );
	client.SetArgv( 1, args );
	client.Run( "remote", ruser );

	// End commands

	client.Final( e );
}

int
CloneUser::StreamExists( StrPtr &filePath )
{
	int i;
	StrRef var, val;

	for( i = 0; mainlines.GetVar( i, var, val ); i++ )
	{
	    if( !filePath.Compare( var ) )
	        return 1;
	}

	mainlines.SetVar( filePath, filePath );
	return 0;
}

const char *
CloneUser::Trim( StrPtr &filePath, StrPtr &val )
{
	StrBuf sharePath;

	char *p = val.Text() + filePath.Length() + 1;
	char *e = p;

	while( *e && *e != ' ' )
	    ++e;

	sharePath.Append( p, e - p );

	p = (char *) malloc( sharePath.Length() + 1 );
	strcpy( p, sharePath.Text() );
	return p;
}

void
CloneUser::GetStreamName( StrBuf *filePath, StrPtr &val )
{
	filePath->Clear();

	StrBuf buf;
	buf << val.Text();

	if( buf.Length() < 5 )
	    return;

	char *p, *s;

	s = buf.Text();
	if( *s == '-' ) s++;
	p = s + 2;
	p = strchr( p, '/' );

	if( !p || !*p )
	    return;

	p++;
	p = strchr( p, '/' );

	if( !p )
	    return;

	filePath->Append( s, p - s );
}

void
CloneUser::OutputStat( StrDict *varList )
{
	// Capture data from info and remote

	if( GetCommand() == "info" || GetCommand() == "info-init" )
	{
	    StrPtr *s;

	    unicode = varList->GetVar( P4Tag::v_unicode ) != 0;
	    security = varList->GetVar( P4Tag::v_security ) != 0;

	    s = varList->GetVar( P4Tag::v_userName );
	    if( s )
	        userName.Set( s );

	    s = varList->GetVar( P4Tag::v_serverAddress );
	    if( s )
	        serverAddress.Set( s );

	    s = varList->GetVar( P4Tag::v_caseHandling );

	    if( !s || *s == "sensitive"   ) caseFlag << "-C0";
	    else if(  *s == "insensitive" ) caseFlag << "-C1";
	    else if(  *s == "hybrid"      ) caseFlag << "-C2";

	    if( GetCommand() == "info" )
	    {
	        s = varList->GetVar( "allowFetch" );

	        if( !s || s->Atoi() < 2 )
	            commandError++;
	    }
	}
	else if( GetCommand() == "remote-out" )
	{
	    int i;
	    int count = 0;
	    int quoted;
	    StrRef var, val;
	    StrBuf lhs, depot, empty, map;
	    map.Set( "DepotMap" );
	    empty.Set( "..." );
	    const char *p;

	    for( i = 0; varList->GetVar( i, var, val ); i++ )
	    {
	        depot.Clear();

	        if( !map.XCompareN( var ) )
	        {
	            StrOps::GetDepotName( val.Text(), depot );

	            if( !empty.XCompareN( depot )  )
	            {
	                printf("Remote clone spec invalid!\n");
	                commandError++;
	            }

	            if( count++ )
	            {
	                if( depotName != depot )
	                {
	                    printf( "Remote spec references multiple depots on the left hand side of map:\n");
	                    for( int j = 0; varList->GetVar( j, var, val ); j++ )
	                        if( !map.XCompareN( var ) ) printf( "%s\n", val.Text() );
	                    commandError++;
	                    break;
	                }
	            }
	            else
	                depotName << depot;

	            // Validate stream(branch) side of map

	            lhs.Clear();

	            p = val.Text();
	            quoted = (*p++ == '"' );

	            while( *p != 0 )
	            {
	                if( ( quoted && *p == '"' ) ||
	                    (!quoted && *p == ' ' )  )
	                    break;
	                ++p;
	            }

	            if( quoted )
	                lhs.Append( val.Text()+1, (p - val.Text()) - 2 );
	            else
	                lhs.Append( val.Text(), p - val.Text() );

	            p = lhs.Text();
	            if( *p == '-' )
	               ++p;

	            if( TooWide( p ) )
	            {
	                printf("Remote map entry '%s' cannot be allocated a stream name:\n", lhs.Text() );
	                printf("Clone requires at least //<depotname>/<streamname>/ on the left hand side of the map\n");
	                commandError++;
	            }

	            remoteMap.SetVar( var, val );
	            continue;
	        }

	        if( var ==  "Description" )
	            description << val;
	    }
	}
	else if( GetCommand() == "remote-out2" )
	{
	    int i;
	    StrRef var, val;
	    remoteMap.Clear();

	    for( i = 0; varList->GetVar( i, var, val ); i++ )
	        remoteMap.SetVar( var, val );
	}
	else if( GetCommand() == "counter" )
	{
	    StrPtr *s = varList->GetVar( "value" );

	    if( s )
	        maxCommitChange = s->Atoi();
	}
	else if( GetCommand() == "remotes" )
	{
	    ++gotRemote;
	}
}

void
CloneUser::OutputText( const char *data, int length )
{
	printf("OutputText!\n");
}

void
CloneUser::OutputInfo( char level, const char *data )
{
	// quiet where possible

	if( quiet && ( GetCommand() == "remote-in" ||
	               GetCommand() == "switch" ) )
	    return;

	printf("%s\n", data);
}

void
CloneUser::OutputError( const char *errBuf )
{
	if( ( GetCommand() == "remotes" || GetCommand() == "login-s" )
	    && ( !strncmp( errBuf, "Perforce password", 17 ) || 
	         !strncmp( errBuf, "Your session has expired", 24 ) ) )
	{
	    needLogin++;
	}
	else
	{
	    printf( "%s", errBuf );
	    commandError++;
	}
}

void
CloneUser::InputData( StrBuf *buf, Error *e )
{
	if( GetCommand() == "remote-in" ||
	    GetCommand() == "server-in" )
	    buf->Set( inputData );
}

int
CloneUser::TooWide( const char *s )
{
	const char *p;
	return( *s != '/' || *(s+1) != '/' || *(s+2) == '/' ||
	         !( p = strstr(s+2,"/") )  || *(p+1) == '/' ||
	         !( p = strstr(p+1,"/") )  || *(p+1) == '\0' );
}

static void
WriteIgnore( StrPtr *ignore, StrPtr *config, int doClone, Error *e )
{
	FileSys *fsys;

	fsys = FileSys::Create( FST_TEXT );

	fsys->Set( *ignore );

	if( ( fsys->Stat() & ( FSF_EXISTS|FSF_EMPTY ) ) == FSF_EXISTS )
	{
	    // Might have been created by a failed clone, check before
	    // appending.

	    // Assume the clone fetch dumped it here... bail...

	    if( doClone )
	        goto finish;

	    fsys->Open( FOM_READ, e );

	    if( e->Test() )
	        goto finish;

	    StrBuf line;
	    while( fsys->ReadLine( &line, e  ) )
	    {
	        if( !line.Compare( StrRef( INIT_ROOT ) ) )
	        {
	            fsys->Close( e );
	            goto finish;
	        }
	    }

	    fsys->Close( e );
	    delete fsys;
	    fsys = FileSys::Create( FST_ATEXT );
	    fsys->Set( *ignore );
	}

	fsys->Perms( FPM_RW );
	fsys->Open( FOM_WRITE, e );

	if( e->Test() )
	    goto finish;
 
	fsys->Write( *config, e );
	fsys->Write( "\n", 1, e );
	fsys->Write( *ignore, e );
	fsys->Write( StrRef( "\n.svn\n.git\n.DS_Store\n"
	             INIT_ROOT "\n*.swp\n" ), e );
	fsys->Close( e );

finish:
	delete fsys;
}

static void
LockCheck( Error *e )
{
	FileSys *fsys, *altsys;

	fsys = FileSys::Create( FST_BINARY );

	fsys->Set( "db.check" );
	fsys->Perms( FPM_RW );
	fsys->Open( FOM_WRITE, e );

	if( e->Test() )
	    goto finish;

	altsys = FileSys::Create( FST_BINARY );

	altsys->Set( fsys->Name() );
	altsys->Perms( FPM_RW );
	altsys->Open( FOM_READ, e );

	if( !e->Test() )
	{
	    int ffd, afd;

	    ffd = fsys->GetFd();
	    afd = altsys->GetFd();

// Because Solaris locking is at a process level not a file descriptor
// level, we can't do all the checks we want

	    if( ! (
		    lockFile( ffd, LOCKF_EX_NB ) == 0 &&
# ifndef OS_SOLARIS
		    lockFile( afd, LOCKF_SH_NB ) == -1 &&
# endif
		    lockFile( ffd, LOCKF_UN ) == 0 &&
		    lockFile( afd, LOCKF_SH_NB ) == 0 &&
# ifndef OS_SOLARIS
		    lockFile( ffd, LOCKF_EX_NB ) == -1 &&
# endif
		    lockFile( afd, LOCKF_UN ) == 0 ) )
		e->Sys( "lockFile", "db.check" );

	    altsys->Close( e );
	}

	fsys->Close( e );

	delete altsys;

finish:
	fsys->Unlink( e );
	
	delete fsys;
}
