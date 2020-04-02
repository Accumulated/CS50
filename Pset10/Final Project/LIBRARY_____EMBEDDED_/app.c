/*
 * app.c
 *
 *  Created on: Sep 16, 2019
 *      Author: Newname
 */

#include "MCAL/DIO.h"
#include "HAL/LCD.h"
#include "HAL/EKEY_PAD.h"
#include "macros.h"
#include "types.h"
#include "EBOOKS.h"
#include "EMEMBERS.h"
#include <util/delay.h>


void DISPLAY_OnDemand(char *str1, char *str2);


int main(void)
{
	LCD_vidInitialize();
	BOOKS_vidInitialize();
	LinkedList_vidInitialize();

	LinkedList_vidInsertion("1", "Joey");
	LinkedList_vidInsertion("2", "John");
	LinkedList_vidInsertion("3", "Mark");
	LinkedList_vidInsertion("4", "Rose");
	LinkedList_vidInsertion("5", "Sarah");




	BOOKS_vidInsertion("0060832819", "The Zahir", 5);	//
	BOOKS_vidInsertion("0062315005", "The Alchemist", 5);		//
	BOOKS_vidInsertion("1509825428", "Bleak House", 5);		//
	BOOKS_vidInsertion("0141439675", "Hard times", 5);			//



	while(1)
	{
		LCD_vidClearOnDemand(1, 32);

		DISPLAY_OnDemand("1-INSER BOOK", "2-INSER MEMBER");

		DISPLAY_OnDemand("3-BORROW BOOK", "4-RETURN BOOK");

		DISPLAY_OnDemand("5-Show all books", "6-Show all members");

		DISPLAY_OnDemand("7-Member's INFO.", "                 ");

		LCD_String("OPERATION NO. :");
		LCD_vidGoTo(1, 2);


		KeyPad_vidInitialize();

		if(DEAD_SIGNAL_TERMINATE)
		{
			DEAD_SIGNAL_TERMINATE = 0;

			// Reset pointers to the head ot its linked list
			restart_vip();
			BOOKS_restart_vip();

			// Delete the whole data base
			LinkedList_u8DeleteEntire();
			BOOKS_u8DeleteEntire();
			break;
		}
	}
}

void DISPLAY_OnDemand(char *str1, char *str2)
{
	LCD_vidClearOnDemand(1, 32);
	// Display 1st string
	LCD_vidGoTo(1, 1);
	LCD_String(str1);
	// Display 2nd string
	LCD_vidGoTo(1, 2);
	LCD_String(str2);

	_delay_ms(1300);
	// Clear whole display
	LCD_vidClearOnDemand(1, 32);
}

