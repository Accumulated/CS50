#include <stdio.h>
#include <cs50.h>
//from second to last digit
long score=75295647369786;
//from 1st to last digit
int main(void)
{
int sum=0 ; int i,score_x;

    do
{   
    printf("%ld\n", score % 10);    
        sum=sum+score%10;
    score /= 100;
}
    while(score);
    printf(" summagtion = %d \n",sum);
}
