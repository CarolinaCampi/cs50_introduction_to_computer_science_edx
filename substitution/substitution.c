#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check validity of command and key:
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Usage: ./substitution key\n");
        printf("Key must contain 26 letters, without repetitions.\n");
        printf("Not 26 characters.\n");
        return 1;
    }

    for (int i = 0, length = strlen(key); i < length; i++)
    {
        if (key[i] < 'A' || (key[i] > 'Z' && key[i] < 'a') || key[i] > 'z')
        {
            printf("Usage: ./substitution key\n");
            printf("Key must contain 26 letters, without repetitions.\n");
            printf("Not alphabetic characters.\n");
            return 1;
        }

        for (int j = (i + 1); j < length; j++)
        {
            if (key[i] == key[j])
            {
                printf("Usage: ./substitution key\n");
                printf("Key must contain 26 letters, without repetitions.\n");
                printf("Repeated letters.\n");
                return 1;
            }
        }
    }

    // Ask for plaintext
    const string plaintext = get_string("plaintext:  ");

    // Process plaintext using key to obtain ciphertext and print it
    printf("ciphertext: ");

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        // check if its an uppercase letter
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            // find the associated int for the letter, substract A to normalize. So that we are working from 0 to 25.
            int plainletter = (int) plaintext[i];
            plainletter -= 'A';
            int cipherletterUpper = toupper(key[plainletter]);
            printf("%c", cipherletterUpper);
        }
        // check if its an lowercase letter
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            int plainletter = (int) plaintext[i];
            plainletter -= 'a';
            int cipherletterLower = tolower(key[plainletter]);
            printf("%c", cipherletterLower);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
