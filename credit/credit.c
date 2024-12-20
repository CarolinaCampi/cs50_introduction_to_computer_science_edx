#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for their credit/debit card number
    const long cardNumber = get_long("Number: ");

    // Declare and initialize variables for processing
    // Variable for checkSum
    long checkSumCardNumber = cardNumber;
    int sumEven = 0;
    int sumOdd = 0;
    // Variable to get the first two numbers
    long firstTwo = cardNumber;
    // Variable to count the amount of digits in the card number
    int digits = 0;

    // Checksum

    // Calculate the sum of even and odd positions in the card number
    // starting the count from the end
    for (int i = 0; checkSumCardNumber > 0; i++)
    {
        // obtain the last number using the modulo operation
        int modulo = checkSumCardNumber % 10;

        // divide by 10 so that the number "looses" its last number and its ready for next iteration
        checkSumCardNumber /= 10;

        // for odd positions in the card number:
        if ((i % 2) == 0)
        {
            sumOdd += modulo;
        }

        // for even positions in the card number:
        else
        {
            int moduloByTwo = modulo * 2;

            // Loop in case it has two figures
            while (moduloByTwo > 0)
            {
                sumEven += (moduloByTwo % 10);
                moduloByTwo /= 10;
            }
        }
        digits = i + 1;
    }

    // Add sumOdd and sumEven
    const int checkSum = sumOdd + sumEven;

    // Check if checkSum ends in 0 (is divisible by 10)
    if (checkSum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Find the first two digits
        while (firstTwo > 100)
        {
            firstTwo /= 10;
        }

        // All American Express numbers start with 34 or 37; 15-digit numbers
        if ((firstTwo == 34 || firstTwo == 37) && digits == 15)
        {
            printf("AMEX\n");
        }
        // most MasterCard numbers start with 51, 52, 53, 54, or 55, 16-digit numbers,
        else if ((firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || firstTwo == 54 ||
                  firstTwo == 55) &&
                 digits == 16)
        {
            printf("MASTERCARD\n");
        }
        // all Visa numbers start with 4. 13- and 16-digit numbers.
        else if ((firstTwo / 10 == 4) && (digits == 16 || digits == 13))
        {
            printf("VISA\n");
        }
        // fail-safe in case its from another bank
        else
        {
            printf("INVALID\n");
        }
    }
}
