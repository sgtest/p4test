/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

#ifdef OS_NT
extern "C" int lockFileByHandle( HANDLE h, int flag );
#endif
extern "C" int lockFile( int fd, int flag );

enum lockFileFlags {

	LOCKF_UN = 0,		// unlock
	LOCKF_SH = 1,		// shared
	LOCKF_EX = 2,		// exclusive
	LOCKF_SH_NB = 3,	// shared (no block)
	LOCKF_EX_NB = 4		// exclusive (no block)

} ;

