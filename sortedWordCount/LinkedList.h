/*
 * The linked list header file
 * includes macros for making linked lists and nodes, as well
 * as printing attributes of the LL.
 * NO CODE IN THIS HEADER FILE. ONLY DECLARATIONS, TYPEDEFS, AND MACROS
 */

#ifndef LinkedListHeaderWasLoaded
#define LinkedListHeaderWasLoaded

typedef struct LinkedListNode {
	struct LinkedListNode *next_ptr; //pointer to next node
	//struct LinkedListNode *prev_ptr; //pointer to previous node
	int count;
	char *word;
} Node;

typedef struct LinkedList {
	Node *head_ptr;
	Node *tail_ptr;
	int length;
} LL;

#define printAttributes(LL) printf("HEAD @ %p. TAIL @ %p. LENGTH = %d.\n",LL.head_ptr,LL.tail_ptr,LL.length)
#endif