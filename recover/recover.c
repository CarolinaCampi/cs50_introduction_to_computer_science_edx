#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check amount of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    // Open the memory card
    FILE *input = fopen(argv[1], "r");

    // If the forensic image cannot be opened for reading, your program
    // should inform the user as much, and main should return 1
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[512];
    int i = 0;
    char *file_name = malloc(8);
    FILE *output;

    // While there's still data left to read from the memory card
    while (fread(buffer, sizeof(int8_t), 512, input) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            // Create JPEGs from the data named ###.jpg, starting with 000 for the first image and
            // counting up.
            sprintf(file_name, "%03d.jpg", i);
            // Create an output file
            output = fopen(file_name, "w");
            // write on the output file
            fwrite(&buffer, sizeof(int8_t), 512, output);
            // close the output file
            fclose(output);
            i++;
        }
        else if (i > 0)
        {
            sprintf(file_name, "%03d.jpg", i - 1);
            // open the file
            output = fopen(file_name, "a");
            fwrite(&buffer, sizeof(int8_t), 512, output);
            // close the output file
            fclose(output);
        }
    };

    // Close the card file
    fclose(input);
    free(file_name);
}
