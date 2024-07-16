#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Define the block size
    int block_size = 512;

    // Create a buffer for a block of data
    uint8_t buffer[block_size];

    // Initialize variables for file handling
    FILE *img = NULL;
    char filename[8];
    int file_count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, block_size, card) == block_size)
    {
        // Check if the block contains the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a file is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename for the JPEG
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
            file_count++;
        }

        // If a file is open, write the buffer to it
        if (img != NULL)
        {
            fwrite(buffer, 1, block_size, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}
