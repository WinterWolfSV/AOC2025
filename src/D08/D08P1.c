// https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/ #include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Node {
  struct Node *next;
  struct Node *prev;
  int *p1;
  int *p2;
  long dist;
} Node;

typedef struct SortedList {
  int capacity;
  int size;

  int maxval;

  Node *first, *last;
} SortedList;

typedef struct HashSet {
  long *keys;
  long *vals;
  int size;
  int mod;
} HashSet;

int compare(const void *a, const void *b) {
  int *valA = a;
  int *valB = b;
  return *valB - *valA;
}

Node *createNode(int *p1, int *p2, long dist){
  Node *node = malloc(sizeof(*node));
  node->next = NULL;
  node->prev = NULL;
  node->p1 = p1;
  node->p2 = p2;
  node->dist = dist; 
  return node;
}

SortedList *createList(int capacity){
  SortedList *list = calloc(1, sizeof(*list));
  list->capacity = capacity;
  return list;
}

void insert(SortedList *list, Node *node){
  Node *p = list->first; 
  if(!p){
    list->first = node;
    list->last = node;
  } else if(p->dist > node->dist){
    node->next = p;
    p->prev = node;
    list->first = node;
  } else {
    while(p->next && node->dist > p->next->dist){
      p = p->next;
    }
    Node *tmp = p->next;
    if(!tmp){
      list->last = node;
      node->prev = p;
      p->next = node;
    } else {
      p->next = node;
      node->prev = p;
      node->next = tmp;
      tmp->prev = node;
    }
  }
  if(++(list->size) > list->capacity){
    p = list->last;
    list->last = p->prev;
    free(p);
    list->last->next = NULL;
    --(list->size);
  }
}

HashSet *createSet(int size){
  HashSet *set = malloc(sizeof(*set));
  set->keys = calloc(size, sizeof(*(set->keys)));
  set->vals = calloc(size, sizeof(*(set->vals)));
  set->size = size;
  set->mod = 127703;
  return set;
}

void insertSet(HashSet *set, long key, long val){
  unsigned int hash = (key + key * set->mod) % set->size;
  int i = 0;
  while(set->keys[hash + i]) {
    if(set->keys[hash + i] == key){
      break;
    }
    i++;
  }
  set->keys[hash + i] = key;
  set->vals[hash + i] = val;
}

long getSet(HashSet *set, long key){
  unsigned int hash = (key + key * set->mod) % set->size;
  int i = 0;
  while(set->keys[(hash + i) % set->size] != key) {
    if(!(set->keys[hash + i % set->size]))
      return -1;
    i++;
  }
  return set->vals[hash+i];
}

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 1;
  int *point;
  int *p1, *p2; 
  long dist;
  size_t capacity = 8;
  size_t size = 0;
  int **points = malloc(capacity * sizeof(*points));
  int i, j, tmp;

  while((n = getline(&line, &n_, stdin)) != -1){
    if(n > 0 && line[n-1] == '\n') line[n--] = '\0';
    if(!n) continue;
    point = malloc(3 * sizeof(*point));
    tmp = i = j = 0;
    while(line[i] != '\n'){
      if(line[i] == ',' || line[i] == '\n'){
        point[j++] = tmp;
        tmp = 0;
      } else {
        tmp = tmp*10 + line[i]-'0'; 
      }
      i++;
    } 
    point[j] = tmp;

    if(size + 1 == capacity){
      capacity *= 2; 
      points = realloc(points, capacity * sizeof(*points));
    }
    points[size++] = point;
  }
  capacity = size == 20 ? 10 : 1000;
  SortedList *list = createList(capacity);

  for(i = 0; i < size; i++){
    p1 = points[i];
    for(j = i+1; j < size; j++){
      p2 = points[j];
      dist = pow(p1[0]-p2[0],2) + pow(p1[1]-p2[1],2) + pow(p1[2]-p2[2],2);
      if(list->size < capacity || list->last && list->last->dist > dist){
        insert(list, createNode(p1, p2, dist));
      }
    }
  }

  Node *p = list->first;
  i = 1;
  long p1k, p2k;
  long p1v, p2v;
  HashSet *set = createSet(capacity*2);
  while(p){
    p1 = p->p1;
    p2 = p->p2;
    p1k = p1[0]*100000000L + p1[1]*10000L + p1[2];
    p2k = p2[0]*100000000L + p2[1]*10000L + p2[2];
    p1v = getSet(set, p1k); 
    p2v = getSet(set, p2k); 
    if(p1v == -1 && p2v == -1){
      insertSet(set, p1k, i); 
      insertSet(set, p2k, i); 
      i++;
    } else {
      if(p1v != -1 && p2v != -1){
        for(j = 0; j < set->size; j++){
          if(set->vals[j] == p2v){
            set->vals[j] = p1v;
          }
        }
      } else if(p1v == -1){
        insertSet(set, p1k, p2v);
      } else {
        insertSet(set, p2k, p1v);
      }
    }
    p = p->next;
  }

  int *counter = calloc(i, sizeof(*counter));
  for(j = 0; j < set->size; j++){
    if(set->vals[j] != 0){
      counter[set->vals[j]-1]++; 
    }
  }
  // Yes this causes a warning but it works.
  qsort(counter, i, sizeof(counter[0]), compare);
  for(j = 0; j < 3; j++){
    tot *= counter[j];
  }

  printf("%lu", tot);
  free(line);
}
