/*
 * Copyright 1995, 1996 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * MapItem -- mapping entries on a chain
 *
 * A MapItem holds two MapHalfs that constitute a single entry in
 * a MapTable.  MapItem also implement fast searching for entries
 * for MapTable::Check() and MapTable::Translate().
 */

# include <stdhdrs.h>
# include <error.h>
# include <strbuf.h>
# include <vararray.h>

# include <debug.h>

# include "maphalf.h"
# include "maptable.h"
# include "mapstring.h"
# include "mapdebug.h"
# include "mapitem.h"

/*
 * MapItem::Reverse - reverse the chain, to swap precedence
 */

MapItem *
MapItem::Reverse()
{
	MapItem *m = this;
	MapItem *entry = 0;
	int top = m ? m->slot : 0;

	while( m )
	{
	    MapItem *n = m->chain;
	    m->chain = entry;
	    m->slot = top - m->slot;
	    entry = m;
	    m = n;
	}

	return entry;
}

/*
 * MapItem::Tree - recursively construct a trinary sort tree
 */

MapItem *
MapItem::Tree( 
	MapItem **start,
	MapItem **end,
	MapTableT dir,
	MapItem *parent,
	int &depth )
{
	/* No empties */

	if( start == end )
	    return 0;

	/*
	 * start li (middle) ri end 
	 *
	 * (middle) is halfway between start and end.
	 * li is first item that is a parent of middle.
	 * ri is last item li is a parent of.
	 *
	 * We return
	 *
	 *	         *li
	 *             /  |  \
	 *            /   |   \
	 *	     /    |    \
	 *          /     |     \
	 * start->li   li+1->ri  ri->end
	 */

	MapItem **li = start;
	MapItem **ri;

	/*
	 * Quick check: the center tree often ends up in the
	 * shape of a linked list (due to identical entries).
	 * This is an optimization for that case.
	 */

	if( start == end - 1 || (*start)->IsParent( end[-1], dir ) )
	{
	    ri = end;

	    int overlap = 0;
	    int depthBelow = 0;
	    int maxSlot = 0;
	    int pLength = (*start)->Ths( dir )->GetFixedLen();

	    MapItem *last = 0;
	    MapItem::MapWhole *t;

	    while( --ri > start )
		if( (*ri)->Ths( dir )->GetFixedLen() == pLength )
		    break;

	    if( parent )
		overlap = (*start)->Ths( dir )->GetCommonLen( parent->Ths( dir ) );
	    if( ri < end - 1 )
	    {
		t = (*ri)->Whole( dir );

		t->overlap = overlap;
		t->maxSlot = (*ri)->slot;
		t->right = t->left = NULL;

		t->center = Tree( ri + 1, end, dir, *ri, depthBelow );

		if( maxSlot < t->maxSlot )
		    maxSlot = t->maxSlot;

		last = *ri--;
		++depthBelow;
	    }

	    depthBelow += ri - start + 1;

	    while( ri >= start )
	    {
		t = (*ri)->Whole( dir );

		t->overlap = overlap;
		if( maxSlot < (*ri)->slot )
		    maxSlot = (*ri)->slot;
		t->maxSlot = maxSlot;
		t->right = t->left = NULL;
		t->center = last;
		last = *ri--;
	    }

	    if( parent && parent->Whole( dir )->maxSlot < maxSlot )
		parent->Whole( dir )->maxSlot = maxSlot;

	    if( depth < depthBelow )
		depth = depthBelow;

	    return *li;
	}
	else 

	/*
	 * Start in middle.
	 * Move li from start until we find first parent of ri.
	 * Move ri right until we find last child of li.
	 */

	{
	    ri = start + ( end - start ) / 2;

	    while( li < ri && !(*li)->IsParent( *ri, dir ) )
		++li;

	    while( ri < end && (*li)->IsParent( *ri, dir ) )
		++ri;
	}

	/*
	 * Fill in the *li node, which we will return.
	 *
	 * left, right, center computed recursively.
	 */

	MapItem::MapWhole *t = (*li)->Whole( dir );

	int depthBelow = 0;

	t->overlap = 0;
	t->maxSlot = (*li)->slot;

	t->left =    Tree( start, li, dir, *li, depthBelow );
	t->center =  Tree( li + 1, ri, dir, *li, depthBelow );
	t->right =   Tree( ri, end, dir, *li, depthBelow );

	/*
	 * Current depth is 1 + what's below us, as long as one of
	 * our peers isn't deeper.
	 */

	if( depth < depthBelow + 1 )
	    depth = depthBelow + 1;

	/*
	 * Relationship to parent:
	 * parent's maxSlot includes our maxSlot.
	 * our initial substring overlap with our parent.
	 */

	if( parent )
	{
	    if( parent->Whole( dir )->maxSlot < t->maxSlot )
		parent->Whole( dir )->maxSlot = t->maxSlot;

	    t->overlap = t->half.GetCommonLen( parent->Ths( dir ) );
	}

	return *li;
}

/*
 * MapItem::Match() - find best matching MapItem
 *
 * We have a chain of MapItems, but instead use trinary tree constructed
 * by MapItem::Tree for this direction.
 *
 * This has three separate optimizations:
 *
 *	1. The trinary tree itself (instead of a linear scan).  We use
 *	   a trinary tree because we need to order mappings that are
 *	   neither less than nor greater than others, but including them.
 *	   e.g. //depot/main/... includes //depot/main/p4...  As we
 *	   decend the tree, we use MapHalf::Match1 to compare the initial
 *	   substring.  If it matches, we will use MapHalf::Match2 to
 *	   do the wildcard comparison and then follow the center down.
 *
 *	2. Slot precedence.  Once we've had a match, we only need to Match2
 *	   nodes with better precedence (map->slot > best).  Further, once
 *	   we've had a match, we can give up entirely if the tree below
 *	   has no nodes with higher precedence (best > t->maxSlot).
 *
 *	3. Overlap.  As we decend the tree, many of the strings have
 *	   initial substrings in common.  So we remember the offset of 
 *	   the last matching character in the parent's MapHalf, adjust it 
 *	   down if needed so as not to exceed the operlap with this
 *	   MapHalf, and start the match from there.
 */

MapItem *
MapItem::Match( MapTableT dir, const StrPtr &from )
{
	int coff = 0;
	int best = -1;
	MapItem *map = 0;
	MapItem *tree = this;
	MapParams params;

	/* Decend */

	while( tree )
	{
	    MapItem::MapWhole *t = tree->Whole( dir );

	    /*
	     * No better precendence below?  Bail. 
	     */

	    if( best > t->maxSlot )
		break;

	    /*
	     * Match with prev map greater than overlap?  trim. 
	     */

	    if( coff > t->overlap )
		coff = t->overlap;

	    /*
	     * Match initial substring (by which the tree is ordered). 
	     * Can skip match if same initial substring as previous map.
	     */

	    int r = 0;

	    if( coff < t->half.GetFixedLen() )
		r = t->half.Match1( from, coff );

	    /*
	     * Match?  Higher precedence?  Wildcard match?  Save. 
	     */

	    if( !r && best < tree->slot && t->half.Match2( from, params ) )
		map = tree, best = map->slot;

	    /*
	     * Follow to appropriate child. 
	     */

	    if( r < 0 ) 	tree = t->left;
	    else if( r > 0 ) 	tree = t->right;
	    else 		tree = t->center;
	}

	/* 
	 * Best mapping an unmapping?  That's no mapping.
	 */

	if( !map || map->mapFlag == MfUnmap )
	    return 0;

	return map;
}

/*
 * MapPairArray -- pre-join two maps by using the MapTrees
 */

int 
MapPairArray::Compare( const void *a1, const void *a2 ) const
{
	return ((MapPair *)a1)->CompareSlot( (MapPair *)a2 );
}

void
MapPairArray::Match( MapItem *item1, MapItem *tree2 )
{
	// Do non-wildcard initial substrings match?

	MapItem::MapWhole *t1 = item1->Whole( dir1 );

	do {

	    MapItem::MapWhole *t2 = tree2->Whole( dir2 );

	    int r = t2->half.MatchHead( t1->half );

	    if( DEBUG_JOIN )
		p4debug.printf("cmp %d %s %s\n", r, t1->half.Text(), t2->half.Text() );

	    // On match, add this to list of pairs for MapHalf::Join()

	    if( !r && !t2->half.MatchTail( t1->half ) )
		Put( new MapPair( item1, tree2, &t1->half, &t2->half ) );

	    // Recursively explore other matching possibilities.

	    if( r <= 0 && t2->left )   Match( item1, t2->left );
	    if( r >= 0 && t2->right )  Match( item1, t2->right );

	    if( r != 0 )
		return;

	    // tail iteration down the center

	    tree2 = t2->center;
	} while( tree2 );
}

/*
* MapItem::Dump() - dump tree, rooted at this
 */

void
MapItem::Dump( MapTableT d, const char *name, int l )
{
	static const char tabs[] = "\t\t\t\t\t\t\t\t";
	const char *indent = l > 8 ? tabs : tabs + 8 - l;

	if( !l )
	    p4debug.printf( "MapTree\n" );

	if( Whole( d )->left ) 
	    Whole( d )->left->Dump( d, "<<<", l+1 );

	p4debug.printf("%s%s %c%s\n", indent, name, " -+$"[ mapFlag ], Ths(d)->Text() );

	if( Whole( d )->center )
	    Whole( d )->center->Dump( d, "===", l+1 );

	if( Whole( d )->right )
	    Whole( d )->right->Dump( d, ">>>", l+1 );
}
