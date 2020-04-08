#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */

/* Cmp function prototype.
   It receives two pointer of the data type used in the heap, 
   and it returns:
   less than 0  if  a < b
             0  if  a == b
   more than 0  if  a > b
*/
typedef int (*cmp_func_t) (const void *a, const void *b);

/* Heapsort generic function. It sorts an arrangement of pointers,
   for which it requires a cmp function. 
   It modifies the arrangement in-place.
   (Not a heap operation)
*/
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);

/* Implementation of a priority queue (heap) as a max-heap (given a normal cmp function).
   The biggest element will be the one with the highest prioriy. 
   It can be changed to a min-heap with the inverse cmp function.
*/

/* Type used for the heap. */
typedef struct heap heap_t;

/* Creates a heap. Receives the cmp (Comparation) function as parameter.
   Returns a pointer to the heap.
*/
heap_t *new_heap(cmp_func_t cmp);

/* Alternative heap creator. Besides the cmp function, it
   receives an arrangement of values to inicialize the heap.
   0(n) complexity.  
*/
heap_t *new_heap_arr(void *arr[], size_t n, cmp_func_t cmp);

/* Deletes the heap, applying the 'cmp' function given by parameter
   to every element in the heap.
   The pointer to the function can be NULL, in which case it wont be applied.
*/
void heap_delete(heap_t *heap, void delete_element(void *e));

/* Returns the quantity of the heap.
*/
size_t heap_quantity(const heap_t *heap);

/* Returns true if the quantity is 0, false otherwise.
*/
bool heap_empty(const heap_t *heap);

/* It adds the element given by parameter to the heap. 
   The element cant be NULL.
   Returns true if the operation succeded, false otherwise
*/
bool heap_enqueue(heap_t *heap, void *elem);

/* Returns the highest prority element. 
   If the heap is empty it returns NULL.
*/
void *heap_top(const heap_t *heap);

/* Deletes the highest priority element and returns it.
   If the heap is empty, it returns NULL.
*/
void *heap_dequeue(heap_t *heap);


void pruebas_heap_alumno(void);

#endif // HEAP_H

