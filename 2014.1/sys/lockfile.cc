/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */


# define NEED_FILE
# define NEED_FCNTL
# define NEED_FLOCK

# include <stdhdrs.h>
# include <lockfile.h>

# if defined( OS_SOLARIS ) && !defined( OS_SOLARIS25 )
# define flockL flock64
# define FL_SETLKW F_SETLKW64
# define FL_SETLK F_SETLK64
# define FL_GETLK F_GETLK64
# else
# define flockL flock
# define FL_SETLKW F_SETLKW
# define FL_SETLK F_SETLK
# define FL_GETLK F_GETLK
# endif

# if defined ( OS_BEOS )
#include <SupportDefs.h>
extern "C" status_t _klock_node_(int fd);
extern "C" status_t _kunlock_node_(int fd);
#endif

int
lockFile( int fd, int flag )
{

# if defined( OS_OS2 ) || defined( MAC_MWPEF ) || defined( OS_VMS62 )

	return 0;
# else 
# if defined ( OS_BEOS )

	switch( flag )
	{
	case LOCKF_UN:    return _kunlock_node_(fd); 
	case LOCKF_SH:    
	case LOCKF_SH_NB: 
	case LOCKF_EX:    
	case LOCKF_EX_NB: return _klock_node_(fd); 
	}

	return -1;

# else
# ifdef OS_NT

	return lockFileByHandle( (HANDLE)_get_osfhandle( fd ), flag );
# else
# if defined(LOCK_UN) && !defined(sgi) && !defined(OS_QNX) && !defined(OS_AIX)

	switch( flag )
	{
	case LOCKF_UN:    return flock(fd, LOCK_UN); break;
	case LOCKF_SH:    return flock(fd, LOCK_SH); break;
	case LOCKF_SH_NB: return flock(fd, LOCK_SH|LOCK_NB); break;
	case LOCKF_EX:    return flock(fd, LOCK_EX); break;
	case LOCKF_EX_NB: return flock(fd, LOCK_EX|LOCK_NB); break;
	}

	return -1;

# else 
# if defined(OS_SOLARIS10)

	// fcntl on Solaris-10 behaves differently to previous releases and 
	// does not gel well with our locking strategy.  The following code 
	// is an attempt to fake up the locking behaviour that we desire,  
	// while hopefully not leading to writer starvation.

	// Instead of locking the whole file for readers,  region locks of 
	// 1 byte are taken at the callers pid address which will allow for 
	// multiple readers in the system since potential writers now only 
	// block on the first reader's single byte region.  This requires 
	// the use of F_GETLK to acquire the first blocking reader.

	int pid = getpid();
	struct flockL f;

	if( flag != LOCKF_EX )
	{
	    f.l_whence = SEEK_SET;
	    f.l_pid = pid;

	    switch( flag )
	    {
	    case LOCKF_EX_NB: 
	        f.l_start = 0;   f.l_len = 0; f.l_type = F_WRLCK; 
	        return fcntl( fd, FL_SETLK, &f );
	    case LOCKF_SH_NB: 
	        f.l_start = pid; f.l_len = 1; f.l_type = F_RDLCK; 
	        return fcntl( fd, FL_SETLK, &f );
	    case LOCKF_SH:    
	        f.l_start = pid; f.l_len = 1; f.l_type = F_RDLCK;
	        return fcntl( fd, FL_SETLKW, &f );
	    case LOCKF_UN:    
	        f.l_start = 0;   f.l_len = 0; f.l_type = F_UNLCK; 
	        return fcntl( fd, FL_SETLKW, &f );
	    }
	}

	// Handle exclusive blocking lock

	int noOtherLocks = 0;

	for( ;; )
	{
	    f.l_type = F_WRLCK;
	    f.l_whence = SEEK_SET;
	    f.l_pid = pid;
	    f.l_start = 0;
	    f.l_len = 0;

	    if( noOtherLocks )
	        return fcntl( fd, FL_SETLKW, &f );

	    fcntl( fd, FL_GETLK, &f );

	    if( f.l_type == F_RDLCK )
	    {
	        // wait on this single byte

	        f.l_start = f.l_pid;
	        f.l_whence = SEEK_SET;
	        f.l_type = F_WRLCK;
	        f.l_len = 1;
	        f.l_pid = pid;

	        fcntl( fd, FL_SETLKW, &f );  // wait on locks
	        f.l_type = F_UNLCK;
	        fcntl( fd, FL_SETLKW, &f );  // release lock
	        continue;                    // check again
	    }

	    noOtherLocks++;
	}

# else

	int cmd;
	struct flockL f;
	f.l_start = 0;
	f.l_len = 0;
	f.l_pid = getpid();
	f.l_whence = 0;
	switch( flag )
	{
	case LOCKF_UN:    cmd = FL_SETLKW; f.l_type = F_UNLCK; break;
	case LOCKF_SH:    cmd = FL_SETLKW; f.l_type = F_RDLCK; break;
	case LOCKF_SH_NB: cmd = FL_SETLK;  f.l_type = F_RDLCK; break;
	case LOCKF_EX:    cmd = FL_SETLKW; f.l_type = F_WRLCK; break;
	case LOCKF_EX_NB: cmd = FL_SETLK;  f.l_type = F_WRLCK; break;
	default:	
	                  return -1;
	}

	return fcntl( fd, cmd, &f );

# endif
# endif /* LOCK_UN */
# endif /* OS_BEOS */
# endif /* OS_NT */
# endif /* MAC_MWPEF */

}

#ifdef OS_NT
int
lockFileByHandle(HANDLE h, int flag )
{

	/*
	 * NtFlock: flock for windows NT called by bt_fio.cc in dbopen2.
	 */

	OVERLAPPED	ol;
	DWORD		f;
	ol.Internal	= 0;
	ol.InternalHigh	= 0;
	ol.Offset	= 0xFFFFFFFF;
	ol.OffsetHigh	= 0xFFFFFFFF;
	ol.hEvent	= 0;

	switch( flag )
	{
	case LOCKF_UN:    return UnlockFileEx(h, 0, 1, 0, &ol) ? 0 : -1;

	case LOCKF_SH:    f = 0; break;
	case LOCKF_SH_NB: f = LOCKFILE_FAIL_IMMEDIATELY; break;
	case LOCKF_EX:    f = LOCKFILE_EXCLUSIVE_LOCK; break;
	case LOCKF_EX_NB: f = LOCKFILE_FAIL_IMMEDIATELY|LOCKFILE_EXCLUSIVE_LOCK;
	                  break;
	default:
	                  return -1;
	}

	return LockFileEx(h, f, 0, 1, 0, &ol) ? 0 : -1;
}
#endif
