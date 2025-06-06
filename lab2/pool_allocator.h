#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stddef.h>

typedef struct Block {
  struct Block *next;
} Block;

typedef struct {
  char *memory;
  size_t block_amount;
  size_t size_per_block;
  Block *mem_block;
} PoolAllocator;

void pool_alloc_init(PoolAllocator *allocator, size_t count, size_t size_per_block);
void* pool_alloc(PoolAllocator *allocator);
void pool_free(PoolAllocator *allocator, void *ptr);
void pool_deinit(PoolAllocator *allocator);

#endif
