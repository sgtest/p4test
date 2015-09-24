/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * netstd.h - stdio driver for NetTransport, for use with inetd
 *
 * Classes Defined:
 *
 *	NetStdioEndPoint - a stdio subclass of NetEndPoint
 *	NetStdioTransport - a stdio subclass of NetTcpTransport
 *
 * Built upon NetTcpTransport so GetAddress/GetPeerAddress works
 * when invoked via inetd.
 */

class RunCommand;
class NetTcpSelector;

class NetStdioEndPoint : public NetEndPoint {

    public:
			NetStdioEndPoint( Error *e )
			{
				s = -1;
			        rc = 0;
			        isAccepted = false;
			}

			~NetStdioEndPoint();

	StrPtr		*GetHost() { return 0; }
	StrPtr		*GetListenAddress( int f );

	void		Listen( Error *e );
	void		ListenCheck( Error *e );
	int		CheaterCheck( const char *port );
	void		Unlisten();

	NetTransport *	Connect( Error *e );
	NetTransport *	Accept( Error *e );


	int		IsSingle() { return 1; }

    private:

	int		s;
	StrBuf		addr;
	RunCommand	*rc;

} ;

class NetStdioTransport : public NetTransport {

    public:
			NetStdioTransport( int r, int s, bool isAccept );
			~NetStdioTransport();

	StrPtr	*	GetAddress( int f );

	StrPtr	*	GetPeerAddress( int f );
	virtual bool	IsAccepted()
			{
			    return isAccepted;
			}

	void		Send( const char *buffer, int length, Error *e );
	int		Receive( char *buffer, int length, Error *e );

	void		Close();

//	No select() call for NT pipe.  (this will need a lot of native glue).
//
# if defined (OS_NT)
	void		SetBreak( KeepAlive *b ) { breakCallback = 0; }
# else
	void		SetBreak( KeepAlive *b ) { breakCallback = b; }
# endif

	int		GetSendBuffering() { return 2048; }
	int		GetRecvBuffering() { return 2048; }

	int		IsAlive();

    protected:
	bool		isAccepted;

    private:
	int		r;	// receive pipe 
	int		t;	// send pipe

	KeepAlive	*breakCallback;

	StrBuf		addr;

	NetTcpSelector	*selector;

} ;
