#include "linear_allocator.h"

linear_allocator *linear_allocator_init(size_t size) {
  linear_allocator *allocator =
      (linear_allocator *)malloc(sizeof(linear_allocator));
  if (!allocator)
    return NULL;
  allocator->memory_block = malloc(size);
  if (!allocator->memory_block) {
    free(allocator);
    return NULL;
  }
  allocator->total_size = size;
  allocator->offset = 0;
  return allocator;
}

void linear_allocator_deinit(linear_allocator *allocator) {
  if (allocator) {
    free(allocator->memory_block);
    free(allocator);
  }
}

void *linear_allocator_alloc(linear_allocator *allocator, size_t size) {
  if (size == 0) {
    return NULL;
  }

  if (!allocator || allocator->offset + size > allocator->total_size) {
    return NULL;
  }

  void *ptr = (char *)allocator->memory_block + allocator->offset;
  allocator->offset += size;
  return ptr;
}

void linear_allocator_reset(linear_allocator *allocator) {
  if (allocator) {
    allocator->offset = 0;
  }
}
