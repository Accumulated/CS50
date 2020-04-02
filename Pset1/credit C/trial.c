#include <stdio.h>
#include <cs50.h>
//from second to last digit
long score=775295647369786;
int main(void)
{
int sum=0 ; int i,score_x;
score /= 10; 
    do
{   
    printf("%ld\n", score % 10);
    if(2*(score % 10) > 9)
    {
        score_x=2*(score % 10);
    for(i=0;i<=1;i++)
    {        
        sum=sum+score_x%10;        
        score_x /= 10; 
    }
    }
    else
    {
    sum=sum+2*(score % 10);
    }
    score /= 100;
}
    while(score);
    printf(" summagtion = %d \n",sum);
}
