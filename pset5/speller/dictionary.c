// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int handleApostrophe(char letter);
bool checkBucket(const char *word, node *check, int index);
void clearplace(node *word);

// Number of buckets in hash table
const unsigned int N = 19683;

// Hash table
node *table[N];

// Count of words
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // 1 letter words
    if (word[1] == '\0')
    {
        return checkBucket(word, table[((handleApostrophe(word[0])) - 96)*27*27], 1);
    }

    // 2 letter words
    else if (word[2] == '\0')
    {
        return checkBucket(word, table[((handleApostrophe(word[0])) - 96)*27*27 + ((handleApostrophe(word[1])) - 96)*27], 2);
    }

    else
    {
        return checkBucket(word, table[((handleApostrophe(word[0])) - 96)*27*27 + ((handleApostrophe(word[1])) - 96)*27 + ((handleApostrophe(word[2])) - 96)], 3);
    }
}

// if apostrophe, return index after lowercase z, otherwise return lowercase
int handleApostrophe(char letter)
{
    if (letter == 39)
    {
        return 96;
    }
    else
    {
        return (int) tolower(letter);
    }
}

// check linked list with common three letter start
bool checkBucket(const char *word, node *check, int index)
{
    if (check == NULL)
    {
        return false;
    }
    
    // Did we make it to the end of the word already
    if (word[index] == '\0')
    {
        if (check->word[index] == '\0')
        {
            // rare case check
            for (int i = 1; i < index; i++)
            {
                if (tolower(word[i]) != tolower(check->word[i]))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    // have we not reached the point where the index-th letters are the same
    else if (handleApostrophe(check->word[index]) < handleApostrophe(word[index]))
    {
        return checkBucket(word, check->next, index);
    }

    // if index-th letters are the same, check index++-th
    else if (handleApostrophe(check->word[index]) == handleApostrophe(word[index]))
    {
        return checkBucket(word, check, index + 1);
    }

    // if we have passed up the letter in the alphabet, the word isn't there
    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word[1] == '\0')
    {
        return ((handleApostrophe(word[0])) - 96)*27*27;
    }

    // 2 letter words
    else if (word[2] == '\0')
    {
        return ((handleApostrophe(word[0])) - 96)*27*27 + ((handleApostrophe(word[1])) - 96)*27;
    }

    else
    {
        return ((handleApostrophe(word[0])) - 96)*27*27 + ((handleApostrophe(word[1])) - 96)*27 + ((handleApostrophe(word[2])) - 96);
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file and get size
    FILE *my_dictionary = fopen(dictionary, "r");
    fseek(my_dictionary, 0L, SEEK_END);
    int size = ftell(my_dictionary);
    fseek(my_dictionary, 0L, SEEK_SET);
    
    // read to memory
    char dict[size];
    fread(dict, size, 1, my_dictionary);
    
    // initialize and loop
    int index = 0;
    int word_index = 0;
    node *current = malloc(sizeof(node));
    node *prev_node = NULL;
    int prev_place = -1;
    while (dict[index] != '\0') 
    {
        // end of word
        if (dict[index] == '\n')
        {
            current->word[word_index] = '\0';
            index++;
            word_index = 0;
            word_count++;
            
            int place = hash(current->word);
            if (place == prev_place)
            {
                prev_node->next = current;
            }
            else
            {
                table[place] = current;
            }
            prev_node = current;
            prev_place = place;
            node *temp = malloc(sizeof(node));
            current = temp;
        }
        
        // next letter or apostrophe
        else if ((tolower(dict[index]) > 96 && tolower(dict[index]) < 123) || dict[index] == 39)
        {
            current->word[word_index] = dict[index];
            index++;
            word_index++;
        }
        
        // skip other punctuation, don't go past end
        else
        {
            while (dict[index] != '\n' && dict[index] != '\0')
            {
                index++;
            }
        }
    }
    
    free(current);
    
    if (dict[index] == '\0')
    {
        fclose(my_dictionary);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        clearplace(table[i]);
    }
    return true;
}

// free linked list of nodes
void clearplace(node *word)
{
    if (word != NULL)
    {
        node *temp = word->next;
        free(word);
        clearplace(temp);
    }
}