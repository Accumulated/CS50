#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
int ch_flag2 = 0, ch_flag1 = 0, times = 0;
int main(void)
{
    char pasw[3];
    char c = '\0';
    pasw[0] = 'A';
    pasw[1] = 'A';
    pasw[2] = 'A';
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        pasw[0] = c;
        printf("string = \t: %s \n", pasw);
        if (c > 89 && c <= 97)
        {
            c = 'a';
            pasw[0] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag1 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag1 == 1)
        {
            ch_flag1 = 0; 
            pasw[1]++;               
            times++;
            c = '@';
            if (pasw[1] > 90 && pasw[1] <= 97)
            {
                pasw[1] = 'a';
            }
            else if (pasw[1] > 122)
            {
                // ADD check first later then reassign
                // Session #3 flag
                ch_flag2 = 1;
                pasw[1] = 'A';

            } 
        }
        //////// Session 2 //////
        if (ch_flag2 == 1)
        {
            ch_flag2 = 0; 
            pasw[2]++;               
            times++;
            c = '@';
            if (pasw[2] > 90 && pasw[2] <= 97)
            {
                pasw[2] = 'a';
            }
            else if (pasw[2] > 122)
            {
                // ADD check first later then reassign
                // Session #1 flag
                //printf("string final = %s",pasw);
                c=0;
            } 
        }
    }            
}
