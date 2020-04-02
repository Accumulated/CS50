/*
 * KEY_PAD.h
 *
 *  Created on: Aug 24, 2019
 *      Author: Newname
 */

#ifndef HAL_KEY_PAD_H_
#define HAL_KEY_PAD_H_

#define KEY_PAD_PORT	1

#define COL1	0
#define COL2	1
#define COL3	2
#define COL4	3
#define ROW1	4
#define ROW2	5
#define ROW3	6
#define ROW4	7




void caluculation_stage(void);
u8 KeyPad_vidKey_Pressed(void);
void KeyPad_vidInitialize(void);


extern char EX_Insertion_book;	
extern char EX_Insertion_member;
extern char	EX_Borrow;	
extern char EX_Return;


#endif /* HAL_KEY_PAD_H_ */
