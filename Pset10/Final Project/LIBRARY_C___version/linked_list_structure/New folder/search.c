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