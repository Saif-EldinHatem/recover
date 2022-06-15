#include <stdio.h>
#include <stdlib.h>

#define buffersize 512

int main(int argc, char *argv[]) //comments
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGES\n");
        return 1;
    }

    FILE *mcard = fopen(argv[1], "r");

    if (mcard == NULL)//comments
    {
        printf("File doesn't exist\n"); //comments
        return 1;
    }

    unsigned char buffer[buffersize]; //comments
    char filename[8]; //comments
    int images_found = 0;
    FILE *image;
    int new_image = 0;



    while (fread(buffer, 1, buffersize, mcard) == buffersize) // comments
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)// comments
        {
            if (new_image)
            {
                fclose(image);
            }
            else
            {
                new_image = 1;
            }
            sprintf(filename, "%03i.jpg", images_found);
            image = fopen(filename, "w");
            images_found++;
        }
        if (new_image)
        {
            fwrite(buffer, buffersize, 1, image);
        }
    }
    fclose(mcard);
    fclose(image);
}