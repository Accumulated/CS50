

#include "MCAL/DIO.h"
#include "HAL/LCD.h"
#include "HAL/EKEY_PAD.h"
#include <util/delay.h>

#include <stdlib.h>
#include <stdbool.h>

#include "EBOOKS.h"
#include "EMEMBERS.h"



// Define linked list structure
typedef struct books
{
	char *NAME_BOOK;
	char INDEX_BOOK;
	char *SERIAL_NUMBER;
	char COPIES;
	struct books *NEXT_BOOK;

}books;

// identify root and a ptr to move from root
books *root_book, *ptr_book, *book_to_decay;

s8 NoOfBooks = 0, insertion_flag = 0;


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
	root_book -> SERIAL_NUMBER = NULL;
	root_book -> COPIES = 0;
	
	ptr_book = root_book;
}


/********************************* READY *********************************/
// Insertion for values from user
bool BOOKS_vidInsertion(char *serial, char *name, char copies)			// if still, you can change to u8
{
	
	int k = 0, i = 0, j = 0;
	
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
	
	while(serial[i] != '\0')
	{
		i++;
	}

	tmp -> NAME_BOOK = malloc(k+1 *sizeof(char));
	tmp -> SERIAL_NUMBER = malloc(i+1 *sizeof(char));

	// Insert patient details
	tmp -> NEXT_BOOK = ptr_book -> NEXT_BOOK;

	tmp -> INDEX_BOOK = INDEX_BOOKS_GLOBAL;
	tmp -> COPIES = copies;
	
	// Save name
	for(j = 0; j < k ; j++)
	{
		tmp ->  NAME_BOOK[j] = name[j];
	}
	tmp ->  NAME_BOOK[j] = '\0';

	// Save serialNumber
	for(j = 0; j < i ; j++)
	{
		tmp ->  SERIAL_NUMBER[j] = serial[j];
	}
	tmp ->  SERIAL_NUMBER[j] = '\0';


	// Update list
	ptr_book -> NEXT_BOOK = tmp;

	// Indicate success
	LCD_String("BOOKS INSERTED");
	_delay_ms(500);
	LCD_vidClearOnDemand(1, 32);
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

// Search for a book either via ISBN or its location in list
u8 BOOKS_search (char *serial, char index)
{
	// Start after the root
	ptr_book = root_book -> NEXT_BOOK;
	
	bool found = false;


	// Iterating over the linked list after root node
	for(int i = 1; i <= NoOfBooks; i++)
	{
		if(CompareString(serial, ptr_book -> SERIAL_NUMBER) || index == ptr_book -> INDEX_BOOK)
		{
			found = true;
			book_to_decay = ptr_book;
			LCD_vidClearOnDemand(1, 32);

			LCD_String("BOOK'S INFO:");
			LCD_vidGoTo(1, 2);
			LCD_String("wait...");
			_delay_ms(500);

			LCD_vidClearOnDemand(1, 32);

			LCD_String("Name:");
			LCD_vidGoTo(1, 2);
			LCD_String(ptr_book -> NAME_BOOK);
			_delay_ms(2000);

			LCD_vidClearOnDemand(1, 32);

			LCD_String("ISBN:");
			LCD_vidGoTo(1, 2);
			LCD_String(ptr_book -> SERIAL_NUMBER);
			_delay_ms(2000);

			LCD_vidClearOnDemand(1, 32);

			// Update buffer incase of borrowing			
			return ptr_book -> INDEX_BOOK;
		}
		ptr_book = ptr_book -> NEXT_BOOK;
	}

	if(!found)
	{
		LCD_vidGoTo(1, 1);
		LCD_String("NO BOOK found");
		_delay_ms(2000);
		LCD_vidClearOnDemand(1, 32);
		ptr_book = root_book;
		return DoesNot_exist;
	}

	ptr_book = root_book;
	return 0;
}


/*
bool BOOKS_delete (char *serial)
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
	if(CompareString(ptr_book -> SERIAL_NUMBER , serial))
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
*/


// Shows all Books in the library
bool BOOKS_show(void)
{
	LCD_vidClearOnDemand(1, 32);

	ptr_book = root_book -> NEXT_BOOK;

	// Only root is no valid list
	if(!ptr_book)
	{
		LCD_String("NO BOOKS");
		_delay_ms(1000);
		ptr_book = root_book;
		return false;
	}

	do
	{
		LCD_vidGoTo(1, 2);
		LCD_String(ptr_book -> SERIAL_NUMBER);
		LCD_vidGoTo(1, 1);
		LCD_String("-");
		LCD_String(ptr_book -> NAME_BOOK);
		_delay_ms(1000);
		LCD_vidClearOnDemand(17, 32);
		LCD_vidGoTo(1, 2);
		LCD_String("Copies: ");
		LinkedList_vidCompanion(ptr_book -> COPIES);
		_delay_ms(1000);
		LCD_vidClearOnDemand(1, 32);
		
		ptr_book = ptr_book -> NEXT_BOOK;
	}
	while(ptr_book != NULL);
	
	
	ptr_book = root_book;

	return true;
}


// Incase of borrow state
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
		// INvalid number of copies
		return 0;
	}

	return 0;

}

// Incase of return state
bool BOOKS_COPIES_INCREASE(void)
{
	book_to_decay -> COPIES = book_to_decay -> COPIES + 1;
	return 1;
}


bool CompareString(char *str1, char* str2)
{
	u8 equal = 0;
	equal = LengthString(str1, str2);
	if(equal)
	{
		for(u8 i = 0; str1[i] != '\0'; i++)
		{
			if(str1[i] != str2[i])
				return false;
		}
		return true;
	}
	return false;

}


u8 LengthString(char *str1, char *str2)
{
	u8 i = 0, k = 0;
	while(str1[i] != '\0')
	{
		i++;
	}
	while(str2[k] != '\0')
	{
		k++;
	}

	if(k == i)
	{
		return true;
	}
	return false;

}

