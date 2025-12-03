#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  int s = 12;
  int i, j, k;
  int a[s];

  while((n = getline(&line, &n_, stdin)) != -1){
    if(line[n-1] == '\n'){
      line[n-1] = '\0';
      n--;
    }
    if(n == 0) continue; 
    a[0] = 0;
    for(i = 0; i < n ; i++){
      for(j = (i > n-s ? i-n+s : 0); j < s; j++){
        if(a[j] < line[i]){
          for(k = j+1; k < s; k++){
            a[k] = 0;
          }
          a[j] = line[i];
          break;
        } 
      }
    }
    for(i = 0; i < s; i++){
      tot += (a[i]-'0')*pow(10, s-i-1);
    }
  }
  printf("%lu\n", tot);
  free(line);
}
