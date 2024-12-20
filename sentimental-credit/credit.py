import cs50
import re
import math

# Ask the user for their credit/debit card number
cardstr = cs50.get_string("Number: ")
cardint = int(cardstr)

# calculate checksum
sumOdd = 0
sumEven = 0
inProcessCardInt = cardint
for i in range(len(cardstr)):
    # if its in a odd position counting from the back
    if (i % 2 == 0):
        sumOdd += (inProcessCardInt % 10)
    # if its an even position counting from the back
    else:
        moduloByTwo = 2 * (inProcessCardInt % 10)
        sumEven += (moduloByTwo % 10)
        sumEven += (math.floor(moduloByTwo / 10) % 10)
    inProcessCardInt = math.floor(inProcessCardInt / 10)

checksum = sumOdd + sumEven

# if checksum does not end with 0 or is divisible by 10
if ((checksum % 10) != 0):
    # print INVALID
    print("INVALID")

# else check first or first two characters
else:
    # All American Express numbers start with 34 or 37; 15-digit numbers
    if (re.findall(r"\A34", cardstr) == ['34'] or re.findall(r"\A37", cardstr) == ['37']) and len(cardstr) == 15:
        # print AMEX
        print("AMEX")
    # most MasterCard numbers start with 51, 52, 53, 54, or 55, 16-digit numbers,
    elif (re.findall(r"\A[5][1-5]", cardstr) != []) and (len(cardstr) == 16):
        # print MASTERCARD
        print("MASTERCARD")
    # all Visa numbers start with 4. 13- and 16-digit numbers.
    elif re.findall(r"\A4", cardstr) == ['4'] and (len(cardstr) == 16 or len(cardstr) == 13):
        # print VISA
        print("VISA")
    # fail-safe in case its from another bank
    else:
        # print INVALID
        print("INVALID")
