#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  char* line = NULL;
  size_t n = 0;
  int i, curr, dist, tot;
  curr = 50;
  tot = 0;
  while(getline(&line, &n, stdin) != -1){
    i = 1;
    dist = 0;
    while(line[i] != '\n'){
     dist = dist*10 + (line[i]-'0');
     i++;
    }
    if(line[0] == 'R') {
      tot += (curr+dist) / 100;
      curr = (curr+dist) % 100;
    } else {
      tot += ((100 - curr) % 100 + dist) / 100;
      curr = (((curr - dist) % 100) + 100) % 100;
    }
  }
  printf("%d", tot);
}
