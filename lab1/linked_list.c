#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Item *create_item(int data) {
  Item *new_item = (Item *)malloc(sizeof(Item));
  new_item->current = data;
  new_item->next = NULL;
  return new_item;
}

void push_start(Item **start_elem, int data) {
  Item *new_item = create_item(data);
  new_item->next = *start_elem;
  *start_elem = new_item;
}

void push_end(Item **start_elem, int data) {
  Item *new_item = create_item(data);
  if (*start_elem == NULL) {
    *start_elem = new_item;
    return;
  }
  Item *temp_start_elem = *start_elem;
  while (temp_start_elem->next != NULL) {
    temp_start_elem = temp_start_elem->next;
  }
  temp_start_elem->next = new_item;
}

void push_middle(Item **start_elem, int data, int index) {
  if (index <= 0) {
    return;
  }
  Item *new_item = create_item(data);
  Item *temp_start_elem = *start_elem;
  for (int i = 0; i < index - 1; i++) {
    if (temp_start_elem == NULL) {
      return;
    }
    temp_start_elem = temp_start_elem->next;
  }
  new_item->next = temp_start_elem->next;
  temp_start_elem->next = new_item;
}

void delete_item(Item **start_elem, int value) {
  Item *temp_start_elem = *start_elem;
  Item *prev = NULL;
  if (temp_start_elem != NULL && temp_start_elem->current == value) {
    *start_elem = temp_start_elem->next;
    free(temp_start_elem);
    return;
  }
  while (temp_start_elem != NULL && temp_start_elem->current != value) {
    prev = temp_start_elem;
    temp_start_elem = temp_start_elem->next;
  }
  if (temp_start_elem == NULL) {
    return;
  }
  prev->next = temp_start_elem->next;
  free(temp_start_elem);
}

Item *find_item(Item *start_elem, int index) {
  int count = 0;
  Item *temp_start_elem = start_elem;
  while (temp_start_elem != NULL) {
    if (count == index) {
      return temp_start_elem;
    }
    count++;
    temp_start_elem = temp_start_elem->next;
  }
  return NULL;
}

int count_elem(Item *start_elem) {
  int count = 0;
  Item *temp_start_elem = start_elem;
  while (temp_start_elem != NULL) {
    count++;
    temp_start_elem = temp_start_elem->next;
  }
  return count;
}
