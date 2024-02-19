#include "stdio.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv){

  if (argc != 2) {
    printf("Il faut un (seul) argument.\n");
    return 1;
  }

  for (int i = 0; i < strlen(argv[1]); i++){
    if ( isdigit(argv[1][i]) ==0 ){
      printf("Il faut donner un nombre.\n");
      return 1;
    }
  }
  int numbers_count = atoi(argv[1]);

  float fibonacci[numbers_count];
  fibonacci[0] = 0;
  fibonacci[1] = 1;
  printf("%g\n%g\n",fibonacci[0], fibonacci[1]);

  for (int i = 2; i < numbers_count; i++){
    fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    printf("%g\n", fibonacci[i]);
  }
  return 0;
}
