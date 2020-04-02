#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// Define linked list structure
typedef struct node
{
	int num;
	struct node *next;
	int index;
}node;

// identify root and a ptr to move from root
node *root, *ptr;
int NoOfNodes = 0, insertion_flag = 0;

// Prototypes
bool insertion(void);
bool search(void);
bool show(void);
bool delete (int value);
bool delete_entire(void);


int main(void)
{
	int x = 0;
	bool invalid_op = false, del_entire = false;

	// Initializing root node for linked list
	root = malloc(sizeof(node));
	root -> num = 1;
	root -> index = 0;
	root -> next = NULL;
	NoOfNodes++;

	// infinite loop
	while(1)
	{
		ptr = root;
		insertion_flag = false, invalid_op = false;

		// Prompting user for mods
		printf("\nchoose operation \n");
		printf(" 	1- insertion \n");
		printf("	2- search for number  \n");
		printf("	3- SHOW THE LIST\n");
		printf("	4- Deletion for a single node\n");
		printf("	5- Deletion for the entire list\n");
		printf("\nOPERATION #NUMBER \t: ");
		scanf("%d", &x);

		switch(x)
		{
			case 1:
				insertion();
				break;
			case 2:
				search();
				break;
			case 3:
				show();
				break;
			case 4:
				ptr = root;
				printf("\nvalue\t:");
				int value = 0;
				scanf("%d", &value);
				delete(value);
				break;
			case 5:
				ptr = root;
				del_entire = delete_entire();
				break;
			default :
				printf("\nERROR: INVALID OPERATION \n");
				invalid_op = true;
				break;
		}

		if(invalid_op)
		{
			ptr = root;
			delete_entire();
			return 1;
		}

		// Initialize NEW LIST
		if(del_entire)
		{
			printf("DELETION COMPLETED! \n");
			del_entire = false;
			// Reinitialize root
			NoOfNodes = 1;
			root = malloc(sizeof(node));
			root -> num = 1;
			root -> index = 0;
			root -> next = NULL;
			ptr = root;
		}

	}
}

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
	return(true);
}


bool delete (int value)
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

    delete (value);
	return true;
}