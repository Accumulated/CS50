

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MEMBERS.h"
#include "BOOKS.h"

#define AVAILABLE_SHARES 	5

// Define linked list structure
typedef struct members
{
	char *NAME_STRUCT;
	char INDEX_STRUCT;
	char ID_STRUCT;
	char MEMBER_CARD_BOOKS[AVAILABLE_SHARES];
	struct members *NEXT_STRUCT;

}members;

// identify root and a ptr to move from root
members *root_member, *ptr_member;
int NoOfMembers = 0, B_insertion_flag = 0;


// Indication for members locations in members_list
char INDEX_MEMBERS_GLOBAL = 0;


members *search (char id);



int main(void)
{
	LinkedList_vidInitialize();
	BOOKS_vidInitialize();
	
	LinkedList_vidInsertion(5, "NEWNAME");
	LinkedList_vidInsertion(22, "NNNNNNN");
	LinkedList_vidInsertion(5, "KKKSLSKS");
	LinkedList_vidInsertion(11, "MSNMSNS");
	LinkedList_vidInsertion(13, "MSKPALPLASLP");
	LinkedList_vidInsertion(15, "asasasa");
	LinkedList_vidInsertion(18, "zppopiu");
	LinkedList_vidInsertion(20, "monoply");
	LinkedList_vidInsertion(4, "matrix");
	LinkedList_vidInsertion(1, "poma");
	
	
	BOOKS_vidInsertion(12345, "Dickens", 10);
	BOOKS_vidInsertion(12444, "LIAm", 10);
	BOOKS_vidInsertion(55789, "johana", 10);
	BOOKS_vidInsertion(66897, "sarah", 10);
	BOOKS_vidInsertion(44758, "kos", 10);
	

	show();
	BOOKS_show();
	
	Borrow_vid(22, 12444);
	Borrow_vid(22, 12345);
	Borrow_vid(22, 12345);
	Borrow_vid(22, 12345);
	Borrow_vid(22, 12345);
	Borrow_vid(5, 12345);
		Borrow_vid(1, 12345);
	Borrow_vid(5, 12345);
	Borrow_vid(5, 12345);
	Borrow_vid(5, 12345);
	Borrow_vid(5, 12345);
	Borrow_vid(5, 12345);
	Borrow_vid(1, 12345);
	Borrow_vid(1, 12345);
	Borrow_vid(255, 12345);	
	show();
	
	
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	RETURN_vid(5, 12345);
	
	RETURN_vid(1, 12345);
	RETURN_vid(22, 12444);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	RETURN_vid(22, 12345);
	BOOKS_show();
	
}

/********************************* READY *********************************/
// Initialize members list
void LinkedList_vidInitialize(void)
{
	// Initializing list
	root_member = malloc(sizeof(members));
	root_member -> NAME_STRUCT = NULL;
	root_member -> NEXT_STRUCT	= NULL;
	root_member -> ID_STRUCT = 0;
	root_member -> INDEX_STRUCT = 0;
	for(int i = 0; i < AVAILABLE_SHARES; i++)
	{
		root_member -> MEMBER_CARD_BOOKS[i] = 0;
	}
	
	ptr_member = root_member;
}


/********************************* READY *********************************/
// Insertion for values from user
bool LinkedList_vidInsertion(char id, char *name)			// if still, you can change to u8
{
	int k = 0, i = 0;
	
	// Pointer to check for repeated IDs
	members *tmp_detect = NULL;
	tmp_detect = search(id);
	
	// Invalid ID
	if(tmp_detect)
	{
		printf("\nERROR_INSERTION: Repeated ID in the system\n\n");
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

	// Insert patient details
	tmp -> NEXT_STRUCT = ptr_member -> NEXT_STRUCT;

	tmp -> ID_STRUCT = id;
	tmp -> INDEX_STRUCT = INDEX_MEMBERS_GLOBAL;
	
	for(i = 0; i < k ; i++)
	{
		tmp ->  NAME_STRUCT[i] = name[i];
	}
	tmp ->  NAME_STRUCT[i] = '\0';
	
	for(int i = 0; i < AVAILABLE_SHARES; i++)
	{
		tmp -> MEMBER_CARD_BOOKS[i] = 0;
	}
	

	// Update list
	ptr_member -> NEXT_STRUCT = tmp;

	// Indicate success
	printf("MEMBER INSERTED \n\n");
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


// To search for a member
members *search (char id)
{
	// Start after the root
	ptr_member = root_member -> NEXT_STRUCT;
	int value = 0;
	bool found = false;
	
	members *tmp = NULL;
	

	// Iterating over the linked list after root node
	for(int i = 1; i <= NoOfMembers; i++)
	{
		if(id == ptr_member -> ID_STRUCT)
		{
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
void Borrow_vid(char id, unsigned long int serial)
{
	char B_flag = 0;
	int index = 0;
	bool valid_copies = false;
	
	// Search for member
	members *tmp = search(id);
	
	// Search for the book
	index = BOOKS_search(serial);
	
	if(!tmp)
	{
		// Invalid ID
		printf("\n\nERROR_ID: ID not found \n\n");
	}
	else
	{
		// Valid Serial 
		if( index != DoesNot_exist)
		{
			// Scan for empty member card index
			for(int j = 0; j < AVAILABLE_SHARES; j++)
			{
				if(tmp -> MEMBER_CARD_BOOKS[j] == 0)
				{		
					valid_copies = BOOKS_COPIES_DECAY();
					if(valid_copies)
					{
						// Borrow and submit in MEMBER_CARD_BOOKS[] with Book index in BOOKS list
						tmp -> MEMBER_CARD_BOOKS[j] = index;
						printf("\n\nBOOK BORROWED SUCCESSFULLY: \n\n");
						printf("\tlocation %d in member card books for %s is reserved with book %d \n", j, tmp -> NAME_STRUCT, index);
						B_flag = 1;
						j = AVAILABLE_SHARES;					
					}
					else
						printf("\n\nERROR_BOOKS: Book is out of Copies \n\n");
						
				}
				else;
			}
		}
		else
		{
			printf("\n\nInvalid serial number \n\n");
		}
		
		if(!B_flag)
		{
			printf("\n\nERROR_MEMBERS: MEMBER_CARD_BOOKS is full \n\n");
		}
	}
}


bool delete (char id)
{
	if (!ptr_member -> NEXT_STRUCT)
	{
		return false;
	}

	// save the current node
	members *last_before_delete = ptr_member;
	// update new ptr
	ptr_member = ptr_member -> NEXT_STRUCT;
	// save next node
	members *node_after_ptr = ptr_member -> NEXT_STRUCT;

	// DELETION SEQUENCE
	if(ptr_member -> ID_STRUCT == id)
	{
		// Delete and shift
		free(ptr_member);
		last_before_delete -> NEXT_STRUCT = node_after_ptr;
		ptr_member = last_before_delete;
		NoOfMembers--;
		return true;
    }
	else
	{
		delete (id);
	}
	return true;
}



bool show(void)
{
	ptr_member = root_member -> NEXT_STRUCT;
	printf("\n\nNoOfMembers are :%d \n\n", NoOfMembers);
	printf("MEMB_ID, MEMB_NAME, MEMB_BOOKS: \n\n");

	// Only root is no valid list
	if(!ptr_member)
	{
		printf("\nNO Members \n\n");
		ptr_member = root_member;
		return false;
	}

	do
	{
		printf("\t%d, %s, BOOKS:", ptr_member -> ID_STRUCT, ptr_member -> NAME_STRUCT);
		
		// Print Card details
		for(int i = 0; i < AVAILABLE_SHARES; i++)
		{
			printf("\t %d", ptr_member -> MEMBER_CARD_BOOKS[i]);
		}
		printf("\n");
		ptr_member = ptr_member -> NEXT_STRUCT;
	}
	while(ptr_member != NULL);
	
	ptr_member = root_member;
	printf("\n");
	printf("The whole members are showed\n\n");
	return true;
}


// RETURN from books
void RETURN_vid(char id, unsigned long int serial)
{
	char R_flag = 0;
	int index = 0;
	bool valid_copies = false;
	
	// Search for member
	members *tmp = search(id);
	
	// Search for the book
	index = BOOKS_search(serial);
	
	if(!tmp)
	{
		// Invalid ID
		printf("\n\nERROR_ID: ID not found \n\n");
	}
	else
	{
		// Valid Serial 
		if( index != DoesNot_exist)
		{
			// Scan for empty member card index
			for(int j = 0; j < AVAILABLE_SHARES; j++)
			{
				if(tmp -> MEMBER_CARD_BOOKS[j] == index)
				{		
					BOOKS_COPIES_INCREASE();
					
					// Return and remove from MEMBER_CARD_BOOKS[]
					tmp -> MEMBER_CARD_BOOKS[j] = 0;
					printf("\n\nBOOK RETURNED SUCCESSFULLY: \n\n");
					printf("\tlocation %d in member card books for %s is now free for use\n\n", j, tmp -> NAME_STRUCT, index);
					R_flag = 1;
					j = AVAILABLE_SHARES;					

				}
				else;
			}
		}
		else
		{
			printf("\n\nInvalid serial number \n\n");
		}
		
		if(!R_flag)
		{
			printf("\n\nERROR_MEMBERS: No such book in you MEMBER_CARD_BOOKS\n\n");
		}
	}
}
