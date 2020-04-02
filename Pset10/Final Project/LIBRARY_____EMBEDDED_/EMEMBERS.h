
#ifndef MEMBERS_H_
#define MEMBERS_H_

#include <stdbool.h>


void LinkedList_vidInitialize(void);
bool LinkedList_vidInsertion(char *id, char *name);
void LinkedList_vidCompanion(u16 show);
bool LinkedList_show(void);
void LinkedList_vidSearch(char *ptr, char show);


char LinkedList_u8DeleteEntire(void);
void LinkedList_vidRestart (void);
void restart_vip(void);

//bool delete (char *id);

void Borrow_vid(char *id, char *serial);

void RETURN_vid(char *id, char *serial);







#endif
