// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root, *ptr;

// size of DICTIONARY
long int SIZE;
bool LOAD_FLAG;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Restart for every word from the top of the root
        ptr = root;

        // loop to assign the new word in trie
        for (int j = 0; word[j] != '\0'; j++)
        {
            // tmp to store the chars index
            int tmp = 0;

            // checking for '\'' char
            word[j] == '\'' ? (tmp = word[j] - 13) : (tmp = word[j] - 97);

            // first time in the array's index (tmp)
            if (ptr -> children[tmp] == NULL)
            {
                ptr -> children[tmp] = malloc(sizeof(node));

                if (!(ptr -> children[tmp]))
                {
                    printf("error allocating NEWNODE \n");
                    return false;
                }


                // Initializing all indeces to NULL and is_word to false by default
                ptr -> children[tmp] -> is_word = false;
                for (int k = 0; k < N; k++)
                {
                    ptr -> children[tmp] -> children[k] = NULL;
                }

                ptr = ptr -> children [tmp];
            }

            // if an address already existed in this index (tmp)
            else
            {
                // exsist node now assigned to ptr
                ptr = ptr -> children[tmp];
            }
        }
        ptr -> is_word = true;
        SIZE++;
    }

    // Close dictionary
    fclose(file);

    LOAD_FLAG = true;
    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (LOAD_FLAG == true)
    {
        return SIZE;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Restart from beginning
    int k = 0;
    ptr = root;

    // Buffer for word
    while (word[k] != '\0')
    {
        k++;
    }
    char *new_word = malloc(k);


    // To solve the UPPER_CASE problem
    for (int n = 0; n < k; n++)
    {
        if (word[n] >= 'A' && word[n] <= 'Z')
        {
            if (word[n] + 32 == tolower(word[n]))
            {
                new_word[n] = (char) tolower((word[n]));
            }
            else
            {
                free(new_word);
                ptr = root;
                return false;
            }

        }
        else
        {
            new_word[n] = word[n];
        }
    }

    // start traversing trie
    for (int j = 0; j < k; j++)
    {
        int tmp = 0;

        // checking for '\'' char
        new_word[j] == '\'' ? (tmp = (new_word[j] - 13)) : (tmp = (new_word[j] - 97));

        // checking for index value
        if (ptr -> children[tmp] == NULL)
        {
            free(new_word);
            ptr = root;
            return false;
        }
        else
        {
            ptr = ptr -> children[tmp];
        }
    }

    // Checking for is_word field in Dictionary
    if (ptr -> is_word == true)
    {
        free(new_word);
        ptr = root;
        return true;
    }

    free(new_word);
    ptr = root;
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *last_before_stack = NULL;
    int i = 0;

    // looping over the root its self
    for (i = 0; i < N ; i++)
    {
        if (ptr -> children[i] == NULL);
        else
        {
            last_before_stack = ptr;
            ptr = ptr -> children[i];

            unload();
            ptr = last_before_stack;
        }
    }
    if (i == 27)
    {
        free(ptr);
        return true;
    }
    return false;
}
