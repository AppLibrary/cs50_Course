#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}

int compute_score(string word)
{
    int count = 0, score = 0, point;
    int this_word = strlen(word);

    //Iterate Through Each Letter In this_word
    while (count < this_word)
    {
        //Check If Character at Index Is Alphabet
        if (!isalpha(word[count]))
        {
            count++;
        }

        //Make Character Uppercase
        char upper_char = toupper(word[count]);

        //Formula To Find Letter Value Index In Array POINTS
        point = 25 - (90 - upper_char);
        score += POINTS[point];
        count ++;
    }

    return score;
}
