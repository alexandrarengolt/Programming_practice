#define HASHTABLE_H
#include "pool_allocator.h"

typedef struct {
  char *key;
  void *value;
  int is_occupied;
} HashtableItem;

typedef struct {
  HashtableItem *items;
  size_t capacity;
  size_t value_size;
  PoolAllocator *allocator;
} Hashtable;

void hashtable_init(Hashtable *table, size_t capacity, size_t value_size,
                    PoolAllocator *allocator);
int hashtable_insert(Hashtable *table, const char *key, void *value);
void *hashtable_get(Hashtable *table, const char *key);
void hashtable_delete(Hashtable *table, const char *key);
void hashtable_cleanup(Hashtable *table);
