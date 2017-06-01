/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

class ObjStream
{
    public:

	                        ObjStream() { }

	virtual			~ObjStream() { }

	virtual unsigned char	Next( Error *e ) = 0;
	virtual void		GetLine( StrBuf *buf, Error *e ) = 0;

	int			AtEof() { return eof; }

	virtual P4INT64		GetBytesRead() = 0;
	virtual void		ReadFully( Error *e )
	                        {
	                            while( !AtEof() && !e->Test() ) Next( e );
	                        }

    protected:

	int			eof;
} ;

