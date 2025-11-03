// stdlib
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// local
#include "map.h"
#include "ulinkedlist.h"

#define MAX_BUCKETS 128

int hash_f(const char *key) {
  unsigned long hash = 5381;
  int c;

  while ((c = *key++))
    hash = ((hash << 5) + hash) + c;

  return hash % MAX_BUCKETS;
}

void set(map_t *map, char *key, void *val) {
  if (!map->buckets) {
    map->buckets = calloc(MAX_BUCKETS, sizeof(bucket_t *));
  }
  int bucket_id = hash_f(key);
  bucket_t *bucket = map->buckets[bucket_id];
  // if no bucket pointer will be NULL
  if (!bucket) {
    bucket_t *new_bucket = malloc(sizeof(bucket_t));
    ulinkedlist_t *list = malloc(sizeof(ulinkedlist_t));
    keyval_t *kv = malloc(sizeof(keyval_t));
    if (!new_bucket || !list || !kv) {
      free(new_bucket);
      free(list);
      free(kv);
      return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    map->cnt++;
    new_bucket->id = map->cnt;
    new_bucket->list = list;
    kv->key = key;
    kv->val = val;
    addAtTail(new_bucket->list, kv);
    new_bucket->size = new_bucket->list->length;
    map->buckets[bucket_id] = new_bucket;
    return;
  } else {
    keyval_t *kv = malloc(sizeof(keyval_t));
    if (!kv) {
      return;
    }
    kv->key = key;
    kv->val = val;
    addAtTail(bucket->list, kv);
    bucket->size = bucket->list->length;
    return;
  }
}

void *get(map_t *map, char *key) {
  if (!map->buckets) {
    return NULL;
  }
  int bucket_id = hash_f(key);
  bucket_t *bucket = map->buckets[bucket_id];
  if (!bucket) {
    return NULL;
  }
  unode_t *node = bucket->list->head;
  while (node != NULL) {
    keyval_t *kv = (keyval_t *)node->val;
    if (!strcmp(kv->key, key)) {
      return kv->val;
    }
    node = node->next;
  }
  return NULL;
}

bool exists(map_t *map, char *key) { return true; }

void delete(map_t *map, char *key) {}

void freeMap(map_t *map) {}

int main(void) {
  map_t *map = malloc(sizeof(map_t));
  map->cnt = 0;
  char *key = "key";
  int val = 5;
  set(map, key, &val);
  void *ret = get(map, key);
  int *ret_val = (int *)ret;
  printf("%i\n", *ret_val);
}
