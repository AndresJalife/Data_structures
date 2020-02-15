#ifndef _stack_H
#define _stack_H

#include <stdbool.h>


/* *****************************************************************
 *                		DATA TYPES DEFINITION
 * *****************************************************************/


struct stack; 
typedef struct stack stack_t;


/* *****************************************************************
 *                    STACK PRIMITIVES
 * *****************************************************************/

// Creates a new stack.
// Post: returns an empty stack.
stack_t* new_stack(void);

// Deletes the stack
// Pre: the stack was created.
// Post: every element in the stack was deleted.
void delete_stack(stack_t *stack);

// Returns true if the stack is empty, false otherwise.
// Pre: the stack was created.
bool empty_stack(const stack_t *stack);

// Pushes a new element into the stack. Returns false in case of an error.
// Pre: the stack was created.
// Post: the stack has a new element on top.
bool stack_push(stack_t *stack, void* valor);

// Returns the element on top of the stack if its not empty. If its empty, it returns NULL.
// Pre: the stack was created.
void* stack_top(const stack_t *stack);

// It returns the element on top of the stack and deletes it of it. 
// Pre: the stack was created.
void* stack_pop(stack_t *stack);

#endif // _stack_H