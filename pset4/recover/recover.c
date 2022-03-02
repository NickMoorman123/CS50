#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    //check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //ensure file is readable
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }
    
    //read in file bytes and look for start of first jpg
    BYTE buffer[512];
    do 
    {
        fread(buffer, 1, 512, file);
    } while(!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0));
    
    //go through, adding data to jpg files, making new files when needed
    int img_number = 0;
    FILE *img = fopen("000.jpg", "w");
    fwrite(buffer, 1, 512, img);
    while(fread(buffer, 1, 512, file) == 512)
    {
        //check for new jpg and change variables if so
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            img_number++;
            fclose(img);
            char imgFileName[7];
            sprintf(imgFileName, "%03i.jpg", img_number);
            img = fopen(imgFileName, "w");
        }
        fwrite(buffer, 1, 512, img);
    }
    
    fclose(img);
    fclose(file);
}