#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  int i, a, b;

  while((n = getline(&line, &n_, stdin)) != -1){
    if(line[n-1] == '\n'){
      line[n-1] = '\0';
      n--;
    }
    if(n == 0) continue; 
    a = 0;
    b = 0;
    for(i = 0; i < n - 1; i++){
      if(a < line[i]){
        a = line[i];
        b = 0;
      } else if( b < line[i]){
        b = line[i];
      }
    }
    if (b < line[i]){
      b = line[i];
    }
    tot += (a-'0') * 10 + b-'0';
  }
  printf("%lu\n", tot);
  free(line);
}
