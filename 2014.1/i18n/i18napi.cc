/*
 * Copyright 2001 Perforce Software.  All rights reserved.
 *
 */

/*
 * i18napi.cc - API support for charset conversion identifiers
 *
 */
#include <stdhdrs.h>
#include <strbuf.h>

#include "i18napi.h"

static const char *charsetname[] = {
    "none",
    "utf8",
    "iso8859-1",
    "utf16-nobom",
    "shiftjis",
    "eucjp",
    "winansi",
    "winoem",
    "macosroman",
    "iso8859-15",
    "iso8859-5",
    "koi8-r",
    "cp1251",
    "utf16le",
    "utf16be",
    "utf16le-bom",
    "utf16be-bom",
    "utf16",
    "utf8-bom",
    "utf32-nobom",
    "utf32le",
    "utf32be",
    "utf32le-bom",
    "utf32be-bom",
    "utf32",
    "utf8unchecked",
    "utf8unchecked-bom",
    "cp949",
    "cp936",
    "cp950",
    "cp850",
    "cp858",
    "cp1253",
    "cp737",
    "iso8859-7"
};

static unsigned int charsetcount = sizeof(charsetname) / sizeof(*charsetname);

unsigned int 
CharSetApi::CharSetCount()
{
    return charsetcount;
}

const char *
CharSetApi::Name(CharSetApi::CharSet c)
{
	unsigned int i = (unsigned int) c;
	if( i < charsetcount )
	    return charsetname[i];
	return NULL;
}

CharSetApi::CharSet
CharSetApi::Lookup(const char *s)
{
	StrRef st(s);

	for( unsigned int i = 0; i < charsetcount; ++i)
	    if( st == charsetname[i] )
		return (CharSet) i;
	return (CharSet) -1;
}

int
CharSetApi::isUnicode(CharSetApi::CharSet c)
{
	switch( c )
	{
	case UTF_8:
	case UTF_8_BOM:
	case UTF_8_UNCHECKED:
	case UTF_8_UNCHECKED_BOM:
	case UTF_16:
	case UTF_16_LE:
	case UTF_16_BE:
	case UTF_16_BOM:
	case UTF_16_LE_BOM:
	case UTF_16_BE_BOM:
	case UTF_32:
	case UTF_32_LE:
	case UTF_32_BE:
	case UTF_32_BOM:
	case UTF_32_LE_BOM:
	case UTF_32_BE_BOM:
	    return 1;
	}
	return 0;
}

int
CharSetApi::Granularity(CharSetApi::CharSet c)
{
	if( c == UTF_16 || c >= UTF_16_LE && c <= UTF_16_BOM )
	    return 2;
	if( c >= UTF_32 && c <= UTF_32_BOM )
	    return 4;
	if( (unsigned int)c < charsetcount )
	    return 1;
	return 0;
}
