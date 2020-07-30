// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Maximum number of children [a, b, c, ..., z, ']
#define max_children 27

// Represents a node in a trie table
typedef struct node
{
    // char letter;
    struct node *branch[max_children];    //Creates an array to for
    bool eow[max_children];               // Bool array to detect if path is an end of a word.
}
node;

// Prototypes
node *create_node(void);
void trie_free(node *trie_tree);

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
int dict_words = 0;
node *root = NULL;
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    node *parent_node = root;
    node *child_node = NULL;
    // Iterate through each letter of the word
    for (int i = 0; i < n; i++)
    {
        int letter = hash(&word[i]);
        child_node = parent_node->branch[letter];
        // Moves down trie
        if (child_node != NULL && i != n-1)
            {
                parent_node = parent_node->branch[letter];
            }
        // If EOW then return true
        if (i == n-1 && parent_node->eow[letter] == true)
                return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int letter_asci = (int) tolower(*word) - 97;
    return letter_asci;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = create_node();
    char buffer[LENGTH];
    node *parent_node = NULL;
    node *child_node = NULL;
    node *new_node = NULL;

    // Load in external dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (!fp)
    {
        printf("Could not load dictionary.");
        return false;
    }

    // Generate dictionary Trie Table
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        // Create word hash key
        int n = strlen(buffer);   // Number of links required to be made
        int key[n];
        for (int j = 0; j < n; j++)
        {
            key[j] = hash(&buffer[j]);  // Hashes each letter in word into an array
        }

        // Create trie path for word
        parent_node = root;
        for (int j = 0; j < n-1; j++)
        {
            // Links parent node to child node
            if (parent_node->branch[key[j]] == NULL)
            {
                child_node = create_node();
                parent_node->branch[key[j]] = child_node;
            }
            // If path already exists
            else
               child_node = parent_node->branch[key[j]];

            parent_node = child_node;
        }

        // If EOW changes bool to true
        parent_node->eow[key[n-1]] = true;
        dict_words++;

    }
    fclose (fp);
    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    trie_free(root);
    return true;
}

////////////////////////////
///// CUSTOM FUNCITONS /////
////////////////////////////

// Creates a new node
node *create_node(void)
{
    // Malloc space for node
    node *node_p = malloc(sizeof(struct node));
    if (node_p == NULL)
    {
        return false;
    }

    // Initilize node pointers to null
    for (int i = 0; i < max_children; i++)
    {
        node_p->branch[i] = NULL;
        node_p->eow[i] = false;
    }

    return node_p;
}

void trie_free(node *trie_tree)
{
    if (trie_tree == NULL)
    {
        return;
    }

    for (int i = 0; i < max_children; i++)
    {
        trie_free(trie_tree->branch[i]);
    }

    free(trie_tree);
}