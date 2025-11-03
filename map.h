#ifndef HEAP_H
#define HEAP_H

// local
#include "ulinkedlist.h"

#define MAX_BUCKETS 128

typedef struct {
  char *key;
  void *val;
} keyval_t;

typedef struct {
  ulinkedlist_t *list;
  int size;
  int id;
} bucket_t;

typedef struct {
  bucket_t **buckets;
  int cnt;
} map_t;

#endif
