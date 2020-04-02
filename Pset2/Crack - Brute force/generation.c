
#include <stdio.h>
#include <crypt.h>
#include <string.h>
int ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0, times = 0;
void session1(unsigned long length,char p_pasw[]);
void session2(unsigned long length, char p2_pasw[]);
void session3(unsigned long length, char p3_pasw[]);
void session4(unsigned long length, char p4_pasw[]);
void session5(unsigned long length, char p5_pasw[]);
int main(void)
{
    int i=5;
    char pasw[i];
    char c = '\0';
    int length = 6;
    for (int session = 1 ; session <= 5 ; session++)
    {
        for (int j = 0 ; j < session ; j++)
        {
            pasw[j] = 'A';
        }
        printf("the processed is %s with length of %lu characters \n", pasw, strlen(pasw));
        switch(session)
        {
            case 1:
                ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0;
                session1( strlen(pasw),pasw);
                printf("updat1e = %s\n",pasw);
                int k1=get_int("type something to go to 2");
                break;
            case 2:
                ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0;
                session2( strlen(pasw),pasw);
                printf("updat2e = %s\n",pasw);
                int k2 = get_int("type something to go to 3");
             //   o_hash = session2( strlen(pasw),pasw);
                break;
            case 3:
                ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0;
                session3( strlen(pasw),pasw);
                printf("updat3e = %s\n",pasw);
                int k3 = get_int("type something to go to 4 \t ");  
                break;
            case 4:
                ch_flag3 = 0, ch_flag2 = 0, ch_flag1 = 0, ch_flag0 = 0;
                session4(strlen(pasw),pasw);
                printf("updat4e = %s\n",pasw);
                int k4=get_int("type something to go to 5");
                break;
            case 5:
               /* session5( strlen(pasw),pasw);
                printf("updat5e = %s\n",pasw);
                int k5=get_int("type something to go to end");  */              
                break;
        }
    }
      
}

void session1(unsigned long length,char p1_pasw[])
{
    char c = '\0';
    for (c = 'A' ; c >= 65 ; c++)
    {
        p1_pasw[0] = c;
        string o_hash = crypt(p1_pasw,"50");
        printf("string = %s \t hash =%s \n", p1_pasw, o_hash);
        //int k = get_int("type any to pass \n");
        if (c > 89 && c <= 97)
        {
            c = 'a';
            p1_pasw[0] = c;
        }
        else if (c >= 122)
        {
            
            printf("done \n");    
            c=-1;
        }
       
    }
}
void session2(unsigned long length, char p2_pasw[])
{
    char c = '\0';
    // Session #2
    for (c = 'A' ; c >= 65 ; c++)
    {
        p2_pasw[0] = c;
        //check function
        string o_hash = crypt(p2_pasw,"50");
        printf("string = %s \t hash =%s \n", p2_pasw, o_hash);
        //int k = get_int("type any to pass \n");

        if (c > 89 && c <= 97)
        {
            c = 'a';
            p2_pasw[0] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag1 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag1 == 1)
        {
            ch_flag1 = 0; 
            p2_pasw[1]++;               
            times++;
            c = '@';
            if (p2_pasw[1] > 90 && p2_pasw[1] <= 97)
            {
                p2_pasw[1] = 'a';
            }
            else if ( p2_pasw[1] > 122)
            {
                // ADD check first later then reassign
                c=0;
                printf("done \n");
            } 
        }
    }            
}
void session3(unsigned long length, char p3_pasw[])
{
    char c = '\0';
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        p3_pasw[0] = c;
        printf("string = \t: %s \n", p3_pasw);
        if (c > 89 && c <= 97)
        {
            c = 'a';
            p3_pasw[0] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag1 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag1 == 1)
        {
            ch_flag1 = 0; 
            p3_pasw[1]++;               
            times++;
            c = '@';
            if (p3_pasw[1] > 90 && p3_pasw[1] <= 97)
            {
                p3_pasw[1] = 'a';
            }
            else if ( p3_pasw[1] > 122)
            {
                // ADD check first later then reassign
                // Session #3 flag
                ch_flag2 = 1;
                p3_pasw[1] = 'A';

            } 
        }
        //////// Session 2 //////
        if (ch_flag2 == 1)
        {
            ch_flag2 = 0; 
            p3_pasw[2]++;               
            times++;
            c = '@';
            if ( p3_pasw[2] > 90 && p3_pasw[2] <= 97)
            {
                p3_pasw[2] = 'a';
            }
            else if ( p3_pasw[2] > 122)
            {
                // ADD check first later then reassign
                // Session #1 flag
                //printf("string final = %s",pasw);
                c=0;
                printf("done \n");
            } 
        }
    }            
}

void session4(unsigned long length, char p4_pasw[])
{
        char c = '\0';
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        p4_pasw[0] = c;
        printf("string = \t: %s \n", p4_pasw);
        if (c > 89 && c <= 97)
        {
            c = 'a';
            p4_pasw[0] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag1 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag1 == 1)
        {
            ch_flag1 = 0; 
            p4_pasw[1]++;               
            times++;
            c = '@';
            if (p4_pasw[1] > 90 && p4_pasw[1] <= 97)
            {
                p4_pasw[1] = 'a';
            }
            else if (p4_pasw[1] > 122)
            {
                // ADD check first later then reassign
                // Session #3 flag
                ch_flag2 = 1;
                p4_pasw[1] = 'A';

            } 
        }
        //////// Session 2 //////
        if (ch_flag2 == 1)
        {
            ch_flag2 = 0; 
            p4_pasw[2]++;               
            times++;
            c = '@';
            if ( p4_pasw[2] > 90 && p4_pasw[2] <= 97)
            {
                p4_pasw[2] = 'a';
            }
            else if ( p4_pasw[2] > 122)
            {
                // ADD check first later then reassign
                // Session #1 flag
                ch_flag3 = 1;
                p4_pasw[2] = 'A';
            } 
        }
        // Session 1 ////////
        if (ch_flag3 == 1)
        {
            ch_flag3 = 0; 
            p4_pasw[3]++;               
            times++;
            c = '@';
            if ( p4_pasw[3] > 90 && p4_pasw[3] <= 97)
            {
                p4_pasw[3] = 'a';
            }
            else if ( p4_pasw[3] > 122)
            {
                // ADD check first later then reassign
                c=0;
                printf("done \n");
            } 
        }
    }            
}
void session5(unsigned long length, char p5_pasw[])
{
    char c = '\0';
    // Session #4
    for (c = 'A' ; c >= 65 ; c++)
    {
        p5_pasw[4] = c;
        //printf("string = \t: %s \n", pasw);
        if (c > 89 && c <= 97)
        {
            c = 'a';
            p5_pasw[4] = c;
        }
        else if (c >= 122)
        {
            // ADD check first later then reassign
            // Session #3 flag
            ch_flag3 = 1;
             
        }
        /////////  Session #3  /////////
        if (ch_flag3 == 1)
        {
            ch_flag3 = 0; 
            p5_pasw[3]++;               
            times++;
            c = '@';
            if (p5_pasw[3] > 90 && p5_pasw[3] <= 97)
            {
                p5_pasw[3] = 'a';
            }
            else if (p5_pasw[3] > 122)
            {
                // ADD check first later then reassign
                // Session #3 flag
                ch_flag2 = 1;
                p5_pasw[3] = 'A';

            } 
        }
        //////// Session 2 //////
        if (ch_flag2 == 1)
        {
            ch_flag2 = 0; 
            p5_pasw[2]++;               
            times++;
            c = '@';
            if (p5_pasw[2] > 90 && p5_pasw[2] <= 97)
            {
                p5_pasw[2] = 'a';
            }
            else if (p5_pasw[2] > 122)
            {
                // ADD check first later then reassign
                // Session #1 flag
                ch_flag1 = 1;
                p5_pasw[2] = 'A';
            } 
        }
        // Session 1 ////////
        if (ch_flag1 == 1)
        {
            ch_flag1 = 0; 
            p5_pasw[1]++;               
            times++;
            c = '@';
            if (p5_pasw[1] > 90 && p5_pasw[1] <= 97)
            {
                p5_pasw[1] = 'a';
            }
            else if (p5_pasw[1] > 122)
            {
                // ADD check first later then reassign
                // Session #0 flag
                ch_flag0 = 1;
                p5_pasw[1] = 'A';
            } 
        }
        // Session 0 ////////
        if (ch_flag0 == 1)
        {
            ch_flag0 = 0; 
            p5_pasw[0]++;               
            times++;
            c = '@';
            if (p5_pasw[0] > 90 && p5_pasw[0] <= 97)
            {
                p5_pasw[0] = 'a';
            }
            else if (p5_pasw[0] > 122)
            {
                // ADD check first later then reassign
                // last session no flag
                c=0;
                printf("done \n");
            } 
        }       
    }        
}
