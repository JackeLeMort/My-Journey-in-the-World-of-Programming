#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv)
{
  if (argc < 2 || argc > 3){
    printf ("Usage: ./cp file_to_copy (optionnal: new_filename)");
  }

  FILE *source = fopen(argv[1], r);

 # FILE *destinati

}
