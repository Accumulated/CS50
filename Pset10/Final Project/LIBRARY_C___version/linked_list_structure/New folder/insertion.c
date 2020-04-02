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