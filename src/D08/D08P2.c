#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Node {
  int *p1;
  int *p2;
  long dist;
} Node;

typedef struct HashSet {
  long *keys;
  long *vals;
  int size;
  int mod;
} HashSet;

int compare(const void *a, const void *b) {
  long da = (*(Node * const *)a)->dist;
  long db = (*(Node * const *)b)->dist;
  return (da > db) - (da < db);
}

Node *createNode(int *p1, int *p2, long dist){
  Node *node = malloc(sizeof(*node));
  node->p1 = p1;
  node->p2 = p2;
  node->dist = dist; 
  return node;
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

void prepSet(HashSet *set, int **points, int size){
  int *p;
  for(int i = 0; i < size; i++){
    p = points[i];
    long pk = p[0]*100000000L + p[1]*10000L + p[2];
    insertSet(set, pk, i+1);
  }
}

int connect(HashSet *set, Node **list, int start, int amount){
  int *p1, *p2; 
  long p1k, p2k;
  long p1v, p2v;
  int i, j, size;
  size = 1;
  Node *p; 
  for(i = start; i < start + amount; i++){
    p = list[i];  
    p1 = p->p1;
    p2 = p->p2;
    p1k = p1[0]*100000000L + p1[1]*10000L + p1[2];
    p2k = p2[0]*100000000L + p2[1]*10000L + p2[2];
    p1v = getSet(set, p1k); 
    p2v = getSet(set, p2k); 
    if(p1v != -1 && p2v != -1 && p1v != p2v){
      for(j = 0; j < set->size; j++){
        if(set->vals[j] == p2v){
          set->vals[j] = p1v;
        }
      }
    } 
  }
  int tsize = 0;
  bool *count = calloc(set->size, sizeof(*count));

  for(i = 0; i < set->size; i++){
    if(set->vals[i] != 0 && !count[set->vals[i]]) {
      count[set->vals[i]] = 1;
      tsize++;
    }
  }
  free(count);
  return tsize;
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
  int i, j, k;

  while((n = getline(&line, &n_, stdin)) != -1){
    if(n > 0 && line[n-1] == '\n') line[n--] = '\0';
    if(!n) continue;
    point = malloc(3 * sizeof(*point));
    k = i = j = 0;
    while(line[i] != '\n'){
      if(line[i] == ',' || line[i] == '\n'){
        point[j++] = k;
        k = 0;
      } else {
        k = k*10 + line[i]-'0'; 
      }
      i++;
    } 
    point[j] = k;

    if(size + 1 == capacity){
      capacity *= 2; 
      points = realloc(points, capacity * sizeof(*points));
    }
    points[size++] = point;
  }
  HashSet *set = createSet(size*2);
  prepSet(set, points, size);

  capacity = size*(size-1)/2;
  Node **list = malloc(capacity * sizeof(*list));

  int counter = 0;
  for(i = 0; i < size; i++){
    p1 = points[i];
    for(j = i+1; j < size; j++){
      p2 = points[j];
      dist = pow(p1[0]-p2[0],2) + pow(p1[1]-p2[1],2) + pow(p1[2]-p2[2],2);
      if(counter < capacity){
        list[counter] = createNode(p1, p2, dist);
      } 
      counter++;
    }
  }

  qsort(list, capacity, sizeof(*list), compare);

  i = size;
  j = k = 0;
  while(k != 1){
    k = connect(set, list, j, i); 
    j = j+i;
    i = k-1;
  }
  j = j - 1;

  printf("%lu", list[j]->p1[0]*list[j]->p2[0]);

  free(line);
  for(i = 0; i < size; i++){
    free(points[i]);
  }
  free(points);
  for(i = 0; i < capacity; i++){
    free(list[i]);
  }
  free(list);
  free(set->keys);
  free(set->vals);
  free(set);
}

