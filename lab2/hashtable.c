#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

static size_t compute_hash(const char *key) {
  size_t hash = 5381;
  int c;
  while ((c = *key++))
    hash = hash * 33 + c;
  return hash;
}

void hashtable_init(Hashtable *table, size_t capacity, size_t value_size,
                    PoolAllocator *allocator) {
  table->capacity = capacity;
  table->value_size = value_size;
  table->allocator = allocator;

  table->items = (HashtableItem *)calloc(capacity, sizeof(HashtableItem));
}

int hashtable_insert(Hashtable *table, const char *key, void *value) {
  if (!table || !key || !value)
    return -1;

  size_t start_index = compute_hash(key) % table->capacity;

  for (size_t i = 0; i < table->capacity; ++i) {
    size_t index = (start_index + i) % table->capacity;
    HashtableItem *item = &table->items[index];

    if (!item->is_occupied) {
      item->key = (char *)pool_alloc(table->allocator);
      if (!item->key)
        return -1;

      strcpy(item->key, key);

      item->value = pool_alloc(table->allocator);
      if (!item->value) {
        pool_free(table->allocator, item->key);
        return -1;
      }

      memcpy(item->value, value, table->value_size);
      item->is_occupied = 1;
      return 0;
    } else if (strcmp(item->key, key) == 0) {
      memcpy(item->value, value, table->value_size);
      return 0;
    }
  }
  return -1;
}

void *hashtable_get(Hashtable *table, const char *key) {
  if (!table || !key)
    return NULL;

  size_t start_index = compute_hash(key) % table->capacity;

  for (size_t i = 0; i < table->capacity; ++i) {
    size_t index = (start_index + i) % table->capacity;
    HashtableItem *item = &table->items[index];

    if (!item->is_occupied)
      return NULL;

    if (strcmp(item->key, key) == 0) {
      return item->value;
    }
  }
  return NULL;
}

void hashtable_delete(Hashtable *table, const char *key) {
  if (!table || !key)
    return;

  size_t start_index = compute_hash(key) % table->capacity;

  for (size_t i = 0; i < table->capacity; ++i) {
    size_t index = (start_index + i) % table->capacity;
    HashtableItem *item = &table->items[index];

    if (!item->is_occupied)
      return;

    if (strcmp(item->key, key) == 0) {
      pool_free(table->allocator, item->key);
      pool_free(table->allocator, item->value);
      item->key = NULL;
      item->value = NULL;
      item->is_occupied = 0;
      return;
    }
  }
}

void hashtable_cleanup(Hashtable *table) {
  if (!table || !table->items)
    return;

  for (size_t i = 0; i < table->capacity; ++i) {
    HashtableItem *item = &table->items[i];
    if (item->is_occupied) {
      pool_free(table->allocator, item->key);
      pool_free(table->allocator, item->value);
    }
  }

  free(table->items);
  table->items = NULL;
}
