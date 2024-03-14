// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    int buffer_size = HEADER_SIZE;
    char buffer[HEADER_SIZE];

    fread (buffer, 1, HEADER_SIZE, input);
    fwrite (buffer, 1, HEADER_SIZE, output);

    buffer_size = 2;

    while ((fread (buffer, 1, buffer_size, input)) >0){
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] *= factor;
        }
        fwrite (buffer, 1, buffer_size, output);
    }


    fclose(input);
    fclose(output);
}
