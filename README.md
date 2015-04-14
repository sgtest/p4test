# Perforce Open Source Command Line and API

This is the source code for the Perforce command line and API. See LICENSE
for all licensing information.


## Dependencies
Outside of a C/C++ compiler you will need Jam (Just Another Make), a build system
written by Christopher Seiwald. A source bundle can be found here: 

    https://swarm.workshop.perforce.com/files/public/jam/jam-2.6.rc1.zip


## To build the Perforce command line interface
From the root of the p4 source run:

    jam p4

Jam may ask you to specify an OS version if it cannot determine it. For example
on OS X running 'jam p4' will return:

    Set OSVER to 104, 105, or 106 for MACOSX 

To set any options in Jam use the '-s' flag. For the example above you would run:

    jam -sOSVER=106 p4

To build on Cygwin run:

    jam -sOS=CYGWIN

To build on Windows you will need to disable use of Smartheap:

    jam -sSMARTHEAP=0 p4

Builds will be placed in a directory called 'p4-bin/bin.[OS][OSVER]' at the same level as your p4 directory.


## Building with SSL server support
If you wish to build p4 with support for SSL servers you will need to add '-sSSL=yes'
to the Jam call and place builds of libssl and libcrypto from OpenSSL 1.0.1g
into the 'p4-bin/lib.[OS][OSVER]' where 'p4-bin' is the same directory mentioned above.


## To build the Perforce API
From the root of the p4 source run:

    jam -sPRODUCTION=1 p4api.tar

As with building p4, Jam may ask you to specify an OS version.

