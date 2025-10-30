// stdlib
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// local
#include "linkedlist.h"

#include "stack.h"

int push(stack_t *st, int val) { return addAtTail(&st->stack, val); }

int pop(stack_t *st) {
  int val = getByIndex(&st->stack, -1);
  if (val == INT_MIN) {
    return INT_MIN;
  }
  deleteAtIndex(&st->stack, -1);
  return val;
}

int peek(stack_t *st) {
  int val = getByIndex(&st->stack, -1);
  if (val == INT_MIN) {
    return INT_MIN;
  }
  return val;
}

void freeStack(stack_t *st) {
  freeLinkedList(&st->stack);
  free(st);
}
