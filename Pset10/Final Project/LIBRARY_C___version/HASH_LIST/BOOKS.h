


#ifndef BOOKS_H_
#define BOOKS_H_

void BOOKS_vidInitialize(void);
bool BOOKS_vidInsertion(unsigned long int serial, char *name);
char BOOKS_u8DeleteEntire(void);
void BOOKS_vidRestart (void);


bool BOOKS_search (unsigned long int serial);
void BOOKS_restart_vip(void);
bool BOOKS_show(void);
bool BOOKS_delete (unsigned long int serial);




#endif