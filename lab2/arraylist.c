#include "arraylist.h"
#include <string.h>

void arraylist_init(ArrayList *list, linear_allocator *allocator,
                    size_t element_size) {
  list->element_size = element_size;
  list->capacity = 4;
  list->size = 0;
  list->allocator = allocator;
  list->data = linear_allocator_alloc(allocator, list->capacity * element_size);
}

void arraylist_add(ArrayList *list, void *data) {
  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;
    void *new_data = linear_allocator_alloc(list->allocator,
                                            new_capacity * list->element_size);
    if (!new_data)
      return;
    memcpy(new_data, list->data, list->size * list->element_size);
    list->data = new_data;
    list->capacity = new_capacity;
  }
  memcpy((char *)list->data + list->size * list->element_size, data,
         list->element_size);
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (index >= list->size)
    return NULL;
  return (char *)list->data + index * list->element_size;
}

void arraylist_del(ArrayList *list) {
  if (list->size == 0)
    return;
  list->size--;
}

void arraylist_free(ArrayList *list) {
  list->size = 0;
  list->capacity = 0;
  list->data = NULL;
  list->allocator = NULL;
}
