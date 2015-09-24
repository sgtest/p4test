/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msgclient.cc - definitions of errors for client subsystem.
 *
 * Note:
 *
 * Never re-use an error code value,  these may have already been 
 * translated and while deleting the error is OKAY using it for a 
 * different error is not.
 *
 * Its okay to add a message in the middle of the file.
 *
 * When adding a new error make sure its greater than the current high
 * value and update the following number:
 *
 * Current high value for a MsgClient error code is: 42
 */

# include <error.h>
# include <errornum.h>
# include "msgclient.h"

ErrorId MsgClient::Connect             = { ErrorOf( ES_CLIENT, 1, E_FAILED, EV_COMM, 0 ), "Connect to server failed; check $P4PORT." } ;
ErrorId MsgClient::Fatal               = { ErrorOf( ES_CLIENT, 2, E_FATAL, EV_CLIENT, 0 ), "Fatal client error; disconnecting!" } ;
ErrorId MsgClient::BadFlag             = { ErrorOf( ES_CLIENT, 3, E_FAILED, EV_USAGE, 0 ), "Unknown flag.  Try ? for help." } ;
ErrorId MsgClient::ClobberFile         = { ErrorOf( ES_CLIENT, 4, E_FAILED, EV_CLIENT, 1 ), "Can't clobber writable file %file%" } ;
ErrorId MsgClient::MkDir               = { ErrorOf( ES_CLIENT, 5, E_FAILED, EV_CLIENT, 1 ), "can't create directory for %file%" } ;
ErrorId MsgClient::Eof                 = { ErrorOf( ES_CLIENT, 6, E_FAILED, EV_CLIENT, 0 ), "EOF reading terminal." } ;
ErrorId MsgClient::FileOpenError       = { ErrorOf( ES_CLIENT, 40, E_FAILED, EV_CLIENT, 0 ), "Error opening file." } ;
ErrorId MsgClient::CantEdit            = { ErrorOf( ES_CLIENT, 7, E_FAILED, EV_CLIENT, 1 ), "%type% - can't edit this type of file!" } ;
ErrorId MsgClient::NoMerger            = { ErrorOf( ES_CLIENT, 8, E_FAILED, EV_CLIENT, 0 ), "No merge program specified with $P4MERGE or $MERGE." } ;
ErrorId MsgClient::ToolServer2         = { ErrorOf( ES_CLIENT, 10, E_FAILED, EV_CLIENT, 0 ), "Could not start another ToolServer.  Tool is running under ToolServer." } ;
ErrorId MsgClient::ToolServer          = { ErrorOf( ES_CLIENT, 11, E_FAILED, EV_CLIENT, 0 ), "Could not start ToolServer." } ;
ErrorId MsgClient::ToolCmdCreate       = { ErrorOf( ES_CLIENT, 12, E_FAILED, EV_CLIENT, 0 ), "Could not create command to send to ToolServer." } ;
ErrorId MsgClient::ToolCmdSend         = { ErrorOf( ES_CLIENT, 13, E_FAILED, EV_CLIENT, 0 ), "Could not send command to ToolServer." } ;
ErrorId MsgClient::Memory              = { ErrorOf( ES_CLIENT, 14, E_FATAL, EV_CLIENT, 0 ), "Out of memory!" } ;
ErrorId MsgClient::CantFindApp         = { ErrorOf( ES_CLIENT, 15, E_FATAL, EV_CLIENT, 0 ), "Could not find application!" } ;
ErrorId MsgClient::BadSignature        = { ErrorOf( ES_CLIENT, 16, E_FATAL, EV_CLIENT, 0 ), "EDITOR_SIGNATURE must be 4 characters exactly!" } ;
ErrorId MsgClient::BadMarshalInput     = { ErrorOf( ES_CLIENT, 29, E_FAILED, EV_CLIENT, 0 ), "Invalid marshalled data supplied as input." } ;
ErrorId MsgClient::ResolveManually     = { ErrorOf( ES_CLIENT, 18, E_INFO, EV_CLIENT, 0 ), "Must resolve manually." } ;
ErrorId MsgClient::NonTextFileMerge    = { ErrorOf( ES_CLIENT, 19, E_INFO, EV_CLIENT, 0 ), "Non-text file merge." } ;
ErrorId MsgClient::MergeMsg2           = { ErrorOf( ES_CLIENT, 28, E_INFO, EV_CLIENT, 4 ), "Non-text diff: %yours% yours + %theirs% theirs + %both% both + %conflicting% conflicting" } ;
ErrorId MsgClient::MergeMsg3           = { ErrorOf( ES_CLIENT, 20, E_INFO, EV_CLIENT, 4 ), "Diff chunks: %yours% yours + %theirs% theirs + %both% both + %conflicting% conflicting" } ;
ErrorId MsgClient::MergeMsg32          = { ErrorOf( ES_CLIENT, 21, E_INFO, EV_CLIENT, 1 ), "Diff chunks: %chunks% between yours and theirs (no common base)" } ;
ErrorId MsgClient::MergePrompt         = { ErrorOf( ES_CLIENT, 22, E_INFO, EV_CLIENT, 1 ), "Accept(a) Edit(e) Diff(d) Merge (m) Skip(s) Help(?) [%mergeDefault%]: " };
ErrorId MsgClient::MergePrompt2        = { ErrorOf( ES_CLIENT, 26, E_INFO, EV_CLIENT, 1 ), "Accept (at/ay) Skip (s) Help (?) [%mergeDefault%]: " };
ErrorId MsgClient::MergePrompt2Edit    = { ErrorOf( ES_CLIENT, 27, E_INFO, EV_CLIENT, 1 ), "Accept (at/ay) Edit (et/ey) Skip (s) Help (?) [%mergeDefault%]: " };
ErrorId MsgClient::ConfirmMarkers      = { ErrorOf( ES_CLIENT, 23, E_INFO, EV_CLIENT, 0 ), "There are still change markers: confirm accept (y/n)? " };
ErrorId MsgClient::ConfirmEdit         = { ErrorOf( ES_CLIENT, 24, E_INFO, EV_CLIENT, 0 ), "Use 'ae' to indicate original edits: confirm accept merge (y/n)? " };
ErrorId MsgClient::Confirm             = { ErrorOf( ES_CLIENT, 25, E_INFO, EV_CLIENT, 0 ), "This overrides your changes: confirm accept (y/n)? " };
ErrorId MsgClient::CheckFileAssume     = { ErrorOf( ES_CLIENT, 30, E_INFO, EV_CLIENT, 3 ), "%file% - %type%, assuming %type2%." };
ErrorId MsgClient::CheckFileAssumeWild = { ErrorOf( ES_CLIENT, 41, E_INFO, EV_CLIENT, 4 ), "%file% - %type%, assuming %type2% (%modified%)." };
ErrorId MsgClient::CheckFileSubst      = { ErrorOf( ES_CLIENT, 31, E_INFO, EV_CLIENT, 3 ), "%file% - using %type% instead of %type2%" };
ErrorId MsgClient::CheckFileCant       = { ErrorOf( ES_CLIENT, 32, E_INFO, EV_CLIENT, 2 ), "%file% - %type% file can't be added." };
ErrorId MsgClient::FileExists          = { ErrorOf( ES_CLIENT, 34, E_FAILED, EV_CLIENT, 1 ), "%file% - can't overwrite existing file." };
ErrorId MsgClient::NoSuchFile          = { ErrorOf( ES_CLIENT, 35, E_FAILED, EV_CLIENT, 1 ), "%file% - file does not exist." };
ErrorId MsgClient::LoginPrintTicket    = { ErrorOf( ES_CLIENT, 36, E_INFO, EV_NONE, 1 ), "%ticket%" } ;
ErrorId MsgClient::DigestMisMatch      = { ErrorOf( ES_CLIENT, 37, E_FAILED, EV_CLIENT, 3 ), "%clientFile% corrupted during transfer (or bad on the server) %clientDigest% vs %serverDigest%" } ;
ErrorId MsgClient::NotUnderPath        = { ErrorOf( ES_CLIENT, 38, E_FAILED, EV_CLIENT, 2 ), "File %clientFile% is not inside permitted filesystem path %clientPath%" } ;
ErrorId MsgClient::LineTooLong         = { ErrorOf( ES_CLIENT, 39, E_FAILED, EV_CLIENT, 1 ), "Command line too long. Maximum length is %maxLineLen%. This length can be increased by setting filesys.bufsize in P4CONFIG or using -v." };
ErrorId MsgClient::UnknownCharset      = { ErrorOf( ES_CLIENT, 42, E_FATAL, EV_CLIENT, 1 ), "Unknown P4CHARSET %charset%." };

// ErrorId graveyard: retired/deprecated ErrorIds.

ErrorId MsgClient::ZCResolve           = { ErrorOf( ES_CLIENT, 33, E_FAILED, EV_COMM, 2 ), "Zeroconf resolved '%name%' to '%port%'." } ; // DEPRECATED 2013.1 removed ZeroConf
