#include <cs50.h>
#include <stdio.h>

int cardLength (long cardNumber);
int starting_digits (int cardLength, int cardNumber);
int calc_Checksum (long cardNumber);


//Get card length
int card_Length(long cardNumber)
{
    int count = 0;

    while ((cardNumber / 10) != 0)
    {
        cardNumber = cardNumber / 10;
        count++;
    }

    return count;
}

//Find the starting digits
int starting_Two_Digits (int cardLength, int cardNumber)
{
    int two_Digits = 0;
    while (cardLength != 2)
    {
        cardNumber = cardNumber / 10;
        cardLength --;
    }

    two_Digits = cardNumber;
    return two_Digits;
}

//Calculate checksum
int calc_Checksum(long cardNumber)
{
    int count = card_Length(cardNumber);
    int first_digit = 0;
    int sec_digit = 0;
    int prod = 0;
    int total = 0;

    while (count > 1)
    {
        first_digit = cardNumber % 10; //mod card number by 10 to get first digit
        cardNumber = cardNumber / 10;// divide card number by 10
        sec_digit = cardNumber % 10; //mod card number by 10 to get second digit

        prod = prod + (sec_digit * 2);
        total = prod + first_digit;
        count --;
    }
     return total % 10;
}

int main (void)
{
    long cardNumber = get_long("Enter your Credit Card Number: ");
    int cardLength = card_Length(cardNumber);

    int checksum = calc_Checksum(cardNumber);
    printf("%i\n", checksum);

    if(checksum != 0)
    {
        printf("1\n");
        printf("Invalid\n");
        //return 1;
    }

    int twoDigits = starting_Two_Digits(cardLength, cardNumber);

    if((cardLength != 13 && cardLength != 15 && cardLength != 16))
    {
        printf("Invalid\n");
        return 1;
    }

    if (twoDigits == 34 || twoDigits == 37)
    {
        printf("AMEX\n");
    }
    if(twoDigits == 51 || twoDigits == 52 || twoDigits == 53|| twoDigits == 54 || twoDigits == 55)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("VISA\n");
    }

}
