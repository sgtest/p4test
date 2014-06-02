/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 */

# include <stdhdrs.h>
# include <strbuf.h>
# include <vararray.h>
# include <strarray.h>

/*
 * strarray.cc - a 0 based array of StrBufs
 */

class StrVarArray : public VVarArray {

    public:
	void SetCaseFolding( int c ) 
	{
	    caseFolding = c;
	}

	virtual int Compare( const void *a, const void *b ) const 
	{
	    return caseFolding 
		    ? ((StrBuf *)a)->XCompare( *(StrBuf *)b )
		    : ((StrBuf *)a)->CCompare( *(StrBuf *)b );
	}

	virtual void	Destroy( void * ) const {}

	int caseFolding;

} ;

StrArray::StrArray()
{
	array = new StrVarArray;
}

StrArray::~StrArray()
{
	for( int i = 0; i < array->Count(); i++ )
	    delete (StrBuf *)array->Get(i);

	delete array;
}

const StrBuf *
StrArray::Get( int i ) const
{
	return (StrBuf *)array->Get(i);
}

StrBuf *
StrArray::Edit( int i )
{
	return (StrBuf *)array->Edit(i);
}

void
StrArray::Remove( int i )
{
	if( array->Get( i ) )
	{
	    delete Edit( i );
	    array->Remove( i );
	}
}

StrBuf *
StrArray::Put()
{
	return (StrBuf *)array->Put( new StrBuf );
}

int
StrArray::Count() const
{
	return array->Count();
}

void
StrArray::Sort( int caseFolding )
{
	array->SetCaseFolding( caseFolding );
	array->Sort();
}

/*
 * StrPtrArray -- an array of StrPtrs
 */

StrPtrArray::StrPtrArray()
{
	tabVal = 0;
	tabSize = 0;
	tabLength = 0;
}

StrPtrArray::~StrPtrArray()
{
	delete []tabVal;
}

void
StrPtrArray::Put( const StrPtr &val )
{
	// Realloc with spare room

	if( tabLength == tabSize )
	{
	    int newSize = tabSize + 10;
	    StrRef *newtabVal = new StrRef[ newSize ];

	    // unfortunately, invokes destructors
	    // fortunately, there are none

	    if( tabVal )
	    {
		for( int i = 0; i < tabSize; i++ )
		    newtabVal[i] = tabVal[i];

		delete []tabVal;
	    }

	    tabVal = newtabVal;
	    tabSize = newSize;
	}

	tabVal[ tabLength++ ] = val;
}
