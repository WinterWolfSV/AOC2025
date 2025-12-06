#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int maxlines = 5;
  char* line = NULL;
  int** lines = malloc(maxlines*sizeof(*lines));
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  unsigned long temp;
  int i, j, size;
  
  size = 0;

  while((n = getline(&line, &n_, stdin)) != -1){
    while(n > 0 && line[n-1] == '\n' || line[n-1] == ' ') line[--n] = '\0';
    if(!n) continue;
    i = 0;
    j = 0;
    while(line[i] == ' ') i++; 
    lines[size] = calloc(n,sizeof(int));
    while(line[i] != '\0'){
      if(line[i] == ' '){
        while (line[++i] == ' ');
        i--;
        j++; 
      } else {
        lines[size][j] = lines[size][j]*10+ line[i]-'0'; 
      }
      i++;
    }
    size++;
  }
  size--;

  i = 0;
  while(lines[size][i] != 0){
    temp = 0;
    for(j = 0; j < size; j++){
      if(lines[size][i] == '*'-'0'){
        if(temp == 0) temp++;
        temp *= lines[j][i]; 
      } else {
        temp += lines[j][i];
      }
    }
    tot += temp;
    i++;
  }

  printf("%lu", tot);

  for(i = 0; i < maxlines; i++){
    free(lines[i]);
  }
  free(lines);
  free(line);
}
