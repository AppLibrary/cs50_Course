#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    int count = 0, match = 0;
    string c_name;

    //Iterate Through Candidate Array
    while (count < candidate_count)
    {
        //Find The First Element.
        //Instantiate c_name Candidate Name
        c_name = candidates[count].name;

        //Iterate Through c_name One Character At A Time
        for (int i = 0, n = strlen(c_name); i < n; i++)
        {
            //If Vote Name And Candidate Name Is A Match
            if (c_name[i] == name[i])
            {
                //Update match plus 1
                match += 1;
            }
            else
            {
                break;
            }
        }

        if (match == strlen(c_name))
        {
            candidates[count].votes += 1;
        }
        //Update count
        count++;
    }

    if (match == strlen(name))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Set max_vote To Zero
    int  max_vote = 0, count = 0;

    //Iterate Through Candidate Array
    while( count < candidate_count)
    {
        //If Candidate At Index i is Greater Than max_vote
        if (candidates[count].votes > max_vote)
        {
            //Update Max Vote
            max_vote = candidates[count].votes;
        }
        count++;
    }

    //Iterate Through Candidate Array
    for (int i = 0; i < candidate_count; i++)
    {
        //If Candidate At Array Index Is Equal max_vote
        if (candidates[i].votes == max_vote)
        {
            //Print Name At Array Index I
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
