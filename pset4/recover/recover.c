#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check that program was run with one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover file.\n");
        return 1;
    }

    // Open file
    FILE *rawdata = fopen(argv[1], "r");
    if (!rawdata)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[512];
    int ximg = 0;
    char filename[8];
    FILE *img = NULL;

    // Calculate number of elements (blocks) of size 512 bytes.
    fseek(rawdata, 0L, SEEK_END);
    int size = ftell(rawdata);
    rewind(rawdata);
    int nBlocks = size/512;

    for (int i = 0; i < nBlocks; i++)
    {
        // Read block of data into buffer.
        size_t nBytes = fread(buffer, 1, 512, rawdata);

        // Check buffer data block for JPEG Headers.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                // If an image is already opened, close file and iterate filename.
                if (img != NULL)
                {
                    fclose(img);
                    ximg++;
                }

                // Create filename and open image file for writing.
                sprintf(filename, "%03i.jpg", ximg);
                img = fopen(filename, "w");
            }
        }

        // Write buffer data into open file.
        if (img != NULL)
            fwrite(buffer, 1, 512, img);
    }

    // Close last jpg.
    fclose(img);

    // Clost input file.
    fclose(rawdata);

}