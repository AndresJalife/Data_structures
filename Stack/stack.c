#include "stack.h"
#include <stdlib.h>
#define	INICIAL_CAPACITY 8
#define RESIZE_INCREASE 2 
#define RESIZE_DECREASE 2
#define RESIZE_CONDITION 4

struct stack {
    void** data;
    size_t quantity;  // quantity of elements pushed.
    size_t capacity;  // capacity of the array.
};

/* *****************************************************************
 *                    STACK PRIMITIVES
 * *****************************************************************/

bool _stack_resize(stack_t* stack, size_t new_cap){
    /* Resizes the capacity of the stack
       Pre: stack created 
       Post: the stack changed its capacity to "new_cap" and returns true. 
       Or it returns false if it couldn't resize it, and the stack remains intact.*/

    void* new_data = realloc(stack->data, new_cap * sizeof(void*));

    if (!new_data) return false;
  
    stack->data = new_data;
    stack->capacity = new_cap;
    return true;
}

stack_t* new_stack(){
    stack_t* stack = malloc(sizeof(stack_t));

    if (!stack) return NULL;
   
    stack->data = malloc(INICIAL_CAPACITY * sizeof(void*));	
    if (!stack->data){
    	free(stack);
    	return NULL;
    }
    stack->capacity = INICIAL_CAPACITY;
    stack->quantity = 0;

    return stack;
}

void delete_stack(stack_t *stack){
    free(stack->data);
    free(stack);
}

bool empty_stack(const stack_t *stack){
    return (stack->quantity == 0);				
}	

bool stack_push(stack_t *stack, void* valor){
    if (stack->quantity  == stack->capacity){
    	if (!_stack_resize(stack, stack->capacity * RESIZE_INCREASE)) return false;    
    } 
    stack->data[stack->quantity] = valor;
    stack->quantity += 1;
    return true;
}
	
void* stack_top(const stack_t *stack){
    if (empty_stack(stack)) return NULL;

    return stack->data[stack->quantity - 1];
}

void* stack_pop(stack_t *stack){
    if (empty_stack(stack)) return NULL;
	
    if (stack->quantity == stack->capacity / RESIZE_CONDITION){
    	_stack_resize(stack, stack->capacity / RESIZE_DECREASE);
    }
    stack->quantity -= 1;
    return stack->data[stack->quantity];
}
