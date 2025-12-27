#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  int capacity = 8;
  int size = 0;
  int **points = malloc(capacity * sizeof(*points));
  int *point;
  int i, j;

  while((n = getline(&line, &n_, stdin)) != -1){
    while(n > 0 && (line[n-1] == '\n' || line[n-1] == ' ')) line[--n] = '\0';
    if(!n) continue;
    
    if(size + 1 >= capacity){
      capacity *= 2;
      points = realloc(points, capacity*sizeof(*points));
    }
     
    point = calloc(2 , sizeof(*point));
    i = j = 0;
    while(line[i] != '\0'){
      if(line[i] == ',') j++;
      else point[j] = point[j]*10 + line[i]-'0';
      i++;
    }
    points[size++] = point;
  }
  long a, max = 0;
  for(i = 0; i < size; i++){
    for(j = i+1; j < size; j++){
      a = (labs(points[i][0]-points[j][0])+1) * (labs(points[i][1]-points[j][1])+1);
      if(a > max) max = a;
    }
  }
  printf("%ld", max);
  free(line);
}
