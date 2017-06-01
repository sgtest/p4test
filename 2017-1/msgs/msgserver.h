/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msgserver.h - definitions of errors for server subsystem.
 */

class MsgServer {

    public:
	static ErrorId LbrCheckout;
	static ErrorId LbrDiff;
	static ErrorId LbrDigest;
	static ErrorId LbrFileSize;
	static ErrorId LbrCheckin;
	static ErrorId LbrMerge;
	static ErrorId LbrNoTrigger;
	static ErrorId BadRoot;
	static ErrorId BadIPAddr;
	static ErrorId GotUnlocked;
	static ErrorId GotLocked;
	static ErrorId NoInteg;
	static ErrorId GotUnresolved;
	static ErrorId CantOpen;
	static ErrorId NoDumpName;
	static ErrorId DumpNameIsADbName;
	static ErrorId NoCkptName;
	static ErrorId BadJnlFlag;
	static ErrorId BadExtraFlag;
	static ErrorId ExtraIDUsage;
	static ErrorId ServerIDAlreadySet;
	static ErrorId ServerID;
	static ErrorId ServerServicesType;
	static ErrorId ExtraServicesUsage;
	static ErrorId NoServerID;
	static ErrorId DomainIsLocal;
	static ErrorId MetaDumpFailed;
	static ErrorId SkippedJnls;
	static ErrorId Password982;
	static ErrorId BadPassword;
	static ErrorId MustSetPassword;
	static ErrorId WeakPassword;
	static ErrorId TicketOnly;
	static ErrorId Unicode;
	static ErrorId Unicode2;
	static ErrorId Unicode3;
	static ErrorId OperationFailed;
	static ErrorId OperationInfo;
	static ErrorId OperationDate;
	static ErrorId BadCommand;
	static ErrorId IllegalCommand;
	static ErrorId HandshakeFailed;
	static ErrorId ConnectBroken;
	static ErrorId ClientOpFailed;
	static ErrorId OnlyOneFilter;
	static ErrorId JournalFilterBad;
	static ErrorId Usage;
	static ErrorId OldDiffClient;
	static ErrorId OldReconcileClient;
	static ErrorId Jobs982Win;
	static ErrorId No973Wingui;
	static ErrorId JobsDashS;
	static ErrorId AddDelete;
	static ErrorId ZFlagsConflict;
	static ErrorId Password991;
	static ErrorId Password032;
	static ErrorId NoClearText;
	static ErrorId LoginExpired;
	static ErrorId PasswordExpired;
	static ErrorId LoginNotRequired;
	static ErrorId LoginPrintTicket;
	static ErrorId LoginUser;
	static ErrorId LoginGoodTill;
	static ErrorId LoginNoTicket;
	static ErrorId LoggingUserIn;
	static ErrorId LogoutUser;
	static ErrorId LoggedOut;
	static ErrorId Login032;
	static ErrorId Login042;
	static ErrorId Login072;
	static ErrorId SSOfailed;
	static ErrorId SSONoEnv;
	static ErrorId SSOInvalid;
	static ErrorId CantAuthenticate;
	static ErrorId CantChangeOther;
	static ErrorId CantResetPassword;
	static ErrorId NoSuchUser;
	static ErrorId BadPassword0;
	static ErrorId BadPassword1;
	static ErrorId PasswordTooShort2;
	static ErrorId PasswordTooLong;
	static ErrorId PasswordTooSimple;
	static ErrorId NoProxyAuth;
	static ErrorId MimAttack;
	static ErrorId NoMatchingServerSpec;
	static ErrorId NoSvcUserinSrvSpec;
	static ErrorId WrongSvcUserinSrvSpec;
	static ErrorId SvcUserNeedsAuth;
	static ErrorId NoSuppASflag;
	static ErrorId NoSuppVflag;
	static ErrorId SubmitFailed;
	static ErrorId SubmitShelvedFailed;
	static ErrorId SubmitIsShelved;
	static ErrorId SubmitNeedsShelved;
	static ErrorId CounterWarning;
	static ErrorId CouldntLock;
	static ErrorId LockedOnCommit;
	static ErrorId LockLocalError;
	static ErrorId LockGlobalError;
	static ErrorId NoGlobalLock;
	static ErrorId UnlockGlobalError;
	static ErrorId MergesPending;
	static ErrorId RetypeInvalidTempobj;
	static ErrorId ResolveOrRevert;
	static ErrorId CantRevertToPurged;
	static ErrorId NoSubmit;
	static ErrorId TriggerFailed;
	static ErrorId TriggerOutput;
	static ErrorId TriggersFailed;
	static ErrorId SubmitAborted;
	static ErrorId SubmitShelvedAborted;
	static ErrorId PopulateAborted;
	static ErrorId PopulateIsVirtual;
	static ErrorId IntegIsTask;
	static ErrorId NoDefaultSubmit;
	static ErrorId BadImport;
	static ErrorId BadTransfers;
	static ErrorId DigestMisMatch;
	static ErrorId SubmitDataChanged;
	static ErrorId SubmitTampered;
	static ErrorId DirsWild;
	static ErrorId HelpSeeRename;
	static ErrorId PurgeReport;
	static ErrorId SnapReport;
	static ErrorId PurgeWarning;
	static ErrorId PurgeOptGone;
	static ErrorId PurgeBadOption;
	static ErrorId LogCommand;
	static ErrorId LogEstimates;
	static ErrorId Unlicensed;
	static ErrorId TrackCommand;
	static ErrorId MaxLicensedFiles;
	static ErrorId MaxUnLicensedFiles;
	static ErrorId NoCentralLicense;
	static ErrorId RemoteNotAllowed;
	static ErrorId InsecureReplica;
	static ErrorId NoAuthFileCount;
	static ErrorId ClientBadHost;
	static ErrorId NoAuthServiceOnly;
	static ErrorId BadServicePack;
	static ErrorId Startup;
	static ErrorId Shutdown;
	static ErrorId Restarted;
	static ErrorId Restarting;
	static ErrorId CreatingDb;
	static ErrorId Quiescing;
	static ErrorId QuiesceFailed;
	static ErrorId ReDowngrade;
	static ErrorId Initialized;
	static ErrorId AlreadyInitialized;
	static ErrorId UserEmptyGroup;

	static ErrorId PropertyAdd;
	static ErrorId PropertyDelete;
	static ErrorId UseProperty;

	static ErrorId ConfigureSet;
	static ErrorId ConfigureUnSet;
	static ErrorId NotThisConfigVar;
	static ErrorId InvalidConfigValue;
	static ErrorId InvalidConfigScope;
	static ErrorId ConfigureNone;
	static ErrorId ConfigureServerNone;

	static ErrorId CounterDelete;
	static ErrorId CounterSet;
	static ErrorId KeyDelete;
	static ErrorId KeySet;
	static ErrorId CounterGet;
	static ErrorId CounterNotNumeric;
	static ErrorId KeyNotNumeric;
	static ErrorId CounterSetVerbose;
	static ErrorId KeySetVerbose;


	static ErrorId DescribeFixed;
	static ErrorId DescribeAffected;
	static ErrorId DescribeMovedFiles;
	static ErrorId DescribeDifferences;
	static ErrorId DescribeEmpty;
	static ErrorId DescribeShelved;

	static ErrorId Diff2Differ;
	static ErrorId Diff2BadArgs;

	static ErrorId GrepIllegalContext;
	static ErrorId GrepContextTooLarge;

	static ErrorId IndexOutput;

	static ErrorId InfoUser;
	static ErrorId InfoBadUser;
	static ErrorId InfoClient;
	static ErrorId InfoBadClient;
	static ErrorId InfoStream;
	static ErrorId InfoHost;
	static ErrorId InfoDirectory;
	static ErrorId InfoDiskSpace;
	static ErrorId InfoClientAddress;
	static ErrorId InfoPeerAddress;
	static ErrorId InfoServerAddress;
	static ErrorId InfoServerEncryption;
	static ErrorId InfoServerCertExpire;
	static ErrorId InfoServerRoot;
	static ErrorId InfoServerDate;
	static ErrorId InfoServerVersion;
	static ErrorId InfoServerLicense;
	static ErrorId InfoServerLicenseIp;
	static ErrorId InfoServerUptime;
	static ErrorId InfoUnknownClient;
	static ErrorId InfoClientRoot;
	static ErrorId InfoProxyVersion;
	static ErrorId InfoProxyAddress;
	static ErrorId InfoProxyEncryption;
	static ErrorId InfoProxyCertExpire;
	static ErrorId InfoAuthServer;
	static ErrorId InfoServerID;
	static ErrorId InfoServerServices;
	static ErrorId InfoServerReplica;
	static ErrorId InfoChangeServer;
	static ErrorId InfoCaseHandling;
	static ErrorId InfoMinClient;

	static ErrorId PasswordSave;
	static ErrorId PasswordDelete;
	static ErrorId PasswordNoChange;

	static ErrorId ShelveBegin;
	static ErrorId NoDefaultShelve;
	static ErrorId UnshelveNotOwner;
	static ErrorId ShelveUnsubmitted;
	static ErrorId ShelveAborted;
	static ErrorId NoShelve;
	static ErrorId NoShelveDelete;
	static ErrorId ShelveComplete;
	static ErrorId ShelvePromoted;
	static ErrorId UnshelveFileChanged;
	static ErrorId ShelveDelete;
	static ErrorId ShelveMaxSize;
	static ErrorId ShelveTriggersFailed;
	static ErrorId ShelveXOpen;
	static ErrorId ChangesShelved;

	static ErrorId SpecNotCorrect;
	static ErrorId ErrorInSpec;
	static ErrorId SpecArchiveWarning;
	static ErrorId SpecCheckTriggers;

	static ErrorId StreamBadType;
	static ErrorId StreamNotOwner;

	static ErrorId SubmitLocking;
	static ErrorId SubmitComplete;
	static ErrorId SubmitBegin;
	static ErrorId SubmitRenamed;
	static ErrorId SubmitNoParallelThreads;
	static ErrorId SubmitNoParallelTarget;

	static ErrorId PopulateComplete;

	static ErrorId ResolveOptAuto;
	static ErrorId ResolveOptHelp;
	static ErrorId ResolveOptMerge;
	static ErrorId ResolveOptSkip;
	static ErrorId ResolveOptTheirs;
	static ErrorId ResolveOptYours;
	static ErrorId ResolvePromptMerge;
	static ErrorId ResolvePromptTheirs;
	static ErrorId ResolvePromptType;
	static ErrorId ResolvePromptYours;
	static ErrorId ResolveUserError;
	static ErrorId ResolveUserPrompt;
	static ErrorId ResolveUserPrompt2;

	static ErrorId ResolvedFile;
	static ErrorId ResolvedSkipped;
	static ErrorId ResolveTampered;

	static ErrorId JobRebuilt;

	static ErrorId SearchResult;

	static ErrorId DiffCmp;
	static ErrorId DiffList;

	static ErrorId DeltaLine1;
	static ErrorId DeltaLine2;
	static ErrorId DeltaLine3;
	static ErrorId DeltaLine4;

	static ErrorId MonitorDisabled;
	static ErrorId MonitorBadId;
	static ErrorId MonitorNoLockinfo;
	static ErrorId TooManyCommands;

	static ErrorId IstatInvalid;

	static ErrorId UseAdmin;
	static ErrorId UseAdminCheckpoint;
	static ErrorId UseAdminJournal;
	static ErrorId UseAdminSpecDepot;
	static ErrorId UseAdminDBSigs;
	static ErrorId UseAdminImport;
	static ErrorId UseAdminResetPassword;
	static ErrorId UseAdminSetLdapUsers;
	static ErrorId UseAnnotate;
	static ErrorId UseArchive;
	static ErrorId UseBackup;	// added in nimble
	static ErrorId UseBranch;
	static ErrorId UseBrancho;
	static ErrorId UseBranchd;
	static ErrorId UseBranchi;
	static ErrorId UseCachepurge;
	static ErrorId UseChange;
	static ErrorId UseChanged;
	static ErrorId UseChangeo;
	static ErrorId UseChangei;
	static ErrorId UseChanges;
	static ErrorId UseChanget;
	static ErrorId UseChangeU;
	static ErrorId UseChangeUt;
	static ErrorId UseClean;
	static ErrorId UseClient;
	static ErrorId UseCliento;
	static ErrorId UseClientd;
	static ErrorId UseClienti;
	static ErrorId UseClientS;
	static ErrorId UseClients;
	static ErrorId UseCluster;
	static ErrorId UseConfigure;
	static ErrorId UseCopy;
	static ErrorId UseCopyb;
	static ErrorId UseCopyS;
	static ErrorId UseCounter;
	static ErrorId UseCounteri;
	static ErrorId UseCounters;
	static ErrorId UseCstat;
	static ErrorId UseDbpack;
	static ErrorId UseDbstat;
	static ErrorId UseDbverify;
	static ErrorId UseDepot;
	static ErrorId UseDepoto;
	static ErrorId UseDepotd;
	static ErrorId UseDepoti;
	static ErrorId UseDepots;
	static ErrorId UseDescribe;
	static ErrorId UseDiff;
	static ErrorId UseDiff2;
	static ErrorId UseDiff2b;
	static ErrorId UseDiff2n;
	static ErrorId UseDiff2S;
	static ErrorId UseDirs;
	static ErrorId UseDiskspace;
	static ErrorId UseBranches;
	static ErrorId UseLabels;
	static ErrorId UseDomainClients;
	static ErrorId UseDup;
	static ErrorId UseExport;
	static ErrorId UseFetch;
	static ErrorId UseFilelog;
	static ErrorId UseFiles;
	static ErrorId UseFix;
	static ErrorId UseFixes;
	static ErrorId UseFstat;
	static ErrorId UseGrep;
	static ErrorId UseGroup;
	static ErrorId UseGroupo;
	static ErrorId UseGroupd;
	static ErrorId UseGroupi;
	static ErrorId UseGroups;
	static ErrorId UseHave;
	static ErrorId UseHelp;
	static ErrorId UseIndex;
	static ErrorId UseInfo;
	static ErrorId UseInteg;
	static ErrorId UseIntegb;
	static ErrorId UseIntegS;
	static ErrorId UseInteged;
	static ErrorId UseInterChanges;
	static ErrorId UseInterChangesb;
	static ErrorId UseInterChangesS;
	static ErrorId UseIstat;
	static ErrorId UseJob;
	static ErrorId UseJobd;
	static ErrorId UseJobo;
	static ErrorId UseJobi;
	static ErrorId UseJobs;
	static ErrorId UseJobSpec;
	static ErrorId UseJournals;
	static ErrorId UseJournalcopy;
	static ErrorId UseJournalWait;
	static ErrorId UseDurableWait;
	static ErrorId UseKey;
	static ErrorId UseKeyi;
	static ErrorId UseKeys;
	static ErrorId UseLabel;
	static ErrorId UseLabelo;
	static ErrorId UseLabeld;
	static ErrorId UseLabeli;
	static ErrorId UseLabelSync;
	static ErrorId UseLdap;
	static ErrorId UseLdapd;
	static ErrorId UseLdapo;
	static ErrorId UseLdapi;
	static ErrorId UseLdapt;
	static ErrorId UseLdaps;
	static ErrorId UseLdapSync;
	static ErrorId UseLdapSyncG;
	static ErrorId UseLdapSyncU;
	static ErrorId UseLdapsa;
	static ErrorId UseLdapst;
	static ErrorId UseLicense;
	static ErrorId UseList;
	static ErrorId UseLock;
	static ErrorId UseLockg;
	static ErrorId UseLockstat;
	static ErrorId UseLogin;
	static ErrorId UseLoginr;
	static ErrorId UseLogout;
	static ErrorId UseLogger;
	static ErrorId UseLogAppend;
	static ErrorId UseLogParse;
	static ErrorId UseLogRotate;
	static ErrorId UseLogSchema;
	static ErrorId UseLogstat;
	static ErrorId UseLogtail;
	static ErrorId UseMain;
	static ErrorId UseMerge;
	static ErrorId UseMergeb;
	static ErrorId UseMergeS;
	static ErrorId UseMonitor;
	static ErrorId UseMonitorc;
	static ErrorId UseMonitorf;
	static ErrorId UseMonitors;
	static ErrorId UseMonitorP;
	static ErrorId UseMonitorR;
	static ErrorId UseOpen;
	static ErrorId UseOpen2;
	static ErrorId UseOpened;
	static ErrorId UseOpened2;
	static ErrorId UsePasswd;
	static ErrorId UsePopulate;
	static ErrorId UsePopulateb;
	static ErrorId UsePopulateS;
	static ErrorId UsePrint;
	static ErrorId UseProtect;
	static ErrorId UseProtects;
	static ErrorId UseProtectsM;
	static ErrorId UsePrune;
	static ErrorId UsePull;
	static ErrorId UsePurge;
	static ErrorId UsePush;
	static ErrorId UseRelease;
	static ErrorId UseReload;
	static ErrorId UseReconcile;
	static ErrorId UseRecFlush;
	static ErrorId UseRemote;
	static ErrorId UseRemoteo;
	static ErrorId UseRemoted;
	static ErrorId UseRemotei;
	static ErrorId UseRemotes;
	static ErrorId UseRenameUser;
	static ErrorId UseReopen;
	static ErrorId UseResolve;
	static ErrorId UseResolved;
	static ErrorId UseRestore;
	static ErrorId UseResubmit;
	static ErrorId UseRetype;
	static ErrorId UseReview;
	static ErrorId UseReviews;
	static ErrorId UseSearch;
	static ErrorId UseServer;
	static ErrorId UseServero;
	static ErrorId UseServerd;
	static ErrorId UseServeri;
	static ErrorId UseServerc;
	static ErrorId UseServerid;
	static ErrorId UseServers;
	static ErrorId UseSizes;
	static ErrorId UseShelve;
	static ErrorId UseShelvec;
	static ErrorId UseShelvei;
	static ErrorId UseShelvem;
	static ErrorId UseShelver;
	static ErrorId UseShelveNoOpts;
	static ErrorId UseSnap;
	static ErrorId UseSpec;
	static ErrorId UseStatus;
	static ErrorId UseStatusFlush;
	static ErrorId UseStream;
	static ErrorId UseStreamc;
	static ErrorId UseStreamd;
	static ErrorId UseStreami;
	static ErrorId UseStreamo;
	static ErrorId UseStreamEdit;
	static ErrorId UseStreamResolve;
	static ErrorId UseStreamRevert;
	static ErrorId UseStreams;
	static ErrorId UseSubmit;
	static ErrorId UseSubmitc;
	static ErrorId UseSubmitd;
	static ErrorId UseSubmite;
	static ErrorId UseSwitch;
	static ErrorId UseSwitch2;
	static ErrorId UseSync;
	static ErrorId UseSyncp;
	static ErrorId UseSyncs;
	static ErrorId UseTag;
	static ErrorId UseTrait;
	static ErrorId UseTraiti;
	static ErrorId UseTransmit;
	static ErrorId UseTriggers;
	static ErrorId UseTypeMap;
	static ErrorId UseUndo;
	static ErrorId UseUnload;
	static ErrorId UseUnlock;
	static ErrorId UseUnshelve;
	static ErrorId UseUnsubmit;
	static ErrorId UseUnzip;
	static ErrorId UseUser;
	static ErrorId UseUsero;
	static ErrorId UseUserd;
	static ErrorId UseUseri;
	static ErrorId UseUsers;
	static ErrorId UseVerify;
	static ErrorId UseWhere;
	static ErrorId UseZip;
	static ErrorId NotAsService;
	static ErrorId UseProxy;
	static ErrorId UseProxyInfo;
	static ErrorId UsePing;
	static ErrorId UseMove;
	static ErrorId UseMover;

	static ErrorId ServerTooOld;
	static ErrorId ProxyChain;
	static ErrorId ProxyDelivered;
	static ErrorId RmtAuthFailed;
	static ErrorId ServiceNotProvided;
	static ErrorId IncompatibleServers;
	static ErrorId ReplicaRestricted;
	static ErrorId RequiresJournaling;
	static ErrorId ReplicaNoUpgrade;
	static ErrorId ReplicaBadOption;
	static ErrorId ReplicaWrongClient;
	static ErrorId ReplicaWrongLabel;
	static ErrorId ReplicaWrongServer;
	static ErrorId NotACommitServer;
	static ErrorId UnknownReplicationMode;
	static ErrorId MissingReplicationMode;
	static ErrorId UnknownReplicationTarget;
	static ErrorId P4TARGETWasSet;
	static ErrorId P4TARGETWasNotSet;
	static ErrorId CommitServerOverrides;
	static ErrorId ReplicaXferFailed;
	static ErrorId BFNoOverwriteLocal;
	static ErrorId BadPCache;
	static ErrorId ProxyNoRemote;
	static ErrorId ProxyUpdateFail;
	static ErrorId RemoteInvalidCmd;
	static ErrorId InvalidNesting;
	static ErrorId ClientTooOld;
	static ErrorId NoTicketSupport;
	static ErrorId CommandCancelled;
	static ErrorId CommandCancelledByClient;
	static ErrorId AdminNoSpecDepot;
	static ErrorId AdminNoSuchSpec;
	static ErrorId AdminPasswordNoSuchUser;
	static ErrorId AdminPasswordNoPasswords;
	static ErrorId AdminLdapNoneSet;
	static ErrorId ImportReport;
	static ErrorId AdminReplicaCkp;
	static ErrorId NoReplicaJnlControl;
	static ErrorId AdminNothingLocked;
	static ErrorId AdminNothingLogged;
	static ErrorId NoUserLogs;
	static ErrorId AdminSizeData;
	static ErrorId Move091;
	static ErrorId Move101;
	static ErrorId MoveRejected;
	static ErrorId CommandDisabled;
	static ErrorId ActionResolve111;
	static ErrorId BadJournalNum;
	static ErrorId BadCheckpointNum;
	static ErrorId JournalorCheckpointRequired;
	static ErrorId CurJournalButNotJournaling;
	static ErrorId LogtailNoLog;
	static ErrorId CachepurgeNotReplica;
	static ErrorId CachepurgeBadMode;
	static ErrorId ReplicaCacheConfig;
	static ErrorId PullNotReplica;
	static ErrorId CommandRunning;
	static ErrorId PullOnDemand;
	static ErrorId NoUpdateForwarding;
	static ErrorId JournalCopyBadJnlState;
	static ErrorId JournalCopyAppendFailed;
	static ErrorId JournalStateVsSize;
	static ErrorId PullTransferSummary;
	static ErrorId PullTransferChange;
	static ErrorId PullJournalSummary;
	static ErrorId PullJournalDate;
	static ErrorId PullInvalidPos;
	static ErrorId ReplicaServerTime;
	static ErrorId CacheAlreadyPurged;
	static ErrorId JournalCounterMismatch;

	static ErrorId TransferCancelled;
	static ErrorId NoSuchTransfer;
	static ErrorId TransferNotReplica;
	static ErrorId UsersCRNotReplica;
	static ErrorId UsersCRNotBoth;
	static ErrorId TZMismatch;
	static ErrorId NeedFilePath;
	static ErrorId NoSuchField;
	static ErrorId EmptyTypeList;
	static ErrorId NotGraphReady;
	static ErrorId GraphDisabled;
	static ErrorId NotStreamReady;
	static ErrorId NotStreamOwner;
	static ErrorId VersionedStream;

	static ErrorId BadSortOption;
	static ErrorId TooManySortTraits;

	static ErrorId InvalidStartupCommand;
	static ErrorId StartupCommandError;
	static ErrorId InvalidServerChain;
	static ErrorId CommunicationLoop;

        static ErrorId InfoPingTime;
        static ErrorId InfoPingTimeB;
        static ErrorId InfoPingCount;
        static ErrorId InfoPingCountB;
        static ErrorId ErrorPingProtocol;
        static ErrorId ErrorPingParam;

	static ErrorId NoCustomSpec;

	static ErrorId CopyWrongDirection;
	static ErrorId CopyDoNothing;
	static ErrorId CopyNeedsMergeFirst;
	static ErrorId MergeWrongDirection;
	static ErrorId NoReparentingTask;

	static ErrorId BoundClientExists;
	static ErrorId BoundClientServerID;

	static ErrorId UnloadDepotMissing;
	static ErrorId UnloadOtherUser;
	static ErrorId CantUnloadLocked;
	static ErrorId CantUnloadReadOnly;
	static ErrorId TemporaryLabelInfo;
	static ErrorId TargetAccessFailed;
	static ErrorId ChangeNotSubmitted;
	static ErrorId ChangeNotLocal;
	static ErrorId NotInCluster;
	static ErrorId NotClusterStandby;
	static ErrorId NotClusterMaster;
	static ErrorId OpNotAllowedOnRole;

	static ErrorId NotWorkspaceSvr;
	static ErrorId ClusterCannotWriteJournal;
	static ErrorId ClusterNotAllowed;
	static ErrorId ZookeeperInitError;
	static ErrorId MonitorOffInCluster;
	static ErrorId CommandUnsupported;
	static ErrorId MaitModeRestricted;

	static ErrorId NotDistributed;
	static ErrorId NotEdge;
	static ErrorId PortMissing;
	static ErrorId NoteHookError;
	static ErrorId NewUserExists;
	static ErrorId NewUserHasChanges;
	static ErrorId NewUserHasDomains;
	static ErrorId DontRenameSelf;
	static ErrorId UserRenamed;

	static ErrorId AttrNoPropEdge;

	static ErrorId BadTriggerOutput;

	static ErrorId ReopenNotOwnerCL;

	static ErrorId LdapAuthSuccess;
	static ErrorId LdapAuthSuccessD;
	static ErrorId LdapAuthFailed;
	static ErrorId LdapAuthFailedR;
	static ErrorId LdapAuthFailedSasl;
	static ErrorId LdapAuthFailedD;
	static ErrorId LdapNoSupport;
	static ErrorId LdapAuthNone;
	static ErrorId LdapNoPassChange;
	static ErrorId LdapNoEnabled;
	static ErrorId LdapNoConfig;
	static ErrorId LdapErrorInit;
	static ErrorId LdapErrorInitTls;
	static ErrorId LdapErrorSetOpt;
	static ErrorId LdapSearchFailed;
	static ErrorId LdapTestConfig;
	static ErrorId LdapTestConfigAuthz;
	static ErrorId LdapNoEmptyPasswd;
	static ErrorId LdapUserNotFound;
	static ErrorId LdapGroupNotFound;
	static ErrorId LdapMissingCAFile;
	static ErrorId LdapReadCAErr0;
	static ErrorId LdapReadCAErr1;
	static ErrorId LdapReadCAErr2;
	static ErrorId LdapReadCAErr3;
	static ErrorId LdapSyncGrpUserAdd;
	static ErrorId LdapSyncGrpUserDel;
	static ErrorId LdapSyncGrpNoChange;
	static ErrorId LdapSyncNoLdapConf;
	static ErrorId LdapSyncGrpBadConf;
	static ErrorId LdapSyncGrpNotFound;
	static ErrorId LdapMustBeEnabled;
	static ErrorId LdapNoSearchConfig;
	static ErrorId LdapNoAttrConfig;
	static ErrorId LdapNoAttrsFound;
	static ErrorId LdapSyncUserAdd;
	static ErrorId LdapSyncUserUpdate;
	static ErrorId LdapSyncUserDel;
	static ErrorId LdapSyncUserNoChange;

	static ErrorId LicenceInputOnly;

	static ErrorId SwitchBranchData;
	static ErrorId SwitchBranchDataMatch;
	static ErrorId SwitchFilesOpen;
	static ErrorId SwitchBranchExists;
	static ErrorId SwitchNeedsStreamClient;
	static ErrorId SwitchNeedsInit;
	static ErrorId SwitchNotEmpty;
	static ErrorId SwitchFilesUnresolved;
	static ErrorId SwitchAtChange;

	static ErrorId PushTriggersFailed;
	static ErrorId PushClientExists;
	static ErrorId PushPerformance;
	static ErrorId PushCounters;
	static ErrorId ResubmitPrompt;
	static ErrorId ConflictingChange;
	static ErrorId CannotResubmitOpened;
	static ErrorId CannotResubmitNotUnshelved;
	static ErrorId CannotResubmitChange;
	static ErrorId ResolveUnsubmitted;
	static ErrorId SubmitUnsubmitted;
	static ErrorId AddCollision;
	static ErrorId AddCollision2;
	static ErrorId RemoteMappingInvalid;
	static ErrorId RemoteNoTarget;
	static ErrorId UnsubmittedChanges;
	static ErrorId CurrentUnsubmitted;
	static ErrorId InvalidResubmitChoice;
	static ErrorId ResubmitHalted;
	static ErrorId RemoteClientExists;
	static ErrorId FetchPushPreview;
	static ErrorId PushSucceeded;
	static ErrorId FetchSucceeded;
	static ErrorId DVCSNotConfigured;
	static ErrorId AttrNoDVCS;
	static ErrorId UseFetchInstead;
	static ErrorId PushHadConflict;
	static ErrorId FetchHadConflict;
	static ErrorId PushDidNothing;
	static ErrorId FetchDidNothing;
	static ErrorId FetchCopiedArchives;
	static ErrorId FetchDidUnsubmit;
	static ErrorId FetchDidTangent;
	static ErrorId FetchNeedsResubmit;
	static ErrorId PushCryptoError1;
	static ErrorId FetchCryptoError1;
	static ErrorId CannotFetchOpened;
	static ErrorId ResolveThenResume;
	static ErrorId ReviewThenResume;
	static ErrorId BadLocation;
	static ErrorId JournalRotationFail;
	static ErrorId JournalFalseEOF;
	static ErrorId AddressMismatch;
	static ErrorId ClientRejected;
	static ErrorId OpenReadOnly;
	static ErrorId ClientTooOldToSkipXfer;
	static ErrorId PartnerServerTooOld;
	static ErrorId OpenNotDVCSLocal;
	static ErrorId ServerIDIdentity;
	static ErrorId NoTriggerDir;
	static ErrorId NoPullTrigger;

	//nimble
	static ErrorId BackupOff;		// added in nimble
	static ErrorId BackupExiting;	// added in nimble
	static ErrorId BackupBadSvr;		// added in nimble

	// Retired ErrorIds. We need to keep these so that clients 
	// built with newer apis can communicate with older servers
	// still sending these.

	static ErrorId UseAdminCopyin; // DEPRECATED
	static ErrorId UseAdminCopyout; // DEPRECATED
	static ErrorId UseTunables; // DEPRECATED
	static ErrorId UseDomains; // Used in 2009.1 through 2010.2
	static ErrorId PullTransferPending; // Was used in 2010.2 BETA only.
	static ErrorId PasswordTooShort; // DEPRECATED
	static ErrorId SubmitShelvedHasTask; // used in 2013.1 only
	static ErrorId NotClusterService; // Not documented in any release but in 13.2-14.1
	static ErrorId PushCryptoError; // DEPRECATED used in 15.1-2
	static ErrorId FetchCryptoError; // DEPRECATED used in 15.1-2
	static ErrorId PullCommandRunning; // DEPRECATED - use CommandRunning instead
	static ErrorId JcopyCommandRunning; // DEPRECATED - use CommandRunning instead
	static ErrorId NoValidLicense;
};
