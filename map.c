#include <stdlib.h>

/*
	Map with capacity
	---

	Map_str_hash(text);			// Create hash int from char* string

	Map_new(cap);				// Create map with capacity
	Map_set(map, hash, value);	// Set value for map at hash pos
	Map_get(map, hash);			// Get value from hash
	Map_free(map);				// Free all the map and entries

	arr->size;					// Get size of the map
	arr->cap;					// Get capacity of the map
*/

typedef struct {
	int keyId;
	void* elem;
} MapEntry;

typedef struct {
	MapEntry** entries;
	int size;
	int cap;
} Map;


#define Map_null 0
#define Map_fail 0
#define Map_success 1

static void __map_grow_when_cap(Map *map) {
	int cap = map->cap;
	int size = map->size;
	if (size == 0) return;
	if (size != cap) return;
	map->cap = cap * 2;
	MapEntry** newEntries = malloc(sizeof(MapEntry*) * map->cap);
	for (int i = 0; i < size; i++) {
		newEntries[i] = map->entries[i];
	}
	free(map->entries);
	map->entries = newEntries;
}

Map* Map_new(int cap) {
	if (cap < 4) cap = 4;
	Map* m = malloc(sizeof(Map));
	m->size = 0;
	m->cap = cap;
	m->entries = malloc(sizeof(MapEntry*) * cap);
	return m;
}

void Map_set(Map* m, int key, void* elem) {
	int size = m->size;
	for (int i = 0; i < size; i++) {
		MapEntry* e = m->entries[i];
		if (e->keyId == key) {
			e->elem = elem;
			return;
		}
	}

	__map_grow_when_cap(m);
	MapEntry* e = malloc(sizeof(MapEntry));
	e->keyId = key;
	e->elem = elem;
	m->entries[m->size] = e;
	m->size += 1;
}

void* Map_get(Map* m, int key) {
	int size = m->size;
	for (int i = 0; i < size; i++) {
		MapEntry* e = m->entries[i];
		if (e->keyId == key) {
			return e->elem;
		}
	}
	return Map_null;
}

void Map_free(Map* m) {
	for (int i = 0; i < m->size; i++) {
		free(m->entries[i]);
	}
	free(m->entries);
	free(m);
}

int Map_str_hash(char *str)
{
	int hash = 5381;
	int c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}