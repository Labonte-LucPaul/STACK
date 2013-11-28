
/*
 ============================================================================
 Name        : stack.c
 Author      : Luc Paul Labonté
 Date        : 18-11-2012
 Version     : 1.0
 Copyright   : Copy right 2012-2014
 Description : A simple stack of structured "objects".
 Licence     : http://creativecommons.org/licenses/by-sa/3.0/deed.en_US
 Repository  : https://github.com/Labonte-LucPaul/STACK
 Warning     : This code is provide as is.
 ============================================================================
 */
 

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct _snode {

	/// @brief The pointer to the element in the stack.
	StackElement stackElem;

	/// @brief The next node (below) the current one.
	sNode* next;
};

struct _stack {

	/// @brief The pointer to the top most node of the stack!
	sNode* top;

	/// @brief The number of nodes in the stack.
	int count;

	/// @brief The function to use when deleting the stack.
	void (*clear)(StackElement);
};

STACK* STACK_createStack() {

	STACK* s = (STACK*) malloc( sizeof(STACK) );

	if( s == NULL ) {
		return NULL;
	}

	s->top   = NULL;
	s->clear = NULL;
	s->count = 0;

	return s;
}

void STACK_push( StackElement e, STACK* s ) {

	if( s != NULL ) {
		sNode* n = (sNode*) malloc( sizeof(sNode) );

		n->stackElem = e;
		n->next      = s->top;
		s->top       = n;
		s->count++;
	}
}

StackElement STACK_pop( STACK* s ) {

	if( s != NULL && s->count > 0 ) {
		sNode* n = s->top;
		s->top = n->next;
		n->next = NULL;
		s->count--;
		return n->stackElem;
	}

	return NULL;
}

StackElement STACK_consult( STACK* s ) {
	if( s != NULL && s->count > 0 ) {
		return s->top->stackElem;
	}
	return NULL;
}

int STACK_getSize( STACK* s ) {
	if( s != NULL ) {
		return s->count;
	}
	return 0;
}

void STACK_setClearFunction( void* f, STACK* s ) {
	if( s != NULL ) {
		s->clear = f;
	}
}

void STACK_destroy( STACK* s ) {
	sNode* n;
	while( (n = s->top) != NULL ) {
		s->top = n->next;
		if( s->clear != NULL ) {
			s->clear(n->stackElem);
		}
		free( n->stackElem );
		n->stackElem = NULL;
		n->next = NULL;
		free( n );
		n = NULL;
	}
	s->count = 0;
	s->clear = NULL;
	s->top = NULL;
	free( s );
	s = NULL;
}
