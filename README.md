# C Essentials

# Set of `C` mini libs for better `c` coding

## Capacity based list
```cpp
#include "arr.c"

Arr_new(cap);			// Create new array with capacity
Arr_add(arr, element);	// Add new element for the array
Arr_get(arr, id);		// Get the array element or Arr_null;
Arr_set(arr, id, el);	// Set element at id-pos and return Arr_success. Otherwise Arr_fail

Arr_free(arr);			// Free the array
// Note: `Arr_free(arr)` will NOT free each element in the array
// 		Do it by your self before that operation!

arr->size;				// Get size of the array
arr->cap;				// Get capacity of the array

// Note: Do not change `size` or `cap` by hands.
//		It will crash your program at future.
```

## Capacity based HashMap
```cpp
#include "map.c"

Map_str_hash(text);			// Create hash int from char* string

Map_new(cap);				// Create map with capacity
Map_set(map, hash, value);	// Set value for map at hash pos
Map_get(map, hash);			// Get value from hash

Map_free(map);				// Free all the map and entries

// Note: `Map_free` will not free the values. Do it manualy

arr->size;					// Get size of the map
arr->cap;					// Get capacity of the map

// Note: Do not change `arr` or `cap` values by hand
//		It will crash your program
```
* Sample
```cpp
// Helper function for shorter code
int s(char* s) {
	return Map_str_hash(s);
}

int main() {
	// Create Map with 32 capacity
	Map* map = Map_new(32);

	// Set A, B, C keys
	Map_set(map, s("A"), "This is first letter!");
	Map_set(map, s("B"), "The second letter!");
	Map_set(map, s("C"), "C is the last!");

	// Get A, B, C values
	char* a = Map_get(map, s("A"));
	char* b = Map_get(map, s("B"));
	char* c = Map_get(map, s("C"));

	// Get unknown value - will return Map_null
	int d = Map_get(map, s("---"));

	// Print all the values
	printf("%s %s %s %d\n", a, b, c, d);
}


```