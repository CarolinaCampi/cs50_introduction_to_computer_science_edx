#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for the desired height for the pyramids
    printf("How tall should the pyramids be?\n");

    // Check the input to see if it's between 1 and 8 included
    int height;
    do
    {
        height = get_int("Please provide a number between 1 and 8: ");
    }
    while (height < 1 || height > 8);

    // Print the pyramid by rows
    for (int i = 0; i < height; i++)
    {
        // Print the left side
        for (int j = 0; j < height; j++)
        {
            if (j < (height - 1 - i))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // Print the empty space between
        printf("  ");

        // Print the right side of the pyramid
        for (int j = 0; j < height; j++)
        {
            if (j <= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
