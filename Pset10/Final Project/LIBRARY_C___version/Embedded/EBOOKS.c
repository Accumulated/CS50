

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BOOKS.h"


// Define linked list structure
typedef struct books
{
	char *NAME_BOOK;
	char INDEX_BOOK;
	unsigned long int SERIAL_NUMBER;
	char COPIES;
	struct books *NEXT_BOOK;

}books;

// identify root and a ptr to move from root
books *root_book, *ptr_book, *book_to_decay;

int NoOfBooks = 0, insertion_flag = 0;


// Indication for books locations in books_list
char INDEX_BOOKS_GLOBAL = 0;




/********************************* READY *********************************/
// Initialize books list
void BOOKS_vidInitialize(void)
{
	root_book = malloc(sizeof(books));
	
	// Initializing list
	root_book -> NAME_BOOK = NULL;
	root_book -> NEXT_BOOK = NULL;
	root_book -> INDEX_BOOK = 0;
	root_book -> SERIAL_NUMBER = 0;
	root_book -> COPIES = 0;
	
	ptr_book = root_book;
}


/********************************* READY *********************************/
// Insertion for values from user
bool BOOKS_vidInsertion(unsigned int serial, char *name, char copies)			// if still, you can change to u8
{
	
	int k = 0, i = 0;
	
	// Inserting sequence initialized
	ptr_book = root_book;
	books *tmp = malloc(sizeof(books));
	
	// For future reference
	NoOfBooks++;
	INDEX_BOOKS_GLOBAL++;

	

	// Get member's name length
	while(name[k] != '\0')
	{
		k++;
	}
	
	tmp -> NAME_BOOK = malloc(k+1 *sizeof(char));

	// Insert patient details
	tmp -> NEXT_BOOK = ptr_book -> NEXT_BOOK;

	tmp -> SERIAL_NUMBER = serial;
	tmp -> INDEX_BOOK = INDEX_BOOKS_GLOBAL;
	tmp -> COPIES = copies;
	
	for(i = 0; i < k ; i++)
	{
		tmp ->  NAME_BOOK[i] = name[i];
	}
	tmp ->  NAME_BOOK[i] = '\0';

	// Update list
	ptr_book -> NEXT_BOOK = tmp;

	// Indicate success
	printf("success \n\n");
	return true;
}



/********************************* READY *********************************/
char BOOKS_u8DeleteEntire(void)
{
	// Buffer to save the previous condition of ptr
	books *last_before_stack = NULL;

	// Checking on the next field
	if(ptr_book -> NEXT_BOOK != NULL)
	{
		last_before_stack = ptr_book;
		ptr_book = ptr_book -> NEXT_BOOK;
		BOOKS_u8DeleteEntire();
		ptr_book = last_before_stack;
	}

	// free current node and return
	free(ptr_book);
	NoOfBooks = 0;
	return 0;
}



void BOOKS_vidRestart (void)
{
	BOOKS_restart_vip();
	BOOKS_u8DeleteEntire();
	BOOKS_vidInitialize();
}

void BOOKS_restart_vip(void)
{
	ptr_book = root_book;
}


int BOOKS_search (unsigned int serial)
{
	// Start after the root
	ptr_book = root_book -> NEXT_BOOK;
	
	bool found = false;
	int value = 0;

	// Iterating over the linked list after root node
	for(int i = 1; i <= NoOfBooks; i++)
	{
		if(serial == ptr_book -> SERIAL_NUMBER)
		{
			found = true;
			book_to_decay = ptr_book;
			
			// Update buffer incase of borrowing			
			return ptr_book -> INDEX_BOOK;
		}
		ptr_book = ptr_book -> NEXT_BOOK;
	}

	if(!found)
	{
		//printf("\nNOT FOUND\n");
		ptr_book = root_book;
		return DoesNot_exist;
	}

	ptr_book = root_book;
	return 0;
}



bool BOOKS_delete (unsigned int serial)
{
	if (!ptr_book -> NEXT_BOOK)
	{
		return false;
	}

	// save the current node
	books *last_before_delete = ptr_book;
	// update new ptr
	ptr_book = ptr_book -> NEXT_BOOK;
	// save next node
	books *node_after_ptr = ptr_book -> NEXT_BOOK;

	// DELETION SEQUENCE
	if(ptr_book -> SERIAL_NUMBER == serial)
	{
		// Delete and shift
		free(ptr_book);
		last_before_delete -> NEXT_BOOK = node_after_ptr;
		ptr_book = last_before_delete;
		NoOfBooks--;
		return true;
    }
	else
	{
		BOOKS_delete (serial);
	}
	return true;
}



bool BOOKS_show(void)
{
	ptr_book = root_book -> NEXT_BOOK;
	printf("NoOfBooks is:%d \n", NoOfBooks);
	printf("\n\nlist of all books: \n");

	// Only root is no valid list
	if(!ptr_book)
	{
		printf("\n\nNO ELEMENTS INSERTED\n");
		ptr_book = root_book;
		return false;
	}

	do
	{
		printf("\n\n-)%d serial for %s\t", ptr_book -> SERIAL_NUMBER, ptr_book -> NAME_BOOK);
		printf("#COPIES: %d\n\n", ptr_book ->COPIES);
		
		ptr_book = ptr_book -> NEXT_BOOK;
	}
	while(ptr_book != NULL);
	
	
	ptr_book = root_book;
	printf("\n");
	return true;
}


bool BOOKS_COPIES_DECAY(void)
{
	if(book_to_decay -> COPIES > 0)
	{
		// Indication for success
		book_to_decay -> COPIES = book_to_decay -> COPIES - 1;
		return 1;
	}
	
	else
	{
		//printf("INvalid number of copies \n\n");
		return 0;
	}

	return 0;

}


bool BOOKS_COPIES_INCREASE(void)
{

	book_to_decay -> COPIES = book_to_decay -> COPIES + 1;
	return 1;
}
