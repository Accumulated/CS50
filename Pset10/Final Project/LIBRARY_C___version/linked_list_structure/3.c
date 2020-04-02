#include <stdio.h>
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef float f32;
typedef double f64;
#define set_bit(var,bitno)       var |=  (1<<bitno)
#define clear_bit(var,bitno)     var &= ~(1<<bitno)
#define toggle_bit(var,bitno)    var ^=  (1<<bitno)
#define ass_bit(var,bitno,value) (value==0)? (clear_bit(var,bitno)):(set_bit(var,bitno))
#define get_bit(var,bitno)       var &=  (1<<bitno)
#define set_High_nibble(var)       var |=  240
#define set_Low_nibble(var)       var |=  15
#define Clear_High_nibble(var)       var &=  15
#define Clear_Low_nibble(var)       var &=  240
void main()
{
	u8 var,bitno,value;
	// Set one bit
	printf("   Set_bit  \n");
	printf("Enter var : ");
	scanf("%d",&var);
	printf("Enter bitno : ");
	scanf("%d",&bitno);
    set_bit(var,bitno);
	printf("set : %d\n",var);
	// Clear one bit
	printf("   Clear_bit  \n");
	printf("Enter var : ");
	scanf("%d",&var);
	printf("Enter bitno : ");
	scanf("%d",&bitno);
	clear_bit(var,bitno);
    printf("clear : %d\n",var);
	// Toggle one bit
	printf("   Toggle_bit  \n");
	printf("Enter var : ");
	scanf("%d",&var);
	printf("Enter bitno : ");
	scanf("%d",&bitno);
	toggle_bit(var,bitno);
	printf("toggle : %d\n",var);
	// Assign one bit
	printf("   Assign_bit  \n");
	printf("Enter var : ");
	scanf("%d",&var);
	printf("Enter bitno : ");
	scanf("%d",&bitno);
	printf("Enter value : ");
	scanf("%d",&value);
	ass_bit(var,bitno,value);
	printf("assign : %d\n",var);
	// Get the bit
    printf("   Get_bit  \n");
	printf("Enter var : ");
	scanf("%d",&var);
	printf("Enter bitno : ");
	scanf("%d",&bitno);
    get_bit(var,bitno);
	printf("Get : %d\n",var);
	//Set high nibble
	printf("   Set high nibble  \n");
	printf("Enter var : ");
	scanf("%d",&var);
    set_High_nibble(var);
	printf("Set_High_nibble : %d\n",var);
	//Set Low nibble
	printf("   Set low nibble  \n");
	printf("Enter var : ");
	scanf("%d",&var);
    set_Low_nibble(var);
	printf("Set_Low_nibble : %d\n",var);
	//Clear High nibble
	printf("   Clear high nibble  \n");
	printf("Enter var : ");
	scanf("%d",&var);
    Clear_High_nibble(var);
	printf("Clear_High_nibble : %d\n",var);
	//Clear Low nibble
	printf("   Clear low nibble  \n");
	printf("Enter var : ");
	scanf("%d",&var);
    Clear_Low_nibble(var);
	printf("Clear_Low_nibble : %d\n",var);
	
}
	
	