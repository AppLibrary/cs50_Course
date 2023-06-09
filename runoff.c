#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    int count = 0;
    int rc;

    while (count < candidate_count)
    {
        rc = strcmp(name, candidates[count].name);//Compare name to candidate name at index and assign result

        if (rc == 0)
        {
            preferences[voter][rank] = count;
            return true;
        }

        count++;
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // int j = 0;
    // int preferred;

    // for(int i = 0;i < voter_count; i++)
    // {
    //     while(j < candidate_count)
    //     {
    //         preferred = preferences[i][j];

    //         if(candidates[preferred].eliminated == false)
    //         {
    //             candidates[preferred].votes++;
    //             break;
    //         }
    //         j++;
    //     }
    // }

    for (int v = 0; v < voter_count; v++)
    {
        for (int r = 0; r < candidate_count; r++)
        {
            int c = preferences[v][r];
            if (candidates[c].eliminated == false)
            {
                candidates[c].votes++;
                break;
            }
        }
    }
    //return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int total_vote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        total_vote += candidates[i].votes;
    }

    int half_totalVotes = total_vote / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes > half_totalVotes))
        {
            //Print Name At Array Index I
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO

    int min_vote, count = 0;

    //Set min_vote To Candidate Vote Total
    min_vote = voter_count;

    //Iterate Through Candidate Array
    for (; count < candidate_count; count++)
    {

        //If Candidate At Index i is Greater Than max_vote
        if (min_vote > candidates[count].votes && candidates[count].eliminated == false)
        {
            //Update min_vote
            min_vote = candidates[count].votes;
        }
    }

    //Return Mininum Vote
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tie = 0;
    //Iterate Through Candidate Array
    for (int i = 0; i < candidate_count; i++)
    {
        //Return True
        //If min And Vote At Index I Are Equal
        if (min == candidates[i].votes && candidates[i].eliminated == false)
        {
            tie += 1;
        }
    }

    if (tie >= 2 && min > tie)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    int count = 0;

    while (true)
    {
        //Break out of loop
        //If count Is Greater Than Total Candidate
        if (count > candidate_count)
        {
            break;
        }
        //If Candidate At Index Is Not Equal Min
        if (candidates[count].votes == min && candidates[count].eliminated == false)
        {
            //Set Eliminated To True
            candidates[count].eliminated = true;
        }

        //Update Count
        count++;
    }
    return;
}
