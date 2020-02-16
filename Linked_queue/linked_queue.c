#include "linked_queue.h"
#include <stdlib.h>

typedef struct node{
	void* data;
	struct node* next;
}node_t;

struct queue {
    node_t* first;
    node_t* last;
};

queue_t* new_queue(){
	queue_t* queue = malloc(sizeof(queue_t));

	if (!queue)	return NULL;

	queue->first = NULL;
	queue->last = NULL;

	return queue;
}

node_t* _new_node(void* value){
	node_t* node = malloc(sizeof(node_t));

	if (!node) return false;
	
	node->data = value;
	node->next = NULL;

	return node;
}

bool empty_queue(const queue_t *queue){
	if (!queue)	return false;
	
	return (!queue->first);
}

void* queue_dequeue(queue_t *queue){
	if (!queue||empty_queue(queue)) return NULL;
	
	void* value = queue->first->data;
	node_t* aux_node = queue->first->next;
	free(queue->first);

	if (queue->first == queue->last){
		queue->last = NULL;
		queue->first = NULL;
	} else {
		queue->first = aux_node;
	}
	return value;
}

void delete_queue(queue_t *queue, void destroy_data(void*)){
	if (!queue) return;
	
	node_t* current = queue->first;
	node_t* next = NULL;
	while (current){
		if (destroy_data) destroy_data(current->data);

		next = current->next;
		free(current);
		current = next;
	}
	free(queue);
}

bool queue_enqueue(queue_t *queue, void* value){
	if (!queue) return false;
	
	node_t* node = _new_node(value);
	if (!empty_queue(queue)){
		queue->last->next = node;
	} else {
		queue->first = node;
	}
	queue->last = node;
	return true;
}

void* queue_first(const queue_t *queue){
	if (!queue|| empty_queue(queue)) return NULL;
	
	return queue->first->data;
}
