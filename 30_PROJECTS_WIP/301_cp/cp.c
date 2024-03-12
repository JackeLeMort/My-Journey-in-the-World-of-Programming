#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./cp file_to_copy new_filename\n");
        return 1;
    }

    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
      perror("couldn't open source file");
      return 2;
    }

    FILE *destination = fopen(argv[2], "wb");
    if (destination == NULL) {
      perror("couldn't open destination file");
      fclose(source);
      return 3;
    }

    size_t buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytesread;

    while ((bytesread = fread(buffer, 1, buffer_size, source)) > 0) {
        fwrite(buffer, 1, bytesread, destination);
    }

    fclose(destination);
    fclose(source);

    return 0;
}
