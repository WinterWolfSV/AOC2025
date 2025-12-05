#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  unsigned long val;
  unsigned long *l, *h;
  bool hasRanges = false;
  int i, size, capacity;
  size = 0;
  capacity = 8;
  l = malloc(capacity*sizeof(long));
  h = malloc(capacity*sizeof(long));

  while((n = getline(&line, &n_, stdin)) != -1){
    if(line[n-1] == '\n'){
      line[n-1] = '\0';
      n--;
    }
    if(!hasRanges && n != 0){
      i = 0;
      while(line[i] != '-') i++;
      line[i] = '\0'; 
      if(size + 1 > capacity){
        l = realloc(l, capacity*2*sizeof(long));
        h = realloc(h, capacity*2*sizeof(long));
        capacity *= 2;
      }
      l[size] = atol(line);
      h[size] = atol(line+i+1);
      for(i = 0; i < size; i++){
        if(l[size] >= l[i] && l[size] <= h[i]){
          l[size] = h[i] + 1;
        }
        if(h[size] >= l[i]  && h[size] <= h[i]){
          h[size] = l[i] - 1;
        }
        if(l[size] <= l[i] && h[size] >= h[i] && h[i] >= l[i]){
          tot -= h[i]-l[i] + 1;
        }
      }
      if(l[size] <= h[size]){
        tot += h[size]-l[size] + 1;
      }
      size++;
    } else break;
  }

  printf("%lu", tot);
  free(line);
  free(l);
  free(h);
}
