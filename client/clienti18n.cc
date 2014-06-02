/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

# include <stdhdrs.h>

# include <debug.h>
# include <strbuf.h>
# include <strdict.h>
# include <strtable.h>
# include <error.h>
# include <i18napi.h>
# include <charset.h>
# include <charcvt.h>
# include <transdict.h>
# include <options.h>
# include <handler.h>
# include <rpc.h>
# include <ident.h>
# include <enviro.h>

# include <filesys.h>

# include <msgclient.h>
# include <p4tags.h>

# include "clientuser.h"
# include "clientservice.h"
# include "clientmerge.h"
# include "client.h"
# include "regexp.h"

void
Client::SetTrans( int output,
		  int content,
		  int fnames,
		  int dialog )
{
	CharSetCvt *converter = NULL;

	if (dialog == -2)
	    dialog = output;
	if (content == -2)
	    content = output;
	if (fnames == -2)
	    fnames = content;

	// if we were already in unicode mode, take that down
	if( is_unicode )
	    CleanupTrans();

	// if all args are 0, disable translation
	if( !( output | content | fnames | dialog ) )
	{
	    content_charset = 0;
	    GlobalCharSet::Set( 0 );
	    return;
	}

	// we are in unicode mode now...
	is_unicode = 1;

	enviro->SetCharSet(output);
	content_charset = content;
	output_charset = output;
	GlobalCharSet::Set(fnames);
	// our concept of current directory could change at this point
	cwd = "";
	enviro->Config( GetCwd() );

	if (output != 0)
	{
	    converter = CharSetCvt::FindCvt( CharSetCvt::UTF_8,
				     (CharSetCvt::CharSet)output );
	    if (converter)
	    {
                    // TransDict will delete the converter
		translated = new TransDict( this, converter );
                if (fnames == output)
                    transfname = translated;
	    }
	}
	if ( fnames != 0 && fnames != output)
	{
	    converter = CharSetCvt::FindCvt( CharSetCvt::UTF_8,
				     (CharSetCvt::CharSet)fnames );
	    if (converter)
	    {
                    // TransDict will delete the converter
		transfname = new TransDict( this, converter );
 	    }
	}
	if ( dialog != 0 )
	{
	    fromTransDialog = CharSetCvt::FindCvt( CharSetCvt::UTF_8,
					 (CharSetCvt::CharSet)dialog );
	    if (fromTransDialog)
		toTransDialog = fromTransDialog->ReverseCvt();
	}
}

void
Client::CleanupTrans()
{
	if (transfname != this && transfname != translated)
	    delete transfname;
	if (translated != this)
	    delete translated;

	translated = this;
	transfname = this;

        delete fromTransDialog;
	delete toTransDialog;
	fromTransDialog = toTransDialog = NULL;

	is_unicode = 0;
	content_charset = 0;
	output_charset = 0;
 	enviro->SetCharSet( 0 );
}

int Client::ContentCharset()
{
	// Content charset is overridden by server-provided charset if present

	StrPtr *charset = GetVar( P4Tag::v_charset );

	return charset ? charset->Atoi() : content_charset;
}

#if defined ( OS_MACOSX )

int
Client::GuessCharset()
{
        return CharSetApi::UTF_8;
}

#elif defined ( OS_NT )

#include <windows.h>


// these next two routines attempt to determine if the app is a console app
bool
ReadBytes(HANDLE hFile,
          LPVOID buffer,
          DWORD  size)
{
    DWORD bytes;

    if (!ReadFile(hFile,
                  buffer,
                  size,
                  &bytes,
                  NULL))
    {
        return false;
    }
    else if (size != bytes)
    {
        return false;
    }
    return true;
}

// http://www.devx.com/tips/Tip/33584
static bool
UseOEMCodePage()
{
        DWORD nameLength;
        char  nameBuf[256];
        HANDLE hImage;

        DWORD  bytes;
        DWORD  iSection;
        DWORD  SectionOffset;
        DWORD  CoffHeaderOffset;
        DWORD  MoreDosHeader[16];

        ULONG  ntSignature;

        IMAGE_DOS_HEADER      image_dos_header;
        IMAGE_FILE_HEADER     image_file_header;
        IMAGE_OPTIONAL_HEADER image_optional_header;
        IMAGE_SECTION_HEADER  image_section_header;

        nameLength = GetModuleFileName(NULL, nameBuf, 256);
        if (! nameLength || nameLength >= 256)
            return true;
        /*
         *  Open the reference file.
         */ 
         hImage = CreateFile(nameBuf,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

        if (INVALID_HANDLE_VALUE == hImage)
            return true;
        /*
         *  Read the MS-DOS image header.
         */ 
        if (! ReadBytes(hImage,
                &image_dos_header,
                sizeof(IMAGE_DOS_HEADER)))
            return true;

        if (IMAGE_DOS_SIGNATURE != image_dos_header.e_magic)
            return true;

        /*
        *  Read more MS-DOS header.       */ 
        if (! ReadBytes(hImage,
                MoreDosHeader,
                sizeof(MoreDosHeader)))
            return true;

        /*
         *  Get actual COFF header.
         */ 
        CoffHeaderOffset = SetFilePointer(hImage, image_dos_header.e_lfanew,
                                          NULL,
                                          FILE_BEGIN);
        if (CoffHeaderOffset == 0xFFFFFFFF)
            return true;

        CoffHeaderOffset += sizeof(ULONG);

        if (! ReadBytes (hImage, &ntSignature, sizeof(ULONG)))
            return true;

        if (IMAGE_NT_SIGNATURE != ntSignature)
            return true;

        SectionOffset = CoffHeaderOffset + IMAGE_SIZEOF_FILE_HEADER +
                    sizeof(image_optional_header);

        if (! ReadBytes(hImage,
              &image_file_header,
              IMAGE_SIZEOF_FILE_HEADER))
            return true;

        /*
         *  Read optional header.
         */ 
        if (!ReadBytes(hImage,
              &image_optional_header,
              sizeof(image_optional_header)))
            return true;

        if (image_optional_header.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_GUI)
            return false;
        return true;
}

int
Client::GuessCharset()
{
        UINT codePage;
        if (UseOEMCodePage()) // for console apps
            codePage = GetOEMCP();
        else
            codePage = GetACP();
        
        switch (codePage)
        {
            case 437:   return CharSetApi::WIN_US_OEM;
//            case 737:   return CharSetApi::CP737;	// problems
            case 850:   return CharSetApi::CP850;
            case 858:   return CharSetApi::CP858;
            case 932:   return CharSetApi::SHIFTJIS;
            case 936:   return CharSetApi::CP936;
            case 949:   return CharSetApi::CP949;
            case 950:   return CharSetApi::CP950;
            case 1200:  return CharSetApi::UTF_16_LE_BOM;
            case 1201:  return CharSetApi::UTF_16_BE_BOM;
            case 1251:  return CharSetApi::WIN_CP_1251;
            case 1252:  return CharSetApi::WIN_US_ANSI;
            case 1253:  return CharSetApi::CP1253;
            case 10000: return CharSetApi::MACOS_ROMAN;
            case 12000: return CharSetApi::UTF_32_LE_BOM;
            case 12001: return CharSetApi::UTF_32_BE_BOM;
            case 20866: return CharSetApi::KOI8_R;
            case 20932: return CharSetApi::EUCJP;
            case 28591: return CharSetApi::ISO8859_1;
            case 28595: return CharSetApi::ISO8859_5;
            case 28605: return CharSetApi::ISO8859_15;
            case 65001: return CharSetApi::UTF_8;
            default:    return 0;
        }
}


#elif ( defined ( OS_LINUX )   || \
        defined ( OS_FREEBSD ) || \
        defined ( OS_SOLARIS ) || \
        defined ( OS_NETBSD )  )


int
Client::GuessCharset()
{
        const char *setInEnv = enviro->Get( "LANG" );

        if( !setInEnv )
            return 0;

        int begin = 0;
	int len = strlen( setInEnv );

        // if it is just set to C, use UTF_8
        if (len == 1 && setInEnv[0] == 'C')
            return CharSetApi::UTF_8;

        // Now we search for this pattern
        // [language[_territory][.codeset][@modifier]]
        // See http://osr507doc.sco.com/en/man/html.M/locale.M.html
        // We are interested in the codeset so look for '.'
        for (begin=0; begin<len; begin++)
        {
            if (setInEnv[begin] == '.')
                break;
        }

        // modifier is optional
        if (begin < len)
        {
            int end;
            begin++;

            for(end=begin; end<len; end++)
            {
                if (setInEnv[end] == '@')
                    break;
            }
            
            StrBuf charset;
            charset.Set(&(setInEnv[begin]), end-begin);

            if (!StrPtr::CCompare(charset.Text(), "ISO8859-1"))
                return CharSetApi::ISO8859_1;
            if (!StrPtr::CCompare(charset.Text(), "ISO8859-5"))
                return CharSetApi::ISO8859_5;
            if (!StrPtr::CCompare(charset.Text(), "ISO8859-7"))
                return CharSetApi::ISO8859_7;
            if (!StrPtr::CCompare(charset.Text(), "ISO8859-15"))
                return CharSetApi::ISO8859_15;
            if (!StrPtr::CCompare(charset.Text(), "JISX0201.1976-0"))
                return CharSetApi::SHIFTJIS;
            if (!StrPtr::CCompare(charset.Text(), "JISX0208.1983-0"))
                return CharSetApi::SHIFTJIS;
            if (!StrPtr::CCompare(charset.Text(), "EUC-JP"))
                return CharSetApi::EUCJP;
            if (!StrPtr::CCompare(charset.Text(), "UTF-8"))
                return CharSetApi::UTF_8;
            if (!StrPtr::CCompare(charset.Text(), "GB2312.1980-0"))
                return CharSetApi::CP936;
            if (!StrPtr::CCompare(charset.Text(), "GB18030"))
                return CharSetApi::CP936;
            if (!StrPtr::CCompare(charset.Text(), "KSC5601.1987-0"))
                return CharSetApi::CP949;
        }

        return 0;
}

#else

int
Client::GuessCharset()
{
	return CharSetApi::UTF_8;
}
#endif
