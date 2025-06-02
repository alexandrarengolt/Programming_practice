#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
  int current;
  struct Item *next;
} Item;

Item *create_item(int data);
void push_start(Item **start_elem, int data);
void push_end(Item **start_elem, int data);
void push_middle(Item **start_elem, int data, int index);
void delete_item(Item **start_elem, int value);
Item *find_item(Item *start_elem, int index);
int count_elem(Item *start_elem);
