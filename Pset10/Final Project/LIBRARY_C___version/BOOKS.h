


#ifndef BOOKS_H_
#define BOOKS_H_

void BOOKS_vidInitialize(void);
bool BOOKS_vidInsertion(unsigned int serial, char *name, char copies);
bool BOOKS_show(void);


int BOOKS_search (unsigned int serial);
bool BOOKS_COPIES_DECAY(void);
bool BOOKS_COPIES_INCREASE(void);


void BOOKS_restart_vip(void);
void BOOKS_vidRestart (void);
bool BOOKS_delete (unsigned int serial);
char BOOKS_u8DeleteEntire(void);


#define DoesNot_exist	0


#endif