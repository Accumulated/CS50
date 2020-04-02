#include <stdio.h>
#include <cs50.h>
//last 2 digits in 16 digits
long score=123456789987654;
int main(void)
{
    int b_l=0;
    int i=0;
    int l;
    score /= 10000000000000;
       printf("the number whole= %ld \n",score);
    do
{    
    if(b_l ==0 && i==0)
    {
        b_l=score % 10;
        i++;
    }
    l=score % 10;
    score /= 10;
    }
    while(score);
    printf("before last number= %d \n",b_l);
    printf("last number= %d \n",l);
}
