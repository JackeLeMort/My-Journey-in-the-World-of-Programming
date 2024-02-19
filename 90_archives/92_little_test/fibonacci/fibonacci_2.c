#include "stdio.h"
#include <stdlib.h>

int fibonacci(int n);

int main(int argc, char **argv){
  int n = atoi(argv[1]);
  printf("%i\n",fibonacci(n));
}

int fibonacci(int n){
  printf("n = %i\n", n);
  if (n <= 1){
    return 1;
  }
  else {
    return (fibonacci(n-1) + fibonacci(n-2));
  }
}
