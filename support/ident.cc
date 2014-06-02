/*
 * Copyright 1995, 2002 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <stdhdrs.h>

# include <strbuf.h>

# include "ident.h"

# if defined( USE_SSL ) && !defined( OPENSSL_VERSION_TEXT )
extern "C"
{ // OpenSSL
# include "openssl/opensslv.h"
}
# endif //USE_SSL

void
Ident::GetMessage( StrBuf *s, int isServer )
{
    s->Clear();

    *s << "Perforce - The Fast Software Configuration Management System.\n";
    *s << "Copyright 1995-"ID_Y" Perforce Software.  All rights reserved.\n";

# if defined( OS_NT ) || defined( OS_LINUX )
    // Add credit for Smartheap memory manager
    if( isServer )
	*s << "Portions copyright 1991-2005 Compuware Corporation.\n";
# endif

# ifdef USE_SSL
    *s << "This product includes software developed by the OpenSSL Project\n";
    *s << "for use in the OpenSSL Toolkit (http://www.openssl.org/)\n";
    *s << "See 'p4 help legal' for full OpenSSL license information\n";
    *s << "Version of OpenSSL Libraries: " << OPENSSL_VERSION_TEXT << "\n";
# endif //USE_SSL

    *s << "Rev. " << GetIdent() << " (" << GetDate() << ").\n";
}
