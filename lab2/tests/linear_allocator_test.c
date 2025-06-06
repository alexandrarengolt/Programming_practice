#include "../linear_allocator.h"
#include <assert.h>
#include <stdlib.h>

void linear_allocator_init_test() {
  size_t size = 2 * 1024;
  linear_allocator *alloc = linear_allocator_init(size);

  assert(alloc != NULL);
  assert(alloc->memory_block != NULL);
  assert(alloc->total_size == size);
  assert(alloc->offset == 0);

  linear_allocator_deinit(alloc);
}

void linear_allocator_reset_test() {
  size_t size = 2 * 1024;
  linear_allocator *alloc = linear_allocator_init(size);

  void *ptr1 = linear_allocator_alloc(alloc, sizeof(void *));
  linear_allocator_reset(alloc);
  void *ptr2 = linear_allocator_alloc(alloc, sizeof(void *));

  assert(ptr1 == ptr2);
  linear_allocator_deinit(alloc);
}

void linear_allocator_alloc_test() {
  linear_allocator *alloc = linear_allocator_init(2 * 1024);

  int *ptr1 = linear_allocator_alloc(alloc, sizeof(int));
  assert(ptr1 != NULL);

  *ptr1 = 1;
  assert(*ptr1 == 1);
  assert(alloc->offset == sizeof(int));

  int *ptr2 = linear_allocator_alloc(alloc, sizeof(int));
  assert(ptr2 != NULL);

  *ptr2 = 2;
  assert(*ptr2 == 2);
  assert(alloc->offset == sizeof(int) + sizeof(int));

  linear_allocator_deinit(alloc);
}

void linear_allocator_out_of_memory_test() {
  size_t size = 2 * 1024;
  linear_allocator *alloc = linear_allocator_init(size);

  int *ptr = linear_allocator_alloc(alloc, 3 * 1024);

  assert(ptr == NULL);
  linear_allocator_deinit(alloc);
}

void linear_allocator_null_pointer() {
  size_t size = 2 * 1024;
  linear_allocator *alloc = linear_allocator_init(size);

  int *ptr = linear_allocator_alloc(alloc, 0 * 1024);

  assert(ptr == NULL);

  linear_allocator_deinit(alloc);
}

int main() {
  linear_allocator_init_test();
  linear_allocator_alloc_test();
  linear_allocator_out_of_memory_test();
  linear_allocator_reset_test();
  linear_allocator_null_pointer();
  return 0;
}
