/*******************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * Ivan Novak
 *
 * Implements a dictionary's functionality.
 *******************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>
#include <cs50.h>
#include <string.h>


#define TBLLNG 27
/**
 * Returns true if word is in dictionary else false.
 */ 

typedef struct node
{
    bool is_word;
    struct node* children[TBLLNG];
} 
node;

node* Root = NULL; 
long ListCount = 0;
long NewNodeCount = 0;
long DelNodeCount = 0;

node* NewNode(void)
{
  node* Res = malloc(sizeof(node));
  Res->is_word = false;
  for(int i = 0; i < TBLLNG; i++) Res->children[i] = NULL;
  return Res;
}

node* DelNode(node* Node)
{ 
    if(Node == NULL) return NULL;
    for(int i = 0; i < TBLLNG; i++) DelNode(Node->children[i]);  
    free(Node);
    return NULL;
}

node* AddChar(node* Node, const char* s)
{
  //  printf("%c", *s);
    int c = TBLLNG-1;
    if (Node == NULL) Node = NewNode();
    if(*s != '\'') c = *s-'a';
    if(*s++ == '\n') Node->is_word = true;
    else Node->children[c]=AddChar(Node->children[c], s++);
    return Node;
}

bool NodeCheck(node* Node, const char* s)
{
    int c = TBLLNG-1;
    if (Node == NULL) return false;
    if(*s != '\'') c = tolower(*s)-'a';
    if(*s++ == '\0') return Node->is_word;
    else return NodeCheck(Node->children[c], s++);
}

bool check(const char* word)
{
    return NodeCheck(Root, word); 
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    Root = NewNode();
    FILE *dist = fopen(dictionary, "r");
    char s[LENGTH+2];   
    while(fgets(s, LENGTH+2, dist) != NULL)
    { 
        ListCount++;
 //       printf("%li ", ListCount);
        AddChar(Root, s);
    } 
    fclose(dist);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return ListCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    Root = DelNode(Root);
    ListCount = 0;
    return true;
}
