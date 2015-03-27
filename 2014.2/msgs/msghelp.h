/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msghelp.h - definitions of errors for help subsystem.
 */

class MsgHelp {

    public:

	static ErrorId NoHelp;
	static ErrorId HelpPerforce;
	static ErrorId HelpUsage;
	static ErrorId HelpSimple;
	static ErrorId HelpCommands;
	static ErrorId HelpUndoc;
	static ErrorId HelpEnvironment;
	static ErrorId HelpFiletypes;
	static ErrorId HelpJobView;
	static ErrorId HelpRevisions;
	static ErrorId HelpViews;
	static ErrorId HelpMaxResults;
	static ErrorId HelpCachepurge;
	static ErrorId HelpCharset;
	static ErrorId HelpCommandments;
	static ErrorId HelpCredits;
	static ErrorId HelpAdd;
	static ErrorId HelpAnnotate;
	static ErrorId HelpAdmin;
	static ErrorId HelpAdministration;
	static ErrorId HelpArchive;
	static ErrorId HelpAttribute;
	static ErrorId HelpBranch;
	static ErrorId HelpBranches;
	static ErrorId HelpBroker;
	static ErrorId HelpBuildserver;
	static ErrorId HelpChange;
	static ErrorId HelpChanges;
	static ErrorId HelpClient;
	static ErrorId HelpClients;
	static ErrorId HelpCluster;
	static ErrorId HelpConfigure;
	static ErrorId HelpConfigurables;
	static ErrorId HelpCopy;
	static ErrorId HelpCopyshelf;
	static ErrorId HelpCounter;
	static ErrorId HelpCounters;
	static ErrorId HelpCstat;
	static ErrorId HelpDbpack;
	static ErrorId HelpDbschema;
	static ErrorId HelpDbstat;
	static ErrorId HelpDbverify;
	static ErrorId HelpDepot;
	static ErrorId HelpDepots;
	static ErrorId HelpDelete;
	static ErrorId HelpDescribe;
	static ErrorId HelpDiff;
	static ErrorId HelpDiff2;
	static ErrorId HelpDirs;
	static ErrorId HelpDiskspace;
	static ErrorId HelpDuplicate;
	static ErrorId HelpEdit;
	static ErrorId HelpExport;
	static ErrorId HelpDistributed;
	static ErrorId HelpFiles;
	static ErrorId HelpFilelog;
	static ErrorId HelpFix;
	static ErrorId HelpFixes;
	static ErrorId HelpForwardingreplica;
	static ErrorId HelpFstat;
	static ErrorId HelpGrep;
	static ErrorId HelpGroup;
	static ErrorId HelpGroups;
	static ErrorId HelpHave;
	static ErrorId HelpHelp;
	static ErrorId HelpIndex;
	static ErrorId HelpInfo;
	static ErrorId HelpInteg;
	static ErrorId HelpInteg3;
	static ErrorId HelpInteged;
	static ErrorId HelpInterchanges;
	static ErrorId HelpIstat;
	static ErrorId HelpJob;
	static ErrorId HelpJobs;
	static ErrorId HelpJobSpec;
	static ErrorId HelpJournalcopy;
	static ErrorId HelpJournaldbchecksums;
	static ErrorId HelpJournals;
	static ErrorId HelpKey;
	static ErrorId HelpKeys;
	static ErrorId HelpLabel;
	static ErrorId HelpLabels;
	static ErrorId HelpLabelsync;
	static ErrorId HelpLegal;
	static ErrorId HelpLdap;
	static ErrorId HelpLdaps;
	static ErrorId HelpLicense;
	static ErrorId HelpList;
	static ErrorId HelpLock;
	static ErrorId HelpLockstat;
	static ErrorId HelpLogappend;
	static ErrorId HelpLogger;
	static ErrorId HelpLogin;
	static ErrorId HelpLogout;
	static ErrorId HelpLogparse;
	static ErrorId HelpLogrotate;
	static ErrorId HelpLogschema;
	static ErrorId HelpLogstat;
	static ErrorId HelpLogtail;
	static ErrorId HelpMerge;
	static ErrorId HelpMerge3;
	static ErrorId HelpMonitor;
	static ErrorId HelpMove;
	static ErrorId HelpNetworkAddress;
	static ErrorId HelpObliterate;
	static ErrorId HelpOpened;
	static ErrorId HelpPing;
	static ErrorId HelpPasswd;
	static ErrorId HelpPopulate;
	static ErrorId HelpPrint;
	static ErrorId HelpProperty;
	static ErrorId HelpProtect;
	static ErrorId HelpProtects;
	static ErrorId HelpProxy;
	static ErrorId HelpPrune;
	static ErrorId HelpPull;
	static ErrorId HelpReload;
	static ErrorId HelpRename;
	static ErrorId HelpRenameUser;
	static ErrorId HelpReconcile;
	static ErrorId HelpReopen;
	static ErrorId HelpReplication;
	static ErrorId HelpResolve;
	static ErrorId HelpResolved;
	static ErrorId HelpRestore;
	static ErrorId HelpRetype;
	static ErrorId HelpRevert;
	static ErrorId HelpReview;
	static ErrorId HelpReviews;
	static ErrorId HelpTunables;
	static ErrorId HelpSearch;
	static ErrorId HelpServer;
	static ErrorId HelpServerid;
	static ErrorId HelpServers;
	static ErrorId HelpSet;
	static ErrorId HelpShelve;
	static ErrorId HelpSizes;
	static ErrorId HelpSnap;
	static ErrorId HelpSpec;
	static ErrorId HelpStream;
	static ErrorId HelpStreamintro;
	static ErrorId HelpStreams;
	static ErrorId HelpSubmit;
	static ErrorId HelpSync;
	static ErrorId HelpTag;
	static ErrorId HelpTickets;
	static ErrorId HelpTrigger;
	static ErrorId HelpTriggers;
	static ErrorId HelpTrust;
	static ErrorId HelpTypeMap;
	static ErrorId HelpUnload;
	static ErrorId HelpUnlock;
	static ErrorId HelpUnshelve;
	static ErrorId HelpUser;
	static ErrorId HelpUsers;
	static ErrorId HelpVerify;
	static ErrorId HelpWhere;
	static ErrorId HelpReplicate;

	static ErrorId ResolveUserHelp;

	// Retired ErrorIds. We need to keep these so that clients 
	// built with newer apis can commnunicate with older servers 
	// still sending these.

	static ErrorId HelpBrowse; // DEPRECATED 2013.1 removed ZeroConf
	static ErrorId HelpZeroConf; // DEPRECATED 2013.1 removed ZeroConf
};
