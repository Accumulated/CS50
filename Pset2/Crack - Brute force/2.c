#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
int ch_flag1 = 0, times = 0;
int main(void)
{
    char pasw[2];
    char c = '\0';
    pasw[0] = 'A';
    pasw[1] = 'A';
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        pasw[0] = c;
        //add check here
        string o_hash = crypt(pasw,"50");
        printf("string = %s \t hash =%s \n", pasw, o_hash);
        //int k = get_int("type any to pass \n");
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
                return 1;
            } 
        }
    }            
}
