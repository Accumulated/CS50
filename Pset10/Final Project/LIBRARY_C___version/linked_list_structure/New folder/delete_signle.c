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