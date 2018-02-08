// This program scours raw binary data for jpegs. If found, creates seperate files for each jpeg.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#define NOINFLOOP 2000000

int main(int argc, char* argv[])
{
    int startPoint;
    int endPoint;
    FILE* outptr;
    int storage[100000];
    int preventInfLoop = 0;
    int JpegSig = 0xffd8ffe;
    char* outfiles[52] = {"picture1.jpg", "picture2.jpg", "picture3.jpg", "picture4.jpg", "picture5.jpg", "picture6.jpg",
    "picture7.jpg", "picture8.jpg", "picture9.jpg", "picture10.jpg", "picture11.jpg", "picture12.jpg", "picture13.jpg",
    "picture14.jpg", "picture5.jpg", "picture16.jpg", "picture17.jpg", "picture18.jpg", "picture19.jpg", "picture20.jpg",
    "picture21.jpg", "picture22.jpg", "picture23.jpg", "picture24.jpg", "picture25.jpg", "picture26.jpg", "picture27.jpg",
    "picture28.jpg", "picture29.jpg", "picture30.jpg", "picture31.jpg", "picture32.jpg", "picture33.jpg", "picture34.jpg",
    "picture35.jpg","picture36.jpg", "picture37.jpg", "picture38.jpg", "picture39.jpg", "picture40.jpg", "picture41.jpg",
    "picture42.jpg", "picture43.jpg", "picture44.jpg", "picture45.jpg", "picture46.jpg", "picture47.jpg", "picture48.jpg",
    "picture49.jpg", "picture50.jpg", "picture51.jpg", "picture52.jpg"};

    // Ensure proper usage
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

    // Find length of infile
    fseek(inptr, 0, SEEK_END);
    int fileSize = ftell(inptr) - 1;
    // Return to beginning of file
    fseek(inptr, 0, SEEK_SET);


    // Create temporary storage
    FIRST3BYTES first3;
    // Create counter for outfiles
    int f = 0;


    while (1)
    {


    // Find Jpeg signatures
    while (1)
    {
        // Read in chunks of size JpegSig (3 bytes) at a time and store in first3
        fread(&first3, sizeof(JpegSig), 1, inptr);

        preventInfLoop += 1;
        if (preventInfLoop > NOINFLOOP)
        {
            // Close infile
            fclose(inptr);

            // Close outfile
            fclose(outptr);

            exit(0);
        }


        // If signature is found, create an output file and break out of loop
        if (first3.first == 0xff && first3.second == 0xd8 && first3.third == 0xff)
        {
            char* outfile = outfiles[f];
            outptr = fopen(outfile, "w");
            if (inptr == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", outfile);
                return 3;
            }

            // Seek back 4 bytes to record proper startpoint for outfile
            fseek(inptr, -4, SEEK_CUR);
            startPoint = ftell(inptr);
            fseek(inptr, 4, SEEK_CUR);

            // Find end of file (aka beginning of next jpeg file)
            while (1)
            {

                fread(&first3, sizeof(JpegSig), 1, inptr);

                if (first3.first == 0xff && first3.second == 0xd8 && first3.third == 0xff)
                {
                    fseek(inptr, -4, SEEK_CUR);
                    endPoint = ftell(inptr);
                    break;
                }

                preventInfLoop += 1;
                if (preventInfLoop > NOINFLOOP)
                {
                    endPoint = fileSize;
                    break;
                }
            }

            f +=1;
            break;
        }



    }

    // Seek to the start of the file
    fseek(inptr, startPoint, SEEK_SET);

    // Transcribe bytes from inptr into temporary storage
    fread(&storage, 1, endPoint - startPoint, inptr);
    // Transcribe bytes from temporary storage into outfile
    fwrite(&storage, 1, endPoint - startPoint, outptr);

}


}