#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Returns 1
    //If argc is not 2
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    //Open card_file
    FILE *card_file = fopen(argv[1], "r");

    //Return 2
    //If card_file equals NULL
    if (card_file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    int BLOCK_SIZE = 512;

    BYTE block[BLOCK_SIZE];

    FILE *jpeg_file = NULL;

    char *name = malloc(sizeof(char) * 7);

    int count = 0;

    while (fread(block, BLOCK_SIZE, 1, card_file) == 1) //Read from file in buffer block
    {
        //Check for jpeg signature
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (count > 0)//If count greater 0
            {
                fclose(jpeg_file);//Close the file
            }

            //make name of image
            sprintf(name, "%03d.jpg", count);//Create File Name

            // open image file
            jpeg_file = fopen(name, "w");//Open file

            if (jpeg_file == NULL)//Return 3 if jpeg is NULL
            {
                fprintf(stderr, "Could not create %s.\n", name);
                return 3;
            }
            count++;
        }

        if (count != 0) //If file is Open
        {
            fwrite(block, BLOCK_SIZE, 1, jpeg_file);//Write BLOCK_SIZE to jpeg_file
        }
    }

    free(name);

    fclose(jpeg_file);

    fclose(card_file);
}
