#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
int ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0, times = 0;
int main(void)
{
    char pasw[6];
    char c = '\0';
    int length = 6;
    pasw[0] = 'A';
    pasw[1] = 'A';
    pasw[2] = 'A';
    pasw[3] = 'A';
    pasw[4] = 'A'; 
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        pasw[4] = c;
        printf("string = \t: %s \n", pasw);
        if (c > 89 && c <= 97)
        {
            c = 'a';
            pasw[4] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag3 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag3 == 1)
        {
            ch_flag3 = 0; 
            pasw[3]++;               
            times++;
            c = '@';
            if (pasw[3] > 90 && pasw[3] <= 97)
            {
                pasw[3] = 'a';
            }
            else if (pasw[3] > 122)
            {
                // ADD check first later then reassign
                // Session #3 flag
                ch_flag2 = 1;
                pasw[3] = 'A';

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
                ch_flag1 = 1;
                pasw[2] = 'A';
            } 
        }
        // Session 1 ////////
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
                // Session #0 flag
                ch_flag0 = 1;
                pasw[1] = 'A';
            } 
        }
        // Session 0 ////////
        if (ch_flag0 == 1)
        {
            ch_flag0 = 0; 
            pasw[0]++;               
            times++;
            c = '@';
            if (pasw[0] > 90 && pasw[0] <= 97)
            {
                pasw[0] = 'a';
            }
            else if (pasw[0] > 122)
            {
                // ADD check first later then reassign
                // last session no flag
                pasw[0] = 'A';
                printf("string final = %s",pasw);
                return 1;
            } 
        }       
    }            
}
