/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <stdhdrs.h>
# include <strbuf.h>
# include "mapchar.h"

static const char *const mapCharNames[] = {
	"0",
	"c",
	"/",
	"%",
	"*",
	"."
} ;

int
MapChar::Set( char *&p, int &nStars, int &nDots )
{
	this->c = *p;

	if( c == '/' )
	{
		cc = cSLASH;
		++p;
	}
	else if( c == '.' && p[1] == '.' && p[2] == '.' )
	{
		cc = cDOTS;
		paramNumber = PARAM_BASE_DOTS + nDots++;
		p += 3;
	}
	else if( c == '%' && p[1] == '%' && p[2] >= '0' && p[2] <= '9' )
	{
		cc = cPERC;
		paramNumber = PARAM_BASE_PERCENT + ( p[2] - '0' );
		p += 3;
	}
	else if( c == '*' )
	{
		cc = cSTAR;
		paramNumber = PARAM_BASE_STARS + nStars++;
		++p;
	}
	else if( c == '\0' )
	{
		cc = cEOS;
		return 0;
	}
	else 
	{
		cc = cCHAR;
		++p;
	}

	return 1;
}

void
MapChar::MakeParam( StrBuf &p, MapChar *mc2, int &wildSlot )
{
	if( cc == cDOTS && mc2->cc == cDOTS )
	{
	    p << "...";
	}
	else
	{
	    p << "%%" << ++wildSlot;
	}
}

const char *
MapChar::Name()
{
	return mapCharNames[ cc ];
}

