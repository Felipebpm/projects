
// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

const int ALPHA_SIZE = 27;

// indexes the letters

int indexer(char c);

// defines nodes
typedef struct node
{
    bool EOW;
    struct node *path[ALPHA_SIZE];
}
node;


node *root;

bool freenode(node *x)
{
    for (int i = 0; i < ALPHA_SIZE; i++)
    {
        if (x->path[i] != NULL)
        {
            freenode(x->path[i]);
        }
    }
    free(x);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int level;
    int length = strlen(word);
    int index;
    node *trav = root;

    for (level = 0; level < length; level++)
    {
        index = indexer(word[level]);

        if (!trav->path[index])
        {
            return false;
        }

        trav = trav->path[index];
    }

    return (trav != NULL && trav->EOW);
}

int NOW = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // creating words
    node *trav = NULL;
    root = (node *)malloc(sizeof(node));
    int ch = 0;

    while (EOF != (ch = fgetc(dict)))
    {
        int index;
        trav = root;

        for (; ch != '\n'; ch = fgetc(dict))
        {
            index = indexer(ch);
            if (trav->path[index] == NULL)
            {
                trav->path[index] = (node *)malloc(sizeof(node));
            }

            trav = trav->path[index];
        }

        // mark last node as leaf
        trav->EOW = true;
        NOW++;
    }
    // free(trav) - what I'd do differently.
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return NOW;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    bool f = freenode(root);
    if (f == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int indexer(char c)
{
    if (c == '\0')
    {
        return 25;
    }
    else if (c == '\'')
    {
        return 26;
    }
    else
    {
        return (tolower(c) - 'a');
    }

}