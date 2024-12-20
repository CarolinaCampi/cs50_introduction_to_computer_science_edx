#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int value_word(string word);

int main(void)
{
    // Prompt two players to submit their words
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Check the value of each word
    int sumP1 = value_word(player1);
    int sumP2 = value_word(player2);

    // Compare the values
    // Print the result
    if (sumP1 > sumP2)
    {
        printf("Player 1 wins!\n");
    }
    else if (sumP1 < sumP2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Check the value of each word
int value_word(string word)
{
    int sum = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        char charUpper = toupper(word[i]);
        switch (charUpper)
        {
            case 'A':
                sum += 1;
                break;
            case 'B':
                sum += 3;
                break;
            case 'C':
                sum += 3;
                break;
            case 'D':
                sum += 2;
                break;
            case 'E':
                sum += 1;
                break;
            case 'F':
                sum += 4;
                break;
            case 'G':
                sum += 2;
                break;
            case 'H':
                sum += 4;
                break;
            case 'I':
                sum += 1;
                break;
            case 'J':
                sum += 8;
                break;
            case 'K':
                sum += 5;
                break;
            case 'L':
                sum += 1;
                break;
            case 'M':
                sum += 3;
                break;
            case 'N':
                sum += 1;
                break;
            case 'O':
                sum += 1;
                break;
            case 'P':
                sum += 3;
                break;
            case 'Q':
                sum += 10;
                break;
            case 'R':
                sum += 1;
                break;
            case 'S':
                sum += 1;
                break;
            case 'T':
                sum += 1;
                break;
            case 'U':
                sum += 1;
                break;
            case 'V':
                sum += 4;
                break;
            case 'W':
                sum += 4;
                break;
            case 'X':
                sum += 8;
                break;
            case 'Y':
                sum += 4;
                break;
            case 'Z':
                sum += 10;
                break;
            default:
                sum += 0;
                break;
        }
    }
    return sum;
}
