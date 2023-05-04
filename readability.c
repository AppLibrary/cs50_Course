#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string cls);
int count_words(string cws);
int count_sentences(string css);
float coleman_liau_formula(int cls, int cws, int css);

//This Program Returns Graded Reading
//Level of a User Inputted Text
int main(void)
{
    //get input string from user
    string user_text = get_string("Text: ");

    //Print user_text to screen
    printf("%s\n", user_text);

    int letter_count = count_letters(user_text);
    int word_count = count_words(user_text);
    int sentences_count = count_sentences(user_text);
    int coleman_formula = coleman_liau_formula(letter_count, word_count, sentences_count);

    //printf("%i letter\n", letter_count);
    //printf("%i word\n", word_count);
    //printf("%i sentences\n", sentences_count);

    if (coleman_formula < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_formula >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", coleman_formula);
    }
}

//Function To Count Number Of Letters
int count_letters(string cls)
{
    int count = 0;
    int isletter = 0;
    int n = strlen(cls);

    //While Loop Iterate Through n+1
    while (count < n + 1)
    {
        //If Character At Index Count is Alphabet
        if (isalpha(cls[count]))
        {
            //Update by 1
            isletter += 1;
        }
        count++;
    }
    return isletter;
}

//Function To Count Number Of Words
int count_words(string cws)
{
    int count = 0;
    int word = 0;
    int n = strlen(cws);

    //Iterate Through Each Letter In cws
    while (count < n)
    {
        //If Value At Index count Is A Space
        //And count Is Less Than 1
        if (cws[0] == ' ' && count < 1)
        {
            //Update count
            count++;
        }
        //If Value At Index is Not Null
        //Or If Value At Index Is A Space Character
        if (cws[count] == ' ' || cws[count + 1] == '\0')
        {
            //Update word
            word += 1;
        }
        char letter = cws[count];
        count++;
    }
    return word;
}
//Function To Count Number Of Sentences
int count_sentences(string css)
{
    int count = 0;
    int sentence = 0;
    int n = strlen(css);

    //Iterate Through Each Letter In cws
    while (count < n + 1)
    {

        //If Value At Index is Not Null
        //Or If Value At Index Is A Period Character
        if (css[count] == '.' || css[count] == '!' || css[count] == '?')
        {
            //Update word
            sentence += 1;
        }
        char letter = css[count];
        count++;
    }
    return sentence;
}

//Coleman Liau Formula Function Return Index
float coleman_liau_formula(int cls, int cws, int css)
{
    float L = (float)cls / (float)cws * 100;
    float S = (float)css / (float)cws * 100;
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}
