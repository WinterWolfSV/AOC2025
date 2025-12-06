#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int maxlines = 6;
  char** lines = calloc(maxlines,sizeof(*lines));
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  unsigned long temp;
  int i, j, size;
  int arr[8] = {0};
  
  size = 0;

  while((n = getline(&lines[size], &n_, stdin)) != -1){
    if(n > 0 && lines[size][n-1] == '\n') lines[size][--n] = '\0';
    if(!n) continue;
    size++;
    j = n;
  }

  size--;
  n = 0;
  for(i = j-1; i >= 0; i--){ 
    temp = 0;
    for(j = 0; j < size; j++){
      if(lines[j][i] == ' ') continue;
      arr[n] =  arr[n]*10 + lines[j][i] - '0';
    }
    n++;
    
    if(lines[size][i] != ' '){
      for(j = 0; j < n; j++){
        if(lines[size][i] == '*'){
          if(temp == 0) temp++;
          temp *= arr[j]; 
        } else if(lines[size][i] == '+'){
          temp += arr[j];
        }
        arr[j] = 0;
      }
      n = 0;
      i--;
    }
    tot += temp;
  }

  printf("%lu", tot);

  for(i = 0; i < maxlines; i++){
    free(lines[i]);
  }
  free(lines);
}
