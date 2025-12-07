#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  int i;

  n = getline(&line, &n_,stdin);
  bool *last, *curr, *tmp;
  last = calloc((n-1),sizeof(bool));
  curr = calloc((n-1),sizeof(bool));

  for(i = 0; i < n-1; i++){
    if(line[i] == 'S'){
      last[i] = 1;
      break;
    }
  }

  while((n = getline(&line, &n_, stdin)) != -1){
    if(n > 0 && line[n-1] == '\n') line[n--] = '\0';
    if(!n) continue;

    for(i = 0; i < n; i++){
      if(last[i]){
        if(line[i] == '^'){
          curr[i+1] = 1; 
          curr[i-1] = 1;
          tot++;
        } else {
          curr[i] = 1;
        } 
      } 
    }

    tmp = last;
    last = curr;
    curr = tmp;
    memset(curr, 0, n*sizeof(*curr));
  }
  printf("%lu", tot);
  free(line);
}
