#include <stdlib.h>

/*
	Array with capacity
	---

	Arr_new(cap);			// Create new array with capacity
	Arr_add(arr, element);	// Add new element for the array
	Arr_get(arr, id);		// Get the array element or Arr_null;
	Arr_set(arr, id, el);	// Set element at id-pos and return Arr_success. Otherwise Arr_fail
	Arr_free(arr);			// Free the array

	arr->size;				// Get size of the array
	arr->cap;				// Get capacity of the array
*/

typedef struct {
	void** elems;
	int size;
	int cap;
} Arr;

#define Arr_null 0
#define Arr_fail 0
#define Arr_success 1

static void __arr_grow_when_cap(Arr *arr) {
	int cap = arr->cap;
	int size = arr->size;
	if (size == 0) return;
	if (size != cap) return;
	arr->cap = cap * 2;
	void** newElems = malloc(sizeof(void*) * arr->cap);
	for (int i = 0; i < size; i++) {
		newElems[i] = arr->elems[i];
	}
	free(arr->elems);
	arr->elems = newElems;
}

void Arr_add(Arr *arr, void* elem) {
	__arr_grow_when_cap(arr);
	arr->elems[arr->size] = elem;
	arr->size += 1;
}

Arr* Arr_new(int cap) {
	if (cap < 4) cap = 4;
	Arr* arr = malloc(sizeof(Arr));
	arr->elems = malloc(sizeof(void*) * cap);
	arr->size = 0;
	arr->cap = cap;
	return arr;
}

void Arr_free(Arr* arr) {
	free(arr->elems);
	free(arr);
}

void* Arr_get(Arr* arr, int id) {
	if (id < 0 || id >= arr->size) {
		return Arr_null;
	}
	return arr->elems[id];
}

int Arr_set(Arr *arr, int id, void* elem) {
	if (id < 0 || id >= arr->size) {
		return Arr_fail;
	}
	arr->elems[id] = elem;
	return Arr_success;
}