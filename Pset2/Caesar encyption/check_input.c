// Check for valid input for caeser
bool check (argv[1])
 {
    for(int i = 0 , n = strlen(argv[1]) ; i < n ; i++)
        {
             c = (int) argv[1][i];
            //checking for inputs rather than numbers
            if( c >= 48 && c<=57 )
            {
               // printf("valid input \n");
            }
            else
            {                
                i=n;
                return false;
            }
        }
 }
