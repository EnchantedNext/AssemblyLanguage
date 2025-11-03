#ifndef ULINKEDLIST_H
#define ULINKEDLIST_H

typedef struct unode_t unode_t;

struct unode_t {
  void *val;
  unode_t *next;
};

typedef struct {
  unode_t *head;
  unode_t *tail;
  int length;
} ulinkedlist_t;

int addAtTail(ulinkedlist_t *list, void *val);

int addAtHead(ulinkedlist_t *list, void *val);

int addAtIndex(ulinkedlist_t *list, void *val, int idx);

void *getByIndex(ulinkedlist_t *list, int idx);

int deleteAtIndex(ulinkedlist_t *list, int idx);

void freeLinkedList(ulinkedlist_t *list);

#endif
