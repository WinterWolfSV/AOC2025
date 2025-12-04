#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int size = 138;

int magick(char** lines, int r, int c){
  int neighbours = 0;
  int i, j;
  for(i = -1; i <= 1; i++){
    if(r+i < 0 || r+i >= size) continue;
    for(j = -1; j <= 1; j++){
      if(c+j < 0 || c+j >= size) continue;
      if(!(i == 0 && j == 0) && lines[r+i][c+j] == '@'){
        neighbours++; 
      }
    }
  }
  return neighbours;
}

int fullRun(char** lines){
  int tot = 0;
  int i, j;
  bool removable[size * size];
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      if(lines[i][j] == '@' && magick(lines, i, j) < 4){
        tot++;
        removable[i*size + j] = 1;
      } else {
        removable[i*size + j] = 0;
      }
    }
  }
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      if(removable[i*size + j]){
        lines[i][j] = '.';
      }
    }
  }
  return tot;
}

int main(){
  char** lines = calloc((size+1), sizeof(char*));
  int ci = 0;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  int i, j;

  while((n = getline(&lines[ci], &n_, stdin)) != -1){
    if(n == 0 || n == 1) continue;
    if(lines[ci][n-1] == '\n'){
      lines[ci][n-1] = '\0';
      n--;
    }
    ci++;
  }

  while((n = fullRun(lines)) != 0){
    tot += n;
  }
  printf("tot: %lu",tot); 

  for(i = 0; i <= size; i++){
    free(lines[i]);
  }
  free(lines);
}
