#include <stdio.h>
#include <stdlib.h>

int main(){
  char* line = NULL;
  size_t n = 0;
  int i, sum, temp, tot;
  sum = 50;
  tot = 0;
  while(getline(&line, &n, stdin) != -1){
    i = 1;
    temp = 0;
    while(line[i] != '\n'){
     temp = temp*10 + (line[i]-'0');
     i++;
    }
    sum += line[0] == 'R' ? temp : -temp;
    if(sum%100 == 0){
      tot++;
    }
  }
  printf("%d", tot);
}
