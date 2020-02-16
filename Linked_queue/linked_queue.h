#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>


/* ******************************************************************
 *               DATA TYPE DEFINITIONS
 * *****************************************************************/

struct queue;
typedef struct queue queue_t;


/* ******************************************************************
 *                QUEUE PRIMITIVES
 * *****************************************************************/

// Creates a new queue.
// Post: returns the empty queue.
queue_t* new_queue(void);

// Deletes the queue. If destroy_data is received, for every element of the queue, 
// this function will be aplied to it.
// Pre: the queue was created, destroy_data is a function capable of destroying 
// the elementss of the queue.
// Post: all elements of the queue are deleted.
void delete_queue(queue_t *queue, void destroy_data(void*));

// Returns true if the queue is empty, false otherwise.
// Pre: the queue was created.
bool empty_queue(const queue_t *queue);

// Enqueues a new element, returns flase in case of an error. 
// Pre: the queue was created.
bool queue_enqueue(queue_t *queue, void* valor);

// Returns the first element of the queue. If its empty, it returns NULL.
// Pre: the queue was created.
void* queue_first(const queue_t *queue);

// It returns the first element of the queue and it deletes it from the queue. If its empty
// it returns NULL.  queue.
// Pre: the queue was created.
void* queue_dequeue(queue_t *queue);

#endif // QUEUE_H
