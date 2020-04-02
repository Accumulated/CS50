#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string.h>


#define N	10



// Represents a node in a trie
typedef struct books_load
{
    bool is_book;
	//int Index_OfCurrent_Book;
    struct books_load *children[N];
}
books_load;


// Represents a trie_structure
books_load *root_trie, *ptr_trie;


// Size of library
long int SIZE = 0;

// Load flag to indicate either fail or success
bool LOAD_FLAG;





int main(void)
{
	Library_vidInitialize();
	char *x = "0123456789";
	bool t;
	t = Library_BoolInsertion(x);
	x = "0123456789";
	
	if(t)
	{
		printf("inserted \n\n");
		ptr_trie = root_trie;
		t = check(x);
		if(t)
		{
			printf("found before unloading\n\n");
			printf("size of library is :%d  BOOKS\n\n", SIZE);
		}
		
		ptr_trie = root_trie;
		unload();

		return 0;
	}
	
	ptr_trie = root_trie;
	unload();
	return 1;
	
}






// // Insert serials into memory, returning true if successful else false
bool Library_BoolInsertion(const char *serial)
{	
	// Restart for every serial from the top of the root
	ptr_trie = root_trie;

	// loop to assign the new word in trie
	for (int j = 0; serial[j] != '\0'; j++)
	{
		// tmp to store the chars index
		int tmp = 0;

		tmp = serial[j] % 48;

		// first time in the array's index (tmp)
		if (ptr_trie -> children[tmp] == NULL)
		{
			ptr_trie -> children[tmp] = malloc(sizeof(books_load));

			if (!(ptr_trie -> children[tmp]))
			{
				printf("error allocating NEWNODE \n");
				return false;
			}


			// Initializing all indeces to NULL and is_word to false by default
			ptr_trie -> children[tmp] -> is_book = false;
			for (int k = 0; k < N; k++)
			{
				ptr_trie -> children[tmp] -> children[k] = NULL;
			}

			ptr_trie = ptr_trie -> children [tmp];
		}

		// if an address already existed in this index (i.e. tmp)
		else
		{
			// exsist node now assigned to ptr
			ptr_trie = ptr_trie -> children[tmp];
		}
	}
	ptr_trie -> is_book = true;
	SIZE++;


	printf("LOAD IS A SUCCESS \n");
	LOAD_FLAG = true;
    // Indicate success
    return true;
}





bool Library_vidInitialize(void)
{
	// Initialize trie
    root_trie = malloc(sizeof(books_load));
    if (root_trie == NULL)
    {
        return false;
    }
    root_trie -> is_book = false;
    for (int i = 0; i < N; i++)
    {
        root_trie -> children[i] = NULL;
    }
	ptr_trie = root_trie;
}


// Returns number of books in library if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (LOAD_FLAG == true)
    {
        return SIZE;
    }
    return 0;
}




// Returns true if book is in library else false
bool check(const char *serial)
{
    // Restart from beginning
    int k = 0;
    ptr_trie = root_trie;

    // String length
    while (serial[k] != '\0')
    {
        k++;
    }

    // start traversing trie
    for (int j = 0; j < k; j++)
    {
        int tmp = 0;

		tmp = serial[j] % 48;

        // checking for index value
        if (ptr_trie -> children[tmp] == NULL)
        {
            ptr_trie = root_trie;
            return false;
        }
        else
        {
            ptr_trie = ptr_trie -> children[tmp];
        }
    }

    // Checking for is_word field in library
    if (ptr_trie -> is_book == true)
    {
        ptr_trie = root_trie;
        return true;
    }

    ptr_trie = root_trie;
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
	// Remeber to start ptr_trie with root_trie
    books_load *last_before_stack = NULL;
    int i = 0;

    // looping over the root its self
    for (i = 0; i < N ; i++)
    {
        if (ptr_trie -> children[i] == NULL);
        else
        {
            last_before_stack = ptr_trie;
            ptr_trie = ptr_trie -> children[i];

            unload();
            ptr_trie = last_before_stack;
        }
    }
    if (i == 10)
    {
        free(ptr_trie);
        return true;
    }
    return false;
}




























