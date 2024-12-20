#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Ask user for the text to be analyzed
    string inputText = get_string("Text: ");

    // Criteria:
    // index = 0.0588 * L - 0.296 * S - 15.8
    // where L is the average number of letters per 100 words in the text, and S is the average
    // number of sentences per 100 words in the text.

    int inputLength = strlen(inputText);
    int letterCounter = 0;
    int spaceCounter = 0;
    int pointCounter = 0;

    for (int i = 0; i < inputLength; i++)
    {
        char charUppercase = toupper(inputText[i]);
        int numberCharUpper = (int) charUppercase;
        // check if the character is a letter
        if (numberCharUpper >= 65 && numberCharUpper <= 90)
        {
            letterCounter++;
        }
        // check if its a space
        else if (inputText[i] == ' ')
        {
            spaceCounter++;
        }
        // check if its a point
        else if (inputText[i] == '.' || inputText[i] == '?' || inputText[i] == '!')
        {
            pointCounter++;
        }
    }
    // A final "space" is added to represent the final word that does no have a space afterwords
    int wordCounter = spaceCounter + 1;

    // Average word length per 100 words (L)
    // L = (Letters ÷ Words) × 100
    float L = (float) letterCounter * 100 / (float) wordCounter;

    // Average number of sentence per 100 words (s)
    // S = (Sentences ÷ Words) × 100
    float S = (float) pointCounter * 100 / (float) wordCounter;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // Outputs:
    //  "Grade X", if X is between 1 and 16, where “X” is the grade level computed, rounded to the
    //  nearest integer
    if (index >= 1 && index <= 16)
    {
        printf("Grade %.0f\n", round(index));
    }
    //  "Before Grade 1" if X less than 1
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    //  "Grade 16+" if X bigger than 16
    else
    {
        printf("Grade 16+\n");
    }
}
