// Modifies the volume of an audio file

#include <stdio.h>
#include <stdlib.h>

// WAV files begin with a 44-byte “header”
// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// sequence of samples, each a single 2-byte (16-bit) integer

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // each byte of a WAV file’s header as: uint8_t
    uint8_t header[HEADER_SIZE];

    // read
    fread(header, HEADER_SIZE, 1, input);
    // write
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // each sample of audio in a WAV file as: int16_t
    int16_t buffer;

    // read
    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        // Update volume of sample
        buffer *= factor;
        // write
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
