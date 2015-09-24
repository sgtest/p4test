/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * -vrpc=1 show connection
 * -vrpc=2 show calls to invoke and dispatches
 * -vrpc=3 show variable settings in send/receive buffers
 * -vrpc=5 show flow control details 
 */

extern void DumpError( Error &e, const char *func );

// RPC debugging levels
# define DEBUG_CONNECT	( p4debug.GetLevel( DT_RPC ) >= 1 )
# define DEBUG_FUNCTION	( p4debug.GetLevel( DT_RPC ) >= 2 )
# define DEBUG_VARS	( p4debug.GetLevel( DT_RPC ) >= 3 )
# define DEBUG_FLOW	( p4debug.GetLevel( DT_RPC ) >= 5 )

// Server debugging levels
# define DEBUG_SVR_ERROR	( p4debug.GetLevel( DT_SERVER ) >= 1 )
# define DEBUG_SVR_WARN		( p4debug.GetLevel( DT_SERVER ) >= 2 )
# define DEBUG_SVR_INFO		( p4debug.GetLevel( DT_SERVER ) >= 4 )

# define RPC_DBG_PRINT( level, msg ) \
	do \
	{ \
	    if( level ) \
	    { \
		p4debug.printf( "%s" msg "\n", RpcTypeNames[GetRpcType()] ); \
	    } \
	} while(0);

# define RPC_DBG_PRINTF( level, msg, ... ) \
	do \
	{ \
	    if( level ) \
	    { \
		p4debug.printf( "%s" msg "\n", RpcTypeNames[GetRpcType()], __VA_ARGS__ ); \
	    } \
	} while(0);

// Cluster debugging levels
# define DEBUG_CLUSTER_ERROR ( p4debug.GetLevel( DT_CLUSTER ) >= 1 )
# define DEBUG_CLUSTER_WARN  ( p4debug.GetLevel( DT_CLUSTER ) >= 2 )
# define DEBUG_CLUSTER_INFO  ( p4debug.GetLevel( DT_CLUSTER ) >= 3 )
# define DEBUG_CLUSTER_FUNC  ( p4debug.GetLevel( DT_CLUSTER ) >= 4 )
# define DEBUG_CLUSTER_FINE  ( p4debug.GetLevel( DT_CLUSTER ) >= 5 )

# define CLUSTER_ENTER() \
	do { \
	    if( DEBUG_CLUSTER_FUNC ) \
		p4debug.printf( "ENTER [%s:%d] %s.\n", __FILE__, __LINE__, __FUNCTION__); \
	} while(0);

# define CLUSTER_DUMP_ERROR( error ) \
	do { \
	    if( DEBUG_CLUSTER_ERROR ) \
		DumpError( error, __FUNCTION__ );\
	} while(0);
