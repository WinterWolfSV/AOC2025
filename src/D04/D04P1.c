#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void apply(int i, int* arr){
  arr[i-1]++;
  arr[i]++;
  arr[i+1]++;
}

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  int i, j;

  int *u, *d;
  char *last = NULL;

  while((n = getline(&line, &n_, stdin)) != -1){
    if(line[n-1] == '\n'){
      line[n-1] = '\0';
      n--;
    }
    if(n == 0) continue;
    if(!last){ 
      last = calloc(n, sizeof(char*));
      u = calloc(n+2, sizeof(int*));
      d = calloc(n+2, sizeof(int*));
    }
    for(i = 0; i < n; i++){
      j = i+1;
      if(last[i] == '@'){
        apply(j, u);
        apply(j, d);
      }    
      if(line[i] == '@'){
        apply(j, u);
      }
    }
    for(i = 0; i < n; i++){
      if(last[i] == '@' && u[i+1] < 5) tot++;
    }
    free(u);
    u = d;
    d = calloc(n+2, sizeof(int*));
    strcpy(last, line);
  }
  i = 0;
  while((j = last[i]) != '\0'){
    if(j == '@'){
      apply(i+1, u);
    }
    i++;
  }
  i = 0;
  while((j = last[i]) != '\0'){
    if(j == '@' && u[i+1] < 5) tot ++;
    i++;
  }

  printf("%lu", tot);
  free(line);
  free(last);
  free(u);
  free(d);
}
