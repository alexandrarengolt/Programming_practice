#define ARRAYLIST_H

#include "linear_allocator.h"

typedef struct {
    size_t element_size;
    size_t capacity;
    size_t size;
    void* data;
    linear_allocator* allocator;
} ArrayList;

void arraylist_init(ArrayList* list, linear_allocator* allocator, size_t element_size);
void arraylist_add(ArrayList* list, void* data);
void* arraylist_get(ArrayList* list, size_t index);
void arraylist_del(ArrayList* list);
void arraylist_free(ArrayList* list);
