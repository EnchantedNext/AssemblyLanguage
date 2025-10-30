#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node_t node_t;

struct node_t {
  int val;
  node_t *next;
};

typedef struct {
  node_t *head;
  node_t *tail;
  int length;
} linkedlist_t;

int addAtTail(linkedlist_t *list, int val);

int addAtHead(linkedlist_t *list, int val);

int addAtIndex(linkedlist_t *list, int val, int idx);

int getByIndex(linkedlist_t *list, int idx);

int deleteAtIndex(linkedlist_t *list, int idx);

void freeLinkedList(linkedlist_t *list);

#endif
