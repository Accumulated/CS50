
#ifndef MEMBERS_H_
#define MEMBERS_H_


void LinkedList_vidInitialize(void);
bool LinkedList_vidInsertion(char id, char *name);
bool show(void);


char LinkedList_u8DeleteEntire(void);
void LinkedList_vidRestart (void);
void restart_vip(void);
bool delete (char id);


void Borrow_vid(char id, unsigned long int serial);
void RETURN_vid(char id, unsigned long int serial);






#endif