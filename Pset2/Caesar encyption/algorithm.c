// ciphering algoritm

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{   
    //printf("%i",(int)argv[0]);
    printf("%s\n",argv[1]);
   // printf("%i",(int)argv[2]);
    while(1)
    {
    int c;
    char x;
    string plain = get_string("type your string : ");
    string s= plain;
    //show the string again
    for(int i = 0, n = strlen(plain) ; i < n ; i++)
    {
        printf("%c\t",plain[i]);
        //printf("the number BECOMES  %c \n",plain[i]+1);
        if((int)plain[i] >= 65 && (int)plain[i] <= 90)
        {
            if(((int)plain[i]+1 ) > 90)
            {
            x= (plain[i]+1 )%91 +65;
           // x=(char)(c);
            printf("the character saved is %c \n",x);
            s[i] = x;       
            }
            else
            {
                x= (plain[i]+1 )%91;
               // x=(char)(c);
                printf("the character saved is %c \n",x);
                s[i] = x;  
            }
        }
        // Small letters
        else if((int)plain[i] >= 97 && (int)plain[i] <= 122)
        {
            if(((int)plain[i]+1 ) > 122)
            {
                x= (plain[i]+1 )%123 +97;
                //x=(char)(c);
                printf("the character saved is %c \n",x);
                s[i] = x;       
            }
            else
            {
                x= ((int)plain[i]+1 )%123;
                //x=(char)(c);
                printf("the character saved is %c \n",x);
                s[i] = x;  
            }    
        }
        else
        {
        }
    }
    printf("\n");
    printf("the whole cipher \" %s \"  \n",s);
    //printf("the whole plain \" %s \"  \n",plain);
}
}
// Capital letters
/*if(plain[i] <= 65 && plain[i] >= 90)
{
    if((plain[i]+1 ) > 90)
    {
    c= (plain[i]+1 )%91 +65;
    x=(char)(c);
    s[i] = x;       
    }
    else
    {
        c= (plain[i]+1 )%91;
        x=(char)(c);
        s[i] = x;  
    }
}
// Small letters
else if(plain[i] <= 97 && plain[i] >= 122)
{
    if((plain[i]+1 ) > 122)
    {
    c= (plain[i]+1 )%123 +97;
    x=(char)(c);
    s[i] = x;       
    }
    else
    {
        c= (plain[i]+1 )%123;
        x=(char)(c);
        s[i] = x;  
    }    
}
else
{
    
}*/

