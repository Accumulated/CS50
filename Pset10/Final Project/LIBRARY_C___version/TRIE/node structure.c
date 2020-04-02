#include "dictionary.h"

// Represents a node in a trie
typedef struct books_load
{
    bool is_book;
    struct books_load *children[N];
}
books_load;

// Represents a trie

node *root_trie, *ptr_trie;

// size of DICTIONARY
long int SIZE;
bool LOAD_FLAG;