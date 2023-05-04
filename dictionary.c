// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 300;

// Hash table
node *table[N];

// Word Counter
int word_counter = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    unsigned int key_len = strlen(word);

    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }

    value = value % N;
    return value;

    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    int index = 0;


    char word[LENGTH + 1];

    //Open dictionary for read
    FILE *dict = fopen(dictionary, "r");

    //return 1 if NULL
    if(dict == NULL)
    {
        return false;
    }

    //Iterate through file until EOF
    while (fscanf(dict, "%s", word) != EOF)
    {
        //malloc a new node
        node *new_node = malloc(sizeof(node));

        //malloc size of a node
        if(new_node == NULL)
        {
            //unload();
            return false;
        }

        strcpy(new_node -> word, word);//copy word into node
        new_node -> next = NULL;//point node->next to NULL
        index = hash(word); //hash index of word


        if(table[index] != NULL) //Check head of list is not NULL
        {
            new_node -> next = table[index]; //point new node to head->next
            table[index] = new_node;//point head to new node
        }
        else
        {
            table[index] = new_node;//point head to new node
        }

        word_counter++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
   int count = 0;
   node *cursor;

   while (count < N)
   {
       cursor = table[count];

        for (node *temp = cursor; temp != NULL; )
        {
            temp = cursor -> next;
            free(cursor);
            cursor = temp;
        }
       count++;
   }
   return true;
}
