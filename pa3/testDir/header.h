#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>

typedef struct SortedList
{
	int (*comparator)( void *, void * ); //comparator function needed to sort nodes
	void (*destroyer)( void * ); //destroy function needed to free data
	struct SortedListNode *head; //pointer to the first node of the list
}SortedList;
typedef struct SortedList* SortedListPtr;

#endif