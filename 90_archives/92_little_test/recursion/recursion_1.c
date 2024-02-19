#include "stdio.h"

int addition(int n);

int main(void){
  int  n;
  printf("input the last range number: ");
  scanf("%d", &n);
  printf("%i\n", addition(n));
}

int addition(int n){
  if (n > 0){
    return n + addition(n-1);
  }
}
