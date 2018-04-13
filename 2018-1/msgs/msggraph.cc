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
 * Current high value for a MsgGraph error code is 352
 */

# include <error.h>
# include <errornum.h>
# include <msggraph.h>

ErrorId MsgGraph::CommitDataShort     = { ErrorOf( ES_GRAPH, 1, E_INFO, EV_NONE, 3 ), "commit %sha%\ntree %tree%\n%description%\n" } ;
ErrorId MsgGraph::UseGraph            = { ErrorOf( ES_GRAPH, 61, E_FAILED, EV_USAGE, 0 ), "Usage: see %'p4 help graph'%" } ;
ErrorId MsgGraph::UseCatFile          = { ErrorOf( ES_GRAPH, 2, E_FAILED, EV_USAGE, 0 ), "Usage: %'cat-file [ commit | -n repo blob | -t ] object-sha'%" } ;
ErrorId MsgGraph::UseChanges          = { ErrorOf( ES_GRAPH, 226, E_FAILED, EV_USAGE, 0 ), "Usage: %'changes [-m max] -n repo commit...'%" } ;
ErrorId MsgGraph::UseLsTree           = { ErrorOf( ES_GRAPH, 3, E_FAILED, EV_USAGE, 0 ), "Usage: %'ls-tree [ -r [--name-only] ]  treeish-sha'%\n%'       ls-tree [ -r [--name-only] ] -n //repo/name [commit|reference]'%" } ;
ErrorId MsgGraph::UseDescribe         = { ErrorOf( ES_GRAPH, 230, E_FAILED, EV_USAGE, 0 ), "Usage: %'describe -n repo [-s] commit'%" } ;
ErrorId MsgGraph::UseDiff             = { ErrorOf( ES_GRAPH, 259, E_FAILED, EV_USAGE, 0 ), "Usage: %'diff [ -d<flags> -sr ] [files...]'%" } ;
ErrorId MsgGraph::UseDiffTree         = { ErrorOf( ES_GRAPH, 4, E_FAILED, EV_USAGE, 0 ), "Usage: %'diff-tree -n repo tree-1-sha tree-2-sha'%" } ;
ErrorId MsgGraph::UseDiff2            = { ErrorOf( ES_GRAPH, 223, E_FAILED, EV_USAGE, 0 ), "Usage: %'diff2 [ -d<flags> -Od -q -u ] file file2'%" } ;
ErrorId MsgGraph::UseDirs             = { ErrorOf( ES_GRAPH, 228, E_FAILED, EV_USAGE, 0 ), "Usage: %'dirs filespec'%" } ;
ErrorId MsgGraph::UseFilelog          = { ErrorOf( ES_GRAPH, 235, E_FAILED, EV_USAGE, 0 ), "Usage: %'filelog [ -d -m max --first-parent ] -n repo filespec'%" } ;
ErrorId MsgGraph::FollowDeletedWildcard = { ErrorOf( ES_GRAPH, 317, E_FAILED, EV_USAGE, 0 ), "Wildcard in path not allowed with -d." } ;
ErrorId MsgGraph::UseFiles            = { ErrorOf( ES_GRAPH, 224, E_FAILED, EV_USAGE, 0 ), "Usage: %'files [-m max] filespec'%" } ;
ErrorId MsgGraph::UseFstat            = { ErrorOf( ES_GRAPH, 262, E_FAILED, EV_USAGE, 0 ), "Usage: %'fstat [ -m max ] file...'%" } ;
ErrorId MsgGraph::UseLock             = { ErrorOf( ES_GRAPH, 246, E_FAILED, EV_USAGE, 0 ), "Usage: %'lock [-c change] file...'%" } ;
ErrorId MsgGraph::UseLog              = { ErrorOf( ES_GRAPH, 6, E_FAILED, EV_USAGE, 0 ), "Usage: %'log -n repo [ -u user -A date -B date -p -N N -X N ] [ -a | -m N ] [ commit... ]'%" } ;
ErrorId MsgGraph::UseShowRef          = { ErrorOf( ES_GRAPH, 58, E_FAILED, EV_USAGE, 0 ), "Usage: %'show-ref [ -a -n repo -u user -t type -m N -e|-E filter]'%" } ;
ErrorId MsgGraph::UseMerge            = { ErrorOf( ES_GRAPH, 7, E_FAILED, EV_USAGE, 0 ), "Usage: %'merge [ -n ] [ --ff-only ] [ --no-ff | --squash ] other-branch'%" } ;
ErrorId MsgGraph::UseMerge2           = { ErrorOf( ES_GRAPH, 330, E_FAILED, EV_USAGE, 0 ), "Usage: %'merge [ -n ] [ --ff-only ] [ --no-ff | --squash ] --repo repo --target target-branch other-branch'%" } ;
ErrorId MsgGraph::UseRebase           = { ErrorOf( ES_GRAPH, 327, E_FAILED, EV_USAGE, 0 ), "Usage: %'graph rebase [ -r ref -f ] --repo repo --target target source'%" } ;
ErrorId MsgGraph::UseCherryPick       = { ErrorOf( ES_GRAPH, 328, E_FAILED, EV_USAGE, 0 ), "Usage: %'graph cherry-pick [ -r ref -f ] --repo repo --target target source'%" } ;
ErrorId MsgGraph::UseOpen             = { ErrorOf( ES_GRAPH, 221, E_FAILED, EV_USAGE, 0 ), "Usage: %'add/edit/delete [-c changelist#] [-n] [-t type] files...'%" } ;
ErrorId MsgGraph::UseTag              = { ErrorOf( ES_GRAPH, 211, E_FAILED, EV_USAGE, 0 ), "Usage: %'tag -n repo [ -d tag | -l [ -m max ] | -c comment | -o ] tag [ sha ]'%" } ;
ErrorId MsgGraph::UseTags             = { ErrorOf( ES_GRAPH, 335, E_FAILED, EV_USAGE, 0 ), "Usage: %'graph tags [-o] [-m max]'%" } ;
ErrorId MsgGraph::UseReconcile        = { ErrorOf( ES_GRAPH, 261, E_FAILED, EV_USAGE, 0 ), "Usage: %'reconcile [ -a -e -d -n -c change ]'%" } ;
ErrorId MsgGraph::UseReopen           = { ErrorOf( ES_GRAPH, 257, E_FAILED, EV_USAGE, 0 ), "Usage: %'reopen [-c changelist#] files...'%" } ;
ErrorId MsgGraph::UseResolve          = { ErrorOf( ES_GRAPH, 220, E_FAILED, EV_USAGE, 0 ), "Usage: %'resolve'%" } ;
ErrorId MsgGraph::UseResolved         = { ErrorOf( ES_GRAPH, 244, E_FAILED, EV_USAGE, 0 ), "Usage: %'resolved'%" } ;
ErrorId MsgGraph::UseRevert           = { ErrorOf( ES_GRAPH, 222, E_FAILED, EV_USAGE, 0 ), "Usage: %'revert [ -n -w -a -c changelist# ] files...'%" } ;
ErrorId MsgGraph::UseSwitch           = { ErrorOf( ES_GRAPH, 216, E_FAILED, EV_USAGE, 0 ), "Usage: %'switch [-l | [-a|-c|-d|-n repo] branch]'%" } ;
ErrorId MsgGraph::UseUnlock           = { ErrorOf( ES_GRAPH, 247, E_FAILED, EV_USAGE, 0 ), "Usage: %'unlock [-c change] file...'%" } ;
ErrorId MsgGraph::UseReceivePack      = { ErrorOf( ES_GRAPH, 59, E_FAILED, EV_USAGE, 0 ), "Usage: %'receive-pack -n repo [-u user -v] -i files... [ -r refs... | -F refs... | -p packed-refs ]'%" } ;
ErrorId MsgGraph::UsePackObjects      = { ErrorOf( ES_GRAPH, 60, E_FAILED, EV_USAGE, 0 ), "Usage: %'pack-objects -n repo [-u user] -o git-pack-dir [ -a | commit... ]'%" } ;
ErrorId MsgGraph::UseGraphSync        = { ErrorOf( ES_GRAPH, 62, E_FAILED, EV_USAGE, 0 ), "Usage: %'sync [-f -n -q -k] [ commit... ]'%" } ;
ErrorId MsgGraph::UseGraphProtects    = { ErrorOf( ES_GRAPH, 66, E_FAILED, EV_USAGE, 0 ), "Usage: %'protects -n repo -u user [ -r reference ] [ file... ]'%" } ;
ErrorId MsgGraph::UseGraphList        = { ErrorOf( ES_GRAPH, 69, E_FAILED, EV_USAGE, 0 ), "Usage: %'list-repos [ -n repo -u user -m max ]'%" } ;
ErrorId MsgGraph::UseGraphCollect     = { ErrorOf( ES_GRAPH, 77, E_FAILED, EV_USAGE, 0 ), "Usage: %'collect [ -n -A -t days ]'%" } ;
ErrorId MsgGraph::UseGraphForkRepo    = { ErrorOf( ES_GRAPH, 80, E_FAILED, EV_USAGE, 0 ), "Usage: %'fork-repo [ -u user ] -n repo -t new-repo'%" } ;
ErrorId MsgGraph::UseGraphDeleteRepo  = { ErrorOf( ES_GRAPH, 81, E_FAILED, EV_USAGE, 0 ), "Usage: %'delete-repo [ -u user] -n repo'%" } ;
ErrorId MsgGraph::UseGraphLFSPush     = { ErrorOf( ES_GRAPH, 89, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-push [ -u user ] -n repo -i /path/to/lfs/file -r sha-256-hash'%" } ;
ErrorId MsgGraph::UseGraphLFSFetch    = { ErrorOf( ES_GRAPH, 90, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-fetch [ -u user ] -n repo -o /path/to/lfs/file -r sha-256-hash'%" } ;
ErrorId MsgGraph::UseGraphLFSStat     = { ErrorOf( ES_GRAPH, 144, E_FAILED, EV_USAGE, 0 ), "Usage: %'lfs-stat [ -u user ] -n repo oid...'%" } ;
ErrorId MsgGraph::UseGraphSubmodule   = { ErrorOf( ES_GRAPH, 252, E_FAILED, EV_USAGE, 0 ), "Usage: %'submodule -n repo [-p path -t submodule -d -l]'%" } ;
ErrorId MsgGraph::UseGraphVerify      = { ErrorOf( ES_GRAPH, 132, E_FAILED, EV_USAGE, 0 ), "Usage: %'verify [-q] -n repo'%" } ;
ErrorId MsgGraph::UseGraphPackInfo    = { ErrorOf( ES_GRAPH, 284, E_FAILED, EV_USAGE, 0 ), "Usage: %'pack-info -n repo'%" } ;
ErrorId MsgGraph::UsePermissionG      = { ErrorOf( ES_GRAPH, 110, E_FAILED, EV_USAGE, 0 ), "Usage: %'grant-permission [ -f ] [ -r ref ] -p perm -g group|-u user -d graphdepot|-n //repo/name'%" } ;
ErrorId MsgGraph::UsePermissionR      = { ErrorOf( ES_GRAPH, 111, E_FAILED, EV_USAGE, 0 ), "Usage: %'revoke-permission [ -f ] [ -r ref ] -p perm -g group|-u user -d graphdepot|-n //repo/name'%" } ;
ErrorId MsgGraph::UsePermissionS      = { ErrorOf( ES_GRAPH, 112, E_FAILED, EV_USAGE, 0 ), "Usage: %'show-permission [ -r ref ] [ -u user ] [ -g group ] [ -p perm ] -d graphdepot|-n //repo/name'%" } ;
ErrorId MsgGraph::UsePermissions      = { ErrorOf( ES_GRAPH, 334, E_FAILED, EV_USAGE, 0 ), "Usage: %'show-permissions [ -d graphdepot | -n //repo/name ] [ -u user ]'%" } ;
ErrorId MsgGraph::UsePermissionC      = { ErrorOf( ES_GRAPH, 113, E_FAILED, EV_USAGE, 0 ), "Usage: %'check-permission -n //repo/name [ -r ref ] -u user -p perm'%" } ;
ErrorId MsgGraph::UsePermNoRef        = { ErrorOf( ES_GRAPH, 279, E_FAILED, EV_USAGE, 1 ), "Usage: -r (ref) not required for permission '%perm%'" } ;
ErrorId MsgGraph::UsePermNeedRef      = { ErrorOf( ES_GRAPH, 290, E_FAILED, EV_USAGE, 1 ), "Usage: -r (ref) required for permission '%perm%'" } ;
ErrorId MsgGraph::UsePermBadRestrict  = { ErrorOf( ES_GRAPH, 307, E_FAILED, EV_USAGE, 1 ), "Usage: -n (repo) required for permission '%perm%'" } ;
ErrorId MsgGraph::UseRefHist          = { ErrorOf( ES_GRAPH, 115, E_FAILED, EV_USAGE, 0 ), "Usage: %'ref-hist [ -n repo -r ref -u user -t reftype -a action -s start -e end -m max]'%" } ;
ErrorId MsgGraph::UsePubKey           = { ErrorOf( ES_GRAPH, 127, E_FAILED, EV_USAGE, 0 ), "Usage: %'pubkey -d | -i [-f] [-u user] [-s scope]'%" } ;
ErrorId MsgGraph::UsePubKeyS          = { ErrorOf( ES_GRAPH, 128, E_FAILED, EV_USAGE, 0 ), "Usage: %'pubkeys [-u user] [-s scope]'%" } ;
ErrorId MsgGraph::ReferenceData       = { ErrorOf( ES_GRAPH, 8, E_INFO, EV_NONE, 5 ), "%depot% %sha% %owner% %type% %name%" } ;
ErrorId MsgGraph::ReferenceHistory    = { ErrorOf( ES_GRAPH, 116, E_INFO, EV_NONE, 7 ), "%repo% %sha% %type% %name% %action% %user% %date%" } ;
ErrorId MsgGraph::ReferenceDataShort  = { ErrorOf( ES_GRAPH, 9, E_INFO, EV_NONE, 3 ), "%depot% %sha% %name%" } ;
ErrorId MsgGraph::ReferenceDataMatch  = { ErrorOf( ES_GRAPH, 302, E_INFO, EV_NONE, 3 ), "%depot% %sha% %name% *" } ;
ErrorId MsgGraph::ReferenceDataEmpty  = { ErrorOf( ES_GRAPH, 342, E_INFO, EV_NONE, 3 ), "%depot% (no branches)" } ;
ErrorId MsgGraph::RepositoryData      = { ErrorOf( ES_GRAPH, 70, E_INFO, EV_NONE, 1 ), "%repo%" } ;
ErrorId MsgGraph::FileLogData         = { ErrorOf( ES_GRAPH, 10, E_INFO, EV_NONE, 4 ), "%depotFile%%depotRev% (%action%) %commit%" } ;
ErrorId MsgGraph::SubmoduleData       = { ErrorOf( ES_GRAPH, 253, E_INFO, EV_NONE, 3 ), "%repo% %path% %subrepo%" } ;
ErrorId MsgGraph::WrongClientType     = { ErrorOf( ES_GRAPH, 11, E_FAILED, EV_USAGE, 1 ), "A client of this type may not have a view that includes %depotFile%" } ;
ErrorId MsgGraph::NotSupported        = { ErrorOf( ES_GRAPH, 241, E_FAILED, EV_USAGE, 0 ), "This operation is not supported." } ;
ErrorId MsgGraph::CmdNotSupported     = { ErrorOf( ES_GRAPH, 249, E_FAILED, EV_USAGE, 1 ), "'p4 %cmd%' is not supported when using a graph type client." } ;
ErrorId MsgGraph::CurrentBranchShort  = { ErrorOf( ES_GRAPH, 12, E_INFO, EV_NONE, 2 ), "%depot% %branchName%" } ;
ErrorId MsgGraph::DetachedHead        = { ErrorOf( ES_GRAPH, 227, E_INFO, EV_NONE, 1 ), "%repoName% DETACHED HEAD" } ;
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
ErrorId MsgGraph::LooseWriterBadAccess = { ErrorOf( ES_GRAPH, 54, E_FATAL, EV_FAULT, 1 ), "LbrGraphLooseWriter: invalid operation %operation%." } ;
ErrorId MsgGraph::LbrWriteOnly        = { ErrorOf( ES_GRAPH, 55, E_FAILED, EV_FAULT, 0 ), "This librarian type only supports write access." } ;
ErrorId MsgGraph::TreeMissing         = { ErrorOf( ES_GRAPH, 56, E_FAILED, EV_FAULT, 1 ), "Tree record not found in db for sha %sha%." } ;
ErrorId MsgGraph::TreeNotUnique       = { ErrorOf( ES_GRAPH, 57, E_FAILED, EV_USAGE, 1 ), "Tree sha prefix %sha% is not unique. Please specify a longer prefix." } ;
ErrorId MsgGraph::RcvRefSyntax        = { ErrorOf( ES_GRAPH, 63, E_FAILED, EV_USAGE, 1 ), "Specify reference update as %'[-r|-F] <ref>=<sha>'%, not %value%." } ;
ErrorId MsgGraph::RcvFileName         = { ErrorOf( ES_GRAPH, 64, E_FAILED, EV_USAGE, 1 ), "File %filename% must be either a packfile or a loose object." } ;
ErrorId MsgGraph::NotFastForward      = { ErrorOf( ES_GRAPH, 65, E_WARN, EV_USAGE, 3 ), "Reference %branchName% may not be set to %newSha% because that is not a fast-forward update from %currentSha%." } ;
ErrorId MsgGraph::NotFastForward2     = { ErrorOf( ES_GRAPH, 340, E_FAILED, EV_USAGE, 3 ), "Reference %branchName% cannot be used as this would not be a fast-forward update from %oldSha% to %targetSha%." } ;
ErrorId MsgGraph::NotAGraphDepot      = { ErrorOf( ES_GRAPH, 67, E_FAILED, EV_USAGE, 1 ), "%depotName% is not a graph depot." } ;
ErrorId MsgGraph::UnknownRepo         = { ErrorOf( ES_GRAPH, 68, E_FAILED, EV_USAGE, 1 ), "%file% is not a repository in a graph depot." } ;
ErrorId MsgGraph::IllegalRefChar      = { ErrorOf( ES_GRAPH, 71, E_FAILED, EV_USAGE, 1 ), "Invalid character '%char%' in reference." } ;
ErrorId MsgGraph::IllegalRefSubstr    = { ErrorOf( ES_GRAPH, 72, E_FAILED, EV_USAGE, 1 ), "Invalid substring '%sequence%' in reference." } ;
ErrorId MsgGraph::UnqualifiedRef      = { ErrorOf( ES_GRAPH, 73, E_FAILED, EV_USAGE, 0 ), "Unqualified reference name is not allowed here." } ;
ErrorId MsgGraph::InvalidParentChar   = { ErrorOf( ES_GRAPH, 74, E_FAILED, EV_USAGE, 1 ), "Invalid character '%char%' in parent traversal." } ;
ErrorId MsgGraph::NoSuchParent        = { ErrorOf( ES_GRAPH, 75, E_FAILED, EV_USAGE, 2 ), "Commit %sha% does not contain a reference to parent number %parent%." } ;
ErrorId MsgGraph::RefTargetMissing    = { ErrorOf( ES_GRAPH, 76, E_WARN, EV_USAGE, 2 ), "Reference %ref% specifies a non-existent commit %commit%." } ;
ErrorId MsgGraph::InvalidReference    = { ErrorOf( ES_GRAPH, 82, E_FAILED, EV_USAGE, 2 ), "Reference %ref% could not be interpreted in repository %repository%" } ;
ErrorId MsgGraph::InvalidRepoRef      = { ErrorOf( ES_GRAPH, 282, E_FAILED, EV_USAGE, 1 ), "Reference is not valid for repo %repo%!" };
ErrorId MsgGraph::InvalidRepo         = { ErrorOf( ES_GRAPH, 83, E_FAILED, EV_USAGE, 1 ), "Repository %repository% does not appear to be valid." } ;
ErrorId MsgGraph::PackObjectCount     = { ErrorOf( ES_GRAPH, 84, E_FATAL, EV_FAULT, 2 ), "Pack construction wrote %actual% objects rather than the anticipated %expected% objects." } ;
ErrorId MsgGraph::PackObjectMissing   = { ErrorOf( ES_GRAPH, 85, E_FATAL, EV_FAULT, 1 ), "Pack construction failure: object %sha% missing from database." } ;
ErrorId MsgGraph::PackFileMissing     = { ErrorOf( ES_GRAPH, 303, E_FATAL, EV_FAULT, 0 ), "Pack file missing." } ;
ErrorId MsgGraph::PackObjectLength    = { ErrorOf( ES_GRAPH, 86, E_FATAL, EV_FAULT, 3 ), "Pack verification failure: Expected object of type %objectType% and length %objectLength% but uncompressed an object of length %actualLength%." } ;
ErrorId MsgGraph::InvalidRepoName     = { ErrorOf( ES_GRAPH, 87, E_FAILED, EV_USAGE, 1 ), "Repository name [%repoName% is invalid|is missing]. Please specify a name in the format //depot-name/path/to/repo." } ;
ErrorId MsgGraph::InvalidDepotName    = { ErrorOf( ES_GRAPH, 255, E_FAILED, EV_USAGE, 1 ), "Graph Depot name %depotName% is invalid. The name may not include the string %'.git'%." } ;
ErrorId MsgGraph::NotASha256          = { ErrorOf( ES_GRAPH, 92, E_FAILED, EV_USAGE, 1 ), "%sha% is not a valid SHA-256 value." } ;
ErrorId MsgGraph::LFSShaMismatch      = { ErrorOf( ES_GRAPH, 93, E_FAILED, EV_FAULT, 2 ), "LFS file push failure: content sha was %actual% instead of the expected sha %expected%." } ;
ErrorId MsgGraph::LFSAlreadyPresent   = { ErrorOf( ES_GRAPH, 143, E_INFO, EV_USAGE, 1 ), "LFS blob %sha% already exists." } ;
ErrorId MsgGraph::AtomicPushFailed    = { ErrorOf( ES_GRAPH, 94, E_FAILED, EV_FAULT, 1 ), "Reference %ref% could not be updated, and the command specified --atomic. No reference updates were performed." } ;
ErrorId MsgGraph::TriggerErrorMessage = { ErrorOf( ES_GRAPH, 95, E_FAILED, EV_ADMIN, 1 ), "%msg%" } ;
ErrorId MsgGraph::UseRepo             = { ErrorOf( ES_GRAPH, 96, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo [ -i -o -d -f ] [ repo ]'%" } ;
ErrorId MsgGraph::UseRepoo            = { ErrorOf( ES_GRAPH, 97, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -o repo'%" } ;
ErrorId MsgGraph::UseRepod            = { ErrorOf( ES_GRAPH, 98, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -d [ -f ] repo'%" } ;
ErrorId MsgGraph::UseRepoi            = { ErrorOf( ES_GRAPH, 99, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo -i'%" } ;
ErrorId MsgGraph::UseRepoc            = { ErrorOf( ES_GRAPH, 298, E_FAILED, EV_USAGE, 0 ), "Usage: %'repo [ --create-index | --drop-index ] [ repo ]'%" } ;
ErrorId MsgGraph::UseRepos            = { ErrorOf( ES_GRAPH, 100, E_FAILED, EV_USAGE, 0 ), "Usage: %'repos [-e|-E filter -m max -u user -O owner --from=origin]'%" } ;
ErrorId MsgGraph::ReposData           = { ErrorOf( ES_GRAPH, 101, E_INFO, EV_NONE, 5 ), "%repo% %owner% %forked% %created% %description%" } ;
ErrorId MsgGraph::RepoSave            = { ErrorOf( ES_GRAPH, 102, E_INFO, EV_NONE, 1 ), "Repo %repoName% saved." } ;
ErrorId MsgGraph::RepoNoChange        = { ErrorOf( ES_GRAPH, 103, E_INFO, EV_NONE, 1 ), "Repo %repoName% not changed." } ;
ErrorId MsgGraph::RepoDelete          = { ErrorOf( ES_GRAPH, 104, E_INFO, EV_NONE, 1 ), "Repo %repoName% deleted." } ;
ErrorId MsgGraph::NoSuchRepo          = { ErrorOf( ES_GRAPH, 105, E_FAILED, EV_UNKNOWN, 1 ), "Repo '%repo%' doesn't exist." } ;
ErrorId MsgGraph::BadRepoName         = { ErrorOf( ES_GRAPH, 106, E_FAILED, EV_USAGE, 1 ), "Repo name '%repo%' invalid. Specify name as //depot/repo/name." } ;
ErrorId MsgGraph::NotInGraphDepot     = { ErrorOf( ES_GRAPH, 107, E_FAILED, EV_USAGE, 1 ), "Repo name '%repo%' must be located in a valid graph depot." } ;
ErrorId MsgGraph::CantAutocreateRepo  = { ErrorOf( ES_GRAPH, 108, E_FAILED, EV_ADMIN, 1 ), "Repo '%repo%' does not exist in this server, and server policy prevents automatic creation of new repos. Please contact the server administrator to create the repo, then retry the operation." } ;
ErrorId MsgGraph::OutOfRepoLicenses   = { ErrorOf( ES_GRAPH, 273, E_FAILED, EV_ADMIN, 1 ), "Repo '%repo%' does not exist in this server, and server has hit maximum limit for new repos." } ;
ErrorId MsgGraph::MustForceFork       = { ErrorOf( ES_GRAPH, 109, E_FAILED, EV_USAGE, 2 ), "Repo %repo% was forked from %forkedRepo%. To create a fork of a fork, specify -f." } ;
ErrorId MsgGraph::ShowPermission      = { ErrorOf( ES_GRAPH, 114, E_INFO, EV_NONE, 5 ), "%repo% %branch% %type% %user% %perm%" } ;
ErrorId MsgGraph::DepotHasRepos       = { ErrorOf( ES_GRAPH, 118, E_FAILED, EV_NOTYET, 2 ), "Depot %depot% isn't empty of repos. One or more repos are still present in the depot directory. Display the existing repos with %'p4 repos -e'% %depotPrefix%. Delete those repos using %'p4 repo -d'%, then retry the depot deletion." } ;
ErrorId MsgGraph::EmptyRepo           = { ErrorOf( ES_GRAPH, 119, E_WARN, EV_EMPTY, 1 ), "%repo% is empty." } ;
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
ErrorId MsgGraph::PubKeyUpdateAction  = { ErrorOf( ES_GRAPH, 131, E_INFO, EV_NONE, 2 ), "Public Key for %user% with %scope% scope updated." } ;
ErrorId MsgGraph::PubKeyDeleteAction  = { ErrorOf( ES_GRAPH, 281, E_INFO, EV_NONE, 2 ), "Public Key for %user% with %scope% scope deleted." } ;
ErrorId MsgGraph::PubKeyNotExist      = { ErrorOf( ES_GRAPH, 150, E_FAILED, EV_USAGE, 2 ), "Public Key for %user% with %scope% scope does not exist." } ;
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
ErrorId MsgGraph::NoRepoSelected      = { ErrorOf( ES_GRAPH, 153, E_FAILED, EV_USAGE, 1 ), "Client %client% has no repos mapped. This command requires at least one repo to be mapped in the client's view." } ;
ErrorId MsgGraph::RefAlreadyExists    = { ErrorOf( ES_GRAPH, 159, E_FAILED, EV_USAGE, 1 ), "Reference %refName% already exists." } ;
ErrorId MsgGraph::RefDoesntExist      = { ErrorOf( ES_GRAPH, 160, E_FAILED, EV_USAGE, 2 ), "Reference %refName% does not exist[ in repo %repo%]." } ;
ErrorId MsgGraph::RefValidation       = { ErrorOf( ES_GRAPH, 161, E_FAILED, EV_USAGE, 1 ), "Reference update failed to validate. Reference %refName% may not be given the value %newSha% because the reference was expected to refer to %checkSha% but it actually refers to %headSha%." } ;
ErrorId MsgGraph::SpecifyForce        = { ErrorOf( ES_GRAPH, 162, E_FAILED, EV_USAGE, 1 ), "To change the value of the %fieldName% field, you must specify the -f flag." } ;
ErrorId MsgGraph::RebaseDefaultBranchForce  = { ErrorOf( ES_GRAPH, 350, E_FAILED, EV_USAGE, 1 ), "Cannot rebase the default branch '%branch%' on repo '%repo%'; use -f to force rebase." } ;
ErrorId MsgGraph::OpenSuccess         = { ErrorOf( ES_GRAPH, 200, E_INFO, EV_NONE, 2 ), "%depotFile% - opened for %action%" } ;
ErrorId MsgGraph::NoMultiRepoSubmit   = { ErrorOf( ES_GRAPH, 201, E_FAILED, EV_USAGE, 1 ), "Client %client% must specify precisely one repo in its View." } ;
ErrorId MsgGraph::NoReposForSubmit    = { ErrorOf( ES_GRAPH, 299, E_FAILED, EV_USAGE, 0 ), "None of repos involved by this change are mapped by this client." } ;
ErrorId MsgGraph::SingleRepoOnly      = { ErrorOf( ES_GRAPH, 203, E_FAILED, EV_USAGE, 0 ), "This command requires that exactly 1 repo be mapped by this client." } ;
ErrorId MsgGraph::DiffData            = { ErrorOf( ES_GRAPH, 204, E_INFO, EV_NONE, 2 ), "==== %depotFile% - %localPath% ====" } ;
ErrorId MsgGraph::NotAtHead           = { ErrorOf( ES_GRAPH, 205, E_FAILED, EV_USAGE, 5 ), "%command% failed: In %repo%, the head of %branch% is currently %headRef%, but your client is currently at %haveRef%. Sync to the head and try again." } ;
ErrorId MsgGraph::RepoNotHad          = { ErrorOf( ES_GRAPH, 263, E_FAILED, EV_USAGE, 1 ), "Submit failed: Your client includes %repo%, but you are not currently synced to that repo. You must sync to the head before submitting." } ;
ErrorId MsgGraph::SyncAdd             = { ErrorOf( ES_GRAPH, 206, E_INFO, EV_NONE, 2 ), "%depotFile% - added as %localPath%" } ;
ErrorId MsgGraph::SyncDelete          = { ErrorOf( ES_GRAPH, 207, E_INFO, EV_NONE, 2 ), "%depotFile% - deleted as %localPath%" } ;
ErrorId MsgGraph::SyncUpdate          = { ErrorOf( ES_GRAPH, 208, E_INFO, EV_NONE, 2 ), "%depotFile% - updating %localPath%" } ;
ErrorId MsgGraph::SyncIntegUpdate     = { ErrorOf( ES_GRAPH, 209, E_INFO, EV_NONE, 1 ), "%depotFile% - is opened and not being changed" } ;
ErrorId MsgGraph::SyncIntegDelete     = { ErrorOf( ES_GRAPH, 258, E_INFO, EV_NONE, 1 ), "%depotFile% - is opened for delete -- not changed" } ;
ErrorId MsgGraph::SyncUptodate        = { ErrorOf( ES_GRAPH, 210, E_INFO, EV_NONE, 1 ), "%depotFile% - is up-to-date" } ;
ErrorId MsgGraph::SyncRefresh         = { ErrorOf( ES_GRAPH, 276, E_INFO, EV_NONE, 2 ), "%depotFile% - refreshing %localPath%" } ;
ErrorId MsgGraph::RefAlreadySet       = { ErrorOf( ES_GRAPH, 212, E_FAILED, EV_USAGE, 1 ), "Reference %ref% already has a value; specify -f to force the new value." } ;
ErrorId MsgGraph::NoSuchTag           = { ErrorOf( ES_GRAPH, 213, E_FAILED, EV_USAGE, 1 ), "No such tag %tagName%" } ;
ErrorId MsgGraph::TagSaved            = { ErrorOf( ES_GRAPH, 214, E_INFO, EV_NONE, 1 ), "Tag %tagName% saved." } ;
ErrorId MsgGraph::TagDeleted          = { ErrorOf( ES_GRAPH, 215, E_INFO, EV_NONE, 1 ), "Tag %tagName% deleted." } ;
ErrorId MsgGraph::NotSyncd            = { ErrorOf( ES_GRAPH, 217, E_FAILED, EV_USAGE, 2 ), "Client %client% cannot create a new branch in repo %repo% because it is not currently syncd." } ;
ErrorId MsgGraph::BranchCreated       = { ErrorOf( ES_GRAPH, 218, E_INFO, EV_NONE, 2 ), "Branch %branchName% created in repo %repo%." } ;
ErrorId MsgGraph::BranchDeleted       = { ErrorOf( ES_GRAPH, 219, E_INFO, EV_NONE, 2 ), "Branch %branchName% deleted in repo %repo%." } ;
ErrorId MsgGraph::BranchAlreadyExists = { ErrorOf( ES_GRAPH, 283, E_FAILED, EV_USAGE, 2 ), "Branch %branchName% already exists in repo %repo%." } ;
ErrorId MsgGraph::DefaultBranchReset  = { ErrorOf( ES_GRAPH, 301, E_INFO, EV_NONE, 1 ), "DefaultBranch set to %branchName% for repo %repo%." } ;
ErrorId MsgGraph::FilesData           = { ErrorOf( ES_GRAPH, 225, E_INFO, EV_NONE, 1 ), "%depotFile%" } ;
ErrorId MsgGraph::ResolvedData        = { ErrorOf( ES_GRAPH, 245, E_INFO, EV_NONE, 4 ), "%clientFile% %how% %depotFile% %shaBuf%" } ;
ErrorId MsgGraph::DescribeFile        = { ErrorOf( ES_GRAPH, 231, E_INFO, EV_NONE, 2 ), "%depotFile% (%action%)" } ;
ErrorId MsgGraph::DirsData            = { ErrorOf( ES_GRAPH, 229, E_INFO, EV_NONE, 1 ), "%depotDir%" } ;
ErrorId MsgGraph::SyncNotSameBranch   = { ErrorOf( ES_GRAPH, 232, E_FAILED, EV_USAGE, 2 ), "Cannot sync to %target% because this client currently has files opened on branch %branch%." } ;
ErrorId MsgGraph::SyncNotFastForward  = { ErrorOf( ES_GRAPH, 233, E_FAILED, EV_USAGE, 2 ), "Cannot sync to %target% because it would not be a forward merge from the files opened at %haveCommit%." } ;
ErrorId MsgGraph::SyncUnknownBranch   = { ErrorOf( ES_GRAPH, 234, E_FATAL, EV_FAULT, 0 ), "Client has opened files, but is on an unknown branch." } ;
ErrorId MsgGraph::CommitSummary       = { ErrorOf( ES_GRAPH, 236, E_INFO, EV_NONE, 4 ), "Commit: %sha%\nAuthor: %authorName%\nDate: %authorDate%\nDescription: %description%\n" } ;
ErrorId MsgGraph::NoMergeOpenFiles    = { ErrorOf( ES_GRAPH, 237, E_FAILED, EV_USAGE, 0 ), "Merge not allowed: workspace has opened files." } ;
ErrorId MsgGraph::FastForwardMerge    = { ErrorOf( ES_GRAPH, 238, E_INFO, EV_NONE, 3 ), "Fast-forward merge of branch %branchName% to commit %sha%[ in repo %repo%]." } ;
ErrorId MsgGraph::MergePreview        = { ErrorOf( ES_GRAPH, 291, E_INFO, EV_NONE, 3 ), "%action% of branch %branchName% would succeed[ in repo %repo%]." } ;
ErrorId MsgGraph::BranchNotFound      = { ErrorOf( ES_GRAPH, 240, E_FAILED, EV_USAGE, 1 ), "Branch %branchName% not found." } ;
ErrorId MsgGraph::ManyReposUseAll     = { ErrorOf( ES_GRAPH, 308, E_FAILED, EV_USAGE, 0 ), "Multiple repos mapped by client; use -n to specify a single repo or -a for all." } ;
ErrorId MsgGraph::MergeComplete       = { ErrorOf( ES_GRAPH, 242, E_INFO, EV_NONE, 1 ), "Merge completed as %sha%[ in repo %repo%]." } ;
ErrorId MsgGraph::CherryPickComplete  = { ErrorOf( ES_GRAPH, 326, E_INFO, EV_NONE, 1 ), "Cherry-pick completed as %sha%[ in repo %repo%]." } ;
ErrorId MsgGraph::NoChangeFixes       = { ErrorOf( ES_GRAPH, 243, E_FAILED, EV_USAGE, 1 ), "Change %change% has fixes attached, and therefore may not be submitted." } ;
ErrorId MsgGraph::UnsupportedFileType = { ErrorOf( ES_GRAPH, 248, E_FAILED, EV_USAGE, 1 ), "File type %fileType% is not currently supported." } ;
ErrorId MsgGraph::ChangeViewBranch    = { ErrorOf( ES_GRAPH, 250, E_FAILED, EV_USAGE, 0 ), "Can't sync to a different branch when limited by changeview" } ;
ErrorId MsgGraph::ChangeViewFuture    = { ErrorOf( ES_GRAPH, 251, E_FAILED, EV_USAGE, 0 ), "Can't sync to a future sha when limited by changeview" } ;
ErrorId MsgGraph::SubmoduleOpen       = { ErrorOf( ES_GRAPH, 254, E_FAILED, EV_USAGE, 2 ), "In repo %repo%, file %depotFile% is part of a submodule and therefore must be modified in the submodule, not in this repo." } ;
ErrorId MsgGraph::UnknownRefType      = { ErrorOf( ES_GRAPH, 256, E_FAILED, EV_USAGE, 1 ), "Reference type %refType% unrecognized." } ;
ErrorId MsgGraph::CommitFileLog       = { ErrorOf( ES_GRAPH, 260, E_INFO, EV_NONE, 5 ), "commit %sha%\n[Merge: %merge%\n]Author: %author%\nDate: %date%\n%description%\n" } ;
ErrorId MsgGraph::CantUpgradePackDir  = { ErrorOf( ES_GRAPH, 264, E_INFO, EV_NONE, 1 ), "Failed to rename archive for repo %repo%." } ;
ErrorId MsgGraph::NoMatchingRepos     = { ErrorOf( ES_GRAPH, 265, E_FAILED, EV_USAGE, 1 ), "%spec% - No matching repos." } ;
ErrorId MsgGraph::InvalidRevSpec      = { ErrorOf( ES_GRAPH, 266, E_FAILED, EV_USAGE, 1 ), "Unexpected argument syntax[ - %revSpec%]" } ;
ErrorId MsgGraph::CorruptedTree       = { ErrorOf( ES_GRAPH, 267, E_FATAL, EV_FAULT, 1 ), "Tree node %sha% has no children, it might be corrupted or unreachable." } ;
ErrorId MsgGraph::NoAdvancedMappings  = { ErrorOf( ES_GRAPH, 268, E_FAILED, EV_USAGE, 0 ), "Cannot use '+' or '&' mappings in the same view as graph depot paths." } ;
ErrorId MsgGraph::CantAddToRepo       = { ErrorOf( ES_GRAPH, 269, E_FAILED, EV_NONE, 1 ), "p4 add of '%filepath%' failed - verify that this is the correct path and the repository for this file exists." } ;
ErrorId MsgGraph::CantUpdateMirror    = { ErrorOf( ES_GRAPH, 277, E_FAILED, EV_NONE, 3 ), "p4 %action% of '%filepath%' failed - repo '%repo%' is mirrored and cannot be updated." } ;
ErrorId MsgGraph::CantSubmitMirror    = { ErrorOf( ES_GRAPH, 278, E_FAILED, EV_NONE, 1 ), "Submit failed: repo '%repo%' is mirrored and cannot be updated." } ;
ErrorId MsgGraph::CantSubmitEmpty     = { ErrorOf( ES_GRAPH, 292, E_FAILED, EV_NONE, 0 ), "Submit failed: no modified repo files - submit empty commit requires '--allow-empty'." } ;
ErrorId MsgGraph::AutoLabelsOnly      = { ErrorOf( ES_GRAPH, 270, E_FAILED, EV_USAGE, 1 ), "Graph depot paths are only permitted in automatic labels." };
ErrorId MsgGraph::LabelViewMustLimit  = { ErrorOf( ES_GRAPH, 271, E_FAILED, EV_USAGE, 1 ), "Graph depot paths must be explicitly limited in label views." };
ErrorId MsgGraph::LabelViewMustNotLimit = { ErrorOf( ES_GRAPH, 272, E_FAILED, EV_USAGE, 1 ), "Only graph depot paths may be explicitly limited in label views." };
ErrorId MsgGraph::RepoNotMirrored     = { ErrorOf( ES_GRAPH, 274, E_FAILED, EV_USAGE, 1 ), "Repo '%repo%' not configured for mirror operation." } ;
ErrorId MsgGraph::RepoIsMirrored      = { ErrorOf( ES_GRAPH, 275, E_FAILED, EV_USAGE, 1 ), "Repo '%repo%' is configured only for mirror operations." } ;
ErrorId MsgGraph::GraphNotCompat      = { ErrorOf( ES_GRAPH, 280, E_FAILED, EV_USAGE, 1 ), "This version of the API is not compatible with GraphDepot." } ;
ErrorId MsgGraph::InvalidDefaultBranch = { ErrorOf( ES_GRAPH, 285, E_INFO, EV_USAGE, 1 ), "DefaultBranch '%defaultbranch%' must begin with \"refs/\" if git is to use it." } ;
ErrorId MsgGraph::LsTree              = { ErrorOf( ES_GRAPH, 286, E_INFO, EV_NONE, 4 ), "%mode% %type% %sha%\t%path%" } ;
ErrorId MsgGraph::LsTreeNameOnly      = { ErrorOf( ES_GRAPH, 287, E_INFO, EV_NONE, 4 ), "%path%" } ;
ErrorId MsgGraph::MergeConflict       = { ErrorOf( ES_GRAPH, 288, E_FAILED, EV_USAGE, 1 ), "Merge failed, conflict detected for '%depotFile%'" } ;
ErrorId MsgGraph::MergeNotText        = { ErrorOf( ES_GRAPH, 289, E_FAILED, EV_USAGE, 1 ), "Merge failed, non-textual file '%depotFile%'" } ;
ErrorId MsgGraph::MergeSkippedResolve = { ErrorOf( ES_GRAPH, 300, E_FAILED, EV_USAGE, 0 ), "Merge failed, some file(s) were skipped in interactive resolve." } ;
ErrorId MsgGraph::LFSDisabled         = { ErrorOf( ES_GRAPH, 293, E_FAILED, EV_FAULT, 1 ), "Import of LFS objects is disabled for '%repo%'." } ;
ErrorId MsgGraph::UseUpdateRef        = { ErrorOf( ES_GRAPH, 294, E_FAILED, EV_USAGE, 0 ), "Usage: %'update-ref -n repo [-u user -v] [-r refs... | -F refs...]'%" } ;
ErrorId MsgGraph::RepoIndexAlready    = { ErrorOf( ES_GRAPH, 295, E_FAILED, EV_USAGE, 1 ), "'%repo%' - index already exists." } ;
ErrorId MsgGraph::RepoIndexNone       = { ErrorOf( ES_GRAPH, 296, E_FAILED, EV_USAGE, 1 ), "'%repo%' - index does not exist." } ;
ErrorId MsgGraph::RepoIndexSuccess    = { ErrorOf( ES_GRAPH, 297, E_INFO, EV_NONE, 3 ), "'%repo%' - index created, %commits% commit(s), %files% file(s)." } ;
ErrorId MsgGraph::NoRepoEdgeSubmit    = { ErrorOf( ES_GRAPH, 304, E_FAILED, EV_NONE, 0 ), "Cannot submit using a graph client on edge replica." } ;
ErrorId MsgGraph::MirrorMissingFile   = { ErrorOf( ES_GRAPH, 305, E_FAILED, EV_NONE, 1 ), "Mirrored repo '%repo%' is missing some LFS files. Mirroring does not support LFS files.\n'%file%' missing LFS object." } ;
ErrorId MsgGraph::NoWriteForRef       = { ErrorOf( ES_GRAPH, 306, E_FAILED, EV_FAULT, 2 ), "%file% - no write permission on %ref% reference." } ;
ErrorId MsgGraph::RepoSwitchChanged   = { ErrorOf( ES_GRAPH, 309, E_INFO, EV_NONE, 3 ), "%depot% changed branch from %orig% to %name%" } ;
ErrorId MsgGraph::RepoAlreadyOnBranch = { ErrorOf( ES_GRAPH, 310, E_INFO, EV_NONE, 2 ), "%depot% is already on branch %name%" } ;
ErrorId MsgGraph::RepoSwitchMissing   = { ErrorOf( ES_GRAPH, 311, E_INFO, EV_NONE, 3 ), "%depot% has no branch %name%, will remain on branch %orig%" } ;
ErrorId MsgGraph::BlobNotFoundRepo    = { ErrorOf( ES_GRAPH, 312, E_FAILED, EV_FAULT, 2 ), "Commit '%sha%' not found in %repo%." } ;
ErrorId MsgGraph::FilelogMessage      = { ErrorOf( ES_GRAPH, 313, E_INFO, EV_USAGE, 5 ), "blob %blobsha% commit %commit% %action% on %date% by %user% %description%" } ;
ErrorId MsgGraph::MergeOfMessage      = { ErrorOf( ES_GRAPH, 314, E_INFO, EV_UNKNOWN, 1 ), "merge of %parents%" } ;
ErrorId MsgGraph::DescribeDiff        = { ErrorOf( ES_GRAPH, 315, E_INFO, EV_UNKNOWN, 2 ), "\n==== %repoFile% (%type%) ====\n" } ;
ErrorId MsgGraph::HeadChanged         = { ErrorOf( ES_GRAPH, 316, E_FAILED, EV_NONE, 3 ), "The head reference for %repo% has changed during the submit. Expect %expected% Observed %observed%. Resync and retry." } ;
ErrorId MsgGraph::SubmitCompleteWithRepo = { ErrorOf( ES_GRAPH, 318, E_INFO, EV_NONE, 3 ), "%change% renamed %commitSha% and submitted on %repo%." } ;
ErrorId MsgGraph::LbrPackCacheRequiresServerLocks = { ErrorOf( ES_GRAPH, 319, E_FAILED, EV_NONE, 0 ), "Internal error: LbrPackCache passed NULL serverLocks" } ;
ErrorId MsgGraph::Rebased             = { ErrorOf( ES_GRAPH, 320, E_INFO, EV_NONE, 5 ), "Rebased %baseSha% to %srcSha% onto %dstSha% to create %newSha% in repo %repo%." } ;
ErrorId MsgGraph::RebasedNoop         = { ErrorOf( ES_GRAPH, 351, E_INFO, EV_NONE, 2 ), "The target and base commits are the same - '%baseSha%'. Nothing to do." } ;
ErrorId MsgGraph::CherryPicked        = { ErrorOf( ES_GRAPH, 321, E_INFO, EV_NONE, 4 ), "Cherry picked %srcSha% onto %dstSha% to create %newSha% in repo %repo%." } ;
ErrorId MsgGraph::CherryPickedNoop      = { ErrorOf( ES_GRAPH, 352, E_INFO, EV_NONE, 2 ), "The target and cherry-pick commits are the same - '%baseSha%'. Nothing to do." } ;
ErrorId MsgGraph::RefUpdated          = { ErrorOf( ES_GRAPH, 322, E_INFO, EV_NONE, 2 ), "Reference %branch% updated to %newSha%" } ;
ErrorId MsgGraph::BadMergeMode        = { ErrorOf( ES_GRAPH, 323, E_FAILED, EV_UNKNOWN, 0 ), "Can't merge and cherry-pick at the same time!" } ;
ErrorId MsgGraph::BadSource           = { ErrorOf( ES_GRAPH, 324, E_FAILED, EV_UNKNOWN, 2 ), "Source '%commitish%' not found in %repo%." } ;
ErrorId MsgGraph::BadTarget           = { ErrorOf( ES_GRAPH, 325, E_FAILED, EV_UNKNOWN, 2 ), "Target '%commitish%' not found in %repo%." } ;
ErrorId MsgGraph::BadAtRev            = { ErrorOf( ES_GRAPH, 329, E_FAILED, EV_ILLEGAL, 1 ), "Invalid changelist/client/label/date/ref/sha '@%arg%'." } ;
ErrorId MsgGraph::NoMergeRequired     = { ErrorOf( ES_GRAPH, 331, E_INFO, EV_NONE, 1 ), "Nothing to merge[ for repo %repo%]" } ;
ErrorId MsgGraph::EditedWasDelete     = { ErrorOf( ES_GRAPH, 332, E_INFO, EV_NONE, 1 ), "%depotFile% - edit of deleted file; must %'revert'%" } ;
ErrorId MsgGraph::AlreadyDeleted      = { ErrorOf( ES_GRAPH, 333, E_INFO, EV_NONE, 1 ), "%depotFile% - open for delete of already deleted file; automatically removed" } ;
ErrorId MsgGraph::FileSpecific        = { ErrorOf( ES_GRAPH, 336, E_INFO, EV_NONE, 0 ), "File specific revisions:" } ;
ErrorId MsgGraph::FileSpecificData    = { ErrorOf( ES_GRAPH, 337, E_INFO, EV_NONE, 3 ), "%depot% %file% %sha%" } ;
ErrorId MsgGraph::OpenMustResolve     = { ErrorOf( ES_GRAPH, 338, E_INFO, EV_USAGE, 2 ), "%depotFile% - must %'sync'%/%'resolve'% %sha% before submitting" } ;
ErrorId MsgGraph::SyncResolve         = { ErrorOf( ES_GRAPH, 339, E_INFO, EV_NONE, 2 ), "%depotFile% - must %'resolve'% %sha% before submitting" } ;
ErrorId MsgGraph::NoPermOnRefRepo     = { ErrorOf( ES_GRAPH, 341, E_WARN, EV_NONE, 4 ), "User %user% does not have %permission% privilege for reference %ref% on repo %repo%." } ;
ErrorId MsgGraph::NoSuchRepoGrantPerm = { ErrorOf( ES_GRAPH, 345, E_FAILED, EV_UNKNOWN, 1 ), "Repo '%repo%' doesn't exist. Use '-f' to grant/revoke permission." } ;
ErrorId MsgGraph::NoSuchUserGrantPerm = { ErrorOf( ES_GRAPH, 343, E_FAILED, EV_UNKNOWN, 1 ), "User '%user%' doesn't exist. Use '-f' to grant/revoke permission." } ;
ErrorId MsgGraph::NoSuchGroupGrantPerm = { ErrorOf( ES_GRAPH, 344, E_FAILED, EV_UNKNOWN, 1 ), "Group '%group%' doesn't exist. Use '-f' to grant/revoke permission." } ;
ErrorId MsgGraph::IdWildPerm          = { ErrorOf( ES_DM, 346, E_FAILED, EV_USAGE, 1 ), "Only a single '*' is allowed as wildcard in permission target: '%id%'." } ;
ErrorId MsgGraph::DescribeHeader      = { ErrorOf( ES_GRAPH, 347, E_INFO, EV_NONE, 1 ), "Repo: %Reponame% CommitSHA: %SHA% Branch: %branchName%" } ;
ErrorId MsgGraph::CommitFileShort     = { ErrorOf( ES_GRAPH, 348, E_INFO, EV_NONE, 2 ), "commit %sha% %repo%[\nMerge: %merge%]" } ;
ErrorId MsgGraph::SHANotFound         = { ErrorOf( ES_GRAPH, 349, E_FAILED, EV_NONE, 2 ), "%sha% not found in change records for %repo%" } ;

// ErrorId graveyard: retired/deprecated ErrorIds. 

ErrorId MsgGraph::AmbiguousRepoName   = { ErrorOf( ES_GRAPH, 120, E_FAILED, EV_USAGE, 2 ), "Repo name '%repo%' may not be used. It would be an ambiguous name, because a repo named %otherRepo% already exists." } ;
ErrorId MsgGraph::SubmitComplete      = { ErrorOf( ES_GRAPH, 202, E_INFO, EV_NONE, 2 ), "%change% renamed %commitSha% and submitted." } ;
