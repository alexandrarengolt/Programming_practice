#include "../pool_allocator.h"
#include <assert.h>
#include <stdlib.h>

void tpool_init() {
  PoolAllocator allocator;
  pool_alloc_init(&allocator, 3, 4);

  assert(allocator.memory != NULL);
  assert(allocator.mem_block != NULL);

  pool_deinit(&allocator);
}

void tpool_free() {
  PoolAllocator allocator;
  pool_alloc_init(&allocator, 3, 4);

  void *block1 = pool_alloc(&allocator);
  void *block2 = pool_alloc(&allocator);

  assert(block1 != NULL);
  assert(block2 != NULL);

  pool_free(&allocator, block1);
  pool_free(&allocator, block2);

  Block *current_mem_block = allocator.mem_block;
  int free_count = 0;
  while (current_mem_block) {
    free_count++;
    current_mem_block = current_mem_block->next;
  }

  assert(free_count == 3);

  pool_deinit(&allocator);
}

void tpool_block_use_block_again() {
  PoolAllocator allocator;
  pool_alloc_init(&allocator, 3, 4);

  void *blocks[3];
  for (int i = 0; i < 3; ++i) {
    blocks[i] = pool_alloc(&allocator);
    assert(blocks[i] != NULL);
  }

  void *block_overflow = pool_alloc(&allocator);
  assert(block_overflow == NULL);

  pool_free(&allocator, blocks[1]);

  void *reused_block = pool_alloc(&allocator);
  assert(reused_block == blocks[1]);

  pool_deinit(&allocator);
}

void tpool_overflow_blocks() {
  PoolAllocator allocator;
  pool_alloc_init(&allocator, 3, 4);

  void *block1 = pool_alloc(&allocator);
  void *block2 = pool_alloc(&allocator);
  void *block3 = pool_alloc(&allocator);

  assert(block1 != NULL);
  assert(block2 != NULL);
  assert(block3 != NULL);

  void *block4 = pool_alloc(&allocator);
  assert(block4 == NULL);

  pool_deinit(&allocator);
}

int main() {
  tpool_init();
  tpool_free();
  tpool_block_use_block_again();
  tpool_overflow_blocks();
  return 0;
}