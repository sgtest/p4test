/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * ClientUserDebug -- version of output that always to stdout
 */

class ClientUserDebug : public ClientUser {

    public:

	void		OutputTag( const char *tag, 
				const char *data, int length );

	virtual void	OutputInfo( char level, const char *data );
	virtual void 	OutputError( const char *errBuf );
	virtual void 	OutputText( const char *data, int length );

} ;

/*
 * ClientUserDebugMsg -- dump Error info for debugging
 */

class ClientUserDebugMsg : public ClientUserDebug {

    public:

	virtual void	Message( Error* err );

} ;

/*
 * ClientUserFmt -- format output with user-specified string
 */

class ClientUserFmt : public ClientUser {

    public:

	ClientUserFmt( const StrPtr *fmt ) { this->fmt = fmt; };

	void		Message( Error *err );
	void		OutputStat( StrDict *dict );

    private:

	const StrPtr *fmt;
} ;
