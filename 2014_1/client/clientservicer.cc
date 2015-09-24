/*
 * Copyright 1995, 2001 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# ifdef USE_EBCDIC
# define NEED_EBCDIC
# endif

# include <stdhdrs.h>

# include <strbuf.h>
# include <strdict.h>
# include <strops.h>
# include <strarray.h>
# include <strtable.h>
# include <error.h>
# include <mapapi.h>
# include <handler.h>
# include <rpc.h>
# include <md5.h>
# include <i18napi.h>
# include <charcvt.h>
# include <transdict.h>
# include <ignore.h>
# include <debug.h>
# include <tunable.h>

# include <p4tags.h>
# include <msgclient.h>
# include <msgsupp.h>

# include <filesys.h>
# include <pathsys.h>
# include <enviro.h>

# include <readfile.h>
# include <diffsp.h>
# include <diffan.h>
# include <diff.h>

# include "clientuser.h"
# include "client.h"
# include "clientprog.h"

# include "clientservice.h"

/*
 * ReconcileHandle - handle reconcile's list of files to skip when adding
 */

class ReconcileHandle : public LastChance {

    public:
			ReconcileHandle() 
			{ 
			    pathArray = new StrArray;
			    delCount = 0; 
			}
			~ReconcileHandle() 
			{ 
			    delete pathArray; 
			}

			StrArray *pathArray;
			int delCount;
} ;

void
clientReconcileFlush( Client *client, Error *e )
{
	// Delete the client's reconcile handle

	StrRef skipAdd( "skipAdd" );
	ReconcileHandle *recHandle =
			(ReconcileHandle *)client->handles.Get( &skipAdd );

	if( recHandle )
	    delete recHandle;
}

/*
 * clientReconcileEdit() -- "inquire" about file, for 'p4 reconcile'
 *
 * This routine performs clientCheckFile's scenario 1 checking, but
 * also saves the list of files that are in the depot so they can be
 * compared to the list of files on the client when reconciling later for add.
 *
 */

void
clientReconcileEdit( Client *client, Error *e )
{
	client->NewHandler();
	StrPtr *clientType = client->GetVar( P4Tag::v_type );
	StrPtr *digest = client->GetVar( P4Tag::v_digest );
	StrPtr *confirm = client->GetVar( P4Tag::v_confirm, e );
	StrPtr *fileSize = client->GetVar( P4Tag::v_fileSize );
	StrPtr *submitTime = client->GetVar( P4Tag::v_time );

	if( e->Test() && !e->IsFatal() )
	{
	    client->OutputError( e );
	    return;
	}

	const char *status = "exists";
	const char *ntype = clientType ? clientType->Text() : "text";

	// For adding files,  checkSize is a maximum (or use alt type)
	// For flush,  checkSize is an optimization check on binary files.

	offL_t checkSize = fileSize ? fileSize->Atoi64() : 0;

	/*
	 * If we do know the type, we want to know if it's missing.
	 * If it isn't missing and a digest is given, we want to know if
	 * it is the same.
	*/

	FileSys *f = ClientSvc::File( client, e );

	if( e->Test() || !f )
	    return;
	int statVal = f->Stat();

	// Save the list of depot files. We'll diff it against the list of all
	// files on client to find files to add in clientReconcileAdd

	StrRef skipAdd( "skipAdd" );
	ReconcileHandle *recHandle =
			(ReconcileHandle *)client->handles.Get( &skipAdd );

	if( !recHandle )
	{
	    recHandle = new ReconcileHandle;
	    client->handles.Install( &skipAdd, recHandle, e );

	    if( e->Test() )
		return;
	}

	if( !( statVal & ( FSF_SYMLINK|FSF_EXISTS ) ) )
	{
	    status = "missing";
	    recHandle->delCount++;
	} 
	else if ( ( !( statVal & FSF_SYMLINK ) && ( f->IsSymlink() ) ) 
                || ( ( statVal & FSF_SYMLINK ) && !( f->IsSymlink() ) ) ) 
	{
	    recHandle->pathArray->Put()->Set( f->Name() );
	}
	else if( digest )
	{
	    recHandle->pathArray->Put()->Set( f->Name() );
	    if( !checkSize || checkSize == f->GetSize() )
	    {
		StrBuf localDigest;
		f->Translator( ClientSvc::XCharset( client, FromClient ) );

		// Bypass expensive digest computation with -m unless the
		// local file is newer than the submit time. 

		if( !submitTime ||
		    ( submitTime && ( f->StatModTime() > submitTime->Atoi()) ) )
		{
		    f->Digest( &localDigest, e );

		    if( !e->Test() && !localDigest.XCompare( *digest ) )
			status = "same";
		}
		else if( submitTime )
		    status = "same";
	    }

	    // If we can't read the file (for some reason -- wrong type?)
	    // we consider the files different.

	    e->Clear();
	}

	delete f;

	// tell the server 

	client->SetVar( P4Tag::v_type, ntype );
	client->SetVar( P4Tag::v_status, status );
	client->Confirm( confirm );

	// Report non-fatal error and clear it.

	client->OutputError( e );
}

void
clientTraverseDirs( Client *client, const char *dir, int traverse,
		    int noIgnore, MapApi *map, StrArray *files, 
		    StrArray *sizes, Error *e )
{
	// Return all files in dir, and optionally traverse dirs in dir,
	// while checking each file against map before returning it

	// Scan the directory.

	FileSys *f = client->GetUi()->File( FST_BINARY );
	f->SetContentCharSetPriv( client->content_charset );
	f->Set( StrRef( dir ) );
	int fstat = f->Stat();

	Ignore *ignore = client->GetIgnore();
	StrPtr ignored = client->GetIgnoreFile();
	StrBuf from;
	StrBuf to;
	CharSetCvt *cvt = ( (TransDict *)client->transfname )->ToCvt();
	const char *fileName;

	// Use server case-sensitivity rules to find files to add

	from.SetCaseFolding( client->protocolNocase );

	// With unicode server and client using character set, we need
	// to send files back as utf8.

	if( client != client->translated )
	    fileName = cvt->FastCvt( f->Name(), strlen(f->Name()), 0 );
	else
	    fileName = f->Name();

	// If this is a file, not a directory, and not to be ignored,
	// save the filename 

	if( !( fstat & FSF_DIRECTORY ) )
	{
	    if( ( fstat & FSF_EXISTS ) || ( fstat & FSF_SYMLINK ) )
	    {
		if( noIgnore || !ignore->Reject( StrRef(f->Name()), ignored ) )
		{
		    files->Put()->Set( fileName );
		    sizes->Put()->Set( StrNum( f->GetSize() ) );
		}
	    }
	    delete f;
	    return;
	}

	// If this is a symlink to a directory, and not to be ignored,
	// return filename and quit

	if( ( fstat & FSF_SYMLINK ) && ( fstat & FSF_DIRECTORY ) )
	{
	    if( noIgnore || !ignore->Reject( StrRef(f->Name()), ignored ) )
	    {
		files->Put()->Set( fileName );
		sizes->Put()->Set( StrNum( f->GetSize() ) );
	    }
	    delete f;
	    return;
	}

	// This is a directory to be scanned.

	StrArray *a = f->ScanDir( e );

	if( e->Test() )
	{
	    // report error but keep moving

	    delete f;
	    client->OutputError( e );
	    return;
	}

	a->Sort(0);

	// PathSys for concatenating dir and local path,
	// to get full path

	PathSys *p = PathSys::Create();
	p->SetCharSet( f->GetCharSetPriv() );

	// For each directory entry.

	for( int i = 0; i < a->Count(); i++ )
	{
	    // Check mapping, ignore files before sending file or symlink back

	    p->SetLocal( StrRef( dir ), *a->Get(i) );
	    f->Set( *p );
	    int stat = f->Stat();

	    if( client != client->translated )
		fileName = cvt->FastCvt( f->Name(), strlen(f->Name()) );
	    else
		fileName = f->Name();

	    if( stat & FSF_DIRECTORY )
	    {
		if( stat & FSF_SYMLINK )
		{
		    from.Set( fileName );
		    from << "/";

		    if( !map->Translate( from, to, MapLeftRight ) )
			continue;

		    if( noIgnore || !ignore->Reject( StrRef(f->Name()),ignored))
		    {
			files->Put()->Set( fileName );
			sizes->Put()->Set( StrNum( f->GetSize() ) );
		    }
		}
		else if( traverse )
		    clientTraverseDirs( client, f->Name(), traverse, noIgnore,
					map, files, sizes, e );
	    }
	    else if( ( stat & FSF_EXISTS ) || ( stat & FSF_SYMLINK ) )
	    {
		from.Set( fileName );
		if( !map->Translate( from, to, MapLeftRight ) )
		    continue;

		if( noIgnore || !ignore->Reject( StrRef(f->Name()), ignored ) )
		{
		    files->Put()->Set( fileName );
		    sizes->Put()->Set( StrNum( f->GetSize() ) );
		}
	    }
	}

	delete p;
	delete a;
	delete f;
}

void
clientReconcileAdd( Client *client, Error *e )
{
	/*
	 * Reconcile add confirm
	 *
	 * Scans the directory (local syntax) and returns
	 * files in the directory using the full path.  This
	 * differs from clientScanDir in that it returns full
	 * paths, supports traversing subdirectories, and checks
	 * against a mapTable.
	 */

	client->NewHandler();
	StrPtr *dir = client->transfname->GetVar( P4Tag::v_dir, e );
	StrPtr *confirm = client->GetVar( P4Tag::v_confirm, e );
	StrPtr *traverse = client->GetVar( "traverse" );
	StrPtr *skipIgnore = client->GetVar( "skipIgnore" );
	StrPtr *mapItem;

	if( e->Test() )
	    return;

	MapApi *map = new MapApi;
	StrArray *files = new StrArray();
	StrArray *sizes = new StrArray();

	// Construct a MapTable object from the strings passed in by server

	for( int i = 0; mapItem = client->GetVar( StrRef("mapTable"), i ); i++)
	{
	    MapType m;
	    int j;
	    char *c = mapItem->Text();
	    switch( *c )
	    {
	    case '-': m = MapExclude; j = 1; break;
	    case '+': m = MapOverlay; j = 1; break;
	    default:  m = MapInclude; j = 0; break;
	    }
	    map->Insert( StrRef( c+j ), StrRef( c+j ), m );
	}

	clientTraverseDirs( client, dir->Text(), traverse != 0, skipIgnore != 0,
			    map, files, sizes, e );
	delete map;

	// If we have a list of files we know are in the depot already,
	// filter them out of our list of files to add

	StrRef skipAdd( "skipAdd" );
	ReconcileHandle *recHandle =
			(ReconcileHandle *)client->handles.Get( &skipAdd );

	if( recHandle )
	{
	    recHandle->pathArray->Sort(0);

	    int i1 = 0, i2 = 0, i0 = 0, l = 0;

	    while( i1 < files->Count() )
	    {
		if( i2 >= recHandle->pathArray->Count())
		    l = -1;
		else
		    l = files->Get( i1 )->SCompare( 
		        *recHandle->pathArray->Get( i2 ) );

		if( !l )
		{
		    ++i1;
		    ++i2;
		}
		else if( l < 0 )
		{
		    client->SetVar( P4Tag::v_file, i0, *files->Get( i1 ) );
		    if( recHandle->delCount )
		    {
			// Deleted files?  Send filesize info so the
			// server can try to pair up moves.

			client->SetVar( P4Tag::v_fileSize, 
					i0, *sizes->Get( i1 ) );
		    }
		    ++i0;
		    ++i1;
		}
		else
		{
		    ++i2;
		}
	    }
	}
	else
	{
	    for( int j = 0; j < files->Count(); j++ )
		client->SetVar( P4Tag::v_file, j, *files->Get(j) );
	}

	client->Confirm( confirm );
	delete files;
	delete sizes;
}

void
clientExactMatch( Client *client, Error *e )
{
	// Compare existing digest to list of
	// new client files, return match, or not.

	// Args:
	// type     = existing file type (clientpart)
	// digest   = existing file digest
	// fileSize = existing file size
	// charSet  = existing file charset
	// toFileN  = new file local path
	// indexN   = new file index
	// confirm  = return callback
	//
	// Return:
	// toFile   = exact match
	// index    = exact match

	client->NewHandler();
	StrPtr *clientType = client->GetVar( P4Tag::v_type );
	StrPtr *digest = client->GetVar( P4Tag::v_digest );
	StrPtr *fileSize = client->GetVar( P4Tag::v_fileSize );
	StrPtr *confirm = client->GetVar( P4Tag::v_confirm, e );

	if( e->Test() )
	    return;

	StrPtr *matchFile = 0;
	StrPtr *matchIndex = 0;
	FileSys *f = 0;

	for( int i = 0 ; 
	     client->GetVar( StrRef( P4Tag::v_toFile ), i ) ;
	     i++ )
	{
	    delete f;

	    StrVarName path = StrVarName( StrRef( P4Tag::v_toFile ), i );
	    f = ClientSvc::FileFromPath( client, path.Text(), e );

	    // If we encounter a problem with a file, we just don't return
	    // it as a match.  No need to blat out lots of errors.

	    if( e->Test() || !f )
	    {
		e->Clear();
		continue;
	    }

	    int statVal = f->Stat();

	    // Skip files that are symlinks when we
	    // aren't looking for symlinks.

	    if( ( !( statVal & ( FSF_SYMLINK|FSF_EXISTS ) ) )
		|| ( !( statVal & FSF_SYMLINK ) && ( f->IsSymlink() ) )  
                || ( ( statVal & FSF_SYMLINK ) && !( f->IsSymlink() ) ) )
		continue;

	    if( !digest )
	        continue;

	    StrBuf localDigest;
	    f->Translator( ClientSvc::XCharset( client, FromClient ) );
	    f->Digest( &localDigest, e );

	    if( e->Test() )
	    {
		e->Clear();
		continue;
	    }

	    if( !localDigest.XCompare( *digest ) )
	    {
		matchFile  = client->GetVar( StrRef(P4Tag::v_toFile), i );
		matchIndex = client->GetVar( StrRef(P4Tag::v_index), i );
		break; // doesn't get any better
	    }
	}

	delete f;

	if( matchFile && matchIndex )
	{
	    client->SetVar( P4Tag::v_toFile, matchFile );
	    client->SetVar( P4Tag::v_index, matchIndex );
	}

	client->Confirm( confirm );
}

void
clientOpenMatch( Client *client, ClientFile *f, Error *e )
{
	// Follow on from clientOpenFile, not called by server directly.

	// Grab RPC vars and attach them to the file handle so that
	// clientCloseMatch can use them for N-way diffing.

	StrPtr *fromFile = client->GetVar( P4Tag::v_fromFile, e );
	StrPtr *key	 = client->GetVar( P4Tag::v_key, e );
	StrPtr *flags    = client->GetVar( P4Tag::v_diffFlags );
	if( e->Test() )
	    return;
	
	f->matchDict = new StrBufDict;
	f->matchDict->SetVar( P4Tag::v_fromFile, fromFile );
	f->matchDict->SetVar( P4Tag::v_key, key );
	if( flags )
	    f->matchDict->SetVar( P4Tag::v_diffFlags, flags );
	for( int i = 0 ; ; i++ )
	{
	    StrPtr *index = client->GetVar( 
		    StrRef( P4Tag::v_index ),  i );
	    StrPtr *file  = client->GetVar( 
		    StrRef( P4Tag::v_toFile ), i );
	    if( !index || !file )
		break;
	    f->matchDict->SetVar( 
		   StrRef( P4Tag::v_index ),  i, *index );
	    f->matchDict->SetVar( 
		   StrRef( P4Tag::v_toFile ), i, *file );
	}
}

void
clientCloseMatch( Client *client, ClientFile *f1, Error *e )
{
	// Follow on from clientCloseFile, not called by server directly.

	// Compare temp file to existing client files.  Figure out the
	// best match, along with a quantitative measure of how good
	// the match was (lines matched vs total lines).  Stash it
	// in the handle so clientAckMatch can report it back.

	if( !f1->matchDict )
	{
	    e->Set( MsgSupp::NoParm ) << "clientCloseMatch";
	    return;
	}

	StrPtr *matchFile = 0;
	StrPtr *matchIndex = 0;

	StrPtr *fname;
	FileSys *f2 = 0;
	DiffFlags flags;
	if( StrPtr* diffFlags = f1->matchDict->GetVar( P4Tag::v_diffFlags ) )
	    flags.Init( diffFlags );

	int bestNum = 0;
	int bestSame = 0; 
	int totalLines = 0;

	for( int i = 0 ; 
	     fname = f1->matchDict->GetVar( StrRef( P4Tag::v_toFile ), i ) ;
	     i++ )
	{
	    delete f2;

	    f2 = client->GetUi()->File( f1->file->GetType() );
	    f2->SetContentCharSetPriv( f1->file->GetContentCharSetPriv() );
	    f2->Set( *fname );

	    if( e->Test() || !f2 )
	    {
		// don't care
		e->Clear();
		continue;
	    }

	    Sequence s1( f1->file, flags, e );
	    Sequence s2( f2,       flags, e );
	    if ( e->Test() )
	    {
		// still don't care
		e->Clear();
		continue;
	    }

	    DiffAnalyze diff( &s1, &s2 );

	    int same = 0;
	    for( Snake *s = diff.GetSnake() ; s ; s = s->next )
	    {
		same += ( s->u - s->x );
		if( s->u > totalLines )
		    totalLines = s->u;
	    }

	    if( same > bestSame )
	    {
		bestNum = i;
		bestSame = same;
	    }
	}

	delete f2;
	f1->file->Close( e );

	totalLines++; // snake lines start at zero

	if( bestSame )
	{
	    f1->matchDict->SetVar( P4Tag::v_index,
		f1->matchDict->GetVar( StrRef( P4Tag::v_index ), bestNum ) );
	    f1->matchDict->SetVar( P4Tag::v_toFile, 
		f1->matchDict->GetVar( StrRef( P4Tag::v_toFile ), bestNum ) );

	    f1->matchDict->SetVar( P4Tag::v_lower, bestSame );
	    f1->matchDict->SetVar( P4Tag::v_upper, totalLines );
	}

	// clientAckMatch will send this back
}

void
clientAckMatch( Client *client, Error *e )
{
	StrPtr *handle = client->GetVar( P4Tag::v_handle, e );
	StrPtr *confirm = client->GetVar( P4Tag::v_confirm, e );
	
	if( e->Test() )
	    return;

	// Get handle.

	ClientFile *f = (ClientFile *)client->handles.Get( handle, e );

	if( e->Test() )
	    return;

	// Fire everything back.

	StrPtr *fromFile = f->matchDict->GetVar( P4Tag::v_fromFile );
	StrPtr *key	 = f->matchDict->GetVar( P4Tag::v_key );
	StrPtr *toFile   = f->matchDict->GetVar( P4Tag::v_toFile );
	StrPtr *index    = f->matchDict->GetVar( P4Tag::v_index );
	StrPtr *lower    = f->matchDict->GetVar( P4Tag::v_lower );
	StrPtr *upper    = f->matchDict->GetVar( P4Tag::v_upper );

	if( fromFile && key )
	{
	    client->SetVar( P4Tag::v_fromFile,	fromFile );
	    client->SetVar( P4Tag::v_key,	key );
	}
	else
	{
	    e->Set( MsgSupp::NoParm ) << "fromFile/key";
	    return;
	}
	if( toFile && index && lower && upper )
	{
	    client->SetVar( P4Tag::v_toFile, toFile );
	    client->SetVar( P4Tag::v_index,  index );
	    client->SetVar( P4Tag::v_lower,  lower );
	    client->SetVar( P4Tag::v_upper,  upper );
	}

	client->Confirm( confirm );
	delete f;	    
}
