#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{

    // Equal to 255-216-255 decimal
    //int JpegSig = 0xffd8ffe;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover, forensic image\n");
        return 1;
    }

    // Forensic image
    char* infile = argv[1];

    // Open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }



    //int buffer[512];

    //for (int i = 0; i < 4; i++)
    //{
        //buffer[i] = fgetc(inptr);
        //printf("buffer: %i\n", buffer[i]);
    //}

    //fread(&buffer, 1, 512, inptr);
    //printf("buffer: %i\n", *buffer);


    //for (int i = 0; i < 512; i++)
    //{
        //printf("buffer: %i\n", buffer[i]);

    char ch = fgetc(inptr);

    if (ch != 0xff)
    {

    }

    }



}