#include "../stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

void tstack_empty_stack() {
  stack stack;
  init(&stack, 5);

  bool result = is_empty(&stack);

  assert(result == true);
  free(stack.array);
}

void tstack_push() {
  stack stack;
  int output;
  init(&stack, 5);

  push(&stack, 1);
  int result = peek(&stack, &output);

  assert(output == 1);
  assert(result == SUCCESS);
  free(stack.array);
}

void tstack_empty_pop() {
  stack stack;
  int output;
  init(&stack, 5);

  int result = pop(&stack, &output);

  assert(result == STACKUNDERFLOW);
  free(stack.array);
}

void tstack_pop() {
  stack stack;
  int output;
  init(&stack, 5);

  push(&stack, 1);
  push(&stack, 2);
  pop(&stack, &output);
  int result = peek(&stack, &output);

  assert(output == 1);
  assert(result == SUCCESS);
  free(stack.array);
}

void tstack_full_stack() {
  stack stack;
  int output;
  init(&stack, 5);

  for (int i = 1; i <= stack.size + 1; i++) {
    push(&stack, i);
  }
  int result = peek(&stack, &output);

  assert(output == 5);
  assert(is_full(&stack) == true);
  free(stack.array);
}

void tstack_full_stack_error_output() {
  stack stack;
  int output;
  init(&stack, 1);

  push(&stack, 1);
  int result = push(&stack, 2);

  assert(result == STACKOVERFLOW);
}

void tstack_empty_peek() {
  stack stack;
  int output;
  init(&stack, 5);

  int result = peek(&stack, &output);

  assert(result == STACKUNDERFLOW);
  free(stack.array);
}

int main() {
  tstack_empty_stack();
  tstack_push();
  tstack_empty_pop();
  tstack_pop();
  tstack_full_stack();
  tstack_full_stack_error_output();
  tstack_empty_peek();
  return 0;
}
