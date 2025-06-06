#include "../hashtable.h"
#include "../pool_allocator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void thashtable_insert() {
  PoolAllocator allocator;
  Hashtable table;

  pool_alloc_init(&allocator, 1024, sizeof(HashtableItem));

  hashtable_init(&table, 8, sizeof(int), &allocator);

  int val1 = 1;
  int val2 = 2;

  hashtable_insert(&table, "key", &val1);
  hashtable_insert(&table, "second_key", &val2);

  int *result1 = (int *)hashtable_get(&table, "key");
  int *result2 = (int *)hashtable_get(&table, "second_key");

  assert(result1 && *result1 == 1);
  assert(result2 && *result2 == 2);

  hashtable_cleanup(&table);
  pool_deinit(&allocator);
}

void thashtable_update() {
  PoolAllocator allocator;
  Hashtable table;

  pool_alloc_init(&allocator, 1024, sizeof(HashtableItem));
  hashtable_init(&table, 8, sizeof(int), &allocator);

  int old_value = 1;
  int new_value = 2;

  hashtable_insert(&table, "key1", &old_value);
  hashtable_insert(&table, "key1", &new_value);

  int *res = (int *)hashtable_get(&table, "key1");
  assert(res && *res == new_value);

  hashtable_cleanup(&table);
  pool_deinit(&allocator);
}

void thashtable_delete_item() {
  PoolAllocator allocator;
  Hashtable table;

  pool_alloc_init(&allocator, 1024, sizeof(HashtableItem));
  hashtable_init(&table, 8, sizeof(int), &allocator);

  int val = 1;

  hashtable_insert(&table, "key", &val);
  hashtable_delete(&table, "key");

  assert(hashtable_get(&table, "key") == NULL);

  hashtable_cleanup(&table);
  pool_deinit(&allocator);
}

void thashtable_get_undefined_key() {
  PoolAllocator allocator;
  Hashtable table;

  pool_alloc_init(&allocator, 1024, sizeof(HashtableItem));
  hashtable_init(&table, 8, sizeof(int), &allocator);

  assert(hashtable_get(&table, "undefined_key") == NULL);

  hashtable_cleanup(&table);
  pool_deinit(&allocator);
}

void thashtable_collision() {
  PoolAllocator allocator;
  Hashtable table;

  pool_alloc_init(&allocator, 1024, sizeof(HashtableItem));
  hashtable_init(&table, 8, sizeof(int), &allocator);

  int a = 1, b = 2;

  hashtable_insert(&table, "1", &a);
  hashtable_insert(&table, "2", &b);

  int *x = (int *)hashtable_get(&table, "1");
  int *y = (int *)hashtable_get(&table, "2");

  assert(x && *x == 1);
  assert(y && *y == 2);

  hashtable_cleanup(&table);
  pool_deinit(&allocator);
}

int main() {
  thashtable_insert();
  thashtable_update();
  thashtable_delete_item();
  thashtable_get_undefined_key();
  thashtable_collision();
  return 0;
}
