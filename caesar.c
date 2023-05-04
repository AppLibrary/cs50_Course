#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

//Prototype
bool only_digits(string p_text);
char rotate(char pt, int key);

//Main Function
int main(int argc, string argv[])
{
    //If Argument Count Is Not 2
    //Print "Usage: ./caesar key
    if (argc != 2 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (only_digits(argv[1]) != true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //Convert Key to Integer
    int key = atoi(argv[1]);

    //Get User Input
    string plain_text = get_string("Plaintext: ");

    int count = 0;
    char ciphered;
    printf("Ciphertext: ");

    //Loop Through String Length of plain_text
    while (count < strlen(plain_text))
    {
        if (isalpha(plain_text[count]))
        {
            //Variable ciphered instantiated with function call rotate
            //Function Call rotate with two argument passeD
            ciphered = rotate(plain_text[count], key);
            printf("%c", ciphered);

        }
        else
        {
            printf("%c", plain_text[count]);
        }

        count++;
    }
    printf("\n");
}

//Function Returns True If Character Is A Digit
//False If Character Is Not A Digit
bool only_digits(string p_text)
{
    int count = 0, n = strlen(p_text);
    //Iterate through argv[1]

    while (count < n)
    {
        //If Value At Index Is Digit
        //Return true
        if (isdigit(p_text[count]))
        {
            count++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

//Function Rotates The Given Plaintext Strings
char rotate(char plain_t, int key)
{
//...................Algorithm....................//
    char cipher = 0;

    //If plain text is greater than/equal to 'A' + 32 && less 'z'
    if (isupper(plain_t))
    {

        cipher = (((plain_t - 65) + key) % 26) + 65;

    }
    if (islower(plain_t))
    {

        cipher = (((plain_t - 97) + key) % 26) + 97;

    }
    return cipher;
//................................................//
}
