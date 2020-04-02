//transform from string data type to int data type
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{   
    printf("%s\n",argv[1]);
    string typed =argv[1];
    int key[strlen(typed)];
    
    int Dec = 0, sum = 0,  n_shift = strlen(typed) , multi =0 , times = n_shift-1;
    
    for(int i = 0 ; i < n_shift ; i++)
    {
        multi =0;
        Dec= typed[i] % 48;
        printf("the character processed is %i \n",Dec);
        if(multi == times)
        {
            Dec = Dec*1;
            printf("the summation is %i \n",Dec);
        }
        else
        {
            while( multi < times)
            {
                printf("m is %i \n",multi);
                Dec = Dec*10;
                printf("the summation is %i \n",Dec);
                multi++;
            }
        }
        key[i] = Dec;  
        sum= sum + Dec;
        times--;
    }
       printf("the shift  is %i \n",sum);
  
}

