#include <cs50.h>
#include <stdio.h>
#include <string.h>
bool check(int length, string nano[]);
int main(int argc, string argv[])
{
    bool c_flag ;
    char x;
    // Checking for main argc to be 2
    if (argc == 2)
    {
        // Checking over the input chars.
        c_flag = check(strlen(argv[1]), &argv[1]);
        
        // Sequence for valid input only 
        if (c_flag == true)
        {   
            // Shift amount transformed from String to int
            
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

            // Cipher Generation
            string plain  = get_string("plain text: \t");     
            string s= plain;
            //show the string again
            for(int i = 0, n = strlen(plain) ; i < n ; i++)
            {
                printf("%c\t",plain[i]);
                //printf("the number BECOMES  %c \n",plain[i]+1);
                if((int)plain[i] >= 65 && (int)plain[i] <= 90)
                {
                    if(((int)plain[i]+sum ) > 90)
                    {
                    x= (plain[i]+sum )%91 +65;
                   // x=(char)(c);
                   // printf("the character saved is %c \n",x);
                    s[i] = x;       
                    }
                    else
                    {
                        x= (plain[i]+sum )%91;
                       // x=(char)(c);
                        //printf("the character saved is %c \n",x);
                        s[i] = x;  
                    }
                }
                // Small letters
                else if((int)plain[i] >= 97 && (int)plain[i] <= 122)
                {
                    if(((int)plain[i]+sum ) > 122)
                    {
                        x= (plain[i]+sum )%123 +97;
                        //x=(char)(c);
                        //printf("the character saved is %c \n",x);
                        s[i] = x;       
                    }
                    else
                    {
                        x= ((int)plain[i]+sum )%123;
                        //x=(char)(c);
                        //printf("the character saved is %c \n",x);
                        s[i] = x;  
                    }    
                }
                else
                {
                }
            }
            printf("\n");
            printf("the whole cipher \" %s \"  \n",s);          
                }
        else
        {
            printf(" Usage: ./caesar key \n");
        }
        
    }
    else 
    {
        printf(" Usage: ./caesar key \n");
    }
}



// Check for validation of input
bool check(int length, string nano[])
{
    // Printf(" string = %s \n", nano[0]);
    int c, check = 0 ;
    for (int i = 0 ; i < length ; i++)
    {
        c = (int) nano[0][i];
        //checking for inputs rather than numbers
        if (c >= 48 && c <= 57)
        {
            //    printf("valid input \n");
        }
        else
        {                
            i = length;
            // Printf("INVALID INPUT \n");
            check = 1;
        }
    }
    if (check == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
