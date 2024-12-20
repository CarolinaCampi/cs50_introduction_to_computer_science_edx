#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    // Check validity of command and key:
    // If your program is executed without any command-line arguments or with more than one
    // command-line argument, your program should print an error message of your choice (with
    // printf) and return from main a value of 1 (which tends to signify an error) immediately. If
    // any of the characters of the command-line argument is not a decimal digit, your program
    // should print the message Usage: ./caesar key and return from main a value of 1.

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0, length = strlen(argv[1]); i < length; i++)
        {
            if (argv[1][i] <= 48 || argv[1][i] >= 57)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    int key = atoi(argv[1]);

    // Ask for plaintext
    const string plaintext = get_string("plaintext:  ");

    // Process plaintext using key to obtain ciphertext and print it
    printf("ciphertext: ");

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        // checck if its an uppercase letter
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            // find the associated int for the letter, substract A to normalize. So that we are working from 0 to 25.
            int plainletter = (int) plaintext[i];
            plainletter -= 'A';
            int cipherletter = (plainletter + key) % 26;
            cipherletter += 'A';
            printf("%c", cipherletter);
        }
        // checck if its an lowercase letter
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            int plainletter = (int) plaintext[i];
            plainletter -= 'a';
            int cipherletter = (plainletter + key) % 26;
            cipherletter += 'a';
            printf("%c", cipherletter);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
