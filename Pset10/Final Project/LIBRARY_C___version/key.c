#include <stdio.h>
#include <stdlib.h>

char index = 0;
unsigned char ISBN[17] = {0};



// For keypad locker only
char character[12][4] = {
						'0', '1', '2', '3',
						'4', '5', '6', '7',
						'8', '9', '=', '~',
						'%', '&', '@', '#',		
						
						'a', 'b', 'c', 'd',
						'e', 'f', 'g', 'h',
						'i', 'j', 'k', 'l',
						'm', 'n', 'o', 'p',
						
						'q', 'r', 's', 't',					
						'u', 'v', 'w', 'x',
						'y', 'z', '.', ',',
						';', ':', '{', '}',
											};



int main(void)
{

	/*
	for(int j = 0; j < 4; j++)
	{
		for(int k = 0; k < 4; k++)
		{
			ISBN[j*4 +k] = character[j][k];
		}
		
	
	}
	*/
	ISBN[16]='\0';
	printf("%s\n", ISBN);
	
}



// Insertion for values from user
void insertion (u8 value)			// if still, you can change to u8
{

	ISBN[index] = values;

	index++;
	// Indicate success
}