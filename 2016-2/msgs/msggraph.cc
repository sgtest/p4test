/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msggraph.cc - definitions of errors for graph C++ interface
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
 * Current high value for a MsgOs error code is: 163
 */

# include <error.h>
# include <errornum.h>
# include <msggraph.h>

ErrorId MsgGraph::CommitDataShort  = { ErrorOf( ES_GRAPH, 1, E_INFO, EV_NONE, 3 ), "commit %sha%\ntree %tree%\n%description%\n" } ;
ErrorId MsgGraph::UseGraph            = { ErrorOf( ES_GRAPH, 61, E_FAILED, EV_USAGE, 0 ), "Usage: see %'p4 help graph'%" } ;
ErrorId MsgGraph::UseCatFile          = { ErrorOf( ES_GRAPH, 2, E_FAILED, EV_USAGE, 0 ), "Usage: %'cat-file [ commit | -n repo blob | -t ] object-sha'%" } ;
ErrorId MsgGraph::UseLsTree           = { ErrorOf( ES_GRAPH, 3, E_FAILED, EV_USAGE, 0 ), "Usage: %'ls-tree tree-sha'%" } ;
ErrorId MsgGraph::UseDiffTree         = { ErrorOf( ES_GRAPH, 4, E_FAILED, EV_USAGE, 0 ), "Usage: %'diff-tree -n repo tree-1-sha tree-2-sha'%" } ;
ErrorId MsgGraph::UseLog              = { ErrorOf( ES_GRAPH, 6, E_FAILED, EV_USAGE, 0 ), "Usage: %'log -n repo [ -u user -m N ] [ commit... ]'%" } ;
ErrorId MsgGraph::UseShowRef          = { ErrorOf( ES_GRAPH, 58, E_FAILED, EV_USAGE, 0 ), "Usage: %'show-ref [ -a -n repo -u user -t type -m N ]'%" } ;
ErrorId MsgGraph::UseMerge            = { ErrorOf( ES_GRAPH, 7, E_FAILED, EV_USAGE, 0 ), "Usage: %'merge [ --no-ff ] other-branch'%" } ;
ErrorId MsgGraph::UseReceivePack      = { ErrorOf( ES_GRAPH, 59, E_FAILED, EV_USAGE, 0 ), "Usage: %'receive-pack -n repo [-u user -v] -i files... [ -r refs... | -F refs... | -p packed-refs ]'%" } ;
ErrorId MsgGraph::UsePackObjects      = { ErrorOf( ES_GRAPH, 60, E_FAILED, EV_USAGE, 0 ), "Usage: %'pack-objects -n repo [-u user] -o git-pack-dir [ -a | commit... ]'%" } ;
ErrorId MsgGraph::UseGraphSync        = { ErrorOf( ES_GRAPH, 62, E_FAILED, EV_USAGE, 0 ), "Usage: %'sync [ commit... ]'%" } ;
ErrorId MsgGraph::UseGraphProtects    = { ErrorOf( ES_GRAPH, 66, E_FAILED, EV_USAGE, 0 ), "Usage: %'protects -n repo -u user [ -r reference ] [ file... ]'%" } ;
ErrorId MsgGraph::UseGraphList        = { ErrorOf( ES_GRAPH, 69, E_FAILED, EV_USAGE, 0 ), "Usage: %'list-repos [ -n repo -u user -m max ]'%" } ;
ErrorId MsgGraph::UseGraphCollect     = { ErrorOf( ES_GRAPH, 77, E_FAILED, EV_USAGE, 0 ), "Usage: %'collect [ -n -A -t days ]'%" } ;
ErrorId MsgGraph::UseGraphForkRepo    = { ErrorOf( ES_GRAPH, 80, E_FAILED, EV_USAGE, 0 ), "Usage: %'fork-repo [ -u user ] -n repo -t new-repo'%" } ;
ErrorId MsgGraph::UseGraphDeleteRepo  = { ErrorOf( ES_GRAPH, 81, E_FAILED, EV_USAGE, 0 ), "Usage: %'delete-repo [ -u user] -n repo'%" } ;
ErrorId MsgGraph::UseGraphLFSPush     = { ErrorOf( ES_GRAPH, 89, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-push [ -u user ] -n repo -i /path/to/lfs/file -r sha-256-hash'%" } ;
ErrorId MsgGraph::UseGraphLFSFetch    = { ErrorOf( ES_GRAPH, 90, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-fetch [ -u user ] -n repo -o /path/to/lfs/file -r sha-256-hash'%" } ;
ErrorId MsgGraph::UseGraphLFSStat     = { ErrorOf( ES_GRAPH, 144, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-stat [ -u user ] -n repo oid...'%" } ;
ErrorId MsgGraph::UseGraphVerify      = { ErrorOf( ES_GRAPH, 132, E_FAILED, EV_USAGE, 0 ), "Usage: %'verify -n repo'%" } ;
ErrorId MsgGraph::UsePermissionG      = { ErrorOf( ES_GRAPH, 110, E_FAILED, EV_USAGE, 0 ), "Usage: %'grant-permission [ -r ref ] -p perm -g group|-u user -d depot|-n repo'%" } ;
ErrorId MsgGraph::UsePermissionR      = { ErrorOf( ES_GRAPH, 111, E_FAILED, EV_USAGE, 0 ), "Usage: %'revoke-permission [ -r ref ] -p perm -g group|-u user -d depot|-n repo'%" } ;
ErrorId MsgGraph::UsePermissionS      = { ErrorOf( ES_GRAPH, 112, E_FAILED, EV_USAGE, 0 ), "Usage: %'show-permission [ -r ref ] [ -u user ] [ -g group ] [ -p perm ] -d depot|-n repo'%" } ;
ErrorId MsgGraph::UsePermissionC      = { ErrorOf( ES_GRAPH, 113, E_FAILED, EV_USAGE, 0 ), "Usage: %'check-permission -n repo [ -r ref ] -u user -p perm'%" } ;
ErrorId MsgGraph::UseRefHist          = { ErrorOf( ES_GRAPH, 115, E_FAILED, EV_USAGE, 0 ), "Usage: %'ref-hist [ -n repo -r ref -u user -t reftype -a action -s start -e end -m max]'%" } ;
ErrorId MsgGraph::UsePubKey           = { ErrorOf( ES_GRAPH, 127, E_FAILED, EV_USAGE, 0 ), "Usage: %'pubkey -d | -i [-f] [-u user] [-s scope]'%" } ;
ErrorId MsgGraph::UsePubKeyS          = { ErrorOf( ES_GRAPH, 128, E_FAILED, EV_USAGE, 0 ), "Usage: %'pubkeys [-u user] [-s scope]'%" } ;
ErrorId MsgGraph::ReferenceData       = { ErrorOf( ES_GRAPH, 8, E_INFO, EV_NONE, 5 ), "%depot% %sha% %owner% %type% %name%" } ;
ErrorId MsgGraph::ReferenceHistory    = { ErrorOf( ES_GRAPH, 116, E_INFO, EV_NONE, 7 ), "%repo% %sha% %type% %name% %action% %user% %date%" } ;
ErrorId MsgGraph::ReferenceDataShort  = { ErrorOf( ES_GRAPH, 9, E_INFO, EV_NONE, 3 ), "%depot% %sha% %name%" } ;
ErrorId MsgGraph::RepositoryData      = { ErrorOf( ES_GRAPH, 70, E_INFO, EV_NONE, 1 ), "%repo%" } ;
ErrorId MsgGraph::FileLogData         = { ErrorOf( ES_GRAPH, 10, E_INFO, EV_NONE, 4 ), "%depotFile%%depotRev% (%action%) %commit%" } ;
ErrorId MsgGraph::WrongClientType     = { ErrorOf( ES_GRAPH, 11, E_FAILED, EV_USAGE, 1 ), "A client of this type may not have a view that includes %depotFile%" } ;
ErrorId MsgGraph::CurrentBranchShort  = { ErrorOf( ES_GRAPH, 12, E_INFO, EV_NONE, 2 ), "%depot% %branchName%" } ;
ErrorId MsgGraph::ReferenceHeadShort  = { ErrorOf( ES_GRAPH, 13, E_INFO, EV_NONE, 3 ), "%depot% %client% %sha%" } ;
ErrorId MsgGraph::ReferenceHaveShort  = { ErrorOf( ES_GRAPH, 14, E_INFO, EV_NONE, 3 ), "%depot% %client% %sha%" } ;
ErrorId MsgGraph::RepoDefaultBranch   = { ErrorOf( ES_GRAPH, 117, E_INFO, EV_NONE, 2 ), "%repo% %branch% HEAD" } ;
ErrorId MsgGraph::NoSuchObject        = { ErrorOf( ES_GRAPH, 15, E_FAILED, EV_USAGE, 1 ), "No such object %sha%" } ;
ErrorId MsgGraph::NoSuchCommit        = { ErrorOf( ES_GRAPH, 147, E_FAILED, EV_USAGE, 1 ), "No commit named %sha%" } ;
ErrorId MsgGraph::NoSuchDepot         = { ErrorOf( ES_GRAPH, 88, E_FAILED, EV_USAGE, 1 ), "There is no graph depot named %depot%." } ;
ErrorId MsgGraph::UseRevList          = { ErrorOf( ES_GRAPH, 16, E_FAILED, EV_USAGE, 0 ), "Usage: %'rev-list -n repo [ -m N ] [ commit... ]'%" } ;
ErrorId MsgGraph::UseGraphDescribe    = { ErrorOf( ES_GRAPH, 17, E_FAILED, EV_USAGE, 0 ), "Usage: %'describe -n repo commit...'%" } ;
ErrorId MsgGraph::PackRefSyntax       = { ErrorOf( ES_GRAPH, 18, E_FAILED, EV_NOTYET, 1 ), "Unrecognized syntax in packed-refs file: %line%" } ;
ErrorId MsgGraph::PackHeader          = { ErrorOf( ES_GRAPH, 19, E_FAILED, EV_FAULT, 1 ), "Failed to read pack header from %packfile%" } ;
ErrorId MsgGraph::PackMagic           = { ErrorOf( ES_GRAPH, 20, E_FAILED, EV_FAULT, 1 ), "Unrecognized packfile header in %packfile%" } ;
ErrorId MsgGraph::PackIndexCount      = { ErrorOf( ES_GRAPH, 21, E_FAILED, EV_FAULT, 3 ), "Pack file %packfile% has %packcount% objects, but index has %indexcount% objects." } ;
ErrorId MsgGraph::PackTypeByte        = { ErrorOf( ES_GRAPH, 22, E_FAILED, EV_FAULT, 1 ), "Failed to read object type byte from %packfile%" } ;
ErrorId MsgGraph::PackSizeByte        = { ErrorOf( ES_GRAPH, 23, E_FAILED, EV_FAULT, 2 ), "Failed to read object size byte from %packfile%. Error was on byte %bytenumber%." } ;
ErrorId MsgGraph::PackIdxFanoutRead   = { ErrorOf( ES_GRAPH, 24, E_FAILED, EV_FAULT, 1 ), "Failed to read fanout table from %indexfile%" } ;
ErrorId MsgGraph::PackIdxEndOfFile    = { ErrorOf( ES_GRAPH, 25, E_FAILED, EV_FAULT, 1 ), "Premature EOF during SHA read from %indexfile%" } ;
ErrorId MsgGraph::PackIdxPartial      = { ErrorOf( ES_GRAPH, 26, E_FAILED, EV_FAULT, 1 ), "Unexpected partial SHA read from %indexfile%" } ;
ErrorId MsgGraph::PackOffsetEndOfFile = { ErrorOf( ES_GRAPH, 27, E_FAILED, EV_FAULT, 1 ), "Premature EOF during offset read from %indexfile%" } ;
ErrorId MsgGraph::PackOffsetPartial   = { ErrorOf( ES_GRAPH, 28, E_FAILED, EV_FAULT, 1 ), "Unexpected partial offset read from %indexfile%" } ;
ErrorId MsgGraph::PackIdxLargeEndOfFile = { ErrorOf( ES_GRAPH, 29, E_FAILED, EV_FAULT, 1 ), "Premature EOF during large offset read from %indexfile%" } ;
ErrorId MsgGraph::PackLargeOffsetPartial = { ErrorOf( ES_GRAPH, 30, E_FAILED, EV_FAULT, 1 ), "Unexpected partial large offset read from %indexfile%" } ;
ErrorId MsgGraph::DeltaVarint         = { ErrorOf( ES_GRAPH, 31, E_FAILED, EV_FAULT, 0 ), "Failed to read varintZ byte" } ;
ErrorId MsgGraph::DeltaOffset         = { ErrorOf( ES_GRAPH, 32, E_FAILED, EV_FAULT, 1 ), "Failed to read delta source offset at %offset%" } ;
ErrorId MsgGraph::DeltaOffsetMore     = { ErrorOf( ES_GRAPH, 33, E_FAILED, EV_FAULT, 1 ), "Failed to read delta source offset continuation byte %bytenumber%" } ;
ErrorId MsgGraph::DeltaOffsetBits     = { ErrorOf( ES_GRAPH, 34, E_FAILED, EV_FAULT, 1 ), "Delta offset bits %bits% are out of bounds." } ;
ErrorId MsgGraph::DeltaCopyOffset     = { ErrorOf( ES_GRAPH, 35, E_FAILED, EV_FAULT, 0 ), "Failure reading offset bytes for delta copy instruction." } ;
ErrorId MsgGraph::DeltaLengthBits     = { ErrorOf( ES_GRAPH, 36, E_FAILED, EV_FAULT, 1 ), "Delta length bits %bits% are out of bounds." } ;
ErrorId MsgGraph::DeltaCopyLength     = { ErrorOf( ES_GRAPH, 37, E_FAILED, EV_FAULT, 0 ), "Failure reading length bytes for delta copy instruction." } ;
ErrorId MsgGraph::DeltaRefBaseMissing = { ErrorOf( ES_GRAPH, 38, E_FAILED, EV_FAULT, 1 ), "Failed to find source by reference sha %sha%" } ;
ErrorId MsgGraph::DeltaLengthMismatch = { ErrorOf( ES_GRAPH, 39, E_FAILED, EV_FAULT, 2 ), "Delta instructions anticipated a result length of %expected%, but the actual result was length %actual%." } ;
ErrorId MsgGraph::DeltaInsertData     = { ErrorOf( ES_GRAPH, 40, E_FAILED, EV_FAULT, 1 ), "Failure reading insert instruction bytes at byte %bytenumber%." } ;
ErrorId MsgGraph::CommitMissing       = { ErrorOf( ES_GRAPH, 41, E_FAILED, EV_FAULT, 1 ), "Commit record not found in db for sha %sha%." } ;
ErrorId MsgGraph::CommitNotUnique     = { ErrorOf( ES_GRAPH, 42, E_FAILED, EV_USAGE, 1 ), "Commit sha prefix %sha% is not unique. Please specify a longer prefix." } ;
ErrorId MsgGraph::TagMissing          = { ErrorOf( ES_GRAPH, 78, E_FAILED, EV_FAULT, 1 ), "Tag record not found in db for sha %sha%." } ;
ErrorId MsgGraph::TagNotUnique        = { ErrorOf( ES_GRAPH, 79, E_FAILED, EV_USAGE, 1 ), "Tag sha prefix %sha% is not unique. Please specify a longer prefix." } ;
ErrorId MsgGraph::NoEmailStart        = { ErrorOf( ES_GRAPH, 43, E_FAILED, EV_FAULT, 1 ), "Commit object syntax error: email start not found in %line%." } ;
ErrorId MsgGraph::NoEmailEnd          = { ErrorOf( ES_GRAPH, 44, E_FAILED, EV_FAULT, 1 ), "Commit object syntax error: email end not found in %line%." } ;
ErrorId MsgGraph::NoCommitDate        = { ErrorOf( ES_GRAPH, 45, E_FAILED, EV_FAULT, 1 ), "Commit object syntax error: date not found in %line%." } ;
ErrorId MsgGraph::TreeModeEndOfFile   = { ErrorOf( ES_GRAPH, 46, E_FAILED, EV_FAULT, 2 ), "Tree parse error on %sha%: eof during mode parse at offset %offset%." } ;
ErrorId MsgGraph::TreeNameEndOfFile   = { ErrorOf( ES_GRAPH, 47, E_FAILED, EV_FAULT, 2 ), "Tree parse error on %sha%: eof during name parse at offset %offset%." } ;
ErrorId MsgGraph::TreeShaEndOfFile    = { ErrorOf( ES_GRAPH, 48, E_FAILED, EV_FAULT, 2 ), "Tree parse error on %sha%: eof during sha parse at offset %offset%." } ;
ErrorId MsgGraph::LbrShaSyntax        = { ErrorOf( ES_GRAPH, 49, E_FAILED, EV_FAULT, 1 ), "%sha% is not a valid blob sha." } ;
ErrorId MsgGraph::LbrWrongType        = { ErrorOf( ES_GRAPH, 50, E_FAILED, EV_FAULT, 0 ), "This librarian type only supports read-only access." } ;
ErrorId MsgGraph::InvalidBlobHeader   = { ErrorOf( ES_GRAPH, 51, E_FAILED, EV_FAULT, 1 ), "Invalid object header for %sha%." } ;
ErrorId MsgGraph::LbrBadAccess        = { ErrorOf( ES_GRAPH, 52, E_FATAL, EV_FAULT, 1 ), "LbrGraphLoose: invalid operation %operation%." } ;
ErrorId MsgGraph::LbrPackBadAccess    = { ErrorOf( ES_GRAPH, 53, E_FATAL, EV_FAULT, 1 ), "LbrGraphPack: invalid operation %operation%." } ;
ErrorId MsgGraph::LooseWriterBadAccess= { ErrorOf( ES_GRAPH, 54, E_FATAL, EV_FAULT, 1 ), "LbrGraphLooseWriter: invalid operation %operation%." } ;
ErrorId MsgGraph::LbrWriteOnly        = { ErrorOf( ES_GRAPH, 55, E_FAILED, EV_FAULT, 0 ), "This librarian type only supports write access." } ;
ErrorId MsgGraph::TreeMissing         = { ErrorOf( ES_GRAPH, 56, E_FAILED, EV_FAULT, 1 ), "Tree record not found in db for sha %sha%." } ;
ErrorId MsgGraph::TreeNotUnique       = { ErrorOf( ES_GRAPH, 57, E_FAILED, EV_USAGE, 1 ), "Tree sha prefix %sha% is not unique. Please specify a longer prefix." } ;
ErrorId MsgGraph::RcvRefSyntax        = { ErrorOf( ES_GRAPH, 63, E_FAILED, EV_USAGE, 1 ), "Specify reference update as %'[-r|-F] <ref>=<sha>'%, not %value%." } ;
ErrorId MsgGraph::RcvFileName         = { ErrorOf( ES_GRAPH, 64, E_FAILED, EV_USAGE, 1 ), "File %filename% must be either a packfile or a loose object." } ;
ErrorId MsgGraph::NotFastForward      = { ErrorOf( ES_GRAPH, 65, E_WARN, EV_USAGE, 3 ), "Reference %branchName% may not be set to %newSha% because that is not a fast-forward update from %currentSha%." } ;
ErrorId MsgGraph::NotAGraphDepot      = { ErrorOf( ES_GRAPH, 67, E_FAILED, EV_USAGE, 1 ), "%depotName% is not a graph depot." } ;
ErrorId MsgGraph::UnknownRepo         = { ErrorOf( ES_GRAPH, 68, E_FAILED, EV_USAGE, 1 ), "%file% is not a repository in a graph depot." } ;
ErrorId MsgGraph::IllegalRefChar      = { ErrorOf( ES_GRAPH, 71, E_FAILED, EV_USAGE, 1 ), "Invalid character '%char%' in reference." } ;
ErrorId MsgGraph::IllegalRefSubstr    = { ErrorOf( ES_GRAPH, 72, E_FAILED, EV_USAGE, 1 ), "Invalid substring '%sequence%' in reference." } ;
ErrorId MsgGraph::UnqualifiedRef      = { ErrorOf( ES_GRAPH, 73, E_FAILED, EV_USAGE, 0 ), "Unqualified reference name is not allowed here." } ;
ErrorId MsgGraph::InvalidParentChar   = { ErrorOf( ES_GRAPH, 74, E_FAILED, EV_USAGE, 1 ), "Invalid character '%char%' in parent traversal." } ;
ErrorId MsgGraph::NoSuchParent        = { ErrorOf( ES_GRAPH, 75, E_FAILED, EV_USAGE, 2 ), "Commit %sha% does not contain a reference to parent number %parent%." } ;
ErrorId MsgGraph::RefTargetMissing    = { ErrorOf( ES_GRAPH, 76, E_WARN, EV_USAGE, 2 ), "Reference %ref% specifies a non-existent commit %commit%." } ;
ErrorId MsgGraph::InvalidReference    = { ErrorOf( ES_GRAPH, 82, E_FAILED, EV_USAGE, 2 ), "Reference %ref% could not be interpreted in repository %repository%" } ;
ErrorId MsgGraph::InvalidRepo         = { ErrorOf( ES_GRAPH, 83, E_FAILED, EV_USAGE, 1 ), "Repository %repository% does not appear to be valid." } ;
ErrorId MsgGraph::PackObjectCount     = { ErrorOf( ES_GRAPH, 84, E_FATAL, EV_FAULT, 2 ), "Pack construction wrote %actual% objects rather than the anticipated %expected% objects." } ;
ErrorId MsgGraph::PackObjectMissing   = { ErrorOf( ES_GRAPH, 85, E_FATAL, EV_FAULT, 1 ), "Pack construction failure: object %sha% missing from database." } ;
ErrorId MsgGraph::PackObjectLength    = { ErrorOf( ES_GRAPH, 86, E_FATAL, EV_FAULT, 3 ), "Pack verification failure: Expected object of type %objectType% and length %objectLength% but uncompressed an object of length %actualLength%." } ;
ErrorId MsgGraph::InvalidRepoName     = { ErrorOf( ES_GRAPH, 87, E_FAILED, EV_USAGE, 1 ), "Repository name [%repoName% is invalid|is missing]. Please specify a name in the format //depot-name/path/to/repo." } ;
ErrorId MsgGraph::NotASha256          = { ErrorOf( ES_GRAPH, 92, E_FAILED, EV_USAGE, 1 ), "%sha% is not a valid SHA-256 value." } ;
ErrorId MsgGraph::LFSShaMismatch      = { ErrorOf( ES_GRAPH, 93, E_FAILED, EV_FAULT, 2 ), "LFS file push failure: content sha was %actual% instead of the expected sha %expected%." } ;
ErrorId MsgGraph::LFSAlreadyPresent   = { ErrorOf( ES_GRAPH, 143, E_INFO, EV_USAGE, 1 ), "LFS blob %sha% already exists." } ;
ErrorId MsgGraph::AtomicPushFailed    = { ErrorOf( ES_GRAPH, 94, E_FAILED, EV_FAULT, 1 ), "Reference %ref% could not be updated, and the command specified --atomic. No reference updates were performed." } ;
ErrorId MsgGraph::TriggerWarnMessage  = { ErrorOf( ES_GRAPH, 95, E_WARN, EV_ADMIN, 1 ), "%msg%" } ;
ErrorId MsgGraph::UseRepo             = { ErrorOf( ES_GRAPH, 96, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo [ -i -o -d -f ] [ repo ]'%" } ;
ErrorId MsgGraph::UseRepoo            = { ErrorOf( ES_GRAPH, 97, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -o repo'%" } ;
ErrorId MsgGraph::UseRepod            = { ErrorOf( ES_GRAPH, 98, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -d [ -f ] repo'%" } ;
ErrorId MsgGraph::UseRepoi            = { ErrorOf( ES_GRAPH, 99, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -i'%" } ;
ErrorId MsgGraph::UseRepos            = { ErrorOf( ES_GRAPH, 100, E_FAILED, EV_USAGE, 0 ), "Usage: %'repos [-e|-E filter -m max -u user -O owner --from=origin]'%" } ;
ErrorId MsgGraph::ReposData           = { ErrorOf( ES_GRAPH, 101, E_INFO, EV_NONE, 5 ), "%repo% %owner% %forked% %created% %description%" } ;
ErrorId MsgGraph::RepoSave            = { ErrorOf( ES_GRAPH, 102, E_INFO, EV_NONE, 1 ), "Repo %repoName% saved." } ;
ErrorId MsgGraph::RepoNoChange        = { ErrorOf( ES_GRAPH, 103, E_INFO, EV_NONE, 1 ), "Repo %repoName% not changed." } ;
ErrorId MsgGraph::RepoDelete          = { ErrorOf( ES_GRAPH, 104, E_INFO, EV_NONE, 1 ), "Repo %repoName% deleted." } ;
ErrorId MsgGraph::NoSuchRepo          = { ErrorOf( ES_GRAPH, 105, E_FAILED, EV_UNKNOWN, 1 ), "Repo '%repo%' doesn't exist." } ;
ErrorId MsgGraph::BadRepoName         = { ErrorOf( ES_GRAPH, 106, E_FAILED, EV_USAGE, 1 ), "Repo name '%repo%' invalid. Specify name as //depot/repo/name." } ;
ErrorId MsgGraph::NotInGraphDepot     = { ErrorOf( ES_GRAPH, 107, E_FAILED, EV_USAGE, 1 ), "Repo name '%repo%' must be located in a valid graph depot." } ;
ErrorId MsgGraph::CantAutocreateRepo  = { ErrorOf( ES_GRAPH, 108, E_FAILED, EV_ADMIN, 1 ), "Repo '%repo%' does not exist in this server, and server policy prevents automatic creation of new repos. Please contact the server administrator to create the repo, then retry the operation." } ;
ErrorId MsgGraph::MustForceFork       = { ErrorOf( ES_GRAPH, 109, E_FAILED, EV_USAGE, 2 ), "Repo %repo% was forked from %forkedRepo%. To create a fork of a fork, specify -f." } ;
ErrorId MsgGraph::ShowPermission      = { ErrorOf( ES_GRAPH, 114, E_INFO, EV_NONE, 5 ), "%repo% %branch% %type% %user% %perm%" } ;
ErrorId MsgGraph::DepotHasRepos       = { ErrorOf( ES_GRAPH, 118, E_FAILED, EV_NOTYET, 2 ), "Depot %depot% isn't empty of repos. One or more repos are still present in the depot directory. Display the existing repos with %'p4 repos -e'% %depotPrefix%. Delete those repos using %'p4 repo -d'%, then retry the depot deletion." } ;
ErrorId MsgGraph::EmptyRepo           = { ErrorOf( ES_GRAPH, 119, E_WARN, EV_EMPTY, 1 ), "%repo% is empty." } ;
ErrorId MsgGraph::AmbiguousRepoName   = { ErrorOf( ES_GRAPH, 120, E_FAILED, EV_USAGE, 2 ), "Repo name '%repo%' may not be used. It would be an ambiguous name, because a repo named %otherRepo% already exists." } ;
ErrorId MsgGraph::AmbiguousRefUpdate  = { ErrorOf( ES_GRAPH, 129, E_FAILED, EV_USAGE, 3 ), "Reference %ref% may not be set to both %sha% and %otherSha%." } ;
ErrorId MsgGraph::CantCreateRepo      = { ErrorOf( ES_GRAPH, 121, E_FAILED, EV_USAGE, 2 ), "User %user% does not have administrative privileges to create repo %repo%." } ;
ErrorId MsgGraph::CantWriteAllRepo    = { ErrorOf( ES_GRAPH, 163, E_FAILED, EV_USAGE, 2 ), "User %user% does not have write-all permission to initially import repo %repo%." } ;
ErrorId MsgGraph::CantDeleteRepo      = { ErrorOf( ES_GRAPH, 124, E_FAILED, EV_USAGE, 2 ), "User %user% does not have administrative privileges to delete repo %repo%." } ;
ErrorId MsgGraph::CantPruneRepo       = { ErrorOf( ES_GRAPH, 154, E_FAILED, EV_USAGE, 2 ), "User %user% does not have administrative privileges to delete out of date packfiles from repo %repo%." } ;
ErrorId MsgGraph::CantChangeView      = { ErrorOf( ES_GRAPH, 158, E_FAILED, EV_USAGE, 1 ), "Client %client% has already been used to sync files. Run %'p4 sync //...#none'%, then retry this command." } ;
ErrorId MsgGraph::RepoAccessDenied    = { ErrorOf( ES_GRAPH, 122, E_FAILED, EV_USAGE, 1 ), "%repo% - access denied." } ;
ErrorId MsgGraph::NoPermissionOnRef   = { ErrorOf( ES_GRAPH, 123, E_FAILED, EV_USAGE, 3 ), "User %user% does not have %permission% privilege for reference %ref%." } ;
ErrorId MsgGraph::NoMatchPermissions  = { ErrorOf( ES_GRAPH, 125, E_WARN, EV_EMPTY, 0 ), "No matching permissions." } ;
ErrorId MsgGraph::NoLFSPushPerm       = { ErrorOf( ES_GRAPH, 145, E_FAILED, EV_USAGE, 2 ), "User %user% does not have permission to push LFS files to repo %repo%." } ;
ErrorId MsgGraph::NoLFSFetchPerm      = { ErrorOf( ES_GRAPH, 146, E_FAILED, EV_USAGE, 2 ), "User %user% does not have permission to fetch LFS files from repo %repo%." } ;
ErrorId MsgGraph::PubKeyData          = { ErrorOf( ES_GRAPH, 126, E_INFO, EV_NONE, 1 ), "%key%" } ;
ErrorId MsgGraph::BadPublicKey        = { ErrorOf( ES_GRAPH, 130, E_FAILED, EV_USAGE, 0 ), "pubkey failed - error with public key!" } ;
ErrorId MsgGraph::PubKeyTooLong       = { ErrorOf( ES_GRAPH, 135, E_FAILED, EV_USAGE, 0 ), "pubkey failed - too long!" } ;
ErrorId MsgGraph::PubKeyDuplicate     = { ErrorOf( ES_GRAPH, 136, E_FAILED, EV_USAGE, 0 ), "pubkey failed - duplicate key exists!" } ;
ErrorId MsgGraph::PubKeyAction        = { ErrorOf( ES_GRAPH, 131, E_INFO, EV_NONE, 0 ), "Public Key %action%." } ;
ErrorId MsgGraph::PubKeyNotExist      = { ErrorOf( ES_GRAPH, 150, E_FAILED, EV_USAGE, 0 ), "Public Key does not exist." } ;
ErrorId MsgGraph::PubKeyNeedsForce    = { ErrorOf( ES_GRAPH, 157, E_FAILED, EV_USAGE, 2 ), "Public Key for '%user%/%scope%' already exists, use '-f' to replace." } ;
ErrorId MsgGraph::BlobVerified        = { ErrorOf( ES_GRAPH, 133, E_INFO, EV_NONE, 2 ), "%sha% %file%" } ;
ErrorId MsgGraph::BlobDamaged         = { ErrorOf( ES_GRAPH, 134, E_FAILED, EV_FAULT, 3 ), "%file% is damaged: expected %expectedSha% actual %actualSha%" } ;
ErrorId MsgGraph::LFSBlobVerified     = { ErrorOf( ES_GRAPH, 156, E_INFO, EV_NONE, 1 ), "LFS File %LFSFile%" } ;
ErrorId MsgGraph::LFSBlobDamaged      = { ErrorOf( ES_GRAPH, 91, E_FAILED, EV_FAULT, 2 ), "LFS file %LFSFile% is damaged: actual %actualSha%" } ;
ErrorId MsgGraph::ArchiveImported     = { ErrorOf( ES_GRAPH, 137, E_INFO, EV_NONE, 1 ), "Pack %file% imported." } ;
ErrorId MsgGraph::ReferenceAdded      = { ErrorOf( ES_GRAPH, 138, E_INFO, EV_NONE, 2 ), "Reference %ref% added with value %sha%." } ;
ErrorId MsgGraph::ReferenceUpdated    = { ErrorOf( ES_GRAPH, 139, E_INFO, EV_NONE, 2 ), "Reference %ref% updated to value %sha%." } ;
ErrorId MsgGraph::ReferenceDeleted    = { ErrorOf( ES_GRAPH, 140, E_INFO, EV_NONE, 1 ), "Reference %ref% deleted." } ;
ErrorId MsgGraph::ReferenceForced     = { ErrorOf( ES_GRAPH, 141, E_INFO, EV_NONE, 2 ), "Reference %ref% force pushed to new value %sha%." } ;
ErrorId MsgGraph::ObjectStatistics    = { ErrorOf( ES_GRAPH, 142, E_INFO, EV_NONE, 2 ), "Objects added: %commits%/%total% (commits/total)." } ;
ErrorId MsgGraph::ForkTargetNotEmpty  = { ErrorOf( ES_GRAPH, 148, E_FAILED, EV_USAGE, 1 ), "Cannot fork into repo %targetRepo% because it is not empty." } ;
ErrorId MsgGraph::ForkTargetIsSource  = { ErrorOf( ES_GRAPH, 149, E_FAILED, EV_USAGE, 1 ), "Cannot fork %targetRepo% to itself." } ;
ErrorId MsgGraph::DanglingObject      = { ErrorOf( ES_GRAPH, 151, E_FAILED, EV_FAULT, 3 ), "Object %parentSha% refers to nonexistent child object %childNumber% %childSha%" } ;
ErrorId MsgGraph::BlobMissing         = { ErrorOf( ES_GRAPH, 152, E_FAILED, EV_FAULT, 1 ), "Blob data not found in archives for sha %sha%." } ;
ErrorId MsgGraph::LFSBlobMissing      = { ErrorOf( ES_GRAPH, 155, E_FAILED, EV_FAULT, 1 ), "LFS Blob file not found in archives for sha-256 %sha%." } ;
ErrorId MsgGraph::NoRepoSelected      = { ErrorOf( ES_GRAPH, 153, E_FAILED, EV_USAGE, 1 ), "Client %client% specifies no repos to sync. Please check the RepoView value in the client spec to ensure that it describes the appropriate set of repos." } ;
ErrorId MsgGraph::RefAlreadyExists    = { ErrorOf( ES_GRAPH, 159, E_FAILED, EV_USAGE, 1 ), "Reference %refName% already exists." } ;
ErrorId MsgGraph::RefDoesntExist      = { ErrorOf( ES_GRAPH, 160, E_FAILED, EV_USAGE, 1 ), "Reference %refName% does not exist." } ;
ErrorId MsgGraph::RefValidation       = { ErrorOf( ES_GRAPH, 161, E_FAILED, EV_USAGE, 1 ), "Reference update failed to validate. Reference %refName% may not be given the value %newSha% because the reference was expected to refer to %checkSha% but it actually refers to %headSha%." } ;
ErrorId MsgGraph::SpecifyForce        = { ErrorOf( ES_GRAPH, 162, E_FAILED, EV_USAGE, 1 ), "To change the value of the %fieldName% field, you must specify the -f flag." } ;

// ErrorId graveyard: retired/deprecated ErrorIds. 
