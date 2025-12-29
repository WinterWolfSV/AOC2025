#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long check(int **points, int size, int *p1, int *p2, long max){
  int *last, *curr, ofs;
  long ext[4];
  ext[0] = p1[0] < p2[0] ? p1[0] : p2[0]; //min x
  ext[1] = p1[0] > p2[0] ? p1[0] : p2[0]; //max x
  ext[2] = p1[1] < p2[1] ? p1[1] : p2[1]; //min y
  ext[3] = p1[1] > p2[1] ? p1[1] : p2[1]; //max y
  long area = (ext[1]-ext[0]+1)*(ext[3]-ext[2]+1);
  if(area <= max) return -1;
  last = points[0];
  for(int i = 1; i < size + 1; i++){ // Checks if the line between the last and current point pass through the square. 
    curr = points[i%size]; 
    ofs = last[0] == curr[0]; // Looks more scary than it actually is. If x are equal, y is compared and vice versa. 
    if(ext[(!ofs)*2] < last[!ofs] && last[!ofs] < ext[(!ofs)*2+1] &&
        (last[ofs] <= ext[ofs*2] && ext[ofs*2] < curr[ofs] || 
         last[ofs] > ext[ofs*2] && ext[ofs*2] >= curr[ofs] || 
         last[ofs] < ext[ofs*2+1] && ext[ofs*2+1] <= curr[ofs] || 
         last[ofs] >= ext[ofs*2+1] && ext[ofs*2+1] > curr[ofs])) return -1;
    last = curr;
  }
  return area;
}

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
      a = check(points, size, points[i], points[j], max);  
      if(a > max) max = a;
    }

  }
  printf("%ld", max);
  free(line);
}
