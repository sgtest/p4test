/*
 * Copyright 2008 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

enum P4TunableName {

	P4TUNE_CLUSTER_JOURNAL_SHARED = DT_LAST,// see db/dbjournal2.cc
	P4TUNE_DB_ISALIVE,
	P4TUNE_DB_MONITOR_SHARED,
	P4TUNE_DB_PEEKING,
	P4TUNE_DB_REORG_DISABLE,
	P4TUNE_DB_REORG_MISORDER,
	P4TUNE_DB_REORG_OCCUP,
	P4TUNE_DB_TRYLOCK,			// see dbschema.cc
	P4TUNE_DBARRAY_PUTCHECK,		// see dbarray.cc
	P4TUNE_DBARRAY_RESERVE,			// see dbarray.cc
	P4TUNE_DBJOURNAL_BUFSIZE,		// see dbjournal2.cc
	P4TUNE_DBJOURNAL_WORDSIZE,		// see dbjournal2.cc
	P4TUNE_DBOPEN_CACHE,			// see dbopen.cc
	P4TUNE_DBOPEN_CACHE_WIDE,		// see dbopen.cc
	P4TUNE_DBOPEN_FREEPCT,			// see dbopen.cc
	P4TUNE_DBOPEN_MISMATCH_DELAY,		// see bt_fio.cc
	P4TUNE_DBOPEN_NOFSYNC,			// see btree.cc
	P4TUNE_DBOPEN_PAGESIZE,			// see dbopen.cc
	P4TUNE_DBOPEN_RETRY,			// see bt_fio.cc
	P4TUNE_DIFF_BINARY_RCS,			// see dmtypes.cc
	P4TUNE_DIFF_SLIMIT1,
	P4TUNE_DIFF_SLIMIT2,
	P4TUNE_DIFF_STHRESH,
	P4TUNE_DM_ANNOTATE_MAXSIZE,
	P4TUNE_DM_BATCH_DOMAINS,		// see dmdomains.cc
	P4TUNE_DM_CHANGES_THRESH1,		// set dmchanges.cc
	P4TUNE_DM_CHANGES_THRESH2,		// set dmchanges.cc
	P4TUNE_DM_DOMAIN_ACCESSUPDATE,		// see dmadomain.cc
	P4TUNE_DM_DOMAIN_ACCESSFORCE,		// see dmadomain.cc
	P4TUNE_DM_FLUSHFORCE,
	P4TUNE_DM_FLUSHTRY,
	P4TUNE_DM_FSTAT_MAXCONTENT,		// see userfstat.cc
	P4TUNE_DM_GREP_MAXLINELENGTH,
	P4TUNE_DM_GREP_MAXREVS,
	P4TUNE_DM_GREP_MAXCONTEXT,
	P4TUNE_DM_INTEG_ENGINE,
	P4TUNE_DM_INTEG_MAXACT,
	P4TUNE_DM_INTEG_TWEAKS,
	P4TUNE_DM_ISALIVE,			// set dmcaller.cc
	P4TUNE_DM_KEYS_HIDE,			// see dmcounters.cc
	P4TUNE_DM_MAXKEY,			// see dmtypes.cc
	P4TUNE_DM_PASSWORD_MINLENGTH,
	P4TUNE_DM_PROTECTS_ALLOW_ADMIN,
	P4TUNE_DM_PROTECTS_HIDE,
	P4TUNE_DM_PROXY_PROTECTS,
	P4TUNE_DM_QUICK_CLIENTS,
	P4TUNE_DM_QUICK_DOMAINS,
	P4TUNE_DM_QUICK_HAVE,
	P4TUNE_DM_QUICK_INTEG,
	P4TUNE_DM_QUICK_RESOLVE,
	P4TUNE_DM_QUICK_REV,
	P4TUNE_DM_QUICK_WORKING,
	P4TUNE_DM_RESOLVE_ATTRIB,
	P4TUNE_DM_REVCX_THRESH1,
	P4TUNE_DM_REVCX_THRESH2,
	P4TUNE_DM_SHELVE_MAXFILES,
	P4TUNE_DM_SHELVE_MAXSIZE,
	P4TUNE_DM_STATUS_MATCHLINES,		// see userreconcile.cc
	P4TUNE_DM_STATUS_MATCHSIZE,		// see dmreconcile.cc
	P4TUNE_DM_USER_ACCESSUPDATE,		// see dmauser.cc
	P4TUNE_DM_USER_ACCESSFORCE,		// see dmauser.cc
	P4TUNE_DM_USER_LOGINATTEMPTS,		// see dmauser.cc
	P4TUNE_DM_USER_NOAUTOCREATE,		// see dmauser.cc
	P4TUNE_DM_USER_RESETPASSWORD,		// see dmauser.cc
	P4TUNE_FILESYS_BINARYSCAN,		// see filecheck.cc
	P4TUNE_FILESYS_BUFSIZE,			// see filesys.h
	P4TUNE_FILESYS_CACHEHINT,		// see filesys.cc
	P4TUNE_FILESYS_MAKETMP,
	P4TUNE_FILESYS_MAXMAP,			// see readfile.cc
	P4TUNE_FILESYS_MAXSYMLINK,		// see fileiosym.cc
	P4TUNE_FILESYS_MAXTMP,
	P4TUNE_FILESYS_EXTENDLOWMARK,
	P4TUNE_INDEX_DOMAIN_OWNER,              // see dmdomains.cc
	P4TUNE_LBR_BUFSIZE,			// see lbr.h
	P4TUNE_LBR_PROXY_CASE,			// see pxclient.cc
	P4TUNE_LBR_RETRY_MAX,			// see lbrstatus.cc
	P4TUNE_LBR_STAT_INTERVAL,		// see pxclient.cc and lbrstatus.cc
	P4TUNE_LBR_VERIFY_IN,			// see lbrservice.cc
	P4TUNE_LBR_VERIFY_OUT,			// see rhservice.cc
	P4TUNE_LBR_RCS_MAXLEN,			// see lbrkeyed.cc
	P4TUNE_MAP_JOINMAX1,
	P4TUNE_MAP_JOINMAX2,
	P4TUNE_MAP_MAXWILD,
	P4TUNE_NET_BUFSIZE,			// see netbuffer.h
	P4TUNE_NET_KEEPALIVE_DISABLE,		// see nettcptransport.cc
	P4TUNE_NET_KEEPALIVE_IDLE,		// see nettcptransport.cc
	P4TUNE_NET_KEEPALIVE_INTERVAL,		// see nettcptransport.cc
	P4TUNE_NET_KEEPALIVE_COUNT,		// see nettcptransport.cc
	P4TUNE_NET_MAX_FAULT_PUB,		// see proxy/pxclient.cc
	P4TUNE_NET_MAXWAIT,			// see nettcptransport.cc, netssltrancport.cc
	P4TUNE_NET_PARALLEL_MAX,		// see dmparsend.cc
	P4TUNE_NET_RCVBUFSIZE,			// see netbuffer.h
	P4TUNE_NET_REUSEPORT,			// see nettcpendpoint.cc
	P4TUNE_NET_RFC3484,			// see nettcpendpoint.cc
	P4TUNE_NET_TCPSIZE,			// set nettcp.cc
	P4TUNE_NET_BACKLOG,			// see nettcp.cc
	P4TUNE_PROXY_MONITOR_INTERVAL,		// see pxmonitor.cc
	P4TUNE_PROXY_MONITOR_LEVEL,		// see pxmonitor.cc
	P4TUNE_RCS_MAXINSERT,
	P4TUNE_RCS_NOFSYNC,			// see rcsvfile.cc
	P4TUNE_RPC_DELIVER_DUPLEX,		// See userfiles.cc,usersync.cc
	P4TUNE_RPC_HIMARK,
	P4TUNE_RPC_LOWMARK,
	P4TUNE_RPL_CHECKSUM_AUTO,
	P4TUNE_RPL_CHECKSUM_CHANGE,
	P4TUNE_RPL_CHECKSUM_TABLE,
	P4TUNE_RPL_COMPRESS,			// See server / rpl.cc
	P4TUNE_RPL_COUNTER_HOOK,		// See server / userpull.cc
	P4TUNE_RPL_GROUPED,			// See server / rmtservice.cc
	P4TUNE_RPL_JNLWAIT_ADJUST,		// See server / rpl.cc
	P4TUNE_RPL_JNLWAIT_INTERVAL,		// See server / rpl.cc
	P4TUNE_RPL_JNLWAIT_MAX,			// See server / rpl.cc
	P4TUNE_RPL_LABELS_GLOBAL,		// See userlabel/userlabsync
	P4TUNE_RPL_VERIFY_CACHE,		// See rhservice.cc
	P4TUNE_RUN_MOVE_ALLOW,			// see usermove.cc
	P4TUNE_RUN_OBLITERATE_ALLOW,		// see userpurge.cc
	P4TUNE_RUN_USERS_AUTHORIZE,		// see userusers.cc
	P4TUNE_SERVER_COMMANDLIMITS,		// see dmcaller.cc
	P4TUNE_SERVER_FILECHARSET,
	P4TUNE_SERVER_LOCKS_SYNC,		// see usersync.cc
	P4TUNE_SERVER_MAXCOMMANDS,		// see rhmain.cc
	P4TUNE_FILETYPE_MAXTEXTSIZE,		// set useropen.cc
	P4TUNE_SPEC_HASHBUCKETS,		// see rhspecmgr.cc
	P4TUNE_SPEC_CUSTOM,			// see userspec.cc
	P4TUNE_STREAMVIEW_DOTS_LOW,		// see maptable.cc
	P4TUNE_STREAMVIEW_SORT_REMAP,		// see viewgen.cc
	P4TUNE_SUBMIT_UNLOCK_LOCKED,		// see usersubmit.cc
	// vv Smart Heap tunables must be a continuous group vv
	P4TUNE_SYS_MEMORY_POOLFREE,		// see shhandler.cc
	P4TUNE_SYS_MEMORY_PROCFREE,		// see shhandler.cc
	P4TUNE_SYS_MEMORY_POOLGROWINC,		// see shhandler.cc
	P4TUNE_SYS_MEMORY_PROCGROWINC,		// see shhandler.cc
	P4TUNE_SYS_MEMORY_SUBPOOLS,		// see shhandler.cc
	P4TUNE_SYS_MEMORY_LIMIT,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_POOLFREE,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_PROCFREE,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_LIMIT,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_FLUSHPOOL,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_LISTPOOL,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_LISTPOOL2,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_LISTALL,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_LISTALL2,		// see shhandler.cc
	P4TUNE_CMD_MEMORY_CHKPT,		// see shhandler.cc
	// ^^ Smart Heap tunables must be a continuous group ^^
	P4TUNE_SYS_MEMORY_STACKSIZE,
	P4TUNE_SYS_RENAME_MAX,			// see fileiont.cc
	P4TUNE_SYS_RENAME_WAIT,			// see fileiont.cc
	P4TUNE_RPL_FORWARD_ALL,
	P4TUNE_RPL_PULL_POSITION,		// see userpull.cc
	P4TUNE_RPL_PULL_RELOAD,			// see userpull.cc
	P4TUNE_SSL_SECONDARY_SUITE,             // see netssltransport.cc
	P4TUNE_SSL_CLIENT_TIMEOUT,		// see netssltransport.cc
	P4TUNE_TRIGGERS_IO,			// see rhtrigger.cc

	P4TUNE_LAST

}  ;
