/*
 * stack.h
 *
 *  Created on: 18-11-2012
 *  Author: Luc Paul Labonté
 */

#ifndef STACK_H_
#define STACK_H_


/**
 * @defgroup mod_stack stack.h
 * @file stack.h
 * @brief This module allows you to create a dynamic stack that contains
 * elements of your choices! It can be integers, chars, pointers, structs, etc.
 *
 *	@warning This module is provided "as is".
 *
 *	@author Luc Paul Labonté
 *	@date 18-11-2012
 *	@version 1.0
 *
 *
 *	@htmlonly
 *	<a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">
 *	<img alt="Creative Commons License" style="border-width:0"
 *	src="http://i.creativecommons.org/l/by-sa/3.0/88x31.png" /></a><br />
 *	<span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">stack.c</span>
 *	by <span xmlns:cc="http://creativecommons.org/ns#" property="cc:attributionName">
 *	stack</span> is licensed under a <a rel="license"
 *	href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">
 *	Creative Commons Attribution-ShareAlike 3.0 Unported License</a>.
 *	@endhtmlonly
 */

/// @brief The element container to put in the stack.
typedef void* StackElement;

/// @brief The node that will contain the Element and point to the next.
typedef struct _snode sNode;

/// @brief The stack structure that points to the top Node.
typedef struct _stack STACK;

/**
 * 	@brief Constructor of the stack.
 *
 * @return (STACK*) A pointer to the stack structure.
 * @return NULL if an error occured.
 */
STACK* STACK_createStack();

/**
 * 	@brief Will add an element <i>e</i> to the top of the stack.
 *
 * @param e (StackElement) The element container.
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 */
void STACK_push( StackElement e, STACK* s );

/**
 * 	@brief Will remove the top node of the stack and return it's element. It is
 * 		 up to the user to type cast in the right type of the element.
 *
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 * @return (StackElement) The element of the stack.
 * @return NULL if the stack is empty.
 */
StackElement STACK_pop( STACK* s );

/**
 * 	@brief Will <b>only</b> give the StackElement value of the top node. It is
 * 		 up to the user to type cast in the right type of the element.
 *
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 * @return (StackElement) The element of the stack.
 * @return NULL if the stack is empty.
 */
StackElement STACK_consult( STACK* s );

/**
 * 	@brief Gives the size of the stack. The number of nodes.
 *
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 * @return (int) The number of StackElement in the stackk.
 */
int STACK_getSize( STACK* s );

/**
 * 	@brief Will set the pointer to the function for clearing properly, if any, the
 * 		 	structure that is contained in the StackElement.
 *
 *	@warning Procede at your own risks.
 *
 * @param f (void*) The function to be executed when clearing the stack.
 * 	@pre f != NULL
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 */
void STACK_setClearFunction( void* f, STACK* s );

/**
 * 	@brief Destroy the entire stack. Will loop until the last node is removed and
 * 	 	 cleared from the memory. If the function STACK_setClearFunction() is
 * 	 	 used before, the function STACK_destroy() will execute the code provided
 * 	 	 by the function of the user. Set every thing to NULL or zero.
 *
 * @param s (STACK*) The stack pointer.
 * 	@pre s != NULL
 */
void STACK_destroy( STACK* s );

/**
 * @example Using STACK
 *              Here is an example on how to use the stack with a structure and how
 * 	        to clear it properly with the function pointer.
 *
 * @code
 *
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct _num num;
struct _num {
	int myNum;
};

void clearStruct( StackElement e ) {

	((num*)e)->myNum = 0;
	free( e );
	e = NULL;
}
int main(void) {

	STACK* stk = STACK_createStack();

	num* n1 = (num*) malloc( sizeof(num) );
	num* n2 = (num*) malloc( sizeof(num) );
	num* n3 = (num*) malloc( sizeof(num) );
	num* n4 = (num*) malloc( sizeof(num) );
	num* n5 = (num*) malloc( sizeof(num) );
	num* n6 = (num*) malloc( sizeof(num) );
	num* n7 = (num*) malloc( sizeof(num) );

	n1->myNum = 1;
	n2->myNum = 2;
	n3->myNum = 3;
	n4->myNum = 4;
	n5->myNum = 5;
	n6->myNum = 6;
	n7->myNum = 7;

	STACK_push( n1, stk );
	STACK_push( n2, stk );
	STACK_push( n3, stk );
	STACK_push( n4, stk );
	STACK_push( n5, stk );
	STACK_push( n6, stk );

	printf( "Size of stack: %d\n", STACK_getSize(stk) );
	printf( "Top element: %d\n", ((num*)STACK_consult(stk))->myNum );

	printf( "Adding last element.\n" );
	STACK_push( n7, stk );

	printf( "Size of stack: %d\n", STACK_getSize(stk) );
	printf( "Top element: %d\n", ((num*)STACK_consult(stk))->myNum );	// 7

	printf( "Removing 3 top elements.\n" );
	clearStruct( STACK_pop(stk ));	// 7
	clearStruct( STACK_pop(stk ));	// 6
	clearStruct( STACK_pop(stk ));	// 5

	printf( "Size of stack: %d\n", STACK_getSize(stk) );
	printf( "Top element: %d\n", ((num*)STACK_consult(stk))->myNum );	// 4
	printf( "Removing: %d\n", ((num*)STACK_pop(stk))->myNum );	// 4

	// Set the function pointer.
	STACK_setClearFunction( clearStruct, stk );

	printf( "Clearing stack...\n" );
	STACK_destroy( stk );

	free( stk );
	stk = NULL;

	printf( "Is stack is NULL: %d\n", stk == NULL );

	return EXIT_SUCCESS;
}

Results:
	Size of stack: 6
	Top element: 6
	Adding last element.
	Size of stack: 7
	Top element: 7
	Removing 3 top elements.
	Size of stack: 4
	Top element: 4
	Removing: 4
	Clearing stack...
	Is stack is NULL: 1

 *
 * @endcode
 */
#endif /* STACK_H_ */
