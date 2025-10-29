#include <limits.h>
#include <stdlib.h>

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

int addHeadToEmpty(linkedlist_t *this, int val) {
  this->length++;
  node_t *head = malloc(sizeof(node_t));
  head->val = val;
  head->next = NULL;
  this->head = head;
  this->tail = head;
  return 0;
}

int addAtTail(linkedlist_t *this, int val) {
  if (!this->length) {
    return addHeadToEmpty(this, val);
  }
  node_t *node = malloc(sizeof(node_t));
  node->val = val;
  node->next = NULL;
  this->tail->next = node;
  this->tail = this->tail->next;
  this->length++;
  return 0;
}

int addAtHead(linkedlist_t *this, int val) {
  if (!this->length) {
    return addHeadToEmpty(this, val);
  }
  node_t *node = malloc(sizeof(node_t));
  node->val = val;
  node->next = this->head;
  this->head = node;
  this->length++;
  return 0;
}

node_t *findNode(linkedlist_t *this, int idx) {
  node_t *node = this->head;
  for (int i = 0; i < idx; i++) {
    node = node->next;
  }
  return node;
}

int addAtIndex(linkedlist_t *this, int val, int idx) {
  if (idx > this->length) {
    return -1;
  }
  if (idx == -1) {
    return addAtTail(this, val);
  } else if (idx == 0) {
    return addAtHead(this, val);
  }
  node_t *node = findNode(this, idx - 1);
  node_t *new_node = malloc(sizeof(node_t));
  new_node->val = val;
  new_node->next = node->next;
  node->next = new_node;
  this->length++;
  return 0;
}

int getByIndex(linkedlist_t *this, int idx) {
  if (idx >= this->length || idx < -1) {
    return INT_MIN;
  } else if (idx == 0) {
    return this->head->val;
  } else if (idx == -1) {
    return this->tail->val;
  }
  node_t *node = findNode(this, idx);
  return node->val;
}

int deleteAtIndex(linkedlist_t *this, int idx) {
  if (!this->length) {
    return -1;
  }
  if (idx >= this->length || idx < -1) {
    return -1;
  }
  if (idx == 0) {
    node_t *toDelete = this->head;
    this->head = this->head->next;
    if (!this->head) {
      this->tail = NULL;
    }
    this->length--;
    free(toDelete);
    return 0;
  } else if (idx == -1 || idx == this->length - 1) {
    node_t *node = findNode(this, this->length - 2);
    node_t *next = node->next;
    node->next = NULL;
    this->tail = node;
    this->length--;
    free(next);
    return 0;
  }
  node_t *node = findNode(this, idx - 1);
  node_t *next = node->next;
  node->next = node->next->next;
  this->length--;
  free(next);
  return 0;
}

void freeLinkedList(linkedlist_t *this) {
  node_t *node = this->head;
  node_t *next;
  while (node != NULL) {
    next = node->next;
    free(node);
    node = next;
  }
  this->head = NULL;
  this->tail = NULL;
  this->length = 0;
}

int main(void) { return 0; }
