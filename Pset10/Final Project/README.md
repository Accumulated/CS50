Project: "Library system Using AVR microcontroller"

/*Project can be updated to work with RFID technology as for future reference*/

Description:

	In this project the system process the following:
	inserting new books in the library, adding new members,
	fetching information about exsisting members, tradition of borrow and
	return for books from/to library, maintain record about the person
	who has taken the book or even returned it.

TOOLS:

Software:
	Embedded C, along with Data structres i.e. linked lists and arrays.
	Eclipse IDE
	GCC compiler

Hardware:
	ATmega32 - AVR Microcontrollers
	LCD
	Switches to act as if it were keypad.

Files Attached:
	EBOOKS.c: to process operations of inserting, searching via ISBN or index for books
	, delete a book from library, show entire books available.

	EMEMBERS.c: to process borrow and return operations for members,
	adding new members, search for infromation and record about each member,
	see whole members in the DataBase

	MCAL/DIO.c: is used to help with interfacing the AVR microcontroller

	HAL/LCD.c: to print strings, values and different outputs on a 2*16 LCD

	HAL/EKEY_PAD.c: interface keypad switches with AVR and also to get input from user
	and submit it into the right structure or Database


More Details:

printf function simulation:
			LCD is used to Display any content that helps
			the user understands what's going on behind the screen

scanf function simulation:
			Keypad is used as an input to the system

*AVR microcontroller is used to interface with the previous two, for the system to be alive

