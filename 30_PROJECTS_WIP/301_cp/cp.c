#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  if (argc < 2 || argc > 3){
    printf ("Usage: ./cp file_to_copy (optionnal: new_filename)\n");
  }


  FILE *source = fopen (argv[1], "rb");
  FILE *destination = fopen (argv[2], "wb");

  fread (source, )

  fclose(source);
  fclose(destination);
}
