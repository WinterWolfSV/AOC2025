#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gosper(int val){
  int c = val & -val; 
  int r = val + c;
  int ret = (((r ^ val) >> 2) / c) | r;
  return ret;
}

int main(){
  char* line = NULL;
  size_t n_ = 0;
  ssize_t n;
  unsigned long tot = 0;
  size_t capacity = 8;
  int i, j, k, tmp, stage, target;
  int numlamps;
  int numbtn;
  int btns[16]; 

  while((n = getline(&line, &n_, stdin)) != -1){
    if(n > 0 && line[n-1] == '\n') line[--n] = '\0';
    if(!n) continue;
    i = j = k = 0;
    numbtn = numlamps = stage = target = 0;

    char *p = line;
    while(*p){
      if(*p == ' ') {
        p++;
        continue;
      };
      if(stage == 0) {
        if(*p == ']') {
          target = target >> 1;
          stage++;
          numlamps--;
        } 
        else {
          target += *p == '#';
          target = target << 1;
          numlamps++;
        }
      }
      else {
        if(*p == '{') stage++;
        if(*p == '('){
          p++;
          j = 0;
          while(*p && *p != ')'){
            if('0' <= *p && *p <= '9'){
              j += 1<<(numlamps-1-(*p-'0'));
            }
            p++;
          }
          btns[numbtn++] = j;
        }
      }
      p++;
    }

    int max = 1 << numbtn;
    int val;
    for(i = 1; i <= numbtn ; i++){
      tmp = (1<<i) - 1;
      while(tmp < max){
        val = 0;
        for(j = 0; j < numbtn; j++){
          if(tmp & (1 << j)) {
            val = val ^ btns[j]; 
          }
        }
        if(val == target)
          goto found;
        tmp = gosper(tmp);
      }
    }
found:
    tot += i;
  }
  printf("%lu", tot);
  free(line);
}
