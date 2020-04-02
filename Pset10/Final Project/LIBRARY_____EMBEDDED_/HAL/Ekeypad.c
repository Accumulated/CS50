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
#include "EKEY_PAD.h"
#include "util/delay.h"
#include "LCD.h"


#include "../EBOOKS.h"
#include "../EMEMBERS.h"



#define	Insert_new_book			'1'
#define	Insert_new_member		'2'
#define	Borrow					'3'
#define Return					'4'


u8 DEAD_SIGNAL_TERMINATE = 0;

// Flag1 for input1, flag2 for input2
u8 location = 0, X = 0;

u8 result = 0, times = 0;


// General to Accumulate any input in
u8 General_Purpose_String[15] = {0}, GPS_Index = 0;


// Globals for BOOKS & MEMBERS
char id[5] = {0}, copies = 0, ISBN[13] = {0};
char Name[20] = {0};
char serial[13] = {0};


// flags for Globals for BOOKS & MEMBERS 
u8 id_flag = 0, serial_flag = 0, ISBN_flag = 0;
u8 Name_General_flag = 0, copies_flag = 0;


// Indication for which operation and how many submitions in each
u8 operation_flag = 0, operation_fields = 0, operation = 0, BREAK_CODE = 0;


// Prototypes local for tmp usage
void KeyPad_CharAccumulateString(u8 result);
void KEY_PAD_vidOperations(void);
void CopyString(char *ptr);
short int StringToInt(void);
void Operation_Reset(void);
void LCD_OperateResult(void);
void GPS_Reset(void);
void Operation_submit(char x);





// For keypad locker only
u8 character[12][4] = {
						'0', '1', '2', '3',
						'4', '5', '6', '7',
						'8', '9', '@', '~',
						' ', '&', '=', '#',
						
						'a', 'b', 'c', 'd',
						'e', 'f', 'g', 'h',
						'i', 'j', 'n', 'k',
						'l', 'm', '=', '#',
						
						'o', 'p', 'q', 'r',
						's', 't', 'u', 'v',
						'w', 'x', 'y', 'z',
						 ':', ';', '=', '#'
											};

u8 lcd_stage1 = 0, lcd_stage2 = 0, lcd_stage3 = 0;

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


		// change charcters by a button
		if (result == character[(X + 3) % 12][3])
		{
			// Change keyPad on Demand
			X = (X + 4) % 12;
		}
		else if (result == character[11][1])
		{
			// Change keyPad on Demand

			DEAD_SIGNAL_TERMINATE = 1;
		}
		else if (result == character[3][1])
		{
			// DELETE THE PREVIOUS CHAR

			GPS_Index--;
			General_Purpose_String[GPS_Index] = '\0';
			u8 tmp = LCD_u8CurrentLocation_AC();
			LCD_vidInstruction(tmp - 1 + (1<<7), write_operation, IR);
			LCD_String(" ");
			LCD_vidInstruction(tmp - 1 + (1<<7), write_operation, IR);
		}

		// Submit using equal button
		else if (result == character[(X + 3) % 12][2])
		{
			// Change keyPad on Demand
			LCD_vidClearOnDemand(1, 16);

			// Incase of being at the beginning of the program
			if(!operation_flag)
			{
				if(BREAK_CODE)
				{
					BREAK_CODE = 0;
					break;
				}
				LCD_OperateResult();
			}
			else
			{
					KEY_PAD_vidOperations();
			}
		}
		else
		{
			KeyPad_CharAccumulateString(result);
			LCD_vidInstruction(result, write_operation, DR);
		}


	}
	return result;
}

// 1st stage for LCD
void LCD_OperateResult(void)
{
	u8 j = General_Purpose_String[0];
	GPS_Index = 0;

	switch(j)
	{
		case '1':
			LCD_String("NAME:");
			Operation_submit(Insert_new_book);
			LCD_vidGoTo(1, 2);
			break;

		case '2':
			LCD_String("ID:");
			Operation_submit(Insert_new_member);
			LCD_vidGoTo(1, 2);
			break;

		case '3':
			LCD_String("ID:");
			Operation_submit(Borrow);
			LCD_vidGoTo(1, 2);
			break;

		case '4':
			LCD_String("ID:");
			Operation_submit(Return);
			LCD_vidGoTo(1, 2);
			break;

		case '5':
			LCD_String("Book Confirm OP:");
			Operation_submit('5');
			break;

		case '6':
			LCD_String("Member Confirm OP:");
			Operation_submit('6');

			break;

		case '7':
			LCD_String("search ID:");
			Operation_submit('7');
			LCD_vidGoTo(1, 2);
			break;

		default:
			LCD_String("Invalid Operation");
			LCD_vidClearOnDemand(1, 32);
			LCD_vidGoTo(1, 1);
			break;
	}
}


// 2nd stage for LCD
// Pass string to the correspoinding field inside its operation
void KEY_PAD_vidOperations(void)
{
	// Detect operations
	switch(operation)
	{
		case Insert_new_book:
			// Sequential insertion
			
			if(!Name_General_flag)
			{
				// Call to insert name and submit the string
				CopyString(Name);
				Name_General_flag = 1;

				LCD_String("ISBN");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else if(!ISBN_flag)
			{
				// Call to submit ISBN and submit the string
				CopyString(serial);
				ISBN_flag = 1;

				LCD_String("COPIES:");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else if(!copies_flag)
			{
				// Call to submit copies and submit the string
				copies = StringToInt();
				copies_flag = 1;

				LCD_String("Confirm");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else
			{
				// Make sure you checked for 3 inputs
				BOOKS_vidInsertion(serial, Name, copies);
					
				// Reset for recheck
				Name_General_flag = 0;
				copies_flag = 0;
				ISBN_flag = 0;
				LCD_vidClearOnDemand(17, 32);
				Operation_Reset();

			}
			
			GPS_Index = 0;
			GPS_Reset();
			
			break;
			
			
		case Insert_new_member:
			// Sequential insertion

			if(!id_flag)
			{
				// return to insert id and submit the string 
				CopyString(id);
				id_flag = 1;

				LCD_String("NAME:");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else if(!Name_General_flag)
			{
				// return to submit ISBN and submit the string
				CopyString(Name);
				Name_General_flag = 1;

				LCD_String("Confirm");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else
			{
				LinkedList_vidInsertion(id, Name);

				// Reset for recheck
				id_flag = 0;
				Name_General_flag = 0;
				LCD_vidClearOnDemand(17, 32);

				Operation_Reset();
			}
			
			GPS_Index = 0;
			GPS_Reset();
			
			break;


		case Borrow:
			// Sequential insertion

			if(!id_flag)
			{
				// return to insert id and submit the string 
				CopyString(id);
				id_flag = 1;

				LCD_String("ISBN");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else if(!ISBN_flag)
			{
				// return to submit ISBN and submit the string
				CopyString(serial);
				ISBN_flag = 1;

				LCD_String("Confirm");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else
			{
				Borrow_vid(id, serial);
			
				// Reset for checking
				id_flag = 0;
				ISBN_flag = 0;
				LCD_vidClearOnDemand(17, 32);
				Operation_Reset();
			}

			GPS_Index = 0;
			GPS_Reset();
			
			break;

		case Return:
			// Sequential insertion
		
			if(!id_flag)
			{
				// return to insert id and submit the string 
				CopyString(id);
				id_flag = 1;	

				LCD_String("ISBN");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else if(!ISBN_flag)
			{
				// return to submit ISBN and submit the string
				CopyString(serial);
				ISBN_flag = 1;

				LCD_String("Confirm");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else
			{
				// Insert into the list and set ready to overwrite
				RETURN_vid(id, serial);
				id_flag = 0;
				ISBN_flag = 0;
				LCD_vidClearOnDemand(17, 32);
				Operation_Reset();
			}
			
			GPS_Index = 0;
			GPS_Reset();
			break;
			
		// Shows all books in library
		case '5':
			BOOKS_show();
			GPS_Index = 0;
			Operation_Reset();

			break;

		// Shows all member
		case '6':
			LinkedList_show();
			GPS_Index = 0;
			Operation_Reset();
			break;

		// Gives info about specific member
		case '7':
			if(!id_flag)
			{
				// return to submit ID
				CopyString(id);
				id_flag = 1;

				LCD_String("Confirm");
				LCD_vidClearOnDemand(17, 32);
				LCD_vidGoTo(1, 2);
			}
			else
			{
				// Insert into the list and set ready to overwrite
				LinkedList_vidSearch(id, 1);
				id_flag = 0;
				LCD_vidClearOnDemand(17, 32);
				Operation_Reset();
			}

			GPS_Index = 0;
			GPS_Reset();
			break;

		default:
			GPS_Reset();
			GPS_Index = 0;
			break;
	}
}


// Fetch string for every new input
void KeyPad_CharAccumulateString(u8 result)
{
	// For new inputs remeber to set GPS_Index = 0
	General_Purpose_String[GPS_Index] = result;
	GPS_Index++;
	General_Purpose_String[GPS_Index] = '\0';

}


// From string of chars to int
short int StringToInt(void)
{
	u8 j = 0, times = 1;
	u16 sum = 0;

	// Get string length
	while(General_Purpose_String[j] != '\0')
	{
		if(!j)
		{
			j++;
		}
		else
		{
			j++;
			times *= 10;
		}
	}


	// Get serial number from string
	for(j = 0; General_Purpose_String[j] != '\0'; j--)
	{
		// Serial is global variable
		sum += (General_Purpose_String[j] % 48)* times;
		times /=10;
	}

	return sum;
}


// Copy string
void CopyString(char *ptr)
{
	u8 j = 0;

	// Get Name
	for(j = 0; General_Purpose_String[j] != '\0'; j++)
	{
		// Serial is global variable
		ptr[j] = (General_Purpose_String[j]);

	}
	ptr[j] = '\0';
}


// Reset after executing the current operation
void Operation_Reset(void)
{
	// Reset operation fields
	operation = 0;
	operation_flag = 0;
	GPS_Reset();
	BREAK_CODE = 1;

}


// Reset General_Purpose_string with '0' for operation's not to accumulate
void GPS_Reset(void)
{
	for(u8 i = 0; i < sizeof(General_Purpose_String); i++)
	{
		General_Purpose_String[i] = '0';
	}
}


// Submit operation to execute in the next loop
void Operation_submit(char x)
{
	// Clear Display
	LCD_vidClearOnDemand(17, 32);

	// Submit operation global variable
	operation = x;
	operation_flag = 1;
}


