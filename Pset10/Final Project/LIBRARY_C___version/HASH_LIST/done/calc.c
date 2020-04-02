// Insert a new patient (node)
bool insertion(void)
{
	// Prompt user for valid input only (> 1)
	int id_given = 0;
	do
	{
		printf("\nID :");
		scanf("%d", &id_given);
	}
	while(id_given < 1);
	
	// Check for ID in the system
	bool ins_flag = search(id_given);
	
	if(ins_flag)
	{
		printf("\nID \"%d\" ALREADY IN SYSTEM\n", id_given);
		return false;
	}
	
	// Inserting sequence initialized
	ptr = root;
	patient *tmp = malloc(sizeof(patient));
	NoOfNodes++;
	
	// Insert patient details
	printf("\nNEW ID, PLEASE ENTER THE FOLLOWING INFORMATION\n");
	tmp -> next = ptr -> next;	
	tmp -> id = id_given;
	assign(tmp);

	// Update list
	ptr -> next = tmp;
	
	printf("\nINSERTION COMPLETED FOR PATIENT \n");
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