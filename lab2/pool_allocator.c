#include "pool_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void pool_alloc_init(PoolAllocator *allocator, size_t block_amount,
                     size_t size_per_block) {
  allocator->mem_block = NULL;
  allocator->block_amount = block_amount;
  allocator->size_per_block = size_per_block;
  allocator->memory =
      (char *)malloc((sizeof(Block) + size_per_block) * block_amount);

  if (!allocator->memory) {
    return;
  }

  char *current_mem_block = allocator->memory;
  for (size_t i = 0; i < block_amount; ++i) {
    Block *block = (Block *)current_mem_block;

    block->next = allocator->mem_block;
    allocator->mem_block = block;
    current_mem_block += sizeof(Block) + size_per_block;
  }
}

void *pool_alloc(PoolAllocator *allocator) {
  if (!allocator->mem_block) {
    return NULL;
  }

  Block *block = allocator->mem_block;
  allocator->mem_block = block->next;

  return (void *)(block + 1);
}

void pool_free(PoolAllocator *allocator, void *ptr) {
  if (!ptr) {
    return;
  }

  Block *block = ((Block *)ptr) - 1;

  block->next = allocator->mem_block;
  allocator->mem_block = block;
}

void pool_deinit(PoolAllocator *allocator) {
  if (allocator) {
    free(allocator->memory);
    allocator->size_per_block = 0;
    allocator->block_amount = 0;
    allocator->mem_block = NULL;
  }
}
