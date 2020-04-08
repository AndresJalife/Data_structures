#define _POSIX_C_SOURCE 200809L   // Para el strdup
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "heap.h"
#include <stdbool.h>

#define	INICIAL_CAPACITY 15	// 4 niveles de base
#define REDIMENSION_DECREASE_COND 4
#define REDIMENSION 2

// Defino estructuras
struct heap {
	void** data;
	size_t quant;
	size_t size;
	cmp_func_t cmp;
};

// Heap

// Auxiliar functions

heap_t* _new_heap_n(cmp_func_t cmp, size_t n){
	/*Creates a new empty heap with size n*/
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;

	heap->data = malloc(sizeof(void*) * n);
	heap->quant = 0;
	heap->size = n;
	heap->cmp = cmp;

	return heap;
}

void _swap(void* arr[], size_t a, size_t b){
	void* aux = arr[a];
	arr[a] = arr[b];
	arr[b] = aux;
	return;
}

bool _redimension(heap_t* heap, size_t n){
	void** new_data = realloc(heap->data, n * sizeof(void*));
	if (!new_data) return false;
	heap->data = new_data;
	heap->size = n;
	return true;
}

void _downheap(void* arr[], size_t pos, size_t quant, cmp_func_t cmp){
	if (pos >= quant) return;
	size_t min = pos; 
	size_t left = 2 * pos + 1;
	size_t right = 2 * pos + 2;
	if (left < quant && (cmp)(arr[left], arr[min]) > 0) min = left;
	if (right < quant && (cmp)(arr[right], arr[min]) > 0) min = right;
	if (min != pos){
		_swap(arr, pos, min);
		_downheap(arr, min, quant, cmp);
	} 
}

void _upheap(void* arr[], size_t pos, cmp_func_t cmp){
	if (pos == 0) return;
	size_t father = (pos-1) / 2;
	if ((cmp)(arr[father], arr[pos]) < 0) {
		_swap(arr, pos, father);
		_upheap(arr, father, cmp);
	}
}

void _heapify(void** arr, size_t quant, cmp_func_t cmp){
	for (size_t i = (quant / 2) ; i > 0 ; i--){		//From the first father until 0
		_downheap(arr, i - 1, quant , cmp);
	}	
}
// Heap Operations 

size_t heap_quantity(const heap_t *heap){
	return (heap->quant);
}

bool heap_empty(const heap_t *heap){
	return (heap->quant == 0);
}

void *heap_top(const heap_t *heap){
	if (heap_empty(heap)) return NULL;

	return (heap->data[0]);
}

heap_t *new_heap(cmp_func_t cmp){
	heap_t* heap = _new_heap_n(cmp, INICIAL_CAPACITY);
	if (!heap) return NULL;

	return heap;
}

void heap_delete(heap_t *heap, void delete_element(void *e)){
	if (delete_element){
		for (size_t i = 0; i < heap->quant; i++){
			delete_element(heap->data[i]);
		}
	}
	free(heap->data);
	free(heap);
}

heap_t *new_heap_arr(void *arr[], size_t n, cmp_func_t cmp){	
	heap_t* heap = _new_heap_n(cmp, n);
	if (!heap) return NULL;

	memcpy(heap->data, arr, sizeof(void*) * n);
	heap->quant = n;

	if (n > 1) _heapify(heap->data, n, cmp);
	
	return heap;
}

bool heap_enqueue(heap_t *heap, void *elem){
	if (heap->quant == heap->size){
		if (!_redimension(heap, heap->quant * REDIMENSION)) return false;
	}
	heap->data[heap->quant] = elem;
	_upheap(heap->data, heap->quant, heap->cmp);
	heap->quant += 1;
	return true;
}

void *heap_dequeue(heap_t *heap){
	if (heap->quant == 0) return NULL;
	if (heap->quant == heap->size / REDIMENSION_DECREASE_COND && heap->size > INICIAL_CAPACITY) _redimension(heap, heap->size / REDIMENSION);
	void* to_return = heap->data[0];
	_swap(heap->data, 0, heap->quant - 1);
	_downheap(heap->data, 0, heap->quant - 1, heap->cmp);
	heap->quant -= 1;
	return to_return;
}

// Heapsort

void heap_sort(void *elementos[], size_t quant, cmp_func_t cmp){	
	if (!elementos|| !cmp) return;

	_heapify(elementos, quant, cmp);

	for (size_t i = 0; i < quant; i++){
		_swap(elementos, 0, (quant - 1) - i);
		_downheap(elementos, 0, (quant - 1) - i, cmp);
	}
}