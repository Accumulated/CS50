#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //h= hight of the pyramid //w= width of the pyramid
    int w, h, x, space, gap;
    
    //ask for integer value, if not integer repeat the question
    do    
    {
        x = get_int("height: ");
    }
    while (x>8||x<1);    
    
    //to control which line we print over.
    for(h=0 ; h<x ; h++)    
    {
        gap=0;
        space=h;
        
        //to print the spaces behind the hashtags.
        while (space<x-1) 
        {
            printf(" ");
            space++;
        }
        
        // to print the hashtags after the spaces.
        for (w=0 ; w<=h; w++) 
        {
            printf("#");           
        }
        
        //to print the gaps between the allignments
        while (gap<=1) 
        {
            printf(" ");
            gap++;
        }
        
        
        for (w=0 ; w<=h; w++) // to print the hashtags after the gap.
        {        
            printf("#");           
        }
        
        // to repeat for the next line. 
       printf("\n"); 
        
    } 
        
}
