#include <stdio.h>
#include <cs50.h>
int main (void)
{
    long cc_number= get_long("Please enter Credit card number:");
    int count =0;    
    // Credit Card length 
    while(cc_number)
    {
        count++;
        cc_number/=10;

        printf("length is %d \n",count);
    }
    printf("length is %d \n",count);
}
