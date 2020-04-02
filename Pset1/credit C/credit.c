#include <stdio.h>
#include <cs50.h>
void check(long number_c, int count);  
void visa(long number_v);  
void amex(long number_a,int l_a,int b_l_a)  ;  
void mastercard(long number_m,int l_m, int b_l_m) ;  
int l12digit(long number1);
int l22digit(long number2);
int main (void)
{
    while(1)
    {
    long cc_number= get_long("Please enter Credit card number:");
    long ccc_number=cc_number;
    int count =0;    
    // Credit Card length 
    while(ccc_number!=0)
    {
        count++;
        ccc_number/=10;
    }
    printf("length is %d \n",count);
    // Credit card type
    switch(count)
    {
        case 13:
            visa(cc_number);     
            break;
                
        case 15:
            check(cc_number,count);
            break;
                
        case 16:
            check(cc_number,count);
            break;
                
        default:
            printf("INVALID\n");
            break;
                          
    }
    } 
}
//check for length 16
void check(long number_c, int count)
{
    int b_l=0; int i=0;
    int l;
    long number=number_c;
    if (count==16)
        number_c /= 100000000000000;
    else
        number_c /= 10000000000000;
    printf("the number whole= %ld \n",number_c);
      do
    {   
    if(b_l ==0 && i==0)
    {
        b_l=number_c % 10;
        i++;
    }
    l=number_c % 10;
    number_c /= 10;
    }
    while(number_c);
    printf("before last number= %d \n",b_l); 
    printf("last number= %d \n",l);
    if(l==4)
    {
        visa(number);
    }
    else if(l==5)
    {
        mastercard(number,l,b_l);
    }
    else
    {
         amex(number,l,b_l);
    }
}
// MASTERCARD initialization
void mastercard(long number_m,int l_m, int b_l_m) 
{
    if(l_m==5)
    {
        if(b_l_m==1 || b_l_m==2 ||b_l_m==3 ||b_l_m==4 ||b_l_m==5 )
        {
            int x=l12digit(number_m);
            int y=l22digit(number_m);
            int z=x+y;
            int b_l=z%10;
            if(b_l==0)
                printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
      {
            printf("INVALID\n");
        }       
}
// VISA initialization
void visa(long number_v)
{
    int x=l12digit(number_v);
    int y=l22digit(number_v);
    int z=x+y;
    int b_l=z%10;
    if(b_l==0)
        printf("VISA\n");
    else
        printf("INVALID\n");
}
// AMERICAN EXPRESS initialization
void amex(long number_a,int l_a,int b_l_a)  
{
     if(l_a==3)
    {
        if(b_l_a==4 || b_l_a==7  )
        {           
            int x=l12digit(number_a);
            int y=l22digit(number_a);
            int z=x+y;
            int b_l=z%10;
        if(b_l==0)
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
      {
            printf("INVALID\n");
        }
        
}
// Checksum initialization
// 1st to last digits summation
int l12digit(long number1)
{
    int sum=0 ; 
    int i;
    do
    {   
    printf("%ld\n", number1 % 10);    
        sum=sum+number1%10;
    number1 /= 100;
    }
    while(number1);
    printf(" summagtion12last = %d \n",sum);
    return(sum);
}
// Doubled 2nd to last digits summation
int l22digit(long number2)
{
    int sum=0 ; 
    int i,score_x;
    number2 /= 10; 
    do
{   
    printf("%ld\n", number2 % 10);
    if(2*(number2 % 10) > 9)
    {
        score_x=2*(number2 % 10);
    for(i=0;i<=1;i++)
    {        
        sum=sum+score_x%10;        
        score_x /= 10; 
    }
    }
    else
    {
    sum=sum+2*(number2 % 10);
    }
    number2 /= 100;
}
    while(number2);
    printf(" summagtion = %d \n",sum);
    return(sum);
}
