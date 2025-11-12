#include <limits.h>
#include <stdlib.h>

#include "local/linkedlist.h"
#include "local/queue.h"

int enqueue(queue_t *q, int val) { return addAtTail(&q->queue, &val); }

int dequeue(queue_t *q) {
  void *ptr = getByIndex(&q->queue, 0);
  int val = *(int *)ptr;
  if (val == INT_MIN) {
    return INT_MIN;
  }
  deleteAtIndex(&q->queue, 0);
  return val;
}

void freeQueue(queue_t *q) {
  freeLinkedList(&q->queue);
  free(q);
}
