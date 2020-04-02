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