/*
 * Copyright 1995, 2011 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <clientapi.h>
# include <clientprog.h>
# include <timer.h>
# include <progress.h>

ClientProgressText::ClientProgressText( int ty )
    : typeOfProgress( ty ), total( 0 ), cnt( 0 ), first( 1 )
{
}

ClientProgressText::~ClientProgressText()
{
}

void
ClientProgressText::Description( const StrPtr *desc, int units )
{
	printf( "%s ", desc->Text() );
	cnt = 0;
	first = 1;
	total = 0;
}

void
ClientProgressText::Total( long t )
{
	total = t;
}

int
ClientProgressText::Update( long pos )
{
	if( total )
	{
	    int pct = int(100.0 * pos / total);

	    if( !first )
		printf( "\b\b\b\b\b\b" );

	    printf( "%3d%% %c", pct, "|/-\\"[ cnt ] );
	}
	else
	{
	    if( !first )
		printf( "\b\b\b\b\b\b\b\b" );

	    printf( "%6ld %c", pos, "|/-\\"[ cnt ] );
	}

	first = 0;
	fflush(stdout);
	if( ++cnt == 4 )
	    cnt = 0;

	return 0;
}

void
ClientProgressText::Done( int fail )
{
	if( !first )
	    printf( "\b" );
	printf( fail == CPP_FAILDONE ? "failed!\n" : "finishing\n");
}
