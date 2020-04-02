#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "st.h"


int main(void)
{
	int x = 0;
	bool invalid_op = false, del_entire = false;

	printf("\nPLEASE WAIT WHILE CREATING THE HEAD NODE...\n");
	sleep(1);
	// Initializing root node for linked list
	initialize();

	// infinite loop
	while(1)
	{
		restart;
		flag();
		invalid_op = false;

		// Prompting user for mods
		printf("\nchoose operation \n");
		printf(" 	1- insertion \n");
		printf("	2- search for number  \n");
		printf("	3- SHOW THE LIST\n");
		printf("	4- Deletion for a single node\n");
		printf("	5- Deletion for the entire list\n");
		printf("	6- EXIT\n");
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
				restart();
				printf("\nvalue\t:");
				int value = 0;
				scanf("%d", &value);
				delete_single(value);
				break;
			case 5:
				restart();
				del_entire = delete_entire();
				break;
			case 6:
				restart();
				delete_entire();
				return 1;
				break;
			default :
				printf("\nERROR: INVALID OPERATION \n");
				//invalid_op = true;
				break;
		}

		/*if(invalid_op)
		{
			restart();
			delete_entire();
			return 1;
		}*/

		// Initialize NEW LIST
		if(del_entire)
		{
			printf("DELETION COMPLETED! \n");
			printf("\nPLEASE WAIT WHILE CREATING THE HEAD NODE...\n");
			sleep(1);
			del_entire = false;
			
			// Reinitialize root
			initialize();
			restart();
		}

	}
}
