// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int n = hash(word);
    node *s = malloc(sizeof(node));
    strcpy(s->word, word);
    s->next = table[n]->next;

    while (s->next != NULL)
    {
        if (strcasecmp(word, s->next->word) == 0)
        {
            return true;
        }
        else
        {
            s = s->next;
        }
    }
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int n = toupper(word[0]) - 'A';
    if (n >= N)
    {
        return n % N;
    }
    else
    {
    return toupper(word[0]) - 'A';
    }

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *cpy = fopen(dictionary, "r");
    char *buffer = malloc(sizeof(LENGTH));
    if (cpy == NULL)
    {
        return false;
    }

    for (int i = 0; i< N; i++)
    {
            table[i] = malloc(sizeof(node));
    }

    while (fscanf(cpy, "%s", buffer) != EOF)
    {
        node *s = malloc(sizeof(node));
        if (s == NULL)
        {
            return false;
        }

        int n = hash(buffer);

        strcpy(s->word, buffer);
        s->next = table[n]->next;
        table[n]->next = s;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    long c = 0;
   node *t = malloc(sizeof(node));
   for (int i = 0; i < N; i++)
   {
        t->next = table[i]->next;
        table[i]->next = t;
        while (t->next != NULL)
        {
            c++;
            t = t->next;
        }
   }
    return c;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = malloc(sizeof(node));
    node *cursor = malloc(sizeof(node));

    for (int i = 0; i < N; i++)
    {
        cursor = table[i]->next;
        while (cursor->next != NULL)
        {
            tmp = cursor->next;
            cursor = cursor->next;
            free(tmp->next);
        }
    }

        return true;
}