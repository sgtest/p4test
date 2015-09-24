/*
 * Copyright 1995, 2003 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 *
 * Git style ignore file for add/reconcile
 */

# include <stdhdrs.h>
# include <strbuf.h>
# include <error.h>
# include <pathsys.h>
# include <filesys.h>
# include <debug.h>
# include <strarray.h>
# include <maptable.h>
# include "ignore.h"

# ifdef OS_NT
# define SLASH "\\"
# else
# define SLASH "/"
# endif

# define ELLIPSE "..."

Ignore::Ignore()
{
	ignoreList = 0;
}

Ignore::~Ignore()
{
	delete ignoreList;
}

int
Ignore::Reject( 
	const StrPtr &path, 
	const StrPtr &ignoreName,
	const char *configName )
{
	// If we don't have an ignore file, we can just load up the defaults
	// and test against those. If we've already loaded them, lets not do
	// it again and use the existing list instead.
	
	if( !strcmp( ignoreName.Text(), "unset" ) )
	{
	    if( !ignoreList )
	        ignoreList = new StrArray;

	    if( !ignoreList->Count() )
	        InsertDefaults( configName );

	    return RejectCheck( path );
	}

	PathSys *p = PathSys::Create();
	p->Set( path );
	p->ToParent();

	StrBuf saveDepth;

	// Try real hard not to regenerate the ignorelist, this
	// optimization uses the current directory depth and the
	// last found ignorefile depth to reduce the search for
	// config files.

	if( ignoreList && dirDepth.Length() )
	{
	    if( !dirDepth.SCompare( *p ) )
	    {
	        // matching depth bail early

	        delete p;
	        return RejectCheck( path );
	    }
	    else if( !dirDepth.SCompareN( *p ) )
	    {
	        // descending directories can be shortcut.

	        saveDepth << dirDepth;
	    }
	    else if( !p->SCompareN( dirDepth ) &&
	             foundDepth.Length() && !foundDepth.SCompareN( *p ) )
	    {
	        // ascending directories can be shortcut.

	        dirDepth.Set( *p );
	        delete p;
	        return RejectCheck( path );
	    }
	}
	
	StrBuf line;
	Error e;

	dirDepth.Set( *p );

	// No descending optimization, remove list we will recreate it

	if( !saveDepth.Length() )
	{
	    delete ignoreList;
	    ignoreList = new StrArray;
	}
	
	if( !ignoreList->Count() )
	    InsertDefaults( configName );

	PathSys *q = PathSys::Create();
	FileSys *f = FileSys::Create( FileSysType( FST_TEXT|FST_L_CRLF ) );

	// starting from the directory in which the argument supplied file
	// lives,  walk up the tree collecting ignore files as we go

	int found = 0;

	do {
	    if( saveDepth.Length() && !saveDepth.SCompare( *p ) )
	    {
	        delete p;
	        return RejectCheck( path );
	    }

	    e.Clear();
	    StrArray *subList = new StrArray();

	    q->SetLocal( *p, ignoreName );
	    f->Set( *q );

	    f->Open( FOM_READ, &e );

	    if( e.Test() )
	    {
	        delete subList;
	        continue;
	    }

	    // Found ignore file, clear any optimization, reuse foundDepth

	    if( saveDepth.Length() )
	    {
	        delete ignoreList;
	        ignoreList = new StrArray;
	        InsertDefaults( configName );
	        saveDepth.Clear();
	    }

	    // Set foundDepth

	    if( !found++ )
	        foundDepth.Set( *p );

	    while( f->ReadLine( &line, &e ) )
	    {
	        line.TrimBlanks();
	        if( !line.Length() || line.Text()[0] == '#' )
	            continue;
	        Insert( subList, line.Text(), p->Text() );
	    }

	    f->Close( &e );

	    if( DEBUG_MATCH || DEBUG_LIST )
	    {
	        line.Clear();
	        line << "#FILE ";
	        line << f->Name();
	        subList->Put()->Set( line );
	    }

	    // Add this ignorefile to a list (reversing it as its added)

	    for( int i = subList->Count(); i > 0; --i )
	        ignoreList->Put()->Set( subList->Get( i - 1 ) );
	
	    delete subList;
	}
	while( p->ToParent() );

	delete q;
	delete p;
	delete f;

	if( DEBUG_LIST )
	{
	    p4debug.printf("\n\tIgnore list:\n\n");
	    for( int j = 0; j < ignoreList->Count(); ++j )
	    {
	        char *p = ignoreList->Get( j )->Text();
	        p4debug.printf("\t%s\n", p);
	    }
	    p4debug.printf("\n");
	}

	return RejectCheck( path );
}

void
Ignore::InsertDefaults( const char *configName )
{
	// Always add in .p4root and P4CONFIG to the top of new lists

	if( DEBUG_MATCH || DEBUG_LIST )
	    ignoreList->Put()->Set( StrRef( "#FILE - defaults" ) );

	StrBuf line;
	line << ELLIPSE << SLASH << ".p4root";
	ignoreList->Put()->Set( line );
	line << SLASH << ELLIPSE;
	ignoreList->Put()->Set( line );

	if( configName )
	{
	    line.Clear();
	    line << ELLIPSE << SLASH << configName;
	    ignoreList->Put()->Set( line );
	    line << SLASH << ELLIPSE;
	    ignoreList->Put()->Set( line );
	}
}

void
Ignore::Insert( StrArray *subList, const char *ignore, const char *cwd )
{
	StrBuf buf;
	StrBuf buf2;
	const char *lastChar = cwd + strlen( cwd ) - 1;
	char *terminating = (char *)SLASH;

	int reverse = ( *ignore == '!' );
	int isWild = strchr( ignore, '*' ) != 0;

	if( strstr( ignore, "*****" ) || strstr( ignore, "..." ) )
	    buf << "### SENSELESS JUXTAPOSITION ";

	if( reverse )
	{
	    buf << "!";
	    ignore++;
	}

	buf << cwd;
	
	if( *lastChar != *terminating )
	    buf << SLASH;

	// Non wildcard, assume directory

	if( !isWild || *ignore != '*' )
	{
	    buf2 << buf;
	    buf << ignore;
	    subList->Put()->Set( buf );
	    buf2 << ELLIPSE << SLASH << ignore;
	    subList->Put()->Set( buf2 );

	    if( isWild )
	        return;

	    buf << SLASH << ELLIPSE;
	    subList->Put()->Set( buf );
	    buf2 << SLASH << ELLIPSE;
	    subList->Put()->Set( buf2 );
	    return;
	}

	buf << ELLIPSE  << ++ignore;
	subList->Put()->Set( buf );
}

int
Ignore::RejectCheck( const StrPtr &path )
{
	char *ignoreFile;

	for( int i = 0; i < ignoreList->Count(); ++i )
	{
	    char *p = ignoreList->Get( i )->Text();

	    if( ( DEBUG_MATCH ) && !strncmp( p, "#FILE ", 6 ) )
	    {
	        ignoreFile = p+6;
	        continue;
	    }

	    int doAdd = ( *p == '!' );

	    if( doAdd )
	        ++p;

	    if( MapTable::Match( StrRef( p ), path ) )
	    {
	        if( DEBUG_MATCH )
	            p4debug.printf(
	                "\n\tfile[%s]\n\tmatch[%s%s]%s\n\tignore[%s]\n\n",
	                path.Text(), doAdd ? "+" : "-", p, 
	                doAdd ? "KEEP" : "REJECT", ignoreFile );
	        return doAdd ? 0 : 1;
	    }
	}

	return 0;
}

