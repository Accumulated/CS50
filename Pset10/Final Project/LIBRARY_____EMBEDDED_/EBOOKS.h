


#ifndef BOOKS_H_
#define BOOKS_H_


#include <stdbool.h>



void BOOKS_vidInitialize(void);
bool BOOKS_vidInsertion(char *serial, char *name, char copies);
u8 BOOKS_search (char *serial, char index);


char BOOKS_u8DeleteEntire(void);
void BOOKS_vidRestart (void);
void BOOKS_restart_vip(void);
//bool BOOKS_delete (char *serial);


bool BOOKS_show(void);
bool BOOKS_COPIES_DECAY(void);
bool BOOKS_COPIES_INCREASE(void);
bool CompareString(char *str1, char* str2);
u8 LengthString(char *str1, char *str2);


#define DoesNot_exist	0


#endif
