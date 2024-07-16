#include "helpers.h"
#include <math.h> // For round function
#include <stdio.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE Blue = image[i][j].rgbtBlue;
            BYTE Green = image[i][j].rgbtGreen;
            BYTE Red = image[i][j].rgbtRed;
            BYTE gray = (Blue + Green + Red) / 3;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE Blue = image[i][j].rgbtBlue;
            BYTE Green = image[i][j].rgbtGreen;
            BYTE Red = image[i][j].rgbtRed;
            int sepiaRed = round(0.393 * Red + 0.769 * Green + 0.189 * Blue);
            int sepiaGreen = round(0.349 * Red + 0.686 * Green + 0.168 * Blue);
            int sepiaBlue = round(0.272 * Red + 0.534 * Green + 0.131 * Blue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            image[i][j].rgbtBlue = (BYTE) sepiaBlue;
            image[i][j].rgbtGreen = (BYTE) sepiaGreen;
            image[i][j].rgbtRed = (BYTE) sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (temp_image == NULL)
    {
        printf("Not enough memory to store temporary image.\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalBlue = 0, totalGreen = 0, totalRed = 0, count = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalBlue += image[ni][nj].rgbtBlue;
                        totalGreen += image[ni][nj].rgbtGreen;
                        totalRed += image[ni][nj].rgbtRed;
                        count++;
                    }
                }
            }
            temp_image[i][j].rgbtBlue = round(totalBlue / (float) count);
            temp_image[i][j].rgbtGreen = round(totalGreen / (float) count);
            temp_image[i][j].rgbtRed = round(totalRed / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }

    free(temp_image);
}
