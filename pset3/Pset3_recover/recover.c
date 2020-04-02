#include <stdio.h>
#include <stdlib.h>

extern FILE *stderr;

int main(int argc, char *argv[])
{
    // rewrite in a new file flag, file_name to save JPEGS one at a time, size to check EOF
    int i = -1, size = 512, re_write_flag = 0;
    char filename[7];

    // Buffer for tmp storage
    unsigned char buffer[512] = {0}, *buff = buffer;

    if (argc != 2)
    {
        fprintf(stderr, "wrond pattern \n");
        return 1;
    }

    // INPUT FILE
    char *infile = argv[1];

    // READ FROM INPUT FILE.
    FILE *inptr = fopen(infile, "r");

    // Check FOR RETURNED POINTER
    if (inptr == NULL)
    {
        fprintf(stderr, "cann't open %s \n", infile);
        return 2;
    }

    // Reading the first time incase of rubbish value at the beginning of card
    sprintf(filename, "%03i.jpg", i);
    FILE *img = fopen(filename, "w");

    while (size == 512)
    {
        buff = buffer;
        // Read from input file
        size = fread(buff, sizeof(char), 512, inptr);
        if (size == 512)
        {

            // Checking for JPEG
            if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
                buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // Rewrite in a new JPEG file
                // JPEG CONFIRM
                printf("A new JPEG found \n");
                re_write_flag = 1;
            }

            if (re_write_flag == 1)
            {
                printf("closing old file \t and opening a new one \n");
                re_write_flag = 0;
                fclose(img);
                i++;
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
            }

            printf("now writing at the opened file \n");
            fwrite(buff, sizeof(char), 512, img);
        }
    }


    printf("number of JPEGS found are %d \n", i);
    fclose(inptr);
    fclose(img);

}
