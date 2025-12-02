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

unsigned long getInvalids(long a, long b){
  unsigned long tot;
  int n;
  tot = 0;
  while (a <= b){
    n = digCount(a);
    if(!(n & 1)){
      if(a%((int)pow(10,n/2)) == a/((int)pow(10,n/2))){
        tot += a;
      }
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
