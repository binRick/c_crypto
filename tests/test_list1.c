/*******************/
#include <stdio.h>
#include <stdlib.h>
/*******************/
#include "include/module_imports.h"
#include "src/deps.c"
/*******************/

typedef struct node {
  int         key;
  struct node *next;
} node_t;

node_t *l0 = NULL;


int cmp1(node_t *a, node_t *b){
  return(a->key - b->key);
}


int cmp2(node_t *a, node_t *b){
  return(b->key - a->key);
}

#define LIST_APPEND     SL_APPEND
#define LIST_PREPEND    SL_PREPEND
#define LIST_FOREACH    SL_FOREACH

#define LIST_ACTION_COMMON          \
  node_t *i;                        \
  i       = malloc(sizeof(node_t)); \
  i->key  = k;                      \
  i->next = NULL;                   \

#define POPULATE_LIST \
  APPEND_ITEM(10);    \
  APPEND_ITEM(5);     \
  APPEND_ITEM(200);   \
  PREPEND_ITEM(5);    \
  PREPEND_ITEM(1);    \
  APPEND_ITEM(169);   \

#define DO_PRINT_LIST()    {                    \
    node_t *ti; int i = 0;                      \
    LIST_FOREACH(l0, ti) {                      \
      log_debug("key #%d: %d", i + 1, ti->key); \
      i++;                                      \
    }                                           \
}                                               \

void PREPEND_ITEM(int k){
  LIST_ACTION_COMMON
  LIST_PREPEND(l0, i);
}


void APPEND_ITEM(int k){
  LIST_ACTION_COMMON
  LIST_APPEND(l0, i);
}


void dev(){
  dbg(123, % d);
}


int main(){
  log_debug("populating.....");
  POPULATE_LIST
  DO_PRINT_LIST();

  log_debug("sorting.....");
  SL_SORT(l0, cmp1);
  DO_PRINT_LIST();
  log_debug("sorted.....");

  log_debug("sorting.....");
  SL_SORT(l0, cmp2);
  DO_PRINT_LIST();
  log_debug("sorted.....");
  dev();
  return(0);
}
