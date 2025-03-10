#include <stdio.h>
#include <stdlib.h>



int bool_jpg(unsigned char bytes[]);

int main(int argc, char *argv[])
{
    // Check if the user pass the name of the image
    if (argc < 2)
    {
        printf("./recover {name of the image}\n");
        return 1;
    }

    FILE *img;
    img = fopen(argv[1], "r");
    // Check if we can open the image to read the HEX values
    if (img == NULL)
    {
        printf("We cannot open the image to read, sorry :(\n");
        return 1;
    }

    unsigned char array_bytes[512];
    char name[10];
    int count = 0;
    int found = 0;
    FILE *output;

    // Reading byte per byte searching the HEX values that are the beggin of a jpeg
    while (fread(array_bytes, 512, 1, img) != 0)
    {
        if (bool_jpg(array_bytes) == 1)
        {
            if (found == 1)
            {
                fclose(output);
            }
            else
            {
                found = 1;
            }
            // name the new's jpegs
            sprintf(name, "%03d.jpg", count);

            output = fopen(name, "a");

            count++;
        }

        if (found == 1)
        {
            // Create the new image
            fwrite(&array_bytes, 512, 1, output);
        }
    }

    fclose(output);
    fclose(img);
}

int bool_jpg(unsigned char bytes[])
{
    // Test if is the begin of a jpeg image
    if (bytes[0] == 0xFF && bytes[1] == 0xD8 && bytes[2] == 0xFF && (bytes[3] & 0xF0) == 0xE0)
    {
        return 1;
    }

    return 0;
}

