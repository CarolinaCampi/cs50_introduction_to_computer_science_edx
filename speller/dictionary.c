// Implements a dictionary's functionality
#define _GNU_SOURCE
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Amount of words in the hash table
int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain its hash value
    int index = hash(word);
    // Search the hash table at the location specified by the word’s hash value
    for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        // Return false if no word is found
        if (ptr == NULL)
        {
            return false;
        }
        // Return true if the word is found
        else if(strcasestr(ptr->word, word) != NULL && (strlen(ptr->word) == strlen(word)))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Consider a hash function that uses a sum of ASCII values or the length of a word
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error when opening the file.");
        return false;
    }

    // Read each word in the file
    // https://manual.cs50.io/3/fscanf
    char buffer[LENGTH + 1];
    while(fscanf(file, "%s", buffer) != EOF)
    {
        // Add each word to the hash table

        // Create space for a new hash table node
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory could not be allocated to the node.");
            return false;
        }
        // Copy the word into the new node
        // https://manual.cs50.io/3/strcpy
        strcpy(n->word, buffer);
        n->next = NULL;
        // Hash the word to obtain its hash value
        int index = hash(buffer);
        // Insert the new node into the hash table (using the index specified by its hash value)
        if (table[index] == NULL)
        {
            table[index] = n;
            // add to the word count
            wordcount++;
        }
        // If the table already has nodes
        else
        {
            // prepend
            // 1. make the .next od new node point to the existing first node of table[index]
            n->next = table[index];
            // 2. change the table[index] pointer to point to the new first node
            table[index] = n;
            // add to the word count
            wordcount++;
        }
    }

    // Close the dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Option 1: Count each word as you load it into the dictionary. Return that count when size is called.
    // Option 2: Each time size is called, iterate through the words in the hash table to count them up. Return that count.
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Loop through each position in the array
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while(ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }
    return true;
}
