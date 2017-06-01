/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/* 
 * P4Tags.cc - definition of rpc variable names
 */

# include <p4tags.h>

const char P4Tag::c_Ack[] = "client-Ack";
const char P4Tag::c_AckMatch[] = "client-AckMatch";
const char P4Tag::c_ActionResolve[] = "client-ActionResolve";
const char P4Tag::c_CheckFile[] = "client-CheckFile";
const char P4Tag::c_ReconcileEdit[] = "client-ReconcileEdit";
const char P4Tag::c_ChmodFile[] = "client-ChmodFile";
const char P4Tag::c_CloseDiff[] = "client-CloseDiff";
const char P4Tag::c_CloseFile[] = "client-CloseFile";
const char P4Tag::c_CloseMatch[] = "client-CloseMatch";
const char P4Tag::c_CloseMerge[] = "client-CloseMerge";
const char P4Tag::c_ConvertFile[] = "client-ConvertFile";
const char P4Tag::c_Crypto[] = "client-Crypto";
const char P4Tag::c_DeleteFile[] = "client-DeleteFile";
const char P4Tag::c_EditData[] = "client-EditData";
const char P4Tag::c_ErrorPause[] = "client-ErrorPause";
const char P4Tag::c_FstatInfo[] = "client-FstatInfo";
const char P4Tag::c_FstatPartial[] = "client-FstatPartial";
const char P4Tag::c_HandleError[] = "client-HandleError";
const char P4Tag::c_InputData[] = "client-InputData";
const char P4Tag::c_Message[] = "client-Message";
const char P4Tag::c_OpenDiff[] = "client-OpenDiff";
const char P4Tag::c_OpenFile[] = "client-OpenFile";
const char P4Tag::c_OpenMatch[] = "client-OpenMatch";
const char P4Tag::c_OpenMerge2[] = "client-OpenMerge2";
const char P4Tag::c_OpenMerge3[] = "client-OpenMerge3";
const char P4Tag::c_OutputBinary[] = "client-OutputBinary";
const char P4Tag::c_OutputData[] = "client-OutputData";
const char P4Tag::c_OutputError[] = "client-OutputError";
const char P4Tag::c_OutputInfo[] = "client-OutputInfo";
const char P4Tag::c_OutputText[] = "client-OutputText";
const char P4Tag::c_Ping[] = "client-Ping";
const char P4Tag::c_Progress[] = "client-Progress";
const char P4Tag::c_Prompt[] = "client-Prompt";
const char P4Tag::c_MoveFile[] = "client-MoveFile";
const char P4Tag::c_ReconcileAdd[] = "client-ReconcileAdd";
const char P4Tag::c_ReconcileFlush[] = "client-ReconcileFlush";
const char P4Tag::c_ReceiveFiles[] = "client-ReceiveFiles";
const char P4Tag::c_ExactMatch[] = "client-ExactMatch";
const char P4Tag::c_ScanDir[] = "client-ScanDir";
const char P4Tag::c_SendFile[] = "client-SendFile";
const char P4Tag::c_SetPassword[] = "client-SetPassword";
const char P4Tag::c_SSO[] = "client-SSO";
const char P4Tag::c_WriteDiff[] = "client-WriteDiff";
const char P4Tag::c_WriteFile[] = "client-WriteFile";
const char P4Tag::c_WriteMatch[] = "client-WriteMatch";
const char P4Tag::c_WriteMerge[] = "client-WriteMerge";

const char P4Tag::p_compress1[] = "compress1";
const char P4Tag::p_compress2[] = "compress2";
const char P4Tag::p_echo[] = "echo";
const char P4Tag::p_errorHandler[] = "errorHandler";
const char P4Tag::p_flush1[] = "flush1";
const char P4Tag::p_flush2[] = "flush2";
const char P4Tag::p_funcHandler[] = "funcHandler";
const char P4Tag::p_protocol[] = "protocol";
const char P4Tag::p_release[] = "release";
const char P4Tag::p_release2[] = "release2";

// These should be client known variables

const char P4Tag::v_actionOwner[] = "actionOwner";
const char P4Tag::v_action[] = "action";
const char P4Tag::v_api[] = "api";
const char P4Tag::v_app[] = "app";
const char P4Tag::v_appliedJnl[] = "appliedJnl";
const char P4Tag::v_appliedPos[] = "appliedPos";
const char P4Tag::v_andmap[] = "andmap";
const char P4Tag::v_attack[] = "attack";
const char P4Tag::v_attr[] = "attr";
const char P4Tag::v_authServer[] = "authServer";
const char P4Tag::v_autoLogin[] = "autoLogin";
const char P4Tag::v_autoTune[] = "autoTune";
const char P4Tag::v_baseName[] = "baseName";
const char P4Tag::v_bits[] = "bits";
const char P4Tag::v_blob[] = "blob";
const char P4Tag::v_blockCount[] = "blockCount";
const char P4Tag::v_branch[] = "branch";
const char P4Tag::v_broker[] = "broker";
const char P4Tag::v_archiveFile[] = "archiveFile";
const char P4Tag::v_caddr[] = "caddr";
const char P4Tag::v_caseHandling[] = "caseHandling";
const char P4Tag::v_change[] = "change";
const char P4Tag::v_changeIdentity[] = "changeIdentity";
const char P4Tag::v_changeImportedBy[] = "changeImportedBy";
const char P4Tag::v_changeServer[] = "changeServer";
const char P4Tag::v_changeType[] = "changeType";
const char P4Tag::v_charset[] = "charset";
const char P4Tag::v_checkpoint[] = "checkpoint";
const char P4Tag::v_checkLinks[] = "checkLinks";
const char P4Tag::v_clientAddress[] = "clientAddress";
const char P4Tag::v_clientCase[] = "clientCase";
const char P4Tag::v_clientCwd[] = "clientCwd";
const char P4Tag::v_clientFile[] = "clientFile";
const char P4Tag::v_clientHost[] = "clientHost";
const char P4Tag::v_clientName[] = "clientName";
const char P4Tag::v_clientRoot[] = "clientRoot";
const char P4Tag::v_clientStream[] = "clientStream";
const char P4Tag::v_client[] = "client";
const char P4Tag::v_cmpfile[] = "cmpfile";
const char P4Tag::v_code[] = "code";
const char P4Tag::v_commit[] = "commit";
const char P4Tag::v_commitAuthor[] = "author";
const char P4Tag::v_commitAuthorEmail[] = "authorEmail";
const char P4Tag::v_commits[] = "commits";
const char P4Tag::v_committer[] = "committer";
const char P4Tag::v_committerEmail[] = "committerEmail";
const char P4Tag::v_committerDate[] = "committerDate";
const char P4Tag::v_compare[] = "compare";
const char P4Tag::v_confirm[] = "confirm";
const char P4Tag::v_counter[] = "counter";
const char P4Tag::v_cwd[] = "cwd";
const char P4Tag::v_daddr[] = "daddr";
const char P4Tag::v_data[] = "data";
const char P4Tag::v_data2[] = "data2";
const char P4Tag::v_date[] = "date";
const char P4Tag::v_dbstat[] = "dbstat";
const char P4Tag::v_decline[] = "decline";
const char P4Tag::v_depotTime[] = "depotTime";
const char P4Tag::v_desc[] = "desc";
const char P4Tag::v_descKey[] = "oldChange";
const char P4Tag::v_dhash[] = "dhash";
const char P4Tag::v_diffFlags[] = "diffFlags";
const char P4Tag::v_digest[] = "digest";
const char P4Tag::v_digestType[] = "digestType";
const char P4Tag::v_digestTypeMD5[] = "md5";
const char P4Tag::v_digestTypeGitText[] = "GitText";
const char P4Tag::v_digestTypeGitBinary[] = "GitBinary";
const char P4Tag::v_digestTypeSHA256[] = "sha256";
const char P4Tag::v_dir[] = "dir";
const char P4Tag::v_enableGraph[] = "enableGraph";
const char P4Tag::v_enableStreams[] = "enableStreams";
const char P4Tag::v_endFromRev[] = "endFromRev";
const char P4Tag::v_endToRev[] = "endToRev";
const char P4Tag::v_erev[] = "erev";
const char P4Tag::v_expandAndmaps[] = "expandAndmaps";
const char P4Tag::v_externalAuth[] = "externalAuth";
const char P4Tag::v_extraTag[] = "extraTag";
const char P4Tag::v_extraTagType[] = "extraTagType";
const char P4Tag::v_fatal[] = "fatal";
const char P4Tag::v_fileCount[] = "fileCount";
const char P4Tag::v_fileNum[] = "fileNum";
const char P4Tag::v_fileSize[] = "fileSize";
const char P4Tag::v_file[] = "file";
const char P4Tag::v_filter[] = "filter";
const char P4Tag::v_fmt[] = "fmt";
const char P4Tag::v_forceType[] = "forceType";
const char P4Tag::v_fromFile[] = "fromFile";
const char P4Tag::v_fromRev[] = "fromRev";
const char P4Tag::v_fseq[] = "fseq";
const char P4Tag::v_func[] = "func";
const char P4Tag::v_func2[] = "func2";
const char P4Tag::v_handle[] = "handle";
const char P4Tag::v_haveRev[] = "haveRev";
const char P4Tag::v_headAction[] = "headAction";
const char P4Tag::v_headChange[] = "headChange";
const char P4Tag::v_headCharset[] = "headCharset";
const char P4Tag::v_headContent[] = "headContent";
const char P4Tag::v_headModTime[] = "headModTime";
const char P4Tag::v_headRev[] = "headRev";
const char P4Tag::v_headTime[] = "headTime";
const char P4Tag::v_headType[] = "headType";
const char P4Tag::v_himark[] = "himark";
const char P4Tag::v_host[] = "host";
const char P4Tag::v_how[] = "how";
const char P4Tag::v_ignore[] = "ignore";
const char P4Tag::v_initroot[] = "initroot";
const char P4Tag::v_isgroup[] = "isgroup";
const char P4Tag::v_journalcopyFlags[] = "journalcopyFlags";
const char P4Tag::v_job[] = "job";
const char P4Tag::v_jobstat[] = "jobstat";
const char P4Tag::v_jnlBatchSize[] = "jnlBatchSize";
const char P4Tag::v_journal[] = "journal";
const char P4Tag::v_key[] = "key";
const char P4Tag::v_language[] = "language";
const char P4Tag::v_lbrFile[] = "lbrFile";
const char P4Tag::v_lbrRev[] = "lbrRev";
const char P4Tag::v_lbrType[] = "lbrType";
const char P4Tag::v_lbrReplication[] = "lbr.replication";
const char P4Tag::v_leof_num[] = "leofNum";
const char P4Tag::v_leof_sequence[] = "leofSequence";
const char P4Tag::v_ldap[] = "ldap";
const char P4Tag::v_ldapAuth[] = "ldapAuth";
const char P4Tag::v_level[] = "level";
const char P4Tag::v_lfmt[] = "lfmt";
const char P4Tag::v_line[] = "line";
const char P4Tag::v_lower[] = "lower";
const char P4Tag::v_mangle[] = "mangle";
const char P4Tag::v_matchedLine[] = "matchedLine";
const char P4Tag::v_matchBegin[] = "matchBegin";
const char P4Tag::v_matchEnd[] = "matchEnd";
const char P4Tag::v_maxLockTime[] = "maxLockTime";
const char P4Tag::v_maxOpenFiles[] = "maxOpenFiles";
const char P4Tag::v_maxResults[] = "maxResults";
const char P4Tag::v_maxScanRows[] = "maxScanRows";
const char P4Tag::v_mergeAuto[] = "mergeAuto";
const char P4Tag::v_mergeConfirm[] = "mergeConfirm";
const char P4Tag::v_mergeDecline[] = "mergeDecline";
const char P4Tag::v_mergeHow[] = "mergeHow";
const char P4Tag::v_mergePerms[] = "mergePerms";
const char P4Tag::v_minClient[] = "minClient";
const char P4Tag::v_mode[] = "mode";
const char P4Tag::v_monitor[] = "monitor";
const char P4Tag::v_name[] = "name";
const char P4Tag::v_newServerId[] = "newServerId";
const char P4Tag::v_noBase[] = "noBase";
const char P4Tag::v_nocase[] = "nocase";
const char P4Tag::v_noclobber[] = "noclobber";
const char P4Tag::v_noecho[] = "noecho";
const char P4Tag::v_noprompt[] = "noprompt";
const char P4Tag::v_offset[] = "offset";
const char P4Tag::v_oid[] = "oid";
const char P4Tag::v_op[] = "op";
const char P4Tag::v_open[] = "open";
const char P4Tag::v_os[] = "os";
const char P4Tag::v_otherAction[] = "otherAction";
const char P4Tag::v_otherChange[] = "otherChange";
const char P4Tag::v_otherLock[] = "otherLock";
const char P4Tag::v_otherOpen[] = "otherOpen";
const char P4Tag::v_ourLock[] = "ourLock";
const char P4Tag::v_packName[] = "packName";
const char P4Tag::v_parent[] = "parent";
const char P4Tag::v_password[] = "password";
const char P4Tag::v_path[] = "path";
const char P4Tag::v_path2[] = "path2";
const char P4Tag::v_peeking[] = "peeking";
const char P4Tag::v_perm[] = "perm";
const char P4Tag::v_permmax[] = "permMax";
const char P4Tag::v_perms[] = "perms";
const char P4Tag::v_port[] = "port";
const char P4Tag::v_preview[] = "preview";
const char P4Tag::v_prog[] = "prog";
const char P4Tag::v_progress[] = "progress";
const char P4Tag::v_proxy[] = "proxy";
const char P4Tag::v_proxyAddress[] = "proxyAddress";
const char P4Tag::v_proxyEncryption[] = "proxyEncryption";
const char P4Tag::v_proxyCertExpires[] = "proxyCertExpires";
const char P4Tag::v_proxyRoot[] = "proxyRoot";
const char P4Tag::v_proxyVersion[] = "proxyVersion";
const char P4Tag::v_pusher[] = "pusher";
const char P4Tag::v_rActionType[] = "rActionType";
const char P4Tag::v_rActionMerge[] = "rActionMerge";
const char P4Tag::v_rActionTheirs[] = "rActionTheirs";
const char P4Tag::v_rActionYours[] = "rActionYours";
const char P4Tag::v_rAutoResult[] = "rAutoResult";
const char P4Tag::v_rOptAuto[] = "rOptAuto";
const char P4Tag::v_rOptHelp[] = "rOptHelp";
const char P4Tag::v_rOptMerge[] = "rOptMerge";
const char P4Tag::v_rOptSkip[] = "rOptSkip";
const char P4Tag::v_rOptTheirs[] = "rOptTheirs";
const char P4Tag::v_rOptYours[] = "rOptYours";
const char P4Tag::v_rPromptMerge[] = "rPromptMerge";
const char P4Tag::v_rPromptTheirs[] = "rPromptTheirs";
const char P4Tag::v_rPromptType[] = "rPromptType";
const char P4Tag::v_rPromptYours[] = "rPromptYours";
const char P4Tag::v_rUserError[] = "rUserError";
const char P4Tag::v_rUserHelp[] = "rUserHelp";
const char P4Tag::v_rUserPrompt[] = "rUserPrompt";
const char P4Tag::v_rUserResult[] = "rUserResult";
const char P4Tag::v_rcvbuf[] = "rcvbuf";
const char P4Tag::v_reason[] = "reason";
const char P4Tag::v_ref[] = "ref";
const char P4Tag::v_remap[] = "remap";
const char P4Tag::v_remoteFunc[] = "remoteFunc";
const char P4Tag::v_remoteMap[] = "remoteMap";
const char P4Tag::v_remoteRange[] = "remoteRange";
const char P4Tag::v_repo[] = "repo";
const char P4Tag::v_repoName[] = "repoName";
const char P4Tag::v_reresolvable[] = "reresolvable";
const char P4Tag::v_resolved[] = "resolved";
const char P4Tag::v_resolveFlag[] = "resolveFlag";
const char P4Tag::v_resolveType[] = "resolveType";
const char P4Tag::v_rev[] = "rev";
const char P4Tag::v_rev2[] = "rev2";
const char P4Tag::v_rmdir[] = "rmdir";
const char P4Tag::v_rseq[] = "rseq";
const char P4Tag::v_scanSize[] = "scanSize";
const char P4Tag::v_scope[] = "scope";
const char P4Tag::v_security[] = "security";
const char P4Tag::v_sendspec[] = "sendspec";
const char P4Tag::v_sndbuf[] = "sndbuf";
const char P4Tag::v_sequence[] = "sequence";
const char P4Tag::v_server2[] = "server2";
const char P4Tag::v_server[] = "server";
const char P4Tag::v_serverID[] = "serverID";
const char P4Tag::v_serverAddress[] = "serverAddress";
const char P4Tag::v_serverCluster[] = "serverCluster";
const char P4Tag::v_serverDescription[] = "serverDescription";
const char P4Tag::v_serverDate[] = "serverDate";
const char P4Tag::v_serverEncryption[] = "serverEncryption";
const char P4Tag::v_serverCertExpires[] = "serverCertExpires";
const char P4Tag::v_serverName[] = "serverName";
const char P4Tag::v_serverRoot[] = "serverRoot";
const char P4Tag::v_serverType[] = "serverType";
const char P4Tag::v_serverUptime[] = "serverUptime";
const char P4Tag::v_serverLicense[] = "serverLicense";
const char P4Tag::v_serverLicenseIp[] = "serverLicense-ip";
const char P4Tag::v_serverVersion[] = "serverVersion";
const char P4Tag::v_sha[] = "sha";
const char P4Tag::v_showAll[] = "showAll";
const char P4Tag::v_size[] = "size";
const char P4Tag::v_specdef[] = "specdef";		// 97.3
const char P4Tag::v_specstring[] = "specstring";
const char P4Tag::v_specFormatted[] = "specFormatted";
const char P4Tag::v_srev[] = "srev";
const char P4Tag::v_sso[] = "sso";
const char P4Tag::v_startFromRev[] = "startFromRev";
const char P4Tag::v_startToRev[] = "startToRev";
const char P4Tag::v_stat[] = "stat";
const char P4Tag::v_status[] = "status";
const char P4Tag::v_svrname[] = "svrname";
const char P4Tag::v_symref[] = "symref";
const char P4Tag::v_tableexcludelist[] = "tableexcludelist";
const char P4Tag::v_tag[] = "tag";
const char P4Tag::v_tagJnl[] = "tagjnl";
const char P4Tag::v_theirName[] = "theirName";
const char P4Tag::v_theirTime[] = "theirTime";
const char P4Tag::v_time[] = "time";
const char P4Tag::v_toFile[] = "toFile";
const char P4Tag::v_token[] = "token";
const char P4Tag::v_token2[] = "token2";
const char P4Tag::v_total[] = "total";
const char P4Tag::v_totalFileCount[] = "totalFileCount";
const char P4Tag::v_totalFileSize[] = "totalFileSize";
const char P4Tag::v_track[] = "track";			// 2005.2
const char P4Tag::v_trans[] = "trans";			// 2001.2
const char P4Tag::v_tree[] = "tree";
const char P4Tag::v_truncate[] = "truncate";
const char P4Tag::v_type[] = "type";
const char P4Tag::v_type2[] = "type2";
const char P4Tag::v_type3[] = "type3";
const char P4Tag::v_type4[] = "type4";
const char P4Tag::v_unicode[] = "unicode";
const char P4Tag::v_unmap[] = "unmap";
const char P4Tag::v_unresolved[] = "unresolved";
const char P4Tag::v_upper[] = "upper";
const char P4Tag::v_user[] = "user";
const char P4Tag::v_userChanged[] = "userChanged";
const char P4Tag::v_userName[] = "userName";
const char P4Tag::v_version[] = "version";
const char P4Tag::v_warning[] = "warning";
const char P4Tag::v_wingui[] = "wingui";
const char P4Tag::v_workRev[] = "workRev";
const char P4Tag::v_write[] = "write";
const char P4Tag::v_xfiles[] = "xfiles";
const char P4Tag::v_yourName[] = "yourName";

// These should be the server-to-server or server-to-proxy variables

const char P4Tag::v_allTamperCheck[] = "allTamperCheck";
const char P4Tag::v_altArg[] = "altArg";
const char P4Tag::v_altArg2[] = "altArg2";
const char P4Tag::v_altArg3[] = "altArg3";
const char P4Tag::v_arg[] = "arg";
const char P4Tag::v_asBinary[] = "asBinary";
const char P4Tag::v_attrib[] = "attrib";
const char P4Tag::v_author[] = "Author";
const char P4Tag::v_bkupInterval[] ="bkupInterval";
const char P4Tag::v_baseDepotRec[] = "baseDepotRec";
const char P4Tag::v_changeNo[] = "changeNo";
const char P4Tag::v_checkSum[] = "checkSum";
const char P4Tag::v_clientEntity[] = "clientEntity";
const char P4Tag::v_confirm2[] = "confirm2";
const char P4Tag::v_dataHandle[] = "dataHandle";
const char P4Tag::v_delete[] = "delete";
const char P4Tag::v_depotFile[] = "depotFile";
const char P4Tag::v_depotFile2[] = "depotFile2";
const char P4Tag::v_depotName[] = "depotName";
const char P4Tag::v_depotRec[] = "depotRec";
const char P4Tag::v_do[] = "do";
const char P4Tag::v_doForce[] = "doForce";
const char P4Tag::v_doPromote[] = "doPromote";
const char P4Tag::v_fixStatus[] = "fixStatus";
const char P4Tag::v_force[] = "force";
const char P4Tag::v_getFlag[] = "getFlag";
const char P4Tag::v_haveRec[] = "haveRec";
const char P4Tag::v_ignoreIsEdit[] = "ignoreIsEdit";
const char P4Tag::v_index[] = "index";
const char P4Tag::v_integRec[] = "integRec";
const char P4Tag::v_integRec2[] = "integRec2";
const char P4Tag::v_ipaddr[] = "ipaddr";
const char P4Tag::v_keyVal[] = "keyVal";
const char P4Tag::v_labelEntity[] = "labelEntity";
const char P4Tag::v_leaveUnchanged[] = "leaveUnchanged";
const char P4Tag::v_lockAll[] = "lockAll";
const char P4Tag::v_message[] = "message";
const char P4Tag::v_message2[] = "message2";
const char P4Tag::v_movedFile[] = "movedFile";
const char P4Tag::v_movedRev[] = "movedRev";
const char P4Tag::v_noretry[] = "noretry";
const char P4Tag::v_peer[] = "peer";
const char P4Tag::v_peerAddress[] = "peerAddress";
const char P4Tag::v_propigate[] = "propigate";
const char P4Tag::v_replace[] = "replace";
const char P4Tag::v_reopen[] = "reopen";
const char P4Tag::v_revertUnchanged[] = "revertUnchanged";
const char P4Tag::v_revRec[] = "revRec";
const char P4Tag::v_revtime[] = "revtime";
const char P4Tag::v_revver[] = "revver";
const char P4Tag::v_role[] = "role";
const char P4Tag::v_save[] = "save";
const char P4Tag::v_setViews[] = "setViews"; // set client views even if empty
const char P4Tag::v_shelved[] = "shelved";
const char P4Tag::v_shelveFile[] = "shelveFile";
const char P4Tag::v_state[] = "state";
const char P4Tag::v_table[] = "table";
const char P4Tag::v_traitCount[] = "traitCount";
const char P4Tag::v_tzoffset[] = "tzoffset";
const char P4Tag::v_output[] = "output";
const char P4Tag::v_unloadInterval[] = "unloadInterval";
const char P4Tag::v_value[] = "value";
const char P4Tag::v_workRec[] = "workRec";
const char P4Tag::v_workRec2[] = "workRec2";
const char P4Tag::v_yourDepotRec[] = "yourDepotRec";
const char P4Tag::v_zksEntity[] = "zksEntity";

const char P4Tag::u_add[]      = "add";
const char P4Tag::u_admin[]    = "admin";
const char P4Tag::u_branch[]   = "branch";
const char P4Tag::u_branches[] = "branches";
const char P4Tag::u_change[]   = "change";
const char P4Tag::u_changes[]  = "changes";
const char P4Tag::u_client[]   = "client";
const char P4Tag::u_clients[]  = "clients";
const char P4Tag::u_counter[]  = "counter";
const char P4Tag::u_counters[] = "counters";
const char P4Tag::u_delete[]   = "delete";
const char P4Tag::u_depot[]    = "depot";
const char P4Tag::u_depots[]   = "depots";
const char P4Tag::u_describe[] = "describe";
const char P4Tag::u_diff[]     = "diff"	;
const char P4Tag::u_diff2[]    = "diff2";
const char P4Tag::u_dirs[]     = "dirs"	;
const char P4Tag::u_edit[]     = "edit"	;
const char P4Tag::u_fetch[]    = "fetch";
const char P4Tag::u_filelog[]  = "filelog";
const char P4Tag::u_files[]    = "files";
const char P4Tag::u_fix[]      = "fix";
const char P4Tag::u_fixes[]    = "fixes";
const char P4Tag::u_flush[]    = "flush";
const char P4Tag::u_fstat[]    = "fstat";
const char P4Tag::u_group[]    = "group";
const char P4Tag::u_groups[]   = "groups";
const char P4Tag::u_have[]     = "have";
const char P4Tag::u_help[]     = "help";
const char P4Tag::u_info[]     = "info";
const char P4Tag::u_integrate[]  = "integrate";
const char P4Tag::u_integrated[] = "integrated";
const char P4Tag::u_job[]      = "job";
const char P4Tag::u_jobs[]     = "jobs";
const char P4Tag::u_jobspec[]  = "jobspec";
const char P4Tag::u_label[]    = "label";
const char P4Tag::u_labels[]   = "labels";
const char P4Tag::u_labelsync[]  = "labelsync";
const char P4Tag::u_lock[]       = "lock";
const char P4Tag::u_obliterate[] = "obliterate";
const char P4Tag::u_opened[]   = "opened";
const char P4Tag::u_passwd[]   = "passwd";
const char P4Tag::u_print[]    = "print";
const char P4Tag::u_protect[]  = "protect";
const char P4Tag::u_push[]     = "push";
const char P4Tag::u_reconcile[]   = "reconcile";
const char P4Tag::u_remote[]   = "remote";
const char P4Tag::u_remotes[]  = "remotes";
const char P4Tag::u_rename[]   = "rename";
const char P4Tag::u_reopen[]   = "reopen";
const char P4Tag::u_resolve[]  = "resolve";
const char P4Tag::u_resolved[] = "resolved";
const char P4Tag::u_resubmit[] = "resubmit";
const char P4Tag::u_revert[]   = "revert";
const char P4Tag::u_review[]   = "review";
const char P4Tag::u_reviews[]  = "reviews";
const char P4Tag::u_set[]      = "set";
const char P4Tag::u_stream[]   = "stream";
const char P4Tag::u_streams[]   = "streams";
const char P4Tag::u_submit[]   = "submit";
const char P4Tag::u_switch[]   = "switch";
const char P4Tag::u_sync[]     = "sync";
const char P4Tag::u_triggers[] = "triggers";
const char P4Tag::u_typemap[]  = "typemap";
const char P4Tag::u_undo[]     = "undo";
const char P4Tag::u_unlock[]   = "unlock";
const char P4Tag::u_unsubmit[] = "unsubmit";
const char P4Tag::u_unzip[]    = "unzip";
const char P4Tag::u_user[]     = "user";
const char P4Tag::u_users[]    = "users";
const char P4Tag::u_verify[]   = "verify";
const char P4Tag::u_where[]    = "where";
const char P4Tag::u_zip[]      = "zip";

// server-p4zk message fields
const char P4Tag::z_clusterid[]   = "clusterid";
const char P4Tag::z_clusterrole[] = "clusterrole";
const char P4Tag::z_genNum[]      = "generationNum";
const char P4Tag::z_jnlnum[]      = "journalnumber";
const char P4Tag::z_jnloffst[]    = "journaloffset";
const char P4Tag::z_p4port[]      = "p4port";
const char P4Tag::z_p4target[]    = "p4target";
const char P4Tag::z_pid[]         = "pid";
const char P4Tag::z_serverid[]    = "serverid";
const char P4Tag::z_zkhostport[]  = "zkhostport";
const char P4Tag::z_zkconnecttime[] = "zkconnecttime";
const char P4Tag::z_brokercfg[]   = "brokercfg";
