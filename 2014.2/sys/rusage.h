/*
 * Copyright 2001 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * Rusage -- CPU, etc usage measuring
 *
 * Rusage is a OS specific object that measures CPU time from its 
 * creation, for use in reporting on server speed.
 *
 * Classes:
 *	Rusage - CPU timer
 *
 * Public methods:
 *	Rusage::Start() - restart the timer
 *	Rusage::Message() - format an OS-specific resource usage message
 *	Rusage::Time() - return CPU time in ms
 */

class StrBuf;
struct UsageContext;

struct RusageTrack {
	int	trackable;
	long	utime;
	long	stime;
	long	io_in;
	long	io_out;
	long	net_in;
	long	net_out;
	long	maxrss;
	long	page_faults;
} ;

class Rusage {

    public:

    		Rusage();
		~Rusage();

	void	Start();
	void	Message( StrBuf &msg );
	void	GetTrack( int level, RusageTrack *track );
	int	Time();

    private:

	UsageContext	*tc;		// OS specific

} ;

