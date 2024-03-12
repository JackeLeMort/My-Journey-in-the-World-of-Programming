#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef uint8_t byte;

int main (int argc, char **argv)
{
  if (argc < 2 || argc > 3){
    printf ("Usage: ./cp file_to_copy (optionnal: new_filename)\n");
  }


  FILE *source = fopen (argv[1], "rb");
  FILE *destination = fopen (argv[2], "wb");

  byte b;

  while ( fread (&b, sizeof(b), 1, source) != 0){
    fwrite (&b, sizeof(1), 1, destination);
  }

  fclose(source);
  fclose(destination);
}
