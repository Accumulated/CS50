

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "2.h"


// Define linked list structure
typedef struct members
{
	char *NAME_STRUCT;
	char INDEX_STRUCT;
	char ID_STRUCT;
	struct members *NEXT_STRUCT;

}members;

// identify root and a ptr to move from root
members *root_member, *ptr_member;
int NoOfNodes = 0, insertion_flag = 0;


// Indication for members locations in members_list
char INDEX_MEMBERS_GLOBAL = 0;





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
	
	ptr_member = root_member;
}


/********************************* READY *********************************/
// Insertion for values from user
bool LinkedList_vidInsertion(char id, char *name)			// if still, you can change to u8
{
	
	int k = 0;
	
	// Inserting sequence initialized
	ptr_member = root_member;
	members *tmp = malloc(sizeof(members));
	
	// For future reference
	NoOfNodes++;
	INDEX_MEMBERS_GLOBAL++;

	

	// Get member's name length
	while(name[k] != '\0')
	{
		k++;
	}
	
	tmp -> NAME_STRUCT = malloc(k *sizeof(char));

	// Insert patient details
	tmp -> NEXT_STRUCT = ptr_member -> NEXT_STRUCT;

	tmp -> ID_STRUCT = id;
	tmp -> INDEX_STRUCT = INDEX_MEMBERS_GLOBAL;
	for(int i = 0; i < k ; i++)
	{
		tmp ->  NAME_STRUCT[i] = name[i];
		printf("now processing %c \n\n", name[i]);
	}
	

	// Update list
	ptr_member -> NEXT_STRUCT = tmp;

	// Indicate success
	printf("success \n\n");
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
	NoOfNodes = 0;
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


bool search (char id)
{
	// Start after the root
	ptr_member = root_member -> NEXT_STRUCT;
	int value = 0;
	bool found = false;

	// Iterating over the linked list after root node
	for(int i = 1; i <= NoOfNodes; i++)
	{
		printf("Now processing  ID :%d\n\n", ptr_member -> ID_STRUCT);
		if(id == ptr_member -> ID_STRUCT)
		{
			printf("\n  ID \'%d\' found at index \[%d]\n", ptr_member -> ID_STRUCT, ptr_member -> INDEX_STRUCT);
			found = true;
		}
		ptr_member = ptr_member -> NEXT_STRUCT;
	}

	if(!found)
	{
		printf("\nNOT FOUND\n");
		ptr_member = root_member;
		return false;
	}

	ptr_member = root_member;
	return true;
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
		NoOfNodes--;
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
	printf("the NoOfNodes is:%d \n", NoOfNodes);
	printf("the list is: \n");

	// Only root is no valid list
	if(!ptr_member)
	{
		printf("\nNO ELEMENTS INSERTED\n");
		ptr_member = root_member;
		return false;
	}

	do
	{
		printf("%d ", ptr_member -> ID_STRUCT);
		ptr_member = ptr_member -> NEXT_STRUCT;
	}
	while(ptr_member != NULL);
	ptr_member = root_member;
	printf("\n");
	return true;
}