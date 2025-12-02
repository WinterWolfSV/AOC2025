#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int digCount(long n){
  if(n == 0) return 1;
  int i = 0; 
  while (n != 0){
    n /= 10;
    i++;
  }  
  return i;
}

// number to split, count of digits, length to split at, array with digits
void splitNum(long n, int c, int l, long* vals){
  int i, div;

  div = (int)pow(10, l);
  for(i = 0; i < c/l; i++){
    vals[i] = n % div;
    n = n / div;
  }
}

unsigned long getInvalids(long a, long b){
  unsigned long tot;
  int n, i, j;
  tot = 0;
  n = digCount(b);
  long vals[n];
  while (a <= b){
    n = digCount(a);
    for(i = 1; i < n; i++){
      if(n%i == 0){
        splitNum(a, n, i, vals);
        for(j = 0; j < n/i-1; j++){
          if(vals[j] != vals[j+1]){
            goto next_i;
          }
        }
        tot += a;
        break;
      }
next_i:
    }
    a++; 
  }
  return tot;
}

int main(){
  char* line = NULL;
  size_t n = 0;
  ssize_t s;
  unsigned long tot, d1, d2;
  int i;
  tot = 0;
  while((s = getdelim(&line, &n, ',', stdin)) != -1){
    i = 0;
    if(n>0 && line[s-1] == ',' || line[s-1] == '\n'){
      line[s-1] = '\0';
      s--;
    }
    while(line[i] != '-') { 
      i++;
    }
    line[i] = '\0';

    d1 = atol(line);
    d2 = atol(line+i+1);

    tot += getInvalids(d1,d2); 
  }
  printf("%lu\n", tot);
}
