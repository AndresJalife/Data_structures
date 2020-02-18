#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include "testing.h"

// Defino estructuras

typedef struct node{
	void* data;
	struct node* next;
}node_t;

struct linked_list{
    node_t* first;
    node_t* last;
    size_t lenght;
};

struct linked_list_iter {
	linked_list_t* linked_list;
	node_t* prev;
	node_t* act;
};

// Linked-List operations

linked_list_t* new_linked_list(void){
	linked_list_t* linked_list = malloc(sizeof(linked_list_t));

	if (!linked_list) return NULL;
	
	linked_list->first = NULL;
	linked_list->last = NULL;
	linked_list->lenght = 0;

	return linked_list;
}

node_t* _new_node(void* value){
	node_t* node = malloc(sizeof(node_t));

	if (!node) return NULL;
	
	node->data = value;
	node->next = NULL;

	return node;
}

bool empty_linked_list(const linked_list_t* linked_list){
	if (!linked_list) return false;
	
	return (linked_list->lenght == 0);
}

bool linked_list_insert_first(linked_list_t* linked_list, void* data){
	if (!linked_list) return false;
	
	node_t* node = _new_node(data);
	if (!node) return false;
	
	node_t* aux_node = linked_list->first;
	linked_list->first = node;

	if (!empty_linked_list(linked_list)){	
		linked_list->first->next = aux_node;
	} else {
		linked_list->last = node;
	}
	linked_list->lenght++;
	return true;
}

bool linked_list_insert_last(linked_list_t* linked_list, void* data){
	if (!linked_list) return false;
	
	node_t* node = _new_node(data);
	if (!node) return false;
	
	if (!empty_linked_list(linked_list)){
		linked_list->last->next = node;
	} else {
		linked_list->first = node;
	}
	linked_list->last = node;
	linked_list->lenght++;
	return true;
}

void* linked_list_delete_first(linked_list_t* linked_list){
	if (!linked_list|| empty_linked_list(linked_list)){
		return NULL;
	}
	void* value = linked_list_get_first(linked_list);
	node_t* aux_node = linked_list->first->next;
	free(linked_list->first);

	if (linked_list->first == linked_list->last) linked_list->last = NULL;
	
	linked_list->first = aux_node;
	linked_list->lenght--;
	return value;
}

void* linked_list_get_first(const linked_list_t* linked_list){
	if (!linked_list || empty_linked_list(linked_list)) return NULL;
	
	return linked_list->first->data;
}

void* linked_list_get_last(const linked_list_t* linked_list){
	if (!linked_list|| empty_linked_list(linked_list)) return NULL;
	
	return linked_list->last->data;
}

size_t linked_list_lenght(const linked_list_t* linked_list){
	if (!linked_list) return false;

	return linked_list->lenght;
}

void delete_linked_list(linked_list_t* linked_list, void delete_data(void*)){
	if (!linked_list) return;

	node_t* actual = linked_list->first;
	node_t* next = NULL;
	while (actual){
		if (delete_data) delete_data(actual->data);
		next = actual->next;
		free(actual);
		actual = next;
	}
	free(linked_list);
}


// Internal iterator operation

void linked_list_iterate(linked_list_t* linked_list, bool visit(void* data, void* extra), void* extra){
	if (!linked_list || empty_linked_list(linked_list)|| !visit) return;

	node_t* actual = linked_list->first;
	while(actual){
		if (!visit(actual->data, extra)) return;
		actual = actual->next;
	}
}


//External iterator operations

linked_list_iter_t* new_linked_list_iterator(linked_list_t* linked_list){
	linked_list_iter_t* iter = malloc(sizeof(linked_list_iter_t));
	if (!iter) return NULL;

	iter->linked_list = linked_list;
	iter->prev = NULL;
	iter->act = linked_list->first;

	return iter;
}

bool linked_list_iter_advance(linked_list_iter_t* iter){
	if (!iter || !iter->linked_list|| linked_list_iter_at_end(iter)|| empty_linked_list(iter->linked_list)) return false; 
	
	iter->prev = iter->act;
	iter->act = iter->act->next;
	return true;
}

void* linked_list_iter_get_actual(const linked_list_iter_t* iter){
	if (!iter || !iter->linked_list|| linked_list_iter_at_end(iter)||empty_linked_list(iter->linked_list)) return NULL; 
	
	return iter->act->data;
}

bool linked_list_iter_at_end(const linked_list_iter_t* iter){
	if (!iter || !iter->linked_list) return false; 

	return (iter->act == NULL);
}

void delete_linked_list_iterator(linked_list_iter_t* iter){
	if (!iter || !iter->linked_list) return;  
	free(iter);
}

bool linked_list_iter_insert(linked_list_iter_t* iter, void* data){
	if (!iter || !iter->linked_list) return false; 
	
	if (iter->act == iter->linked_list->first){
		bool inserted = linked_list_insert_first(iter->linked_list, data);
		if (!inserted) return false;
		iter->act = iter->linked_list->first;
	} else {
		node_t* node = _new_node(data);
		if (!node) return false;
		if (linked_list_iter_at_end(iter)) iter->linked_list->last = node;

		node->next = iter->act;
		iter->prev->next = node;
		iter->act = node;
		iter->linked_list->lenght++;
	}
	return true;
}

void* linked_list_iter_delete(linked_list_iter_t* iter){
	if (!iter || !iter->linked_list||empty_linked_list(iter->linked_list)||!iter->act) return NULL; 
	
	void* value = iter->act->data;
	
	if (iter->act == iter->linked_list->first){
		node_t* aux_node = iter->act->next;
		bool deleted = linked_list_delete_first(iter->linked_list);
		if (!deleted) return NULL;
		iter->act = aux_node;
	} else {
		if (iter->act == iter->linked_list->last){
			iter->prev->next = NULL;
			iter->linked_list->last = iter->prev;
			free(iter->act);
			iter->act = NULL;
		} else {
			iter->prev->next = iter->act->next;
			free(iter->act);
			iter->act = iter->prev->next;
		}
		iter->linked_list->lenght--;
	}
	
	return value;
}
