

#include "HAL/LCD.h"
#include "MCAL/DIO.h"

#include "EMEMBERS.h"
#include "EBOOKS.h"


#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>

#define AVAILABLE_SHARES 	5

// Define linked list structure
typedef struct members
{
	char *NAME_STRUCT;
	u8 INDEX_STRUCT;
	char *ID_STRUCT;
	char MEMBER_CARD_BOOKS[AVAILABLE_SHARES];
	struct members *NEXT_STRUCT;

}members;

// identify root and a ptr to move from root
members *root_member, *ptr_member;
s8 NoOfMembers = 0, B_insertion_flag = 0;


// Indication for members locations in members_list
u8 INDEX_MEMBERS_GLOBAL = 0;


members *search (char *id, char OLD_BOOKS);



/********************************* READY *********************************/
// Initialize members list
void LinkedList_vidInitialize(void)
{
	// Initializing list
	root_member = malloc(sizeof(members));
	root_member -> NAME_STRUCT = NULL;
	root_member -> NEXT_STRUCT	= NULL;
	root_member -> ID_STRUCT = NULL;
	root_member -> INDEX_STRUCT = 0;
	for(int i = 0; i < AVAILABLE_SHARES; i++)
	{
		root_member -> MEMBER_CARD_BOOKS[i] = 0;
	}
	
	ptr_member = root_member;
}


/********************************* READY *********************************/
// Insertion for values from user
bool LinkedList_vidInsertion(char *id, char *name)			// if still, you can change to u8
{
	int k = 0, i = 0, j = 0;
	
	// Pointer to check for repeated IDs
	members *tmp_detect = NULL;
	tmp_detect = search(id, 0);
	
	// Invalid ID
	if(tmp_detect)
	{
		LCD_String("ERROR_INSERTION!");
		return false;
	}
	
	
	// Inserting sequence initialized
	ptr_member = root_member;
	members *tmp = malloc(sizeof(members));
	
	// For future reference
	NoOfMembers++;
	INDEX_MEMBERS_GLOBAL++;

	

	// Get member's name length
	while(name[k] != '\0')
	{
		k++;
	}
	
	tmp -> NAME_STRUCT = malloc(k+1 *sizeof(char));


	// Get member's id length
	while(id[j] != '\0')
	{
		j++;
	}

	tmp -> ID_STRUCT = malloc(j+1 *sizeof(char));


	// Insert patient details
	tmp -> NEXT_STRUCT = ptr_member -> NEXT_STRUCT;

	tmp -> INDEX_STRUCT = INDEX_MEMBERS_GLOBAL;
	


	for(i = 0; i < k ; i++)
	{
		tmp ->  NAME_STRUCT[i] = name[i];
	}
	tmp ->  NAME_STRUCT[i] = '\0';
	

	for(i = 0; i < j ; i++)
	{
		tmp ->  ID_STRUCT[i] = id[i];
	}
	tmp ->  ID_STRUCT[i] = '\0';


	for(i = 0; i < AVAILABLE_SHARES; i++)
	{
		tmp -> MEMBER_CARD_BOOKS[i] = 0;
	}
	

	// Update list
	ptr_member -> NEXT_STRUCT = tmp;

	// Indicate success
	LCD_String("MEMBER INSERTED");
	_delay_ms(500);
	LCD_vidClearOnDemand(1, 32);
	return true;
}



/********************************* READY *********************************/
char LinkedList_u8DeleteEntire(void)
{
	// Buffer to save the previous condition of ptr
	members *last_before_stack = NULL;

	// Checking on the next field
	if(ptr_member -> NEXT_STRUCT != NULL)
	{
		last_before_stack = ptr_member;
		ptr_member = ptr_member -> NEXT_STRUCT;
		LinkedList_u8DeleteEntire();
		ptr_member = last_before_stack;
	}

	// free current node and return
	free(ptr_member);
	NoOfMembers = 0;
	return 0;
}



void LinkedList_vidRestart (void)
{
	restart_vip();
	LinkedList_u8DeleteEntire();
	LinkedList_vidInitialize();
}


void restart_vip(void)
{
	ptr_member = root_member;
}

void LinkedList_vidSearch(char *ptr, char show)
{
	search(ptr, show);
}

// To search for a member
members *search (char *id, char OLD_BOOKS)
{
	// Start after the root
	ptr_member = root_member -> NEXT_STRUCT;

	bool found = false;
	
	members *tmp = NULL;
	

	// Iterating over the linked list after root node
	for(int i = 1; i <= NoOfMembers; i++)
	{
		if(CompareString(id, ptr_member -> ID_STRUCT))
		{
			// Write Member Name on LCD
			LCD_vidClearOnDemand(1, 32);
			LCD_String("NAME: ");
			LCD_String(ptr_member -> NAME_STRUCT);

			// Write Member ID on LCD
			LCD_vidGoTo(1, 2);
			LCD_String("ID: ");
			LCD_String(ptr_member -> ID_STRUCT);
			_delay_ms(2000);

			// Write Member BOOK's on LCD
			LCD_vidClearOnDemand(1, 32);

			// Don't show the books
			if(!OLD_BOOKS);
			else
			{
				LCD_vidGoTo(1, 1);
				LCD_String("Borrowed BOOKS:");
				for(u8 i = 0; i < AVAILABLE_SHARES; i++)
				{
					LCD_vidGoTo(i + 1, 2);

					if(!ptr_member -> MEMBER_CARD_BOOKS[i]);
					else
					{
						BOOKS_search(0, ptr_member -> MEMBER_CARD_BOOKS[i]);
					}
				}
			}

			LCD_vidClearOnDemand(1, 32);
			found = true;
			return  ptr_member;

		}
		ptr_member = ptr_member -> NEXT_STRUCT;
	}

	if(!found)
	{
		ptr_member = root_member;
		return NULL;
	}

	ptr_member = root_member;
	return tmp;
}


// Borrow from books
void Borrow_vid(char *id, char *serial)
{
	u8 B_flag = 0;
	u8 index = 0;
	bool valid_copies = false;
	
	// Search for member and don't show the old books
	members *tmp = search(id, 0);
	
	// Search for the book via serial
	index = BOOKS_search(serial, 0);
	
	if(!tmp)
	{
		// Invalid ID
		LCD_String("ERROR_ID!");
	}
	else
	{
		// Valid Serial 
		if( index != DoesNot_exist)
		{
			// Scan for empty member card index
			for(u8 j = 0; j < AVAILABLE_SHARES; j++)
			{
				if(tmp -> MEMBER_CARD_BOOKS[j] == 0)
				{		
					valid_copies = BOOKS_COPIES_DECAY();
					if(valid_copies)
					{
						// Borrow and submit in MEMBER_CARD_BOOKS[] with Book index in BOOKS list
						tmp -> MEMBER_CARD_BOOKS[j] = index;

						LCD_String("BORROW -> SUCCESS:");
						LCD_vidGoTo(1, 2);
						LCD_String("Copies - 1.");
						_delay_ms(2000);
						LCD_vidClearOnDemand(1, 32);

						B_flag = 1;
						j = AVAILABLE_SHARES;					
					}
					else
					{
						LCD_String("Out of copies!");
						_delay_ms(2000);
						LCD_vidClearOnDemand(1, 32);
					}
						
				}
				else;
			}
		}
		else
		{
			LCD_String("Invalid ISBN");
			_delay_ms(2000);
			LCD_vidClearOnDemand(1, 32);
			B_flag = 1;
		}
		
		if(!B_flag)
		{
			LCD_String("Card_full");
			_delay_ms(2000);
			LCD_vidClearOnDemand(1, 32);
		}
	}
}


// Show all members
bool LinkedList_show(void)
{
	ptr_member = root_member -> NEXT_STRUCT;

	LCD_vidGoTo(1, 1);
	LCD_String("NoOfMembers are:");
	LCD_vidGoTo(1, 2);
	LinkedList_vidCompanion(NoOfMembers);
	_delay_ms(1000);
	LCD_vidClearOnDemand(1, 32);


	// Only root is no valid list
	if(!ptr_member)
	{
		LCD_String("NO Members");
		_delay_ms(2000);
		LCD_vidClearOnDemand(1, 32);
		ptr_member = root_member;
		return false;
	}


	do
	{
		LCD_vidGoTo(1, 2);
		LCD_String("MEMB_ID:");
		LCD_String(ptr_member -> ID_STRUCT);

		LCD_vidGoTo(1, 1);
		LCD_String("MEMB_NAME:");
		LCD_String(ptr_member -> NAME_STRUCT);

		_delay_ms(2000);
		LCD_vidClearOnDemand(1, 32);

		LCD_String("ID_BOOKS:");
		for(u8 i = 0; i < AVAILABLE_SHARES; i++)
		{
			LCD_vidGoTo(i + 1, 2);
			LinkedList_vidCompanion(ptr_member -> MEMBER_CARD_BOOKS[i]);
		}

		_delay_ms(2000);
		LCD_vidClearOnDemand(1, 32);
		ptr_member = ptr_member -> NEXT_STRUCT;
	}
	while(ptr_member != NULL);
	
	ptr_member = root_member;

	return true;
}




// RETURN from books
void RETURN_vid(char *id, char *serial)
{
	char R_flag = 0;
	u8 index = 0;
	

	// Search for member and don't show old books
	members *tmp = search(id, 0);
	
	// Search for the book via ISBN
	index = BOOKS_search(serial, 0);
	
	if(!tmp)
	{
		// Invalid ID
		LCD_String("ERROR:Inv_ID");
		_delay_ms(2000);
		LCD_vidClearOnDemand(1, 32);
	}
	else
	{
		// Valid Serial 
		if( index != DoesNot_exist)
		{
			// Scan for empty member card index
			for(u8 j = 0; j < AVAILABLE_SHARES; j++)
			{
				if(tmp -> MEMBER_CARD_BOOKS[j] == index)
				{		
					BOOKS_COPIES_INCREASE();
					
					// Return and remove from MEMBER_CARD_BOOKS[]
					tmp -> MEMBER_CARD_BOOKS[j] = 0;

					LCD_String("RETURN -> SUCCESS:");
					_delay_ms(2000);
					LCD_vidClearOnDemand(1, 32);
					R_flag = 1;
					j = AVAILABLE_SHARES;					

				}
				else;
			}
		}
		else
		{
			R_flag = 1;
			LCD_String("Invalid ISBN");
			_delay_ms(2000);
			LCD_vidClearOnDemand(1, 32);
		}
		
		if(!R_flag)
		{
			LCD_String("Book not");
			LCD_vidGoTo(1, 2);
			LCD_String("borrowed!");
			_delay_ms(2000);
			LCD_vidClearOnDemand(1, 32);
		}
	}
}


//  for user screen output
void LinkedList_vidCompanion(u16 show)
{

	u16 *ptr = malloc(5 * sizeof(u16));
	s8 k = 0, i = 0 ;

	// get values in order
	do
	{
		ptr[i] = (show%10) + 0x30;
		i++;
		show /= 10;
	}while(show);

	ptr[i] = '\0';

	// get string length
	for(k = 0; ptr[k] != '\0'; k++);

	//LCD_vidGoTo(1,2);

	// reverse the string sent
	for(s8 kk = k-1; kk >= 0; kk-- )
	{
		LCD_vidData(ptr[kk]);
	}


	free(ptr);
}


