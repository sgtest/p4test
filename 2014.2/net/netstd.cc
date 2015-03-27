/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * netstd.cc - stdio driver for NetConnect, for use with inetd
 *
 * Classes Defined:
 *
 *	NetStdioEndPoint - a stdio subclass of NetEndPoint
 *	NetStdioTransport - a stdio subclass of NetTransport
 *
 * The server half of this is simple: read/write stdin/stdout.
 * On UNIX, we use stdin for both reading/writing, oddly enough, 
 * to free up stdout for debugging messages.  This works because
 * stdin is a socket passed from inetd or from our own client half.
 * On NT, we split stdin/stdout (and you can't turn on debug msgs).
 *
 * The client half is more complicated. On UNIX, fork a child whose 
 * fds 0/1 are at one end of a bidirectional socket, and we read
 * and write from the other.  On NT, we use a pair of pipes, but
 * without fork() we have to adjust stdin/stdout before the spawn
 * and then reset it after.
 */

# define NEED_ERRNO
# define NEED_FILE
# define NEED_FCNTL
# define NEED_IOCTL
# define NEED_SIGNAL
# define NEED_SOCKETPAIR

# ifdef OS_NT
// so we get only winsock2, not both winsock and winsock2
# define WIN32_LEAN_AND_MEAN
# endif // OS_NT

# include <stdhdrs.h>
# include <error.h>
# include <strbuf.h>

# include <debug.h>
# include <strops.h>
# include <runcmd.h>
# include <bitarray.h>

# include <keepalive.h>
# include "netportparser.h"
# include "netaddrinfo.h"
# include "netconnect.h"
# include "netstd.h"
# include "netdebug.h"
# include <netselect.h>
# include <msgrpc.h>

/*
 * NetStdioEndPoint
 */

NetStdioEndPoint::~NetStdioEndPoint()
{
	delete rc;
}

void
NetStdioEndPoint::Listen( Error *e )
{
	isAccepted = true;
	// Block SIGPIPE so a departed client doesn't blast us.
	// Block SIGINT, too, so ^C doesn't blast us.

# ifdef SIGPIPE
	signal( SIGPIPE, SIG_IGN );
# endif
	signal( SIGINT, SIG_IGN );

# ifdef HAVE_SOCKETPAIR
	// redirect stdout to stderr for debugging
	dup2( 2, 1 );
# endif
}

int
NetStdioEndPoint::CheaterCheck( const char *port )
{
	return 0;
} 

void
NetStdioEndPoint::ListenCheck( Error *e )
{
}

void
NetStdioEndPoint::Unlisten()
{
}


/*
 * NetStdioTransport
 */

NetTransport *
NetStdioEndPoint::Accept( Error *e )
{
# ifdef HAVE_SOCKETPAIR
	// talk both ways via stdin
	return new NetStdioTransport( 0, 0, true );
# else
	// separate stdin/stdout
# ifdef OS_NT
	setmode( 0, O_BINARY );
	setmode( 1, O_BINARY );
# endif
	return new NetStdioTransport( 0, 1, true );
# endif
}

# if defined( HAVE_SOCKETPAIR ) || defined( OS_NT ) && !defined( __MWERKS__ )

# define GOT_CONNECTED

NetTransport *
NetStdioEndPoint::Connect( Error *e )
{
	int p[2];
	StrBuf cmd = GetPortParser().Host();

	DEBUGPRINTF( DEBUG_CONNECT, "NetStdioEndPoint: cmd='%s'", cmd.Text() );

	RunArgs args( cmd );

	// XXX RunCommand is dynamically allocated
	// to work around linux 2.5 24x86 compiler bug.
	// See job019111
	
	rc = new RunCommand;
	rc->RunChild( args, RCO_SOLO_FD|RCO_P4_RPC, p, e );

	if( e->Test() )
	    return 0;

	return new NetStdioTransport( p[0], p[1], false );
}

# endif

# ifndef GOT_CONNECTED

NetTransport *
NetStdioEndPoint::Connect( Error *e )
{
	e->Set( MsgRpc::Stdio );
	return 0;
}

# endif

StrPtr *
NetStdioEndPoint::GetListenAddress( int f )
{
	addr.Set( "unknown" );
        return &addr;
}

/*
 * NetStdioTransport
 */


NetStdioTransport::NetStdioTransport( int r, int s, bool isAccept  )
: isAccepted( isAccept )
{ 
	this->r = r;
	this->t = s;
	breakCallback = 0;

	selector = new NetTcpSelector( r );
}

NetStdioTransport::~NetStdioTransport() 
{ 
	Close(); 

	delete selector;
}

void
NetStdioTransport::Close( void )
{
	if( r >= 0 ) close( r );
	if( t != r && t >= 0 ) close( t );
	r = t = -1;
}

StrPtr *
NetStdioTransport::GetAddress( int f )
{
	addr.Set( "unknown" );
        return &addr;
}

StrPtr *
NetStdioTransport::GetPeerAddress( int f )
{
	addr.Set( "unknown" );
        return &addr;
}

void
NetStdioTransport::Send( const char *buffer, int length, Error *e )
{
	DEBUGPRINTF( DEBUG_TRANS, "NetStdioTransport send %d bytes", length );

	if( write( t, buffer, length ) != length )
	{
	    e->Net( "write", "socket stdio" );
	    e->Set( MsgRpc::TcpSend );
	}
}

int
NetStdioTransport::Receive( char *buffer, int length, Error *e )
{
	if( breakCallback )
	    for(;;)
	{
	    int readable = 1;
	    int writable = 0;

	    // 500000 is .5 seconds.

	    const int tv = 500000;

	    if( selector->Select( readable, writable, tv ) < 0 )
	    {
		e->Sys( "select", "socket stdio" );
		return 0;
	    }

	    // Before checking for data do the callback isalive test.
	    // If the user defined IsAlive() call returns a zero
	    // value then the user wants this request to terminate.

	    if( !breakCallback->IsAlive() )
	    {
		e->Set( MsgRpc::Break );
		return 0;
	    }

	    if( readable )
		break;
	}

	int l = read( r, buffer, length );

	if( l < 0 )
	{
	    e->Net( "read", "socket stdio" );
	    e->Set( MsgRpc::TcpRecv );
	}

	DEBUGPRINTF( DEBUG_TRANS, "NetStdioTransport recv %d bytes", l );

	return l;
}


# ifdef OS_NT

int
NetStdioTransport::IsAlive()
{
	return 1;
}

# else

int
NetStdioTransport::IsAlive()
{ 
	int readable = 1;
	int writeable = 0;

	if( selector->Select( readable, writeable, 0 ) < 0 )
	    return 0;

	// All good if no EOF waiting

	return !readable || selector->Peek();
}

# endif
