/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msgserver.cc - definitions of errors for server subsystem.
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
 * Current high value for a MsgServer error code is: 676
 * Nimble messages begin at 700, and currently are : 715
 */
# include <error.h>
# include <errornum.h>
# include "msgserver.h"

ErrorId MsgServer::LbrCheckout         = { ErrorOf( ES_SERVER, 1, E_FAILED, EV_FAULT, 1 ), "Librarian checkout %lbrFile% failed." } ;
ErrorId MsgServer::LbrDiff             = { ErrorOf( ES_SERVER, 2, E_FAILED, EV_FAULT, 1 ), "Librarian diff %lbrFile% failed." } ;
ErrorId MsgServer::LbrDigest           = { ErrorOf( ES_SERVER, 3, E_FAILED, EV_FAULT, 1 ), "Librarian digest %lbrFile% failed." } ;
ErrorId MsgServer::LbrFileSize         = { ErrorOf( ES_SERVER, 4, E_FAILED, EV_FAULT, 1 ), "Librarian filesize %lbrFile% failed." } ;
ErrorId MsgServer::LbrCheckin          = { ErrorOf( ES_SERVER, 5, E_FAILED, EV_FAULT, 1 ), "Librarian checkin %lbrFile% failed." } ;
ErrorId MsgServer::LbrMerge            = { ErrorOf( ES_SERVER, 6, E_FAILED, EV_FAULT, 0 ), "Librarian merge failed." } ;
ErrorId MsgServer::LbrNoTrigger        = { ErrorOf( ES_SERVER, 390, E_FAILED, EV_ADMIN, 1 ), "No archive trigger defined for %lbrFile%." } ;
ErrorId MsgServer::BadRoot             = { ErrorOf( ES_SERVER, 7, E_FAILED, EV_ADMIN, 0 ), "Root directory (set with $P4ROOT or -r flag) invalid." } ;
ErrorId MsgServer::BadIPAddr           = { ErrorOf( ES_SERVER, 8, E_FAILED, EV_ADMIN, 0 ), "Licensing error -- invalid server IP address." } ;
ErrorId MsgServer::GotUnlocked         = { ErrorOf( ES_SERVER, 9, E_FAILED, EV_FAULT, 1 ), "%depotFile% became unlocked!" } ;
ErrorId MsgServer::GotLocked           = { ErrorOf( ES_SERVER, 10, E_FAILED, EV_FAULT, 3 ), "%depotFile% was just locked by %user% on %client%!" } ;
ErrorId MsgServer::NoInteg             = { ErrorOf( ES_SERVER, 11, E_FATAL, EV_FAULT, 1 ), "%depotFile% missing integration record!" } ;
ErrorId MsgServer::GotUnresolved       = { ErrorOf( ES_SERVER, 13, E_FATAL, EV_FAULT, 1 ), "%toFile% got unresolved!" } ;
ErrorId MsgServer::CantOpen            = { ErrorOf( ES_SERVER, 14, E_FATAL, EV_FAULT, 2 ), "%depotFile% - can't %action% file!" } ;
ErrorId MsgServer::NoDumpName          = { ErrorOf( ES_SERVER, 15, E_FAILED, EV_USAGE, 0 ), "Must specify dump file." } ;
ErrorId MsgServer::DumpNameIsADbName   = { ErrorOf( ES_SERVER, 621, E_FAILED, EV_USAGE, 1 ), "Cannot specify db name %dbname% as a dump file name." } ;
ErrorId MsgServer::NoCkptName          = { ErrorOf( ES_SERVER, 16, E_FAILED, EV_USAGE, 0 ), "Must specify checkpoint/journal files." } ;
ErrorId MsgServer::BadJnlFlag          = { ErrorOf( ES_SERVER, 17, E_FAILED, EV_USAGE, 0 ), "Unknown journaling flag.  Try 'c', 'd', 'j' or 'r'." } ;
ErrorId MsgServer::BadExtraFlag        = { ErrorOf( ES_SERVER, 18, E_FAILED, EV_USAGE, 0 ), "Unknown -x operation.  Try 'f', 'i', 'u', 'v', or 'x'." } ;
ErrorId MsgServer::ExtraIDUsage        = { ErrorOf( ES_SERVER, 567, E_FAILED, EV_USAGE, 0 ), "Usage: p4d -xD [ serverID ]" } ;
ErrorId MsgServer::ServerIDAlreadySet  = { ErrorOf( ES_SERVER, 568, E_FAILED, EV_USAGE, 1 ), "Server already has a server ID: %serverID%" } ;
ErrorId MsgServer::NoServerID          = { ErrorOf( ES_SERVER, 569, E_FAILED, EV_USAGE, 0 ), "Server does not yet have a server ID." } ;
ErrorId MsgServer::ServerID            = { ErrorOf( ES_SERVER, 570, E_INFO, EV_NONE, 1 ), "Server ID: %serverID%" } ;
ErrorId MsgServer::MetaDumpFailed      = { ErrorOf( ES_SERVER, 19, E_FAILED, EV_FAULT, 1 ), "%file%: metadata dump failed" } ;
ErrorId MsgServer::SkippedJnls	       = { ErrorOf( ES_SERVER, 368, E_FAILED, EV_ADMIN, 1 ), "%count% out of sequence journals were not replayed" } ;

ErrorId MsgServer::Password982         = { ErrorOf( ES_SERVER, 20, E_FAILED, EV_UPGRADE, 0 ), "You need a 98.2 or newer client to access as a password-protected user." } ;
ErrorId MsgServer::BadPassword         = { ErrorOf( ES_SERVER, 21, E_FAILED, EV_CONFIG, 0 ), "Perforce password (P4PASSWD) invalid or unset." } ;
ErrorId MsgServer::MustSetPassword     = { ErrorOf( ES_SERVER, 307, E_FAILED, EV_USAGE, 0 ), "Password must be set before access can be granted." } ;
ErrorId MsgServer::WeakPassword        = { ErrorOf( ES_SERVER, 321, E_FAILED, EV_USAGE, 0 ), "The security level of this server requires the password to be reset." } ;
ErrorId MsgServer::TicketOnly          = { ErrorOf( ES_SERVER, 322, E_FAILED, EV_USAGE, 0 ), "Password not allowed at this server security level, use 'p4 login'." } ;
ErrorId MsgServer::Unicode             = { ErrorOf( ES_SERVER, 22, E_FAILED, EV_CONFIG, 0 ), "Unicode server permits only unicode enabled clients." } ;
ErrorId MsgServer::Unicode2            = { ErrorOf( ES_SERVER, 23, E_FAILED, EV_CONFIG, 0 ), "Unicode clients require a unicode enabled server." } ;
ErrorId MsgServer::OperationFailed     = { ErrorOf( ES_SERVER, 24, E_FAILED, EV_FAULT, 1 ), "Operation: %command%" } ;
ErrorId MsgServer::OperationDate       = { ErrorOf( ES_SERVER, 25, E_FAILED, EV_FAULT, 1 ), "Date %date%:" } ;
ErrorId MsgServer::BadCommand          = { ErrorOf( ES_SERVER, 26, E_FAILED, EV_USAGE, 0 ), "Unknown command.  Try 'p4 help' for info." } ;
ErrorId MsgServer::IllegalCommand      = { ErrorOf( ES_SERVER, 329, E_FAILED, EV_USAGE, 0 ), "Illegal command usage.  Try 'p4 help' for info." } ;
ErrorId MsgServer::HandshakeFailed     = { ErrorOf( ES_SERVER, 27, E_FAILED, EV_COMM, 0 ), "Handshake failed." } ;
ErrorId MsgServer::ConnectBroken       = { ErrorOf( ES_SERVER, 28, E_FAILED, EV_COMM, 1 ), "Connection from %peerAddress% broken." } ;
ErrorId MsgServer::ClientOpFailed      = { ErrorOf( ES_SERVER, 29, E_FAILED, EV_CLIENT, 0 ), "Client side operation(s) failed.  Command aborted." } ;
ErrorId MsgServer::Usage               = { ErrorOf( ES_SERVER, 30, E_FAILED, EV_USAGE, 1 ), "Usage: %usage%" } ;
ErrorId MsgServer::OldDiffClient       = { ErrorOf( ES_SERVER, 31, E_FAILED, EV_UPGRADE, 0 ), "Client doesn't have necessary support for diff -s." } ;
ErrorId MsgServer::OldReconcileClient       = { ErrorOf( ES_SERVER, 583, E_FAILED, EV_UPGRADE, 0 ), "Client doesn't have necessary support for reconcile." } ;
ErrorId MsgServer::Jobs982Win          = { ErrorOf( ES_SERVER, 33, E_FAILED, EV_UPGRADE, 0 ), "Must upgrade to 98.2 p4win to access jobs." } ;
ErrorId MsgServer::No973Wingui         = { ErrorOf( ES_SERVER, 302, E_FAILED, EV_UPGRADE, 0 ), "Must upgrade past 97.3 p4win for this operation." } ;
ErrorId MsgServer::JobsDashS           = { ErrorOf( ES_SERVER, 34, E_FAILED, EV_USAGE, 2 ), "'jobs -s %status%' no longer supported; use 'jobs -e status=%status%." } ;
ErrorId MsgServer::AddDelete           = { ErrorOf( ES_SERVER, 35, E_FAILED, EV_USAGE, 0 ), "Can't add (-a) and delete (-d) at the same time." } ;
ErrorId MsgServer::ZFlagsConflict      = { ErrorOf( ES_SERVER, 537, E_FAILED, EV_USAGE, 0 ), "Must not use both 'z' and 'Z' flags" } ;
ErrorId MsgServer::Password991         = { ErrorOf( ES_SERVER, 36, E_FAILED, EV_UPGRADE, 0 ), "Only 99.1 or later clients support 'p4 passwd'." } ;
ErrorId MsgServer::Password032         = { ErrorOf( ES_SERVER, 310, E_FAILED, EV_UPGRADE, 0 ), "Only 2003.2 or later clients support 'p4 passwd' at this server security level." } ;
ErrorId MsgServer::NoClearText         = { ErrorOf( ES_SERVER, 311, E_FAILED, EV_UPGRADE, 0 ), "This operation is not permitted at this server security level." } ;
ErrorId MsgServer::LoginExpired       = { ErrorOf( ES_SERVER, 312, E_FAILED, EV_ILLEGAL, 0 ), "Your session has expired, please login again." } ;
ErrorId MsgServer::PasswordExpired    = { ErrorOf( ES_SERVER, 455, E_FAILED, EV_ILLEGAL, 0 ), "Your password has expired, please change your password." } ;
ErrorId MsgServer::LoginNotRequired     = { ErrorOf( ES_SERVER, 313, E_INFO, EV_NONE, 0 ), "'login' not necessary, no password set for this user." } ;
ErrorId MsgServer::LoginPrintTicket     = { ErrorOf( ES_SERVER, 314, E_INFO, EV_NONE, 1 ), "%ticket%" } ;
ErrorId MsgServer::LoginUser          = { ErrorOf( ES_SERVER, 325, E_INFO, EV_NONE, 1 ), "User %user% logged in." } ;
ErrorId MsgServer::LoginGoodTill      = { ErrorOf( ES_SERVER, 326, E_INFO, EV_NONE, 4 ), "User %user% ticket expires in %hours% hours %minutes% minutes." } ;
ErrorId MsgServer::LoginNoTicket      = { ErrorOf( ES_SERVER, 327, E_INFO, EV_NONE, 4 ), "User %user% was authenticated by password not ticket." } ;
ErrorId MsgServer::LogoutUser          = { ErrorOf( ES_SERVER, 315, E_INFO, EV_NONE, 1 ), "User %user% logged out." } ;
ErrorId MsgServer::LoggedOut           = { ErrorOf( ES_SERVER, 318, E_FAILED, EV_ILLEGAL, 0 ), "Your session was logged out, please login again." } ;
ErrorId MsgServer::Login032            = { ErrorOf( ES_SERVER, 319, E_FAILED, EV_UPGRADE, 0 ), "Only 2003.2 or later clients support 'p4 login' at this server security level." } ;
ErrorId MsgServer::Login042            = { ErrorOf( ES_SERVER, 335, E_FAILED, EV_UPGRADE, 0 ), "Only 2004.2 or later clients support 'p4 login' for external authentication." } ;
ErrorId MsgServer::Login072            = { ErrorOf( ES_SERVER, 355, E_FAILED, EV_UPGRADE, 0 ), "Only 2007.2 or later clients support 'p4 login' for single sign-on." } ;
ErrorId MsgServer::SSOfailed           = { ErrorOf( ES_SERVER, 356, E_FAILED, EV_UNKNOWN, 1 ), "Single sign-on on client failed: %result%" } ;
ErrorId MsgServer::SSONoEnv            = { ErrorOf( ES_SERVER, 357, E_FAILED, EV_UNKNOWN, 0 ), "Single sign-on on client failed: 'P4LOGINSSO' not set." } ;
ErrorId MsgServer::SSOInvalid        =   { ErrorOf( ES_SERVER, 358, E_FAILED, EV_ILLEGAL, 0 ), "Login invalid." } ;
ErrorId MsgServer::CantAuthenticate    = { ErrorOf( ES_SERVER, 334, E_FAILED, EV_ILLEGAL, 0 ), "Command unavailable: external authentication '%triggerType%' trigger not found." } ;
ErrorId MsgServer::CantChangeOther     = { ErrorOf( ES_SERVER, 336, E_FAILED, EV_ILLEGAL, 0 ), "Cannot change password for another user with external authentication." } ;
ErrorId MsgServer::NoSuchUser          = { ErrorOf( ES_SERVER, 37, E_FAILED, EV_UNKNOWN, 1 ), "User %user% doesn't exist." } ;
ErrorId MsgServer::BadPassword0        = { ErrorOf( ES_SERVER, 38, E_FAILED, EV_ILLEGAL, 0 ), "Password invalid." } ;
ErrorId MsgServer::BadPassword1        = { ErrorOf( ES_SERVER, 39, E_FAILED, EV_ILLEGAL, 0 ), "Passwords don't match." } ;
ErrorId MsgServer::PasswordTooShort2    = { ErrorOf( ES_SERVER, 543, E_FAILED, EV_ILLEGAL, 1 ), "Password should be at least %size% characters in length." } ;
ErrorId MsgServer::PasswordTooLong      = { ErrorOf( ES_SERVER, 527, E_FAILED, EV_ILLEGAL, 1 ), "Password should be no longer than %maxLength% bytes in length." } ;
ErrorId MsgServer::PasswordTooSimple    = { ErrorOf( ES_SERVER, 309, E_FAILED, EV_ILLEGAL, 0 ), "Password should be mixed case or contain non alphabetic characters." } ;
ErrorId MsgServer::NoProxyAuth          = { ErrorOf( ES_SERVER, 369, E_FAILED, EV_ILLEGAL, 1 ), "Authentication from resolved port '%port%' not allowed!" } ;
ErrorId MsgServer::MimAttack            = { ErrorOf( ES_SERVER, 429, E_FAILED, EV_ILLEGAL, 1 ), "Problem with TCP connections between client and server" } ;
ErrorId MsgServer::NoSuppASflag        = { ErrorOf( ES_SERVER, 40, E_FAILED, EV_UPGRADE, 0 ), "Your client doesn't support the -as flag." } ;
ErrorId MsgServer::NoSuppVflag         = { ErrorOf( ES_SERVER, 41, E_FAILED, EV_UPGRADE, 0 ), "Your client doesn't support the -v flag." } ;
ErrorId MsgServer::SubmitFailed        = { ErrorOf( ES_SERVER, 42, E_FAILED, EV_NOTYET, 1 ), "Submit failed -- fix problems above then use 'p4 submit -c %change%'." } ;
ErrorId MsgServer::SubmitShelvedFailed        = { ErrorOf( ES_SERVER, 641, E_FAILED, EV_NOTYET, 1 ), "Submit failed -- fix problems above then use 'p4 submit -e %change%'." } ;
ErrorId MsgServer::CounterWarning      = { ErrorOf( ES_SERVER, 518, E_WARN, EV_NONE, 3 ), "Warning: '%counterName%' counter is now %counterValue%, maximum allowed is %counterMax%" } ;
ErrorId MsgServer::SubmitIsShelved     = { ErrorOf( ES_SERVER, 410, E_FAILED, EV_NOTYET, 1 ), "Change %change% has shelved files --  cannot submit."} ;
ErrorId MsgServer::SubmitNeedsShelved     = { ErrorOf( ES_SERVER, 640, E_FAILED, EV_NOTYET, 1 ), "Change %change% does not have shelved files --  cannot submit."} ;
ErrorId MsgServer::CouldntLock         = { ErrorOf( ES_SERVER, 43, E_FAILED, EV_NOTYET, 0 ), "File(s) couldn't be locked." } ;
ErrorId MsgServer::MergesPending       = { ErrorOf( ES_SERVER, 44, E_FAILED, EV_NOTYET, 0 ), "Merges still pending -- use 'resolve' to merge files." } ;
ErrorId MsgServer::ResolveOrRevert     = { ErrorOf( ES_SERVER, 45, E_FAILED, EV_NOTYET, 0 ), "Out of date files must be resolved or reverted." } ;
ErrorId MsgServer::CantRevertToPurged  = { ErrorOf( ES_SERVER, 501, E_FAILED, EV_NOTYET, 0 ), "%file% has been purged and cannot be reverted. Use 'p4 revert -k' and then 'p4 sync' to get a newer revision." } ;
ErrorId MsgServer::RetypeInvalidTempobj = { ErrorOf( ES_SERVER, 374, E_FAILED, 0, 0 ), "Invalid +S modifier or xtempobj type used for changing librarian filetype.\nSee 'p4 help retype'." } ;
ErrorId MsgServer::NoSubmit            = { ErrorOf( ES_SERVER, 46, E_FAILED, EV_EMPTY, 0 ), "No files to submit." } ;
ErrorId MsgServer::TriggerFailed       = { ErrorOf( ES_SERVER, 47, E_FAILED, EV_NOTYET, 2 ), "'%trigger%' validation failed: %result%" } ;
ErrorId MsgServer::TriggerOutput       = { ErrorOf( ES_SERVER, 362, E_INFO, EV_NOTYET, 1 ), "%result%" } ;
ErrorId MsgServer::TriggersFailed      = { ErrorOf( ES_SERVER, 48, E_FAILED, EV_NOTYET, 1 ), "Submit validation failed -- fix problems then use 'p4 submit -c %change%'." } ;
ErrorId MsgServer::SubmitAborted       = { ErrorOf( ES_SERVER, 49, E_FAILED, EV_NOTYET, 1 ), "Submit aborted -- fix problems then use 'p4 submit -c %change%'." } ;
ErrorId MsgServer::SubmitShelvedAborted       = { ErrorOf( ES_SERVER, 642, E_FAILED, EV_NOTYET, 1 ), "Submit aborted -- fix problems then use 'p4 submit -e %change%'." } ;
ErrorId MsgServer::PopulateAborted     = { ErrorOf( ES_SERVER, 595, E_FAILED, EV_NOTYET, 0 ), "Populate aborted -- fix problems and retry." } ;
ErrorId MsgServer::PopulateIsVirtual   = { ErrorOf( ES_SERVER, 633, E_FAILED, EV_USAGE, 0 ), "Target stream is virtual, cannot update." } ;
ErrorId MsgServer::IntegIsTask         = { ErrorOf( ES_SERVER, 631, E_FAILED, EV_USAGE, 1 ), "Target of integration '%stream%' requires an appropriate task stream client." } ;

ErrorId MsgServer::PropertyAdd         = { ErrorOf( ES_SERVER, 634, E_INFO, 0, 1 ), "Property %settingName% %action%." } ;
ErrorId MsgServer::PropertyDelete      = { ErrorOf( ES_SERVER, 635, E_INFO, 0, 1 ), "Property %settingName% deleted." } ;
ErrorId MsgServer::UseProperty         = { ErrorOf( ES_SERVER, 636, E_FAILED, EV_USAGE, 0 ), "Usage: property [ -a -n name -v value | -d -n name | -l [ -n name ] ] [ -s sequence ] [ -u user | -g group ] [ -A ] [ -F filter -T taglist -m max ]" } ;

ErrorId MsgServer::NoDefaultSubmit     = { ErrorOf( ES_SERVER, 50, E_FAILED, EV_EMPTY, 0 ), "No files to submit from the default changelist." } ;
ErrorId MsgServer::BadImport           = { ErrorOf( ES_SERVER, 354, E_FAILED, EV_CLIENT, 2 ), "Can't copy %depotFile%%depotRev% - revision has been purged!" } ;
ErrorId MsgServer::BadTransfers        = { ErrorOf( ES_SERVER, 51, E_FAILED, EV_CLIENT, 0 ), "Some file(s) could not be transferred from client." } ;
ErrorId MsgServer::DigestMisMatch      = { ErrorOf( ES_SERVER, 465, E_FAILED, EV_CLIENT, 3 ), "%clientFile% corrupted during transfer %clientDigest% vs %serverDigest%" } ;
ErrorId MsgServer::SubmitDataChanged   = { ErrorOf( ES_SERVER, 324, E_FAILED, EV_EMPTY, 0 ), "Files newly opened or reverted during submission." } ;
ErrorId MsgServer::SubmitTampered      = { ErrorOf( ES_SERVER, 342, E_FAILED, 0, 2 ), "%clientFile% tampered with after resolve - edit or revert." } ;
ErrorId MsgServer::DirsWild            = { ErrorOf( ES_SERVER, 52, E_FAILED, EV_USAGE, 0 ), "Wildcard ... not allowed by 'p4 dirs'.  Use * instead." } ;
ErrorId MsgServer::HelpSeeRename       = { ErrorOf( ES_SERVER, 53, E_WARN, EV_USAGE, 0 ), "See 'p4 help rename' for instructions on renaming files." } ;
ErrorId MsgServer::PurgeReport         = { ErrorOf( ES_SERVER, 54, E_WARN, EV_NONE, 0 ), "This was report mode.  Use -y to remove files." } ;
ErrorId MsgServer::SnapReport         = { ErrorOf( ES_SERVER, 346, E_WARN, EV_NONE, 0 ), "This was report mode (-n),  no files were snapped (copied)." } ;
ErrorId MsgServer::PurgeWarning        = { ErrorOf( ES_SERVER, 303, E_WARN, EV_NONE, 2 ), "Warning: could not undo lazy copy link '%target%' -> '%source%" } ;
ErrorId MsgServer::PurgeOptGone        = { ErrorOf( ES_SERVER, 347, E_FAILED, EV_USAGE, 0 ), "Obliterate -z option deprecated - use 'p4 snap' instead" } ;
ErrorId MsgServer::PurgeBadOption      = { ErrorOf( ES_SERVER, 471, E_FAILED, EV_USAGE, 1 ), "'%path%' has revision range (not compatible with -b)." } ;
ErrorId MsgServer::LogCommand          = { ErrorOf( ES_SERVER, 55, E_INFO, EV_NONE, 1 ), "%text%" } ;
ErrorId MsgServer::LogEstimates        = { ErrorOf( ES_SERVER, 632, E_INFO, EV_NONE, 5 ), "Server network estimates: files added/updated/deleted=%filesAdded%/%filesUpdated%/%filesDeleted%, bytes added/updated=%bytesAdded%/%bytesUpdated%" } ;
ErrorId MsgServer::Unlicensed          = { ErrorOf( ES_SERVER, 56, E_FAILED, EV_ADMIN, 0 ), "Unlicensed server cannot start while over user/client quota." } ;
ErrorId MsgServer::TrackCommand        = { ErrorOf( ES_SERVER, 57, E_INFO, EV_NONE, 2 ), "%command%\n%text%" } ;
ErrorId MsgServer::NoValidLicense      = { ErrorOf( ES_SERVER, 58, E_FAILED, EV_ADMIN, 0 ), "Must shutdown unlicensed server to add license." } ;
ErrorId MsgServer::MaxLicensedFiles    = { ErrorOf( ES_SERVER, 463, E_FAILED, EV_ADMIN, 1 ), "Maximum licensed files (%files%) exceeded." } ;
ErrorId MsgServer::MaxUnLicensedFiles  = { ErrorOf( ES_SERVER, 464, E_FAILED, EV_ADMIN, 1 ), "Maximum users/clients AND maximum files (%files%) exceeded." } ;
ErrorId MsgServer::NoCentralLicense    = { ErrorOf( ES_SERVER, 472, E_FAILED, EV_ADMIN, 0 ), "Unlicensed server cannot perform remote authentication." } ;
ErrorId MsgServer::RemoteNotAllowed    = { ErrorOf( ES_SERVER, 664, E_FAILED, EV_ADMIN, 0 ), "This server requires service user authentication for remote server access. Please configure service user accounts for servers which connect to this one." } ;
ErrorId MsgServer::NoAuthFileCount     = { ErrorOf( ES_SERVER, 476, E_FAILED, EV_ADMIN, 0 ), "Files limited license cannot perform remote authentication." } ;
ErrorId MsgServer::ClientBadHost       = { ErrorOf( ES_SERVER, 589, E_FAILED, EV_ADMIN, 0 ), "TCP connection not licensed from '%address%'." } ;
ErrorId MsgServer::NoAuthServiceOnly   = { ErrorOf( ES_SERVER, 590, E_FAILED, EV_ADMIN, 0 ), "Service limited license cannot perform remote authentication." } ;

# ifdef OS_NT
ErrorId MsgServer::BadServicePack      = { ErrorOf( ES_SERVER, 320, E_FAILED, EV_ADMIN, 1 ), "On Windows XP the Perforce server requires at least \"Service Pack 2\",\n        on Windows Server 2003 it requires at least \"Service Pack 1\",\n        and Windows 2000 is no longer supported.\n        This machine is running OS \"%os%\" with \"%pack%\"." } ;
# endif

ErrorId MsgServer::Startup	       = { ErrorOf( ES_SERVER, 337, E_INFO, EV_NONE, 3 ), "Perforce Server starting %date% pid %pid% %ver%[ %mode% mode]." };
ErrorId MsgServer::Shutdown	       = { ErrorOf( ES_SERVER, 338, E_INFO, EV_NONE, 3 ), "Perforce Server shutdown %date% pid %pid%." };
ErrorId MsgServer::Restarted           = { ErrorOf( ES_SERVER, 515, E_INFO, EV_NONE, 2 ), "Perforce Server restarted %date% pid %pid%." };
ErrorId MsgServer::Restarting	       = { ErrorOf( ES_SERVER, 516, E_INFO, EV_NONE, 4 ), "Perforce Server restarting %date% pid %pid% %ver%[ %mode% mode]." };
ErrorId MsgServer::CreatingDb	       = { ErrorOf( ES_SERVER, 340, E_INFO, EV_NONE, 1 ), "Perforce db files in '%root%' will be created if missing..." };
ErrorId MsgServer::Quiescing           = { ErrorOf( ES_SERVER, 648, E_INFO, EV_NONE, 4 ), "Perforce Server quiescing %date% pid %pid%, %cnt% thread(s)." };
ErrorId MsgServer::QuiesceFailed       = { ErrorOf( ES_SERVER, 649, E_INFO, EV_NONE, 4 ), "Perforce Server quiesce %date% pid %pid%, failed after 60 seconds." };
ErrorId MsgServer::ReDowngrade         = { ErrorOf( ES_SERVER, 650, E_WARN, EV_NONE, 4 ), "Perforce Server %date% pid %pid%, downgrading restart to a shutdown." };

                               
ErrorId MsgServer::CounterDelete       = { ErrorOf( ES_SERVER, 100, E_INFO, 0, 1 ), "Counter %counterName% deleted." } ;
ErrorId MsgServer::CounterSet          = { ErrorOf( ES_SERVER, 101, E_INFO, 0, 1 ), "Counter %counterName% set." } ;
ErrorId MsgServer::CounterGet          = { ErrorOf( ES_SERVER, 102, E_INFO, 0, 1 ), "%counterValue%" } ;
ErrorId MsgServer::KeyDelete           = { ErrorOf( ES_SERVER, 626, E_INFO, 0, 1 ), "Key %counterName% deleted." } ;
ErrorId MsgServer::KeySet              = { ErrorOf( ES_SERVER, 627, E_INFO, 0, 1 ), "Key %counterName% set." } ;
ErrorId MsgServer::CounterNotNumeric   = { ErrorOf( ES_SERVER, 423, E_FAILED, EV_USAGE, 1 ), "Can't increment counter '%counterName%' - value is not numeric." } ;
ErrorId MsgServer::KeyNotNumeric   = { ErrorOf( ES_SERVER, 629, E_FAILED, EV_USAGE, 1 ), "Can't increment key '%keyName%' - value is not numeric." } ;
                               
ErrorId MsgServer::DescribeFixed       = { ErrorOf( ES_SERVER, 103, E_INFO, 0, 0 ), "Jobs fixed ...\n" } ;
ErrorId MsgServer::DescribeAffected    = { ErrorOf( ES_SERVER, 104, E_INFO, 0, 0 ), "Affected files ...\n" } ;
ErrorId MsgServer::DescribeMovedFiles  = { ErrorOf( ES_SERVER, 377, E_INFO, 0, 0 ), "\nMoved files ...\n" } ;
ErrorId MsgServer::DescribeDifferences = { ErrorOf( ES_SERVER, 105, E_INFO, 0, 0 ), "\nDifferences ..." } ;
ErrorId MsgServer::DescribeEmpty       = { ErrorOf( ES_SERVER, 106, E_INFO, 0, 0 ), "" } ;
ErrorId MsgServer::DescribeShelved     = { ErrorOf( ES_SERVER, 409, E_INFO, 0, 0 ), "Shelved files ...\n" } ;
                               
ErrorId MsgServer::Diff2Differ         = { ErrorOf( ES_SERVER, 107, E_INFO, 0, 0 ), "(... files differ ...)" } ;
ErrorId MsgServer::Diff2BadArgs        = { ErrorOf( ES_SERVER, 292, E_FAILED, EV_USAGE, 0 ), "File argument(s) require filepath(s), see 'p4 help diff2'." } ;

ErrorId MsgServer::GrepIllegalContext  = { ErrorOf( ES_DM, 433, E_FAILED, 0, 1 ), "%context%: invalid context length argument" } ;
ErrorId MsgServer::GrepContextTooLarge = { ErrorOf( ES_DM, 434, E_FAILED, 0, 2 ), "%context%: larger than maximum of %maxcontext%" } ;

ErrorId MsgServer::IndexOutput         = { ErrorOf( ES_SERVER, 108, E_INFO, 0, 1 ), "%value% words added/deleted." } ;
                               
ErrorId MsgServer::InfoUser            = { ErrorOf( ES_SERVER, 109, E_INFO, 0, 1 ), "User name: %user%" } ;
ErrorId MsgServer::InfoBadUser         = { ErrorOf( ES_SERVER, 110, E_INFO, 0, 1 ), "User name: %user% (illegal)" } ;
ErrorId MsgServer::InfoClient          = { ErrorOf( ES_SERVER, 111, E_INFO, 0, 1 ), "Client name: %client%" } ;
ErrorId MsgServer::InfoBadClient       = { ErrorOf( ES_SERVER, 112, E_INFO, 0, 1 ), "Client name: %client% (illegal)" } ;
ErrorId MsgServer::InfoStream          = { ErrorOf( ES_SERVER, 449, E_INFO, 0, 1 ), "Client stream: %stream%" } ;
ErrorId MsgServer::InfoHost            = { ErrorOf( ES_SERVER, 113, E_INFO, 0, 1 ), "Client host: %host%" } ;
ErrorId MsgServer::InfoDirectory       = { ErrorOf( ES_SERVER, 114, E_INFO, 0, 1 ), "Current directory: %dirName%" } ;
ErrorId MsgServer::InfoDiskSpace       = { ErrorOf( ES_SERVER, 514, E_INFO, 0, 6 ), "%name% (type %fsType%) : %freeBytes% free, %usedBytes% used, %totalBytes% total (%pctUsed%%% full)" } ;
ErrorId MsgServer::InfoClientAddress   = { ErrorOf( ES_SERVER, 115, E_INFO, 0, 1 ), "Client address: %clientAddr%" } ;
ErrorId MsgServer::InfoPeerAddress     = { ErrorOf( ES_SERVER, 584, E_INFO, 0, 1 ), "Peer address: %peerAddr%" } ;
ErrorId MsgServer::InfoServerAddress   = { ErrorOf( ES_SERVER, 116, E_INFO, 0, 1 ), "Server address: %serverAddr%" } ;
ErrorId MsgServer::InfoServerEncryption = { ErrorOf( ES_SERVER, 585, E_INFO, 0, 1 ), "Server encryption: %serverEncryption%" } ;
ErrorId MsgServer::InfoServerCertExpire = { ErrorOf( ES_SERVER, 585, E_INFO, 0, 1 ), "Server cert expires: %serverCertExpire%" } ;
ErrorId MsgServer::InfoProxyAddress    = { ErrorOf( ES_SERVER, 499, E_INFO, 0, 1 ), "Proxy address: %clientAddr%" } ;
ErrorId MsgServer::InfoProxyEncryption  = { ErrorOf( ES_SERVER, 586, E_INFO, 0, 1 ), "Proxy encryption: %proxyEncryption%" } ;
ErrorId MsgServer::InfoProxyCertExpire = { ErrorOf( ES_SERVER, 585, E_INFO, 0, 1 ), "Proxy cert expires: %proxyCertExpire%" } ;
ErrorId MsgServer::InfoServerRoot      = { ErrorOf( ES_SERVER, 117, E_INFO, 0, 1 ), "Server root: %serverRoot%" } ;
ErrorId MsgServer::InfoServerDate      = { ErrorOf( ES_SERVER, 118, E_INFO, 0, 2 ), "Server date: %serverDate% %serverTimeZone%" } ;
ErrorId MsgServer::InfoServerVersion   = { ErrorOf( ES_SERVER, 119, E_INFO, 0, 2 ), "Server version: %id% (%idDate%)" } ;
ErrorId MsgServer::InfoServerLicense   = { ErrorOf( ES_SERVER, 120, E_INFO, 0, 1 ), "Server license: %license%" } ;
ErrorId MsgServer::InfoServerLicenseIp = { ErrorOf( ES_SERVER, 382, E_INFO, 0, 1 ), "Server license-ip: %licenseIp%" } ;
ErrorId MsgServer::InfoServerUptime    = { ErrorOf( ES_SERVER, 367, E_INFO, 0, 1 ), "Server uptime: %uptime%" };
ErrorId MsgServer::InfoUnknownClient   = { ErrorOf( ES_SERVER, 137, E_INFO, 0, 0 ), "Client unknown." } ;
ErrorId MsgServer::InfoClientRoot      = { ErrorOf( ES_SERVER, 138, E_INFO, 0, 1 ), "Client root: %root%" } ;
ErrorId MsgServer::InfoProxyVersion    = { ErrorOf( ES_SERVER, 139, E_INFO, 0, 2 ), "Proxy version: %id% (%idDate%)" } ;
ErrorId MsgServer::InfoAuthServer      = { ErrorOf( ES_SERVER, 140, E_INFO, 0, 1 ), "Authorization server: %authServer%" };
ErrorId MsgServer::InfoChangeServer    = { ErrorOf( ES_SERVER, 370, E_INFO, 0, 1 ), "Changelist server: %changeServer%" };
ErrorId MsgServer::InfoServerID        = { ErrorOf( ES_SERVER, 598, E_INFO, 0, 1 ), "ServerID: %ServerID%" };
ErrorId MsgServer::InfoCaseHandling    = { ErrorOf( ES_SERVER, 426, E_INFO, 0, 1 ), "Case Handling: %caseHandling%" };
ErrorId MsgServer::InfoMinClient       = { ErrorOf( ES_SERVER, 431, E_INFO, 0, 1 ), "Minimum Client Level: %minClient%" };

ErrorId MsgServer::InfoPingTime        = { ErrorOf( ES_SERVER, 393, E_INFO, 0, 1 ), "%fileCount% messages in %time%" };
ErrorId MsgServer::InfoPingTimeB       = { ErrorOf( ES_SERVER, 394, E_INFO, 0, 1 ), "%fileCount% messages of %fileSize% characters in %time%" };
ErrorId MsgServer::InfoPingCount       = { ErrorOf( ES_SERVER, 395, E_INFO, 0, 1 ), "%time% for %fileCount%  messages" };
ErrorId MsgServer::InfoPingCountB      = { ErrorOf( ES_SERVER, 396, E_INFO, 0, 1 ), "%time% for %fileCount% messages of %fileSize% characters" };
ErrorId MsgServer::ErrorPingProtocol   = { ErrorOf( ES_SERVER, 397, E_FAILED, 0, 1 ), "ping remote buffers requires 9.2" };
ErrorId MsgServer::ErrorPingParam     = { ErrorOf( ES_SERVER, 417, E_FAILED, 0, 1 ), "Invalid ping parameter" };

ErrorId MsgServer::PasswordSave        = { ErrorOf( ES_SERVER, 121, E_INFO, 0, 0 ), "Password updated." } ;
ErrorId MsgServer::PasswordDelete      = { ErrorOf( ES_SERVER, 122, E_INFO, 0, 0 ), "Password deleted." } ;
ErrorId MsgServer::PasswordNoChange    = { ErrorOf( ES_SERVER, 123, E_INFO, 0, 0 ), "Password not changed." } ;

ErrorId MsgServer::ShelveBegin         = { ErrorOf( ES_SERVER, 401, E_INFO, 0, 1 ), "Shelving files for change %change%." } ;
ErrorId MsgServer::NoDefaultShelve     = { ErrorOf( ES_SERVER, 402, E_FAILED, EV_EMPTY, 0 ), "No files to shelve from the default changelist." } ;
ErrorId MsgServer::UnshelveNotOwner    = { ErrorOf( ES_SERVER, 404, E_FAILED, EV_ILLEGAL, 1 ), "Only user '%user%' can purge this shelved changelist." } ;
ErrorId MsgServer::ShelveAborted       = { ErrorOf( ES_SERVER, 405, E_FAILED, EV_NOTYET, 1 ), "Shelve aborted -- fix problems then use 'p4 shelve -c %change%'." } ;
ErrorId MsgServer::NoShelve            = { ErrorOf( ES_SERVER, 406, E_FAILED, EV_EMPTY, 0 ), "No files to shelve." } ;
ErrorId MsgServer::NoShelveDelete      = { ErrorOf( ES_SERVER, 411, E_FAILED, EV_EMPTY, 0 ), "No shelved files in changelist to delete." } ;
ErrorId MsgServer::ShelveComplete        = { ErrorOf( ES_SERVER, 412, E_INFO, 0, 1 ), "%change% files shelved." } ;
ErrorId MsgServer::ShelvePromoted        = { ErrorOf( ES_SERVER, 602, E_INFO, 0, 1 ), "%change% files promoted." } ;
ErrorId MsgServer::UnshelveFileChanged = { ErrorOf( ES_SERVER, 407, E_FAILED, EV_EMPTY, 1 ), "%depotFile% - warning: shelved file was modified during transfer!" } ;
ErrorId MsgServer::ShelveDelete        = { ErrorOf( ES_SERVER, 408, E_INFO, 0, 2 ), "Shelved change %change% [partially deleted, still contains %count% file(s).|deleted.]" } ;
ErrorId MsgServer::ShelveMaxSize       = { ErrorOf( ES_SERVER, 413, E_FAILED, EV_USAGE, 2 ), "%clientFile% size greater than shelve allows (max %maxFiles%)." } ;
ErrorId MsgServer::ShelveTriggersFailed       = { ErrorOf( ES_SERVER, 418, E_FAILED, EV_NOTYET, 0 ), "Shelve validation failed -- fix problems then try again." } ;
ErrorId MsgServer::ShelveXOpen          = { ErrorOf( ES_DM, 430, E_INFO, 1, 1 ), "%depotFile% - warning: shelve of +l file" } ;
ErrorId MsgServer::ChangesShelved        = { ErrorOf( ES_SERVER, 614, E_INFO, 1, 1 ), "File(s) shelved in change %change%" } ;

ErrorId MsgServer::SpecNotCorrect      = { ErrorOf( ES_SERVER, 124, E_INFO, 0, 0 ), "Specification not corrected -- giving up." } ;
ErrorId MsgServer::ErrorInSpec         = { ErrorOf( ES_SERVER, 323, E_FAILED, EV_ILLEGAL, 1 ), "Error in %domain% specification." } ;
ErrorId MsgServer::SpecArchiveWarning  = { ErrorOf( ES_SERVER, 333, E_INFO, 0, 0 ), "Warning: couldn't archive to spec depot (%lbrFile%)" } ;
ErrorId MsgServer::SpecCheckTriggers   = { ErrorOf( ES_SERVER, 350, E_INFO, 0, 0 ), "Error parsing form text; check form-out triggers?" } ;

ErrorId MsgServer::SubmitLocking       = { ErrorOf( ES_SERVER, 125, E_INFO, 0, 1 ), "Locking %unlockedCount% files ..." } ;
ErrorId MsgServer::SubmitComplete      = { ErrorOf( ES_SERVER, 126, E_INFO, 0, 1 ), "%change% submitted." } ;
ErrorId MsgServer::SubmitRenamed       = { ErrorOf( ES_SERVER, 127, E_INFO, 0, 2 ), "%change% renamed %newChange% and submitted." } ;
ErrorId MsgServer::SubmitBegin         = { ErrorOf( ES_SERVER, 128, E_INFO, 0, 1 ), "Submitting change %change%." } ;

ErrorId MsgServer::PopulateComplete    = { ErrorOf( ES_SERVER, 591, E_INFO, 0, 2 ), "%fileCount% files branched[ (change %change%)]." } ;
                               
ErrorId MsgServer::ResolveOptAuto      = { ErrorOf( ES_SERVER, 486, E_INFO, 0, 0 ), "a" };
ErrorId MsgServer::ResolveOptHelp      = { ErrorOf( ES_SERVER, 487, E_INFO, 0, 0 ), "?" };
ErrorId MsgServer::ResolveOptMerge     = { ErrorOf( ES_SERVER, 488, E_INFO, 0, 0 ), "am" };
ErrorId MsgServer::ResolveOptSkip      = { ErrorOf( ES_SERVER, 489, E_INFO, 0, 0 ), "s" };
ErrorId MsgServer::ResolveOptTheirs    = { ErrorOf( ES_SERVER, 490, E_INFO, 0, 0 ), "at" };
ErrorId MsgServer::ResolveOptYours     = { ErrorOf( ES_SERVER, 491, E_INFO, 0, 0 ), "ay" };
ErrorId MsgServer::ResolvePromptMerge  = { ErrorOf( ES_SERVER, 492, E_INFO, 0, 1 ), "am: %resolveAction%" };
ErrorId MsgServer::ResolvePromptTheirs = { ErrorOf( ES_SERVER, 493, E_INFO, 0, 1 ), "at: %resolveAction%" };
ErrorId MsgServer::ResolvePromptType   = { ErrorOf( ES_SERVER, 494, E_INFO, 0, 1 ), "%resolveType%:" };
ErrorId MsgServer::ResolvePromptYours  = { ErrorOf( ES_SERVER, 495, E_INFO, 0, 1 ), "ay: %resolveAction%" };
ErrorId MsgServer::ResolveUserError    = { ErrorOf( ES_SERVER, 496, E_INFO, 0, 1 ), "'%option%' is not an option." };
ErrorId MsgServer::ResolveUserPrompt   = { ErrorOf( ES_SERVER, 497, E_INFO, 0, 1 ), "Accept(a) Skip(s) Help(?) %option%: " };
ErrorId MsgServer::ResolveUserPrompt2  = { ErrorOf( ES_SERVER, 517, E_INFO, 0, 1 ), "Accept(at/ay) Skip(s) Help(?) %option%: " };

ErrorId MsgServer::ResolvedFile        = { ErrorOf( ES_SERVER, 129, E_INFO, 0, 3 ), "%toFile% - %how% %fromFile%" } ;
ErrorId MsgServer::ResolvedSkipped     = { ErrorOf( ES_SERVER, 130, E_INFO, 0, 1 ), "%toFile% - resolve skipped." } ;
ErrorId MsgServer::ResolveTampered      = { ErrorOf( ES_SERVER, 452, E_FAILED, 0, 1 ), "%clientFile% tampered with before resolve - edit or revert." } ;
                               
ErrorId MsgServer::JobRebuilt          = { ErrorOf( ES_SERVER, 131, E_INFO, 0, 1 ), "%job% ..." } ;
ErrorId MsgServer::SearchResult        = { ErrorOf( ES_SERVER, 132, E_INFO, 0, 1 ), "%word%" } ;

ErrorId MsgServer::DiffCmp             = { ErrorOf( ES_SERVER, 133, E_INFO, 0, 1 ), "%path%" } ;
ErrorId MsgServer::DiffList            = { ErrorOf( ES_SERVER, 134, E_INFO, 0, 2 ), "%status% %path%" } ;

ErrorId MsgServer::DeltaLine1          = { ErrorOf( ES_SERVER, 135, E_INFO, 0, 2 ), "%lower%: %data%" } ;
ErrorId MsgServer::DeltaLine2          = { ErrorOf( ES_SERVER, 136, E_INFO, 0, 3 ), "%lower%-%upper%: %data%" } ;

ErrorId MsgServer::MonitorDisabled     = { ErrorOf( ES_SERVER, 137, E_FAILED, EV_ADMIN, 0 ), "Monitor not currently enabled." } ;
ErrorId MsgServer::MonitorBadId        = { ErrorOf( ES_SERVER, 138, E_FAILED, EV_USAGE, 1 ), "Invalid session identifier: %id%" } ;
ErrorId MsgServer::TooManyCommands     = { ErrorOf( ES_SERVER, 637, E_FAILED, EV_USAGE, 1 ), "Request refused: this server is configured to run a maximum of %maxCommands% simultaneous commands. Please try again later when the load is lower." } ;

ErrorId MsgServer::ConfigureSet        = { ErrorOf( ES_SERVER, 437, E_INFO, 0, 3 ), "For server '%serverName%', configuration variable '%variableName%' set to '%variableValue%'" } ;
ErrorId MsgServer::ConfigureUnSet      = { ErrorOf( ES_SERVER, 438, E_INFO, 0, 2 ), "For server '%serverName%', configuration variable '%variableName%' removed." } ;
ErrorId MsgServer::NotThisConfigVar    = { ErrorOf( ES_SERVER, 439, E_FAILED, EV_USAGE, 0 ), "Configuration variable '%name%' may not be changed." } ;
ErrorId MsgServer::InvalidConfigValue  = { ErrorOf( ES_SERVER, 440, E_FAILED, EV_USAGE, 0 ), "Configuration variable '%name%' may not be set to '%value%'." } ;
ErrorId MsgServer::ConfigureNone       = { ErrorOf( ES_SERVER, 466, E_INFO, 0, 3 ), "No configurables have been set." } ;
ErrorId MsgServer::ConfigureServerNone = { ErrorOf( ES_SERVER, 467, E_INFO, 0, 3 ), "No configurables have been set for server '%serverName%'." } ;

ErrorId MsgServer::IstatInvalid        = { ErrorOf( ES_SERVER, 460, E_FAILED, EV_USAGE, 1 ), "Stream '%stream%' is invalid, use -f to force check."} ;

ErrorId MsgServer::UseAdmin            = { ErrorOf( ES_SERVER, 200, E_FAILED, EV_USAGE, 0 ), "Usage: admin { checkpoint | journal | resetpassword | restart | stop | updatespecdepot }" } ;
ErrorId MsgServer::UseAdminCheckpoint  = { ErrorOf( ES_SERVER, 203, E_FAILED, EV_USAGE, 0 ), "Usage: admin checkpoint [ -z | -Z ] [ prefix ] " } ;
ErrorId MsgServer::UseAdminJournal     = { ErrorOf( ES_SERVER, 204, E_FAILED, EV_USAGE, 0 ), "Usage: admin journal [ -z ] [ prefix ] " } ;
ErrorId MsgServer::UseAdminSpecDepot   = { ErrorOf( ES_SERVER, 352, E_FAILED, EV_USAGE, 0 ), "Usage: admin updatespecdepot [ -a | -s type ]" } ;
ErrorId MsgServer::UseAdminResetPassword   = { ErrorOf( ES_SERVER, 620, E_FAILED, EV_USAGE, 0 ), "Usage: admin resetpassword -a | -u user" } ;
ErrorId MsgServer::UseAdminDBSigs      = { ErrorOf( ES_SERVER, 502, E_FAILED, EV_USAGE, 0 ), "Usage: journaldbchecksums [ -s -b batchsize -c change -l level -u file -t includelist -T excludelist -v version -z ]" } ;
ErrorId MsgServer::UseAdminImport      = { ErrorOf( ES_SERVER, 360, E_FAILED, EV_USAGE, 0 ), "Usage: admin import [ -l ] [ -b batchsize ]" } ;
ErrorId MsgServer::UseAnnotate         = { ErrorOf( ES_SERVER, 289, E_FAILED, EV_USAGE, 0 ), "Usage: annotate [ -aciIqt -d<flags> ] files..." } ;
ErrorId MsgServer::UseArchive          = { ErrorOf( ES_SERVER, 453, E_FAILED, EV_USAGE, 0 ), "Usage: archive -D depot [-n -h -p -q -t ] files..." } ;
ErrorId MsgServer::UseBranch           = { ErrorOf( ES_SERVER, 205, E_FAILED, EV_USAGE, 0 ), "Usage: branch [ -d -f -i -S stream -P parent -o ] branchname" } ;
ErrorId MsgServer::UseBrancho          = { ErrorOf( ES_SERVER, 206, E_FAILED, EV_USAGE, 0 ), "Usage: branch [ -S stream [ -P parent ] ] -o branchname" } ;
ErrorId MsgServer::UseBranchd          = { ErrorOf( ES_SERVER, 207, E_FAILED, EV_USAGE, 0 ), "Usage: branch -d [ -f ] branchname" } ;
ErrorId MsgServer::UseBranchi          = { ErrorOf( ES_SERVER, 208, E_FAILED, EV_USAGE, 0 ), "Usage: branch -i" } ;
ErrorId MsgServer::UseCachepurge       = { ErrorOf( ES_SERVER, 705, E_FAILED, EV_USAGE, 0 ), "Usage: cachepurge [ -a | -f N | -m N | -s N ] [ -i N -n -R -S N -O -D files... ]" } ;
ErrorId MsgServer::UseChange           = { ErrorOf( ES_SERVER, 209, E_FAILED, EV_USAGE, 0 ), "Usage: change [ -d -i -o -s -t<type> -U<user>] [ -f | -u ] [ [ -O ] changelist# ]" } ;
ErrorId MsgServer::UseChanged          = { ErrorOf( ES_SERVER, 210, E_FAILED, EV_USAGE, 0 ), "Usage: change -d [ -f ] [ -O ] changelist#" } ;
ErrorId MsgServer::UseChangeo          = { ErrorOf( ES_SERVER, 211, E_FAILED, EV_USAGE, 0 ), "Usage: change -o [ -s ] [ -f ] [ [ -O ] changelist# ]" } ;
ErrorId MsgServer::UseChangei          = { ErrorOf( ES_SERVER, 212, E_FAILED, EV_USAGE, 0 ), "Usage: change -i [ -s ] [ -f | -u ]" } ;
ErrorId MsgServer::UseChanget          = { ErrorOf( ES_SERVER, 456, E_FAILED, EV_USAGE, 0 ), "Usage: change -t restricted | public [ -U user ] [ -f | -u | -O ] changelist#" } ;
ErrorId MsgServer::UseChangeU          = { ErrorOf( ES_SERVER, 651, E_FAILED, EV_USAGE, 0 ), "Usage: change -U user [ -t restricted | public ] [ -f ] changelist#" } ;
ErrorId MsgServer::UseChangeUt          = { ErrorOf( ES_SERVER, 652, E_FAILED, EV_USAGE, 0 ), "Usage: change -U user -t restricted | public [ -f ] changelist#" } ;
ErrorId MsgServer::UseChanges          = { ErrorOf( ES_SERVER, 213, E_FAILED, EV_USAGE, 0 ), "Usage: changes [-i -t -l -L -f -c client -m count -s status -u user] [files...]" } ;
ErrorId MsgServer::UseClean            = { ErrorOf( ES_SERVER, 674, E_FAILED, EV_USAGE, 0 ), "Usage: clean [ -a -d -e -I -l -n ] [ files... ]" } ;
ErrorId MsgServer::UseClient           = { ErrorOf( ES_SERVER, 214, E_FAILED, EV_USAGE, 0 ), "Usage: client [ -d -f -Fs -i -o -s ] [ -t template | -S stream ] [ -c change ] [ clientname ]" } ;
ErrorId MsgServer::UseCliento          = { ErrorOf( ES_SERVER, 215, E_FAILED, EV_USAGE, 0 ), "Usage: client -o [ -t template ] clientname" } ;
ErrorId MsgServer::UseClientS          = { ErrorOf( ES_SERVER, 510, E_FAILED, EV_USAGE, 0 ), "Usage: client -S stream [ [ -c change ] -o ] [ clientname ]" } ;
ErrorId MsgServer::UseClientd          = { ErrorOf( ES_SERVER, 216, E_FAILED, EV_USAGE, 0 ), "Usage: client -d [ -f [ -Fs ] ] clientname" } ;
ErrorId MsgServer::UseClienti          = { ErrorOf( ES_SERVER, 217, E_FAILED, EV_USAGE, 0 ), "Usage: client -i [ -f ]" } ;
ErrorId MsgServer::UseClients          = { ErrorOf( ES_SERVER, 504, E_FAILED, EV_USAGE, 0 ), "Usage: client -s [ -f ] -t template | -S stream [ clientname ]" } ;
ErrorId MsgServer::UseCluster          = { ErrorOf( ES_SERVER, 666, E_FAILED, EV_USAGE, 0 ), "Usage: cluster [ add-node <server id> | forward-off | master-stop | service-elect | to-standby]" } ;
ErrorId MsgServer::UseConfigure        = { ErrorOf( ES_SERVER, 436, E_FAILED, EV_USAGE, 0 ), "Usage: configure { show [ allservers | <P4NAME> | <variable> ] | set [<P4NAME>#]variable=value | unset [<P4NAME>#]variable }" } ;
ErrorId MsgServer::UseCopy             = { ErrorOf( ES_SERVER, 450, E_FAILED, EV_USAGE, 0 ), "Usage: copy [ -c changelist# -f -F -m max -n -q -r -s from -v ] [ -b branch to... | -S stream [ -P parent ] [ file... ] | from to ]" } ;
ErrorId MsgServer::UseCopyb            = { ErrorOf( ES_SERVER, 451, E_FAILED, EV_USAGE, 0 ), "Usage: copy [ -c changelist# -f -F -m max -n -q -r -s from -v ] -b branch [ to... ]" } ;
ErrorId MsgServer::UseCopyS            = { ErrorOf( ES_SERVER, 508, E_FAILED, EV_USAGE, 0 ), "Usage: copy [ -c changelist# -f -F -m max -n -q -r -s from -v ] -S stream [ -P parent ] [ file... ]" } ;
ErrorId MsgServer::UseCounter          = { ErrorOf( ES_SERVER, 218, E_FAILED, EV_USAGE, 0 ), "Usage: counter [ -f ] [ -d | -i | -m ] counter_name [ value ] [ ... ]" } ;
ErrorId MsgServer::UseCounteri         = { ErrorOf( ES_SERVER, 424, E_FAILED, EV_USAGE, 0 ), "Usage: counter [ -f ] -i counter_name" } ;
ErrorId MsgServer::UseCounters         = { ErrorOf( ES_SERVER, 219, E_FAILED, EV_USAGE, 0 ), "Usage: counters [ -e nameFilter -m max ]" } ;
ErrorId MsgServer::UseCstat            = { ErrorOf( ES_SERVER, 419, E_FAILED, EV_USAGE, 0 ), "Usage: cstat [files...]" } ;
ErrorId MsgServer::UseDbpack           = { ErrorOf( ES_SERVER, 359, E_FAILED, EV_USAGE, 0 ), "Usage: dbpack [ -c pages -l 0|1|2 ] { -a | dbtable ... }" } ;
ErrorId MsgServer::UseDbstat           = { ErrorOf( ES_SERVER, 344, E_FAILED, EV_USAGE, 0 ), "Usage: dbstat [ -h ] { -a | dbtable ... }\n       dbstat -s" } ;
ErrorId MsgServer::UseDbverify         = { ErrorOf( ES_SERVER, 573, E_FAILED, EV_USAGE, 0 ), "Usage: dbverify [ -t db.table ] [ -U ] [-v]" } ;
ErrorId MsgServer::UseDepot            = { ErrorOf( ES_SERVER, 220, E_FAILED, EV_USAGE, 0 ), "Usage: depot [ -i -o ] [ -d [ -f ] ] depotname" } ;
ErrorId MsgServer::UseDepoto           = { ErrorOf( ES_SERVER, 221, E_FAILED, EV_USAGE, 0 ), "Usage: depot -o depotname" } ;
ErrorId MsgServer::UseDepotd           = { ErrorOf( ES_SERVER, 222, E_FAILED, EV_USAGE, 0 ), "Usage: depot -d depotname" } ;
ErrorId MsgServer::UseDepoti           = { ErrorOf( ES_SERVER, 223, E_FAILED, EV_USAGE, 0 ), "Usage: depot -i" } ;
ErrorId MsgServer::UseDepots           = { ErrorOf( ES_SERVER, 224, E_FAILED, EV_USAGE, 0 ), "Usage: depots" } ;
ErrorId MsgServer::UseDescribe         = { ErrorOf( ES_SERVER, 225, E_FAILED, EV_USAGE, 0 ), "Usage: describe [-d<flags> -m max -s -S -f -O] changelist# ..." } ;
ErrorId MsgServer::UseDiff             = { ErrorOf( ES_SERVER, 226, E_FAILED, EV_USAGE, 0 ), "Usage: diff [ -d<flags> -f -m max -Od -s<flag> -t ] [files...]" } ;
ErrorId MsgServer::UseDiff2            = { ErrorOf( ES_SERVER, 227, E_FAILED, EV_USAGE, 0 ), "Usage: diff2 [ -d<flags> -Od -q -t -u ] [ -b branchName ] [ -S stream ] [ -P parent ] file file2" } ;
ErrorId MsgServer::UseDiff2b           = { ErrorOf( ES_SERVER, 228, E_FAILED, EV_USAGE, 0 ), "Usage: diff2 [ -d<flags> -Od -q -t -u ] -b branchName [ [ file ] file2 ]" } ;
ErrorId MsgServer::UseDiff2S           = { ErrorOf( ES_SERVER, 506, E_FAILED, EV_USAGE, 0 ), "Usage: diff2 [ -d<flags> -Od -q -t -u ] -S stream [ -P parent ] [ [ file ] file2 ]" } ;
ErrorId MsgServer::UseDiff2n           = { ErrorOf( ES_SERVER, 229, E_FAILED, EV_USAGE, 0 ), "Usage: diff2 [ -d<flags> -Od -q -t -u ] file file2" } ;
ErrorId MsgServer::UseDirs             = { ErrorOf( ES_SERVER, 230, E_FAILED, EV_USAGE, 0 ), "Usage: dirs [-C -D -H] [-S stream] dirs..." } ;
ErrorId MsgServer::UseDiskspace        = { ErrorOf( ES_SERVER, 513, E_FAILED, EV_USAGE, 0 ), "Usage: diskspace [ P4ROOT | P4JOURNAL | P4LOG | TEMP | depot ]" } ;
ErrorId MsgServer::UseBranches         = { ErrorOf( ES_SERVER, 534, E_FAILED, EV_USAGE, 0 ), "Usage: branches [ -t ] [ -u user ] [ [-e|-E] query -m max ]" } ;
ErrorId MsgServer::UseLabels           = { ErrorOf( ES_SERVER, 535, E_FAILED, EV_USAGE, 0 ), "Usage: labels [ -t ] [ -u user ] [ -U ] [ [-e|-E] query -m max ] [ -a | -s serverID ]" } ;
ErrorId MsgServer::UseDomainClients    = { ErrorOf( ES_SERVER, 481, E_FAILED, EV_USAGE, 0 ), "Usage: clients [ -t ] [ -u user ] [ -U ] [ [-e|-E] query -m max ] [ -a | -s serverID ] [ -S stream ]" } ;
ErrorId MsgServer::UseDup              = { ErrorOf( ES_SERVER, 351, E_FAILED, EV_USAGE, 0 ), "Usage: duplicate [ -n -q ] from[revRange] to" } ;
ErrorId MsgServer::UseExport           = { ErrorOf( ES_SERVER, 378, E_FAILED, EV_USAGE, 0 ), "Usage: export [ -f -r -F <filter> -j <journal> -c <checkpoint> -l <lines> -J <prefix> -T <tableexcludelist> -P <filterpattern>]" } ;
ErrorId MsgServer::UseFilelog          = { ErrorOf( ES_SERVER, 232, E_FAILED, EV_USAGE, 0 ), "Usage: filelog [ -c changelist# -h -i -l -L -t -m maxRevs -p -s ] files..." } ;
ErrorId MsgServer::UseFiles            = { ErrorOf( ES_SERVER, 233, E_FAILED, EV_USAGE, 0 ), "Usage: files [-a -A -e -m max] [-U] files..." } ;
ErrorId MsgServer::UseFix              = { ErrorOf( ES_SERVER, 234, E_FAILED, EV_USAGE, 0 ), "Usage: fix [ -d ] [ -s status ] -c changelist# jobName ..." } ;
ErrorId MsgServer::UseFixes            = { ErrorOf( ES_SERVER, 235, E_FAILED, EV_USAGE, 0 ), "Usage: fixes [ -i -m max -c changelist# -j jobName ] [files...] " } ;
ErrorId MsgServer::UseFstat            = { ErrorOf( ES_SERVER, 236, E_FAILED, EV_USAGE, 0 ), "Usage: fstat [ -F filter -T fields -m max -r ] [ -c | -e changelist# ] [ -Ox -Rx -Sx ] [-A pattern] [-U] file[rev]..." } ;
ErrorId MsgServer::UseGrep             = { ErrorOf( ES_SERVER, 427, E_FAILED, EV_USAGE, 0 ), "Usage: grep [ -a -i -n -A after -B before -C context -t -s ] [ -v | -l | -L ] [ -F | -G ] -e pattern files..." };
ErrorId MsgServer::UseGroup            = { ErrorOf( ES_SERVER, 237, E_FAILED, EV_USAGE, 0 ), "Usage: group [ -a -A -d -i -o ] groupname" } ;
ErrorId MsgServer::UseGroupo           = { ErrorOf( ES_SERVER, 238, E_FAILED, EV_USAGE, 0 ), "Usage: group -o groupname" } ;
ErrorId MsgServer::UseGroupd           = { ErrorOf( ES_SERVER, 239, E_FAILED, EV_USAGE, 0 ), "Usage: group [ -a ] -d groupname" } ;
ErrorId MsgServer::UseGroupi           = { ErrorOf( ES_SERVER, 240, E_FAILED, EV_USAGE, 0 ), "Usage: group [ -a -A ] -i" } ;
ErrorId MsgServer::UseGroups           = { ErrorOf( ES_SERVER, 241, E_FAILED, EV_USAGE, 0 ), "Usage: groups [ -m max ] [ [ [ -i [ -v ] ] user | group ] | [ -v [ group ] ]  | [ -g | -u | -o name ] ]" } ;
ErrorId MsgServer::UseHave             = { ErrorOf( ES_SERVER, 242, E_FAILED, EV_USAGE, 0 ), "Usage: have [files...]" } ;
ErrorId MsgServer::UseHelp             = { ErrorOf( ES_SERVER, 243, E_FAILED, EV_USAGE, 0 ), "Usage: help [command ...]" } ;
ErrorId MsgServer::UseIndex            = { ErrorOf( ES_SERVER, 244, E_FAILED, EV_USAGE, 0 ), "Usage: index [ -a attrib ] [ -d ] name" } ;
ErrorId MsgServer::UseInfo             = { ErrorOf( ES_SERVER, 245, E_FAILED, EV_USAGE, 0 ), "Usage: info [-s]" } ;
ErrorId MsgServer::UseInteg            = { ErrorOf( ES_SERVER, 246, E_FAILED, EV_USAGE, 0 ), "Usage: integrate [ -c changelist# -D<flags> -f -h -m max -n -Obr -q -r -s from -v ] [ -b branch to... | from to ] [ -S stream [ -P parent ] files... ]" } ;
ErrorId MsgServer::UseIntegb           = { ErrorOf( ES_SERVER, 247, E_FAILED, EV_USAGE, 0 ), "Usage: integrate [ -c changelist# -D<flags> -f -h -m max -n -Obr -q -r -s from -v ] -b branch [ to... ]" } ;
ErrorId MsgServer::UseIntegS           = { ErrorOf( ES_SERVER, 507, E_FAILED, EV_USAGE, 0 ), "Usage: integrate [ -c changelist# -D<flags> -f -h -m max -n -Obr -q -r -s from -v ] -S stream [ -P parent ] [ files... ] " } ;
ErrorId MsgServer::UseInteged          = { ErrorOf( ES_SERVER, 248, E_FAILED, EV_USAGE, 0 ), "Usage: integrated [ -r ] [ -b branch ] [ files... ]" } ;
ErrorId MsgServer::UseInterChanges     = { ErrorOf( ES_SERVER, 304, E_FAILED, EV_USAGE, 0 ), "Usage: interchanges -f -l -t -r -F [ -b branch to... | -S stream [ -P parent ] [ files... ] | from to ]" } ;
ErrorId MsgServer::UseInterChangesb    = { ErrorOf( ES_SERVER, 305, E_FAILED, EV_USAGE, 0 ), "Usage: interchanges -f -l -t -r [ -b branch to... ]" } ;
ErrorId MsgServer::UseInterChangesS    = { ErrorOf( ES_SERVER, 509, E_FAILED, EV_USAGE, 0 ), "Usage: interchanges -f -l -t -r -F -S stream [ -P parent ] [ files... ]" } ;
ErrorId MsgServer::UseIstat            = { ErrorOf( ES_SERVER, 459, E_FAILED, EV_USAGE, 0 ), "Usage: istat [ -a -f -r ] stream" } ;
ErrorId MsgServer::UseJob              = { ErrorOf( ES_SERVER, 249, E_FAILED, EV_USAGE, 0 ), "Usage: job [ -d -f -i -o ] [ jobName ]" } ;
ErrorId MsgServer::UseJobd             = { ErrorOf( ES_SERVER, 250, E_FAILED, EV_USAGE, 0 ), "Usage: job -d jobName" } ;
ErrorId MsgServer::UseJobo             = { ErrorOf( ES_SERVER, 251, E_FAILED, EV_USAGE, 0 ), "Usage: job -o [ jobName ]" } ;
ErrorId MsgServer::UseJobi             = { ErrorOf( ES_SERVER, 252, E_FAILED, EV_USAGE, 0 ), "Usage: job -i [ -f ]" } ;
ErrorId MsgServer::UseJobs             = { ErrorOf( ES_SERVER, 253, E_FAILED, EV_USAGE, 0 ), "Usage: jobs [-e query -i -l -m count -r] [files...]" } ;
ErrorId MsgServer::UseJobSpec          = { ErrorOf( ES_SERVER, 254, E_FAILED, EV_USAGE, 0 ), "Usage: jobspec [ -i -o ]" } ;
ErrorId MsgServer::UseJournalWait      = { ErrorOf( ES_SERVER, 663, E_FAILED, EV_USAGE, 0 ), "Usage: journalwait [ -i ]" } ;
ErrorId MsgServer::UseJournals         = { ErrorOf( ES_SERVER, 700, E_FAILED, EV_USAGE, 0 ), "Usage: journals [-T field...] [-F filter] [-m max]" } ;
ErrorId MsgServer::UseKey              = { ErrorOf( ES_SERVER, 624, E_FAILED, EV_USAGE, 0 ), "Usage: key [ -d | -i | -m ] key_name [ value ] [ ... ]" } ;
ErrorId MsgServer::UseKeyi             = { ErrorOf( ES_SERVER, 625, E_FAILED, EV_USAGE, 0 ), "Usage: key -i key_name" } ;
ErrorId MsgServer::UseKeys             = { ErrorOf( ES_SERVER, 628, E_FAILED, EV_USAGE, 0 ), "Usage: keys [ -e nameFilter -m max ]" } ;
ErrorId MsgServer::UseLabel            = { ErrorOf( ES_SERVER, 255, E_FAILED, EV_USAGE, 0 ), "Usage: label [ -d -f -g -i -o -t template ] labelname" } ;
ErrorId MsgServer::UseLabelo           = { ErrorOf( ES_SERVER, 256, E_FAILED, EV_USAGE, 0 ), "Usage: label -o [ -t template ] labelname" } ;
ErrorId MsgServer::UseLabeld           = { ErrorOf( ES_SERVER, 257, E_FAILED, EV_USAGE, 0 ), "Usage: label -d [ -f -g ] labelname" } ;
ErrorId MsgServer::UseLabeli           = { ErrorOf( ES_SERVER, 258, E_FAILED, EV_USAGE, 0 ), "Usage: label -i [ -f -g ]" } ;
ErrorId MsgServer::UseLabelSync        = { ErrorOf( ES_SERVER, 259, E_FAILED, EV_USAGE, 0 ), "Usage: labelsync [-a -d -g -n -q] -l label [files...]" } ;
ErrorId MsgServer::UseLicense          = { ErrorOf( ES_SERVER, 343, E_FAILED, EV_USAGE, 0 ), "Usage: license [ -i | -o | -u ]" } ;
ErrorId MsgServer::UseList             = { ErrorOf( ES_SERVER, 587, E_FAILED, EV_USAGE, 0 ), "Usage: list [-l label [-d]] [-C] [-M] files..." } ;
ErrorId MsgServer::UseLock             = { ErrorOf( ES_SERVER, 260, E_FAILED, EV_USAGE, 0 ), "Usage: lock [-c changelist#] [files...]" } ;
ErrorId MsgServer::UseLockstat         = { ErrorOf( ES_SERVER, 610, E_FAILED, EV_USAGE, 0 ), "Usage: lockstat [-c client | -C]" } ;
ErrorId MsgServer::UseLogin            = { ErrorOf( ES_SERVER, 316, E_FAILED, EV_USAGE, 0 ), "Usage: login [ -a -p ] [ -s ] [ -h host username ]" } ;
ErrorId MsgServer::UseLogout           = { ErrorOf( ES_SERVER, 317, E_FAILED, EV_USAGE, 0 ), "Usage: logout [ -a ] [ username ]" } ;
ErrorId MsgServer::UseLogger           = { ErrorOf( ES_SERVER, 261, E_FAILED, EV_USAGE, 0 ), "Usage: logger [ -c sequence# ] [ -t counter_name ]" } ;
ErrorId MsgServer::UseLogAppend        = { ErrorOf( ES_SERVER, 560, E_FAILED, EV_USAGE, 0 ), "Usage: logappend -a args..." } ;
ErrorId MsgServer::UseLogParse         = { ErrorOf( ES_SERVER, 574, E_FAILED, EV_USAGE, 0 ), "Usage: logparse [ -e ] [-T field...] [-F filter] [-s offset] [-m max] logfilename" } ;
ErrorId MsgServer::UseLogRotate        = { ErrorOf( ES_SERVER, 561, E_FAILED, EV_USAGE, 0 ), "Usage: logrotate [ -l log ]" } ;
ErrorId MsgServer::UseLogSchema        = { ErrorOf( ES_SERVER, 575, E_FAILED, EV_USAGE, 0 ), "Usage: logschema [-a | recordtype]" } ;
ErrorId MsgServer::UseLogstat          = { ErrorOf( ES_SERVER, 579, E_FAILED, EV_USAGE, 0 ), "Usage: logstat [ -l log ]" } ;
ErrorId MsgServer::UseLogtail          = { ErrorOf( ES_SERVER, 381, E_FAILED, EV_USAGE, 0 ), "Usage: logtail [ -b blocksize ] [ -s starting offset ] [ -m maxBlocks ] [ -l log ]" } ;
ErrorId MsgServer::UseMain             = { ErrorOf( ES_SERVER, 262, E_FAILED, EV_USAGE, 0 ), "Usage: p4d -h for usage." } ;
ErrorId MsgServer::UseMerge            = { ErrorOf( ES_SERVER, 523, E_FAILED, EV_USAGE, 0 ), "Usage: merge [ -c changelist# -F -m max -n -Ob -q -r -s from ] [ -b branch to... | -S stream [ -P parent ] [ file... ] | from to ]" } ;
ErrorId MsgServer::UseMergeb           = { ErrorOf( ES_SERVER, 524, E_FAILED, EV_USAGE, 0 ), "Usage: merge [ -c changelist# -F -m max -n -Ob -q -r -s from ] -b branch [ to... ]" } ;
ErrorId MsgServer::UseMergeS           = { ErrorOf( ES_SERVER, 525, E_FAILED, EV_USAGE, 0 ), "Usage: merge [ -c changelist# -F -m max -n -Ob -q -r -s from ] -S stream [ -P parent ] [ file... ]" } ;
ErrorId MsgServer::UseMonitor          = { ErrorOf( ES_SERVER, 297, E_FAILED, EV_USAGE, 0 ), "Usage: monitor { show | terminate | clear | pause | resume }" } ;
ErrorId MsgServer::UseMonitorc         = { ErrorOf( ES_SERVER, 298, E_FAILED, EV_USAGE, 0 ), "Usage: monitor terminate [arg]" } ;
ErrorId MsgServer::UseMonitorf         = { ErrorOf( ES_SERVER, 299, E_FAILED, EV_USAGE, 0 ), "Usage: monitor clear [arg]" } ;
ErrorId MsgServer::UseMonitors         = { ErrorOf( ES_SERVER, 300, E_FAILED, EV_USAGE, 0 ), "Usage: monitor show [ -a -l -e -s [ R | T | P | I ] ]" } ;
ErrorId MsgServer::UseMonitorP         = { ErrorOf( ES_SERVER, 511, E_FAILED, EV_USAGE, 0 ), "Usage: monitor pause [arg]" } ;
ErrorId MsgServer::UseMonitorR         = { ErrorOf( ES_SERVER, 512, E_FAILED, EV_USAGE, 0 ), "Usage: monitor resume [arg]" } ;
ErrorId MsgServer::UseOpen             = { ErrorOf( ES_SERVER, 263, E_FAILED, EV_USAGE, 0 ), "Usage: add/edit/delete [-c changelist#] [ -d -f -I -k -n -v ] [-t type] files..." } ;
ErrorId MsgServer::UseOpen2            = { ErrorOf( ES_SERVER, 398, E_FAILED, EV_USAGE, 0 ), "Usage: add/delete [-c changelist#] [ -d -f -I -n -v ] [-t type] files..." } ;
ErrorId MsgServer::UseOpened           = { ErrorOf( ES_SERVER, 264, E_FAILED, EV_USAGE, 0 ), "Usage: opened [ -a -m max ] [ -c changelist# -C client -u user -s | -x ] [ files... ]" } ;
ErrorId MsgServer::UseOpened2           = { ErrorOf( ES_SERVER, 661, E_FAILED, EV_USAGE, 0 ), "Usage: opened [ -a -m max -x ] [ files... ]" } ;
ErrorId MsgServer::UsePasswd           = { ErrorOf( ES_SERVER, 265, E_FAILED, EV_USAGE, 0 ), "Usage: passwd [ -O oldPasswd -P newPasswd ] [ username ]" } ;
ErrorId MsgServer::UsePopulate	       = { ErrorOf( ES_SERVER, 592, E_FAILED, EV_USAGE, 0 ), "Usage: populate [ -d desc -f -m max -n -o -r -s from ] [ -b branch to... | -S stream [ -P parent ] [ file... ] | from to ]" } ;
ErrorId MsgServer::UsePopulateb        = { ErrorOf( ES_SERVER, 593, E_FAILED, EV_USAGE, 0 ), "Usage: populate [ -d desc -f -m max -n -o -r -s from ] -b branch [ to... ]" } ;
ErrorId MsgServer::UsePopulateS        = { ErrorOf( ES_SERVER, 594, E_FAILED, EV_USAGE, 0 ), "Usage: populate [ -d desc -f -m max -n -o -r -s from ] -S stream [ -P parent ] [ file... ]" } ;
ErrorId MsgServer::UsePrint            = { ErrorOf( ES_SERVER, 623, E_FAILED, EV_USAGE, 0 ), "Usage: print [-a -A -k -o localFile -q -m max] [-U] files..." } ;
ErrorId MsgServer::UseProtect          = { ErrorOf( ES_SERVER, 266, E_FAILED, EV_USAGE, 0 ), "Usage: protect [ -i | -o ]" } ;
ErrorId MsgServer::UseProtects         = { ErrorOf( ES_SERVER, 339, E_FAILED, EV_USAGE, 0 ), "Usage: protects [ -a | -g group | -u user ] [ -h host ] [ -m ] [ file ... ]" } ;
ErrorId MsgServer::UsePull             = { ErrorOf( ES_SERVER, 441, E_FAILED, EV_USAGE, 0 ), "Usage: pull [ -u | -l [ -s | -j ] | -d -f file -r rev ] [ -J prefix -P filterpattern -T tableexcludelist ] [ -i <N> ]" } ;
ErrorId MsgServer::UsePurge            = { ErrorOf( ES_SERVER, 267, E_FAILED, EV_USAGE, 0 ), "Usage: obliterate [-y -A -b -a -h] files..." } ;
ErrorId MsgServer::UseRelease          = { ErrorOf( ES_SERVER, 268, E_FAILED, EV_USAGE, 0 ), "Usage: revert [ -a -n -k -w -c changelist# ] files..." } ;
ErrorId MsgServer::UseRenameUser       = { ErrorOf( ES_SERVER, 701, E_FAILED, EV_USAGE, 0 ), "Usage: renameuser --from=old --to=new" } ;
ErrorId MsgServer::UseReconcile        = { ErrorOf( ES_SERVER, 582, E_FAILED, EV_USAGE, 0 ), "Usage: reconcile [ -c changelist# ] [ -a -e -d -l -f -I -m -n -w ] [files...]" } ;
ErrorId MsgServer::UseStatus        = { ErrorOf( ES_SERVER, 596, E_FAILED, EV_USAGE, 0 ), "Usage: status [ -c changelist# ] [ -A | [ -a -e -d ] ] [ -f -m -I ] [files...]" } ;
ErrorId MsgServer::UseReload           = { ErrorOf( ES_SERVER, 613, E_FAILED, EV_USAGE, 0 ), "Usage: reload [ -f ] [ -c client ] | [ -l label ] | [ -s stream ] [ -p address ]" } ;
ErrorId MsgServer::UseReopen           = { ErrorOf( ES_SERVER, 269, E_FAILED, EV_USAGE, 0 ), "Usage: reopen [-c changelist#] [-t type] files..." } ;
ErrorId MsgServer::UseResolve          = { ErrorOf( ES_SERVER, 270, E_FAILED, EV_USAGE, 0 ), "Usage: resolve [ -af -am -as -at -ay -A<flags> -c changelist# -d<flags> -f -n -N -o -t -v ] [ files... ]" } ;
ErrorId MsgServer::UseResolved         = { ErrorOf( ES_SERVER, 271, E_FAILED, EV_USAGE, 0 ), "Usage: resolved [ -o ] [files...]" } ;
ErrorId MsgServer::UseRestore          = { ErrorOf( ES_SERVER, 454, E_FAILED, EV_USAGE, 0 ), "Usage: restore -D depot [-n] files..." } ;
ErrorId MsgServer::UseRetype           = { ErrorOf( ES_SERVER, 349, E_FAILED, EV_USAGE, 0 ), "Usage: retype [ -l -n ] -t type files..." } ;
ErrorId MsgServer::UseReview           = { ErrorOf( ES_SERVER, 272, E_FAILED, EV_USAGE, 0 ), "Usage: review [ -c start_changelist# ] [ -t counter_name ]" } ;
ErrorId MsgServer::UseReviews          = { ErrorOf( ES_SERVER, 273, E_FAILED, EV_USAGE, 0 ), "Usage: reviews [ -C client ] [ -c changelist# ] [ files... ]" } ;
ErrorId MsgServer::UseSearch           = { ErrorOf( ES_SERVER, 274, E_FAILED, EV_USAGE, 0 ), "Usage: search [ -m max ] words ..." } ;
ErrorId MsgServer::UseServer           = { ErrorOf( ES_SERVER, 562, E_FAILED, EV_USAGE, 0 ), "Usage: server [ -i | -o | -d | -g ] [ serverID ]" } ;
ErrorId MsgServer::UseServerid         = { ErrorOf( ES_SERVER, 571, E_FAILED, EV_USAGE, 0 ), "Usage: serverid [ serverID ]" } ;
ErrorId MsgServer::UseServero          = { ErrorOf( ES_SERVER, 564, E_FAILED, EV_USAGE, 0 ), "Usage: server -o serverID" } ;
ErrorId MsgServer::UseServerd          = { ErrorOf( ES_SERVER, 565, E_FAILED, EV_USAGE, 0 ), "Usage: server -d serverID" } ;
ErrorId MsgServer::UseServeri          = { ErrorOf( ES_SERVER, 566, E_FAILED, EV_USAGE, 0 ), "Usage: server -i" } ;
ErrorId MsgServer::UseServers          = { ErrorOf( ES_SERVER, 563, E_FAILED, EV_USAGE, 0 ), "Usage: servers" } ;
ErrorId MsgServer::UseSizes            = { ErrorOf( ES_SERVER, 341, E_FAILED, EV_USAGE, 0 ), "Usage: sizes [ -a ] [ -s | -z ] [ -b blocksize ] [ -h | -H ] [ -m max ] [ -S | -U | -A ] files..." } ;
ErrorId MsgServer::UseShelve           = { ErrorOf( ES_SERVER, 399, E_FAILED, EV_USAGE, 0 ), "Usage: shelve [ -a option -p ] [ -i [ -f | -r ] | [ -a option -p ] -r -c changelist | -c changelist [ -d ] [ -f ] [ file ... ] ] [ files ] " } ;
ErrorId MsgServer::UseShelvec          = { ErrorOf( ES_SERVER, 400, E_FAILED, EV_USAGE, 0 ), "Usage: shelve -c changelist# [ -d [ -f ] [ file ... ] | [ -a option -p ] -r | [ -a option -p ] [ -f ] [ file ... ] ]" } ;
ErrorId MsgServer::UseShelvei          = { ErrorOf( ES_SERVER, 414, E_FAILED, EV_USAGE, 0 ), "Usage: shelve -i [ -f | -r ] [ -a option -p ]" } ;
ErrorId MsgServer::UseShelver          = { ErrorOf( ES_SERVER, 415, E_FAILED, EV_USAGE, 0 ), "Usage: shelve -r -c changelist# [ -a option -p ]" } ;
ErrorId MsgServer::UseShelveNoOpts          = { ErrorOf( ES_SERVER, 416, E_FAILED, EV_USAGE, 0 ), "Usage: shelve [ files ]" } ;
ErrorId MsgServer::UseSnap             = { ErrorOf( ES_SERVER, 345, E_FAILED, EV_USAGE, 0 ), "Usage: snap [ -n ] source target" } ;
ErrorId MsgServer::UseSpec             = { ErrorOf( ES_SERVER, 302, E_FAILED, EV_USAGE, 0 ), "Usage: spec [ -d | -i | -o ] type" } ;
ErrorId MsgServer::UseStream           = { ErrorOf( ES_SERVER, 383, E_FAILED, EV_USAGE, 0 ), "Usage: stream [ -d -i -o -P parent -t type -v ] [ -f ] [ streamname ]" } ;
ErrorId MsgServer::UseStreamc          = { ErrorOf( ES_SERVER, 540, E_FAILED, EV_USAGE, 0 ), "Usage: stream [ -P parent ] -t type streamname" } ;
ErrorId MsgServer::UseStreamd          = { ErrorOf( ES_SERVER, 384, E_FAILED, EV_USAGE, 0 ), "Usage: stream -d [ -f ] streamname" } ;
ErrorId MsgServer::UseStreami          = { ErrorOf( ES_SERVER, 385, E_FAILED, EV_USAGE, 0 ), "Usage: stream -i [ -f ]" } ;
ErrorId MsgServer::UseStreamo          = { ErrorOf( ES_SERVER, 386, E_FAILED, EV_USAGE, 0 ), "Usage: stream [ -P parent -t type ] -o streamname" } ;
ErrorId MsgServer::UseStreams          = { ErrorOf( ES_SERVER, 387, E_FAILED, EV_USAGE, 0 ), "Usage: streams [ -U -F filter -T fields -m max ] [ streamPath... ]" } ;
ErrorId MsgServer::UseSubmit           = { ErrorOf( ES_SERVER, 275, E_FAILED, EV_USAGE, 0 ), "Usage: submit [ -i -s -r -f option ] [ -c changelist# | -e shelvedChange# | -d description ] [file] " } ;
ErrorId MsgServer::UseSubmitc          = { ErrorOf( ES_SERVER, 276, E_FAILED, EV_USAGE, 0 ), "Usage: submit [ -r -f option ] -c changelist#" } ;
ErrorId MsgServer::UseSubmitd          = { ErrorOf( ES_SERVER, 446, E_FAILED, EV_USAGE, 0 ), "Usage: submit [ -r -f option ] -d description [ file ]\n" } ;
ErrorId MsgServer::UseSubmite          = { ErrorOf( ES_SERVER, 639, E_FAILED, EV_USAGE, 0 ), "Usage: submit -e shelvedChange#" } ;
ErrorId MsgServer::UseSync             = { ErrorOf( ES_SERVER, 277, E_FAILED, EV_USAGE, 0 ), "Usage: sync [ -f -k -n -N -p -q -s ] [-m max] [files...]" } ;
ErrorId MsgServer::UseSyncp            = { ErrorOf( ES_SERVER, 348, E_FAILED, EV_USAGE, 0 ), "Usage: sync [ -n -N -p -q ] [-m max] [files...]" } ;
ErrorId MsgServer::UseSyncs            = { ErrorOf( ES_SERVER, 503, E_FAILED, EV_USAGE, 0 ), "Usage: sync [ -n -N -q -s ] [-m max] [files...]" } ;
ErrorId MsgServer::UseTag              = { ErrorOf( ES_SERVER, 328, E_FAILED, EV_USAGE, 0 ), "Usage: tag [-d -g -n -U] -l label files..." } ;
ErrorId MsgServer::UseTrait            = { ErrorOf( ES_SERVER, 330, E_FAILED, EV_USAGE, 0 ), "Usage: attribute [-e -f -p] -n name [-v value] files..." } ;
ErrorId MsgServer::UseTransmit         = { ErrorOf( ES_SERVER, 714, E_FAILED, EV_USAGE, 0 ), "Usage: transmit -t taskid" } ;
ErrorId MsgServer::UseTraiti           = { ErrorOf( ES_SERVER, 435, E_FAILED, EV_USAGE, 0 ), "Usage: attribute -i [-e -f -p] -n name [file]" } ;
ErrorId MsgServer::UseTriggers         = { ErrorOf( ES_SERVER, 278, E_FAILED, EV_USAGE, 0 ), "Usage: triggers [ -i | -o ]" } ;
ErrorId MsgServer::UseTypeMap          = { ErrorOf( ES_SERVER, 279, E_FAILED, EV_USAGE, 0 ), "Usage: typemap [ -i | -o ]" } ;
ErrorId MsgServer::UseUnload           = { ErrorOf( ES_SERVER, 611, E_FAILED, EV_USAGE, 0 ), "Usage: unload [ -f -L -z ] [ -c client | -l label | -s stream ] | [ -a | -al | -ac ] [ -d date | -u user ] [ -o output ]" } ;
ErrorId MsgServer::UseUnlock           = { ErrorOf( ES_SERVER, 280, E_FAILED, EV_USAGE, 0 ), "Usage: unlock [ -f ] [-c | -s changelist# | -x ] [files...]" } ;
ErrorId MsgServer::UseUnshelve         = { ErrorOf( ES_SERVER, 403, E_FAILED, EV_USAGE, 0 ), "Usage: unshelve -s changelist# [ -f -n ] [-c changelist#] [-b branch|-S stream] [file ...]" } ;
ErrorId MsgServer::UseUser             = { ErrorOf( ES_SERVER, 281, E_FAILED, EV_USAGE, 0 ), "Usage: user [ -f -d -i -o ] [ username ]" } ;
ErrorId MsgServer::UseUsero            = { ErrorOf( ES_SERVER, 282, E_FAILED, EV_USAGE, 0 ), "Usage: user -o username" } ;
ErrorId MsgServer::UseUserd            = { ErrorOf( ES_SERVER, 283, E_FAILED, EV_USAGE, 0 ), "Usage: user -d [ -f ] username" } ;
ErrorId MsgServer::UseUseri            = { ErrorOf( ES_SERVER, 284, E_FAILED, EV_USAGE, 0 ), "Usage: user -i [ -f ]" } ;
ErrorId MsgServer::UseUsers            = { ErrorOf( ES_SERVER, 285, E_FAILED, EV_USAGE, 0 ), "Usage: users [ -l -a -r -c ] [ -m max ] [ user ... ]" } ;
ErrorId MsgServer::UseVerify           = { ErrorOf( ES_SERVER, 286, E_FAILED, EV_USAGE, 0 ), "Usage: verify [ -m maxRevs ] [ -q -s ] [ -t | -u | -v | -z ] [ -X ] [ -U ] [ -b batch ] files..." } ;
ErrorId MsgServer::UseWhere            = { ErrorOf( ES_SERVER, 287, E_FAILED, EV_USAGE, 0 ), "Usage: where [files...]" } ;
ErrorId MsgServer::UseProxyInfo        = { ErrorOf( ES_SERVER, 541, E_FAILED, EV_USAGE, 0 ), "Usage: proxy" } ;
ErrorId MsgServer::UseProxy            = { ErrorOf( ES_SERVER, 288, E_FAILED, EV_USAGE, 0 ), "Usage: p4p -h for usage." } ;
ErrorId MsgServer::UseMove             = { ErrorOf( ES_SERVER, 375, E_FAILED, EV_USAGE, 0 ), "Usage: move [-c changelist#] [ -f ] [ -k ] [-t type] from to" } ;
ErrorId MsgServer::UsePing             = { ErrorOf( ES_SERVER, 391, E_FAILED, EV_USAGE, 0 ), "Usage: ping [ -f -p ] [ -i iterations ] [ -t seconds ] [ -c messages] [ -s server_message_size ] [-r client_message_size]" };

ErrorId MsgServer::NotAsService      = { ErrorOf( ES_SERVER, 443, E_FAILED, EV_USAGE, 0 ), "Service user may not login to all hosts." } ;

ErrorId MsgServer::ServerTooOld        = { ErrorOf( ES_SERVER, 290, E_FAILED, EV_FAULT, 0 ), "Server is too old for use with Proxy" } ;
ErrorId MsgServer::ProxyChain          = { ErrorOf( ES_SERVER, 291, E_FAILED, EV_FAULT, 0 ), "Proxy servers may not be chained together" } ;
ErrorId MsgServer::ProxyDelivered      = { ErrorOf( ES_SERVER, 293, E_INFO, 0, 1 ), "File %path% delivered from proxy server" } ;
ErrorId MsgServer::RmtAuthFailed       = { ErrorOf( ES_SERVER, 294, E_FAILED, EV_FAULT, 0 ), "Remote authorization server access failed." } ;
ErrorId MsgServer::ServiceNotProvided  = { ErrorOf( ES_SERVER, 572, E_FAILED, EV_USAGE, 0 ), "Server does not provide this service." } ;
ErrorId MsgServer::ReplicaRestricted   = { ErrorOf( ES_SERVER, 420, E_FAILED, EV_FAULT, 0 ), "Replica does not support this command." } ;
ErrorId MsgServer::RequiresJournaling  = { ErrorOf( ES_SERVER, 662, E_FAILED, EV_FAULT, 0 ), "Replication requires that journaling be enabled." } ;
ErrorId MsgServer::ReplicaWrongClient  = { ErrorOf( ES_SERVER, 616, E_FAILED, EV_FAULT, 1 ), "Client '%client%' is not restricted to this server." } ;
ErrorId MsgServer::ReplicaWrongLabel   = { ErrorOf( ES_SERVER, 659, E_FAILED, EV_FAULT, 1 ), "Label '%label%' is not restricted to this server." } ;
ErrorId MsgServer::ChangeNotLocal  = { ErrorOf( ES_SERVER, 665, E_FAILED, EV_USAGE, 1 ), "Change %changeNum% belongs to a client not local to this server." } ;
ErrorId MsgServer::ReplicaWrongServer  = { ErrorOf( ES_SERVER, 658, E_FAILED, EV_USAGE, 4 ), "%objectType% '%objectName%' is restricted to use on server '%serverID%', not '%ourServerID%'." } ;
ErrorId MsgServer::DomainIsLocal  = { ErrorOf( ES_SERVER, 673, E_FAILED, EV_USAGE, 2 ), "%objectType% '%objectName%' is already bound to this server, transfer from remote server is not needed." } ;
ErrorId MsgServer::NotACommitServer    = { ErrorOf( ES_SERVER, 655, E_FAILED, EV_FAULT, 1 ), "Edge Server submit from '%client%' is refused. This server has not been configured as a Commit Server, and will not accept such requests. To accept such requests, please use the 'p4 server' and 'p4 serverid' commands to configure the Commit Server behaviors." } ;
ErrorId MsgServer::ReplicaNoUpgrade    = { ErrorOf( ES_SERVER, 421, E_FAILED, EV_FAULT, 0 ), "Replica can not upgrade automatically." } ;
ErrorId MsgServer::ReplicaBadOption    = { ErrorOf( ES_SERVER, 422, E_FAILED, EV_FAULT, 0 ), "Unknown Replica Option." } ;
ErrorId MsgServer::UnknownReplicationMode = { ErrorOf( ES_SERVER, 468, E_FAILED, EV_FAULT, 1 ), "Unknown replication mode '%mode%'." } ;
ErrorId MsgServer::MissingReplicationMode = { ErrorOf( ES_SERVER, 469, E_FAILED, EV_FAULT, 1 ), "Missing replication mode: please specify %missingMode%." } ;
ErrorId MsgServer::P4TARGETWasSet         = { ErrorOf( ES_SERVER, 615, E_FAILED, EV_FAULT, 0 ), "It appears that the P4TARGET configurable was set for this server, indicating it is a replica server of some type. If that was incorrect, issue the command 'p4d -cshow' to display configurable settings, and issue the command 'p4d \"-cunset P4TARGET\"' to delete the incorrect P4TARGET setting." } ;
ErrorId MsgServer::UnknownReplicationTarget = { ErrorOf( ES_SERVER, 470, E_FAILED, EV_FAULT, 1 ), "Unknown replication target '%target%'." } ;
ErrorId MsgServer::ReplicaXferFailed   = { ErrorOf( ES_SERVER, 474, E_FAILED, EV_FAULT, 0 ), "Transfer of librarian file '%file%' failed." } ;
ErrorId MsgServer::BFNoOverwriteLocal  = { ErrorOf( ES_SERVER, 622, E_FAILED, EV_FAULT, 5 ), "Replica name conflict: Globally-defined object %domainName% of type %domainType% would overwrite locally-defined object %localName% of type %localType%, which is bound to server %serverId%. Replication has been halted for this replica. To resume replication, the locally-defined object must be deleted (e.g., 'p4 client -d' to delete a Build Farm Client)." } ;
ErrorId MsgServer::BadPCache           = { ErrorOf( ES_SERVER, 295, E_FAILED, EV_ADMIN, 0 ), "Proxy Cache directory (set with $P4PCACHE or -r flag) invalid." } ;
ErrorId MsgServer::ProxyNoRemote       = { ErrorOf( ES_SERVER, 296, E_FAILED, EV_ADMIN, 0 ), "Proxy Does not support caching remote server access." } ;
ErrorId MsgServer::ProxyUpdateFail     = { ErrorOf( ES_SERVER, 301, E_WARN, EV_ADMIN, 1 ), "Proxy could not update its cache.  File is %file%" } ;

ErrorId MsgServer::RemoteInvalidCmd    = { ErrorOf( ES_SERVER, 306, E_FAILED, EV_USAGE, 0 ), "User 'remote' is not allowed direct access to commands." } ;
ErrorId MsgServer::InvalidNesting      = { ErrorOf( ES_SERVER, 528, E_FATAL, EV_FAULT, 2 ), "Command %outerCommand% was unexpectedly interrupted by command %nestedCommand%" } ;

ErrorId MsgServer::ClientTooOld        = { ErrorOf( ES_SERVER, 428, E_FAILED, EV_USAGE, 1 ), "Client is too old to use this server.  %message%" } ;

ErrorId MsgServer::NoTicketSupport     = { ErrorOf( ES_SERVER, 331, E_WARN, EV_USAGE, 0 ), "Must upgrade to 2004.2 p4 to access tickets." } ;

ErrorId MsgServer::CommandCancelled    = { ErrorOf( ES_SERVER, 332, E_FAILED, EV_ADMIN, 0 ), "Command terminated by 'p4 monitor terminate'." } ;

ErrorId MsgServer::AdminNoSpecDepot    = { ErrorOf( ES_SERVER, 353, E_FAILED, EV_ADMIN, 0 ), "Can't create forms - no 'spec' depot found." } ;
ErrorId MsgServer::AdminNoSuchSpec     = { ErrorOf( ES_SERVER, 578, E_WARN, EV_ADMIN, 1 ), "No form specifications of type %specName% were found." } ;
ErrorId MsgServer::AdminPasswordNoSuchUser = { ErrorOf( ES_SERVER, 618, E_FAILED, EV_UNKNOWN, 1 ), "%user% - no such user, or user does not have a password." } ;
ErrorId MsgServer::AdminPasswordNoPasswords = { ErrorOf( ES_SERVER, 619, E_FAILED, EV_EMPTY, 0 ), "No users with passwords found." } ;

ErrorId MsgServer::ImportReport        = { ErrorOf( ES_SERVER, 361, E_INFO, EV_NONE, 1 ), "Imported %count% journal record(s)." } ;

ErrorId MsgServer::AdminNothingLocked  = { ErrorOf( ES_SERVER, 366, E_INFO, EV_ADMIN, 0 ), "No tables locked." } ;
ErrorId MsgServer::AdminReplicaCkp     = { ErrorOf( ES_SERVER, 529, E_INFO, EV_ADMIN, 0 ), "The 'pull' command will perform the checkpoint at the next rotation of the journal on the master." } ;
ErrorId MsgServer::NoUserLogs          = { ErrorOf( ES_SERVER, 638, E_WARN, EV_ADMIN, 0 ), "No serverlog.file configurables specify logs which capture user log records." } ;
ErrorId MsgServer::AdminNothingLogged  = { ErrorOf( ES_SERVER, 373, E_WARN, EV_ADMIN, 0 ), "No journal or log files found." } ;
ErrorId MsgServer::LogtailNoLog  = { ErrorOf( ES_SERVER, 389, E_WARN, EV_ADMIN, 0 ), "Perforce server is not logging to an errorLog." } ;
ErrorId MsgServer::AdminSizeData  = { ErrorOf( ES_SERVER, 372, E_INFO, EV_ADMIN, 2 ), "%name% %size% bytes" } ;

ErrorId MsgServer::Move091             = { ErrorOf( ES_SERVER, 376, E_FAILED, EV_UPGRADE, 0 ), "Only 2009.1 or later clients support 'p4 move'." } ;
ErrorId MsgServer::Move101             = { ErrorOf( ES_SERVER, 425, E_FAILED, EV_UPGRADE, 0 ), "Only 2010.1 or later clients support 'p4 move -f'." } ;
ErrorId MsgServer::MoveRejected        = { ErrorOf( ES_SERVER, 542, E_FAILED, EV_ADMIN, 0 ), "Operation 'move' disabled on this server."} ;
ErrorId MsgServer::CommandDisabled     = { ErrorOf( ES_SERVER, 600, E_FAILED, EV_ADMIN, 1 ), "Operation '%commandName%' disabled on this server."} ;

ErrorId MsgServer::ActionResolve111    = { ErrorOf( ES_SERVER, 498, E_WARN, EV_UPGRADE, 2 ), "%localFile% - upgrade to a 2011.1 or later client to perform an interactive %resolveType% resolve, or use resolve -a." } ;

ErrorId MsgServer::BadJournalNum       = { ErrorOf( ES_SERVER, 379, E_FAILED, EV_ADMIN, 1 ), "Journal %number% is not available" } ;
ErrorId MsgServer::BadCheckpointNum       = { ErrorOf( ES_SERVER, 380, E_FAILED, EV_ADMIN, 1 ), "Checkpoint %number% is not available" } ;
ErrorId MsgServer::JournalorCheckpointRequired = { ErrorOf( ES_SERVER, 388, E_FAILED, EV_ADMIN, 0 ), "A journal or checkpoint number is required (-j or -c)" } ;
ErrorId MsgServer::CurJournalButNotJournaling = { ErrorOf( ES_SERVER, 432, E_FAILED, EV_ADMIN, 0 ), "The current journal may not be exported because journaling is disabled." } ;
ErrorId MsgServer::PullNotReplica = { ErrorOf( ES_SERVER, 442, E_FAILED, EV_ADMIN, 0 ), "Pull only allowed on replica servers." } ;
ErrorId MsgServer::PullCommandRunning = { ErrorOf( ES_SERVER, 656, E_FAILED, EV_USAGE, 0 ), "A pull command is already running in this server." } ;
ErrorId MsgServer::TransferCancelled   = { ErrorOf( ES_SERVER, 643, E_INFO, EV_NONE, 0 ), "The file content transfer was cancelled." } ;
ErrorId MsgServer::NoSuchTransfer      = { ErrorOf( ES_SERVER, 644, E_FAILED, EV_ADMIN, 2 ), "File %lbrFile% revision %lbrRev% is not currently scheduled to be transferred." } ;
ErrorId MsgServer::PullOnDemand   = { ErrorOf( ES_SERVER, 645, E_FAILED, EV_ADMIN, 0 ), "This command is not used with an ondemand replica server." } ;
ErrorId MsgServer::TransferNotReplica = { ErrorOf( ES_SERVER, 500, E_FAILED, EV_ADMIN, 0 ), "Verify -t only allowed on replica servers." } ;
ErrorId MsgServer::UsersCRNotReplica = { ErrorOf( ES_SERVER, 536, E_FAILED, EV_ADMIN, 0 ), "Users -c and -r only allowed on replica servers." } ;
ErrorId MsgServer::UsersCRNotBoth = { ErrorOf( ES_SERVER, 539, E_FAILED, EV_ADMIN, 0 ), "Users -c and -r may not be used together." } ;
ErrorId MsgServer::TZMismatch	       = { ErrorOf( ES_SERVER, 538, E_WARN, EV_ADMIN, 0 ), "Replica Timezone does not match master.  This will cause problems with keywords." } ;
ErrorId MsgServer::PullTransferPending = { ErrorOf( ES_SERVER, 457, E_INFO, EV_NONE, 0 ), "%file% %rev% %type% %state% %process% %timestamp%" } ;
ErrorId MsgServer::PullTransferSummary = { ErrorOf( ES_SERVER, 519, E_INFO, EV_NONE, 4 ), "File transfers: %transfersActive% active/%transfersTotal% total, bytes: %bytesActive% active/%bytesTotal% total." } ;
ErrorId MsgServer::PullJournalSummary  = { ErrorOf( ES_SERVER, 530, E_INFO, EV_NONE, 3 ), "Current %server% journal state is:\tJournal %journal%,\tSequence %sequence%." } ;
ErrorId MsgServer::PullJournalDate     = { ErrorOf( ES_SERVER, 597, E_INFO, EV_NONE, 1 ), "The statefile was last modified at:\t%lastModTime%." } ;
ErrorId MsgServer::ReplicaServerTime  = { ErrorOf( ES_SERVER, 653, E_INFO, EV_NONE, 2 ), "The replica server time is currently:\t%serverDate% %serverTimeZone%" };
ErrorId MsgServer::CacheAlreadyPurged  = { ErrorOf( ES_SERVER, 706, E_INFO, EV_NONE, 2 ), "Cached content of %file% %rev% has already been purged." } ;
ErrorId MsgServer::JournalCounterMismatch  = { ErrorOf( ES_SERVER, 531, E_WARN, EV_NONE, 2 ), "Journal Counter Rotation Mismatch counter %counter% should be %journal%" };


ErrorId MsgServer::NeedFilePath         = { ErrorOf( ES_SERVER, 532, E_FAILED, EV_USAGE, 1 ), "Empty file path not allowed in '%filespec%'." } ;
ErrorId MsgServer::NoSuchField          = { ErrorOf( ES_SERVER, 444, E_FAILED, EV_UNKNOWN, 1 ), "Field %field% doesn't exist." } ;
ErrorId MsgServer::EmptyTypeList        = { ErrorOf( ES_SERVER, 445, E_FAILED, EV_UNKNOWN, 1 ), "The list of fields may not be empty." } ;
ErrorId MsgServer::NotStreamReady       = { ErrorOf( ES_SERVER, 447, E_FAILED, EV_USAGE, 1 ), "Client '%client%' requires an application that can fully support streams." } ;
ErrorId MsgServer::NotStreamOwner       = { ErrorOf( ES_SERVER, 473, E_FAILED, EV_USAGE, 2 ), "Currently only user '%user%' can submit to stream '%stream%'." } ;
ErrorId MsgServer::VersionedStream      = { ErrorOf( ES_SERVER, 599, E_FAILED, EV_USAGE, 1 ), "Can't submit from a noncurrent stream client '%stream%'." } ;
ErrorId MsgServer::BadSortOption        = { ErrorOf( ES_SERVER, 461, E_FAILED, EV_USAGE, 1 ), "%name% is not a valid sort attribute name." } ;
ErrorId MsgServer::TooManySortTraits    = { ErrorOf( ES_SERVER, 462, E_FAILED, EV_USAGE, 0 ), "Too many sort attributes (only 2 allowed)." } ;

ErrorId MsgServer::AttrNoPropEdge    = { ErrorOf( ES_SERVER, 601, E_FAILED, EV_USAGE, 0 ), "Cannot add or change propagating attributes on pending files from an edge server." } ;
ErrorId MsgServer::InvalidStartupCommand = { ErrorOf( ES_SERVER, 448, E_FAILED, EV_ADMIN, 1 ), "Startup command '%cmd%' is unknown or invalid." } ;
ErrorId MsgServer::StartupCommandError = { ErrorOf( ES_SERVER, 458, E_FAILED, EV_ADMIN, 1 ), "Startup command failed: %message%" } ;
ErrorId MsgServer::InvalidServerChain  = { ErrorOf( ES_SERVER, 505, E_FAILED, EV_USAGE, 1 ), "%serverType% servers may not be chained." } ;
ErrorId MsgServer::CommunicationLoop   = { ErrorOf( ES_SERVER, 576, E_FAILED, EV_USAGE, 1 ), "Server %serverID% may not send a message to itself." } ;

ErrorId MsgServer::NoCustomSpec = { ErrorOf( ES_SERVER, 475, E_FAILED, EV_ADMIN, 1 ), "Custom spec of type '%specType%' is not allowed. Set spec.custom=1 to override." } ;
ErrorId MsgServer::OnlyOneFilter       = { ErrorOf( ES_SERVER, 533, E_FAILED, EV_USAGE, 0 ), "Specify either -e or -E, not both." } ;
ErrorId MsgServer::JournalFilterBad    = { ErrorOf( ES_SERVER, 647, E_FAILED, EV_USAGE, 0 ), "-P filter patterns must take the form: [ic:|xc:|if:|xf:]//pattern" } ;

ErrorId MsgServer::CopyWrongDirection  = { ErrorOf( ES_SERVER, 520, E_FAILED, EV_USAGE, 1 ), "Stream %stream% needs 'merge' not 'copy' in this direction." } ;
ErrorId MsgServer::CopyDoNothing       = { ErrorOf( ES_SERVER, 521, E_FAILED, EV_USAGE, 1 ), "Stream %stream% not configured to 'copy' or 'merge' changes in this direction." } ;
ErrorId MsgServer::CopyNeedsMergeFirst = { ErrorOf( ES_SERVER, 522, E_FAILED, EV_USAGE, 1 ), "Stream %stream% cannot 'copy' over outstanding 'merge' changes." } ;
ErrorId MsgServer::MergeWrongDirection = { ErrorOf( ES_SERVER, 526, E_FAILED, EV_USAGE, 1 ), "Stream %stream% needs 'copy' not 'merge' in this direction." } ;
ErrorId MsgServer::NoReparentingTask   = { ErrorOf( ES_SERVER, 654, E_FAILED, EV_USAGE, 1 ), "Stream %stream% is a task stream and therefore cannot 'merge' or 'copy' to/from streams other than its parent." } ;

ErrorId MsgServer::UnloadDepotMissing  = { ErrorOf( ES_SERVER, 612, E_FAILED, EV_USAGE, 0 ), "No unload depot has been defined for this server." } ;
ErrorId MsgServer::UnloadOtherUser     = { ErrorOf( ES_SERVER, 617, E_FAILED, EV_USAGE, 0 ), "Specify the '-f' flag in order to unload clients or labels owned by another user." } ;
ErrorId MsgServer::CantUnloadLocked    = { ErrorOf( ES_SERVER, 630, E_FAILED, EV_USAGE, 2 ), "Specify the '-L' flag in order to unload locked %domainType% %domainName%." } ;
ErrorId MsgServer::BoundClientExists   = { ErrorOf( ES_SERVER, 580, E_FAILED, EV_USAGE, 1 ), "Client %client% already exists." } ;
ErrorId MsgServer::NewUserExists       = { ErrorOf( ES_SERVER, 702, E_FAILED, EV_USAGE, 1 ), "User %user% already exists." } ;
ErrorId MsgServer::NewUserHasDomains   = { ErrorOf( ES_SERVER, 711, E_FAILED, EV_USAGE, 1 ), "User %user% has already created workspaces, labels, or other spec objects in this server." } ;
ErrorId MsgServer::NewUserHasChanges   = { ErrorOf( ES_SERVER, 712, E_FAILED, EV_USAGE, 1 ), "User %user% has already created changelists in this server." } ;
ErrorId MsgServer::DontRenameSelf      = { ErrorOf( ES_SERVER, 703, E_FAILED, EV_USAGE, 1 ), "User %user% is the current user, and cannot be renamed." } ;
ErrorId MsgServer::UserRenamed         = { ErrorOf( ES_SERVER, 710, E_INFO, 0, 2 ), "User %oldUser% renamed to %newUser%." } ;
ErrorId MsgServer::BoundClientServerID = { ErrorOf( ES_SERVER, 581, E_FAILED, EV_USAGE, 0 ), "Bound client must be created on a server with a fixed identity." } ;
ErrorId MsgServer::ChangeNotSubmitted  = { ErrorOf( ES_SERVER, 657, E_FAILED, EV_USAGE, 1 ), "Change %changeNum% is not a submitted change." } ;
ErrorId MsgServer::NotInCluster        = { ErrorOf( ES_SERVER, 667, E_FAILED, EV_USAGE, 0 ), "Server is not a member of a cluster." } ;
ErrorId MsgServer::NotClusterReplica   = { ErrorOf( ES_SERVER, 668, E_FAILED, EV_USAGE, 0 ), "Server is not a depot-standby." } ;
ErrorId MsgServer::NotClusterMaster    = { ErrorOf( ES_SERVER, 669, E_FAILED, EV_USAGE, 2 ), "Server '%server%' is not a depot-master (current journal owner is '%owner%')." } ;
ErrorId MsgServer::NotClusterService   = { ErrorOf( ES_SERVER, 707, E_FAILED, EV_USAGE, 0 ), "Server is not a service-node." } ;
ErrorId MsgServer::NotEdgeLocal        = { ErrorOf( ES_SERVER, 713, E_FAILED, EV_USAGE, 0 ), "Server is not a workspace-server." } ;
ErrorId MsgServer::ClusterCannotWriteJournal  = { ErrorOf( ES_SERVER, 670, E_FAILED, EV_USAGE, 0 ), "Journal writing is not enabled at this server." } ;
ErrorId MsgServer::ClusterNotAllowed   = { ErrorOf( ES_SERVER, 671, E_FAILED, EV_USAGE, 1 ), "Operation '%op%' is not supported for a cluster member." } ;
ErrorId MsgServer::CommandUnsupported  = { ErrorOf( ES_SERVER, 715, E_FAILED, EV_USAGE, 1 ), "Command '%op%' is not supported on this hardware platform." } ;

ErrorId MsgServer::TemporaryLabelInfo  = { ErrorOf( ES_SERVER, 588, E_INFO, EV_NONE, 2 ), "Temporary label '%label%' updated %count% total file(s)." } ;

ErrorId MsgServer::NotDistributed      = { ErrorOf( ES_SERVER, 660, E_FAILED, EV_USAGE, 0 ), "This command is only supported in a distributed configuration." } ;
ErrorId MsgServer::PortMissing         = { ErrorOf( ES_SERVER, 672, E_FAILED, EV_USAGE, 1 ), "This network address '%addr%' does not include a port name or number." } ;
ErrorId MsgServer::TargetAccessFailed  = { ErrorOf( ES_SERVER, 708, E_FAILED, EV_COMM, 0 ), "Replica access to P4TARGET server failed." } ;

ErrorId MsgServer::BadTriggerOutput         = { ErrorOf( ES_SERVER, 675, E_FAILED, EV_ADMIN, 2 ), "A server-side trigger ('%trigger%') produced indecipherable output (%type%)" } ;

ErrorId MsgServer::ReopenNotOwnerCL	= { ErrorOf( ES_SERVER, 676, E_FAILED, EV_USAGE, 4 ), "%depotFile%%haveRev% already open on client '%client%' in %change% - not reopened." } ;

// ErrorId graveyard: retired/deprecated ErrorIds. 

ErrorId MsgServer::UseAdminCopyin      = { ErrorOf( ES_SERVER, 201, E_FAILED, EV_USAGE, 0 ), "Usage: admin copyin prefix" } ; // DEPRECATED
ErrorId MsgServer::UseAdminCopyout     = { ErrorOf( ES_SERVER, 202, E_FAILED, EV_USAGE, 0 ), "Usage: admin copyout prefix" } ; // DEPRECATED
ErrorId MsgServer::UseTunables    = { ErrorOf( ES_SERVER, 371, E_FAILED, EV_USAGE, 0 ), "Usage: tunables [ -a ]" } ; // DEPRECATED
ErrorId MsgServer::UseDomains          = { ErrorOf( ES_SERVER, 231, E_FAILED, EV_USAGE, 0 ), "Usage: branches/labels [ -t ] [ -u user ] [ [-e|-E] query -m max ]" } ; // DEPRECATED
ErrorId MsgServer::PasswordTooShort     = { ErrorOf( ES_SERVER, 308, E_FAILED, EV_ILLEGAL, 0 ), "Password should be at least 8 characters in length." } ; // DEPRECATED
ErrorId MsgServer::SubmitShelvedHasTask     = { ErrorOf( ES_SERVER, 646, E_FAILED, EV_NOTYET, 1 ), "Client %client% is a task stream client --  cannot submit shelved change."} ;
