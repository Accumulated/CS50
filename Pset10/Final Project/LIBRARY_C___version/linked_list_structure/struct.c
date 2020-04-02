#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "st.h"


typedef struct node
{
	int num;
	struct node *next;
	int index;
}node;

// identify root and a ptr to move from root
node *root, *ptr;
int NoOfNodes = 0, insertion_flag = 0;


bool insertion(void)
{
	int location = 0, value = 0;

	// Prompting user for input
	printf("\nvalue\t:");
	scanf("%d", &value);
	printf("\nlocation :");
	scanf("%d", &location);

	// Solve boundary problem
	if(location > NoOfNodes)
	{
		//delete_entire();
		printf("\nERROR: out of bonds \n");
		ptr = root;
		return false;
	}

	ptr = root;
	int index = 0;

	// Buffer to Store the previous node address for current index
	node *tmp = NULL;

	// Indicating location according to linked list
	for(index = 0; index < location; index++)
	{
		insertion_flag = 1;
		tmp = ptr;
		ptr = ptr -> next;
		if (ptr == NULL)
		{
			// Allocate new node and assign to the current ptr -> next
			tmp -> next = malloc(sizeof(node));
			tmp -> next -> next = NULL;
			tmp -> next -> num = value;
			tmp -> next -> index = (index + 1);
			NoOfNodes++;

			printf("\nlocation is at index %d \t", index + 1);
			printf("NEW NODE..BE CAREFULL! \n");

			// Indicate success
			ptr = root;
			return true;
		}
	}

	// Protect root node
	if(!insertion_flag)
	{
		printf("ERROR: PERMISSION DENIED \n");
		return false;
	}

	// Redefine the sequence of nodes
	tmp -> next = malloc(sizeof(node));
	tmp -> next -> next = ptr;
	tmp -> next -> num = value;
	tmp -> next -> index = index;
	NoOfNodes++;

	// Update index
	ptr -> index = (index + 1);
	printf("INSERTION COMPLETED \n");
	ptr = root;
	return true;
}

bool search (void)
{
	// Start after the root
	ptr = root -> next;
	int value = 0;
	bool found = false;

	// Prompt user for input
	printf("\nvalue\t:");
	scanf("%d", &value);

	// Iterating over the linked list after root node
	for(int i = 1; i < NoOfNodes; i++)
	{
		if(value == ptr -> num)
		{
			printf("\n \'%d\' found at index \[%d]\n", value, i);
			found = true;
		}
		ptr = ptr -> next;
	}

	if(!found)
	{
		printf("\nNOT FOUND\n");
		ptr = root;
		return false;
	}

	ptr = root;
	return true;
}

bool show(void)
{
	ptr = root -> next;
	printf("the NoOfNodes is:%d \n", NoOfNodes - 1);
	printf("the list is: \n");

	// Only root is no valid list
	if(!ptr)
	{
		printf("\nNO ELEMENTS INSERTED\n");
		ptr = root;
		return false;
	}

	do
	{
		printf("%d ", ptr -> num);
		ptr = ptr -> next;
	}
	while(ptr != NULL);
	ptr = root;
	printf("\n");
	return true;
}

bool delete_entire(void)
{
	// Buffer to save the previous condition of ptr
	node *last_before_stack = NULL;

	// Checking on the next field
	if(ptr -> next != NULL)
	{
		last_before_stack = ptr;
		ptr = ptr -> next;
		delete_entire();
		ptr = last_before_stack;
	}

	// free current node and return
	free(ptr);
	NoOfNodes--;
	return(true);
}


bool delete_single (int value)
{
	if (!ptr -> next)
	{
		return false;
	}

	// save the current node
	node *last_before_delete = ptr;
	// update new ptr
	ptr = ptr -> next;
	// save next node
	node *node_after_ptr = ptr -> next;

	// DELETION SEQUENCE
	if(ptr -> num == value)
	{
		// Delete and shift
		free(ptr);
		last_before_delete -> next = node_after_ptr;
		ptr = last_before_delete;
		NoOfNodes--;
    }

    delete_single(value);
	return true;
}


void restart(void)
{
	ptr = root;
}

void initialize(void)
{
	root = malloc(sizeof(node));
	root -> num = 1;
	root -> index = 0;
	root -> next = NULL;
	NoOfNodes = 1;
}

void flag(void)
{
	insertion_flag = false;
}




