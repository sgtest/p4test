/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msgos.cc - definitions of errors for zlib C++ interface
 *
 * Note:
 *
 * Never re-use an error code value,  these may have already been 
 * translated, so using it for a different error is not OK.
 *
 * ErrorIds which are no longer used should be moved to the bottom
 * of the list, with a trailing comment like this: // DEPRECATED.
 * We keep these to maintain compatibility between newer api clients
 * and older servers which send old ErrorIds.
 *
 * Its okay to add a message in the middle of the file.
 *
 * When adding a new error make sure its greater than the current high
 * value and update the following number:
 *
 * Current high value for a MsgOs error code is: 11
 */

# include <error.h>
# include <errornum.h>
# include <msgos.h>

ErrorId MsgOs::Sys                     = { ErrorOf( ES_OS, 1, E_FAILED, EV_FAULT, 3 ), "%operation%: %arg%: %errmsg%" } ;
ErrorId MsgOs::Sys2                    = { ErrorOf( ES_OS, 9, E_FAILED, EV_FAULT, 3 ), "%operation2%: %arg2%: %errmsg2%" } ;  // like Sys but different parm names
ErrorId MsgOs::SysUn                   = { ErrorOf( ES_OS, 2, E_FAILED, EV_FAULT, 3 ), "%operation%: %arg%: unknown errno %errno%" } ;
ErrorId MsgOs::SysUn2                  = { ErrorOf( ES_OS, 10, E_FAILED, EV_FAULT, 3 ), "%operation2%: %arg2%: unknown errno %errno2%" } ;  // like SysUn but different parm names
ErrorId MsgOs::ChmodBetrayal           = { ErrorOf( ES_OS, 11, E_FATAL, EV_FAULT, 4 ), "File mode modification failed! File %oldname% was successfully renamed to %newname% but the file permissions were not correctly changed to read-only. The current permissions are %perms% and the file inode number is %inode%." } ;

# ifdef OS_NT

ErrorId MsgOs::Net                     = { ErrorOf( ES_OS, 3, E_FAILED, EV_COMM, 3 ), "%operation%: %arg%: %errmsg%" } ;
ErrorId MsgOs::NetUn                   = { ErrorOf( ES_OS, 4, E_FAILED, EV_COMM, 3 ), "%operation%: %arg%: unknown network error %errno%" } ;

# endif                         

ErrorId MsgOs::TooMany                 = { ErrorOf( ES_OS, 5, E_FATAL, EV_FAULT, 1 ), "%handle%: too many handles!" } ;
ErrorId MsgOs::Deleted                 = { ErrorOf( ES_OS, 6, E_FATAL, EV_FAULT, 1 ), "%handle%: deleted handled!" } ;
ErrorId MsgOs::NoSuch                  = { ErrorOf( ES_OS, 7, E_FATAL, EV_FAULT, 1 ), "%handle%: no such handle!" } ;

ErrorId MsgOs::EmptyFork               = { ErrorOf( ES_OS, 8, E_FAILED, EV_CLIENT, 1 ), "Resource fork for %file% from server is empty." } ;

// ErrorId graveyard: retired/deprecated ErrorIds. 
