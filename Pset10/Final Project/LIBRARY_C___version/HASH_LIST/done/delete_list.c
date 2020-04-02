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