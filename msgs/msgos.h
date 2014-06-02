/*
 * Copyright 1995, 2000 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * msgos.h - definitions of operating system specific errors
 */

class MsgOs {

    public:

	static ErrorId Sys;
	static ErrorId Sys2;
	static ErrorId SysUn;
	static ErrorId SysUn2;
	static ErrorId Net;
	static ErrorId NetUn;

	static ErrorId TooMany;
	static ErrorId Deleted;
	static ErrorId NoSuch;
	static ErrorId ChmodBetrayal;

	static ErrorId EmptyFork;

	// Retired ErrorIds. We need to keep these so that clients 
	// built with newer apis can commnunicate with older servers 
	// still sending these.
} ;
