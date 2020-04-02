/*
 * KeyPad.c
 *
 *  Created on: Aug 28, 2019
 *      Author: Newname
 */


/*
 * KEY_PAD.C
 *
 *  Created on: Aug 27, 2019
 *      Author: Newname
 */

#include "../MCAL/DIO.h"
#include "KEY_PAD.h"
#include "util/delay.h"
#include "LCD.h"
#include "BOOKS.h"
#include "MEMBERS.h"


#define	Insert_new_book			'1'
#define	Insert_new_member		'2'
#define	Borrow					'3'
#define Return					'4'




// Flag1 for input1, flag2 for input2
u8 location = 0, X = 0;

u8 result = 0, times = 0;


// General to Accumulate any input in
char General_Purpose_String[15] = {0}, GPS_Index = 0;


// Globals for BOOKS & MEMBERS
char id = 0, copies = 0, ISBN[13] = {0};
char Name[10] = NULL;
short int serial = 0;

// flags for Globals for BOOKS & MEMBERS 
char id_flag = 0, serial_flag = 0, ISBN_flag = 0;
char Name_General_flag = 0, copies_flag = 0;


// For keypad locker only
u8 character[12][4] = {
						'0', '1', '2', '3',
						'4', '5', '6', '7',
						'8', '9', '=', '~',
						'%', '&', '@', '#',		
						
						'a', 'b', 'c', 'd',
						'e', 'f', 'g', 'h',
						'i', 'j', '=', 'k',
						'l', 'm', 'n', '#',
						
						'o', 'p', 'q', 'r',
						's', 't', 'u', 'v',
						'w', 'x', '=', 'y',
						'z', ';', ':', '#'
											};



// Columns are input, Rows are output
void KeyPad_vidInitialize(void)
{
	// Set low nibble columns are input and pulled up
	DIO_vidSetPinxDir(KEY_PAD_PORT, COL1, INPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, COL2, INPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, COL3, INPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, COL4, INPUT);

	// Set high nibble rows as output
	DIO_vidSetPinxDir(KEY_PAD_PORT, ROW1, OUTPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, ROW2, OUTPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, ROW3, OUTPUT);
	DIO_vidSetPinxDir(KEY_PAD_PORT, ROW4, OUTPUT);

	// Rows are all  zeros
	DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 0);
	DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 0);
	DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 0);
	DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 0);

	KeyPad_vidKey_Pressed();

}


u8 KeyPad_vidKey_Pressed(void)
{
	while(1)
	{
		// 1st stage Make sure key is released
		do
		{
			// Rows are all  zeros
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 0);
		}
		while((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) != 0x0f);

		// 2nd stage
		do
		{
			do
			{
				// delay for  noise
				_delay_ms(20);
			}
			while((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) == 0x0f);

			// Delay for De_bounce
			_delay_ms(20);
		}
		while((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) == 0x0f);


		while(1)
		{
			// 3rd stage
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 1);

			if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) != 0x0f)
			{
				location = X;		//0
				break;
			}

			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 1);

			if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) != 0x0f)
			{
				location = X + 1;		//1
				break;
			}

			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 0);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 1);

			if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) != 0x0f)
			{
				location = X + 2;		//2
				break;
			}

			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW1, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW2, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW3, 1);
			DIO_vidSetPortBitValue(KEY_PAD_PORT, ROW4, 0);

			if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) != 0x0f)
			{
				location = X + 3;		//3
				break;
			}

		}


		// Check for column location
		if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) == 0x0E)
			result = character[location][COL1];
		if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) ==  0x0D)
			result = character[location][COL2];
		if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) ==  0x0B)
			result = character[location][COL3];
		if((DIO_GetPinValue(KEY_PAD_PORT) & 0x0f) ==  0x07)
			result = character[location][COL4];


		// Clear display by a button
		if (result == character[X + 3][3])
		{
			// Change keyPad on Demand
			X = (X + 4) % 12;
		}
	}
	return result;
}


// Fetch string for every new input
char *KeyPad_CharAccumulateString(char result)
{
	// For new inputs remeber to set GPS_Index = 0
	General_Purpose_String[GPS_Index] = result;
	GPS_Index++;
	General_Purpose_String[GPS_Index] = '\0';

	
	return General_Purpose_String;
}


// From string of number chars to int
short int StringToInt(void)
{
	char j = 0, k = 0;
	short int sum = 0;
	
	// Get string length
	while(General_Purpose_String[j] != '\0')
		j++;
	
	k = j;
	
	// Get serial number from string
	for(j = 0; General_Purpose_String[j] != '\0'; j++)
	{
		// Serial is global variable
		sum += (General_Purpose_String[j] % 48) * pow(10,k-1);

	}
	return sum;
}


// Copy string 
void CopyString(void)
{
	// Get Name
	for(j = 0; General_Purpose_String[j] != '\0'; j++)
	{
		// Serial is global variable
		Name[j] = (General_Purpose_String[j]);

	}
	Name[j] = '\0';
}


// Pass string to the correspoinding field inside its operation
void KEY_PAD_vidOperation(char operation)
{
	// Detect operations
	switch(operation)
	{
		case Insert_new_book:
			// Sequemtial insertion
			
			if(!Name_General_flag)
			{
				// Call to insert name and submit the string
				CopyString();
				Name_General_flag = 1;
			}
			else if(!ISBN_flag)
			{
				// Call to submit ISBN and submit the string
				serial = StringToInt();
				ISBN_flag = 1;
			}
			else if(!copies_flag)
			{
				// Call to submit copies and submit the string
				copies = StringToInt();
				copies_flag = 1;
			}
			else
			{
				// Make sure you checked for 3 inputs
				BOOKS_vidInsertion(serial, name, copies);	
					
				// Reset for recheck
				Name_General_flag = 0;
				copies_flag = 0;
				ISBN_flag = 0;
			}
			
			GPS_Index = 0;
			
			break;
			
			
		case Insert_new_member:
			// Sequential insertion

			if(!id_flag)
			{
				// return to insert id and submit the string 
				id = StringToInt();
				id_flag = 1;
			}
			else if(!Name_General_flag)
			{
				// return to submit ISBN and submit the string
				CopyString();
				Name_General_flag = 1;
			}
			else
			{
			LinkedList_vidInsertion(id, name);
			
			// Reset for recheck
			id_flag = 0;
			Name_General_flag = 0;				
			}
			
			GPS_Index = 0;
			
			break;


		case Borrow:
			// Sequential insertion

			if(!id_flag)
			{
				// return to insert id and submit the string 
				id = StringToInt();
				id_flag = 1;
			}
			else if(!ISBN_flag)
			{
				// return to submit ISBN and submit the string
				serial = StringToInt();
				ISBN_flag = 1;
			}
			else
			{
				Borrow_vid(id, serial);
			
				// Reset for recheck
				id_flag = 0;
				ISBN_flag = 0;
			}
			
			GPS_Index = 0;
			
			break;

		case Return:
			// Sequential insertion
		
			if(!id_flag)
			{
				// return to insert id and submit the string 
				id = StringToInt();
				id_flag = 1;	
			}
			else if(!ISBN_flag)
			{
				// return to submit ISBN and submit the string
				serial = StringToInt();
				ISBN_flag = 1;			
			}
			else
			{
				// Insert into the list and set ready to overwrite
				RETURN_vid(id, serial);
				id_flag = 0;
				ISBN_flag = 0;				
			}
			
			GPS_Index = 0;
			break;
			
		default:
			break;
	}
}









/*		
				unsigned short int input; // 16 bits

				
				ISBN[4] = '\0';
				index = 0;
				times = 1000;
				
				// Fetch input from structre
				for(char iii = 0; ISBN[iii] != '\0'; iii++)
				{
					input = ISBN[iii] *times;
					times /=10;
				}



*/









/*






		// INdication for "=" sign and start specific operation
		else if(result == character[X + 2][2] && operation_flag == 1 && !OP)
		{
			operation_flag = 0;
			Operation(OP);
		}
		
		// Execute operation
		else if(result == character[X + 2][2] && operation_flag == 0)
		{
			
			operation_flag = 1;
			OP = 0;
			IF(EX_Insertion_book)
			{
				BOOKS_
			}
			
			

			// Return to the main function in lock.c
			index = 0;

			break;
		
		}
		
		// Fetch numbers for operation
		else
		{
			// Get input from user
			if(operation_flag)
			{
				OP = result;
			}
			else
			{
				if(EX_Insertion_book)
				{
					// Result is saved in ISBN 
					ISBN[index] = result % 48;
					index++;					
				}
				else if(EX_Insertion_member)
				{
					
				}
					
				else if(EX_Borrow)
				{
					
				}
				else if(EX_Return)
				{
					
				}
			}
		}*/
