// Declares a dictionary's functionality

#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>


// Prototypes
bool unload(void);
bool check(const char *word);
unsigned int size(void);
bool Library_vidInitialize(void);
bool Library_BoolInsertion(const char *serial);



#endif // LIBRARY_H
