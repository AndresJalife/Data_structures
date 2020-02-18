#ifndef linked_list_H
#define linked_list_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                	DATA TYPES DEFINITIONS
 * *****************************************************************/


typedef struct linked_list linked_list_t;
typedef struct linked_list_iter linked_list_iter_t;


/* ******************************************************************
 *                       OPERATIONS
 * *****************************************************************/

// Creates a new linked_list.
linked_list_t *new_linked_list(void);

// Returns true if the linked list is empty, false otherwise
bool empty_linked_list(const linked_list_t* linked_list);

// Inserts a the data given by parameter in the first position of the linked list. 
// Returns false in case of an error.
bool linked_list_insert_first(linked_list_t* linked_list, void* data);

// Inserts a the data given by parameter in the last position of the linked list. 
bool linked_list_insert_last(linked_list_t* linked_list, void* data);

// Elimina el primer elemento de la linked_list, si está vacía, devuelve NULL.
// Pre: La linked_list fue creada.
// Post: se devolvió el primer elemento de la linked_listl,la linked_list
// contiene un elemento menos, si la linked_list no estaba vacía.
void* linked_list_delete_first(linked_list_t* linked_list);

// Returns the first node of the list, or NULL if its empty.
void* linked_list_get_first(const linked_list_t* linked_list);

// Returns the last node of the list, or NULL if its empty.
void* linked_list_get_last(const linked_list_t* linked_list);

// Returns the lenght of the list
size_t linked_list_lenght(const linked_list_t* linked_list);

// Deletes the linked list and every node in it. If delete_data is received by parameter, for every node 
// in the list it applies the function.
// Pre: Delete_data is a function capable of destroying the data of the linked list, or NULL if its not needed.
void delete_linked_list(linked_list_t* linked_list, void delete_data(void *));


// Internal iterator operation // 

// It iters the whole list applying the function "visit()" to every node. 
// If the function "visit()" returns false, the iteration is automatically interrumpted.
// Post: "visit()" has been applied to every node in the list.
void linked_list_iterate(linked_list_t* linked_list, bool visit(void* data, void* extra), void* extra);


// External iterator operations //

// Creates a new iterator
// Post: returns a new iterator pointing the first node of the linked list given by parameter.
linked_list_iter_t *new_linked_list_iterator(linked_list_t* linked_list);

// The iterator advances one node in the linked list. 
// Returns false if the iterator is at the end of the list or if its empty.
// cuando ya está al final de la linked_list o si no tiene nodos. 
bool linked_list_iter_advance(linked_list_iter_t* iter);

// Returns the node pointed by the iterator
void* linked_list_iter_get_actual(const linked_list_iter_t* iter);

// Returns true if the iterator is pointing the last node of the linked list, false otherwise.  
bool linked_list_iter_at_end(const linked_list_iter_t* iter);

// Deletes the iterator without modifying the linked list.
void delete_linked_list_iterator(linked_list_iter_t* iter);

// Inserts the data as a new node in the position the iterator is pointing. 
bool linked_list_iter_insert(linked_list_iter_t *iter, void *data);

// Deletes the node pointed by the iterator. 
void* linked_list_iter_delete(linked_list_iter_t* iter);

#endif // linked_list_H