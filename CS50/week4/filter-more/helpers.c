#include "helpers.h"
#include <math.h> // For round function
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;
            BYTE gray = round((blue + green + red) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // 初始化所有變量
    int totalRedX = 0, totalGreenX = 0, totalBlueX = 0;
    int totalRedY = 0, totalGreenY = 0, totalBlueY = 0;

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
            // 重置累加變量
            totalRedX = totalGreenX = totalBlueX = 0;
            totalRedY = totalGreenY = totalBlueY = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRedX += image[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        totalGreenX += image[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        totalBlueX += image[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];

                        totalRedY += image[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        totalGreenY += image[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        totalBlueY += image[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                    else
                    {
                        // 超出範圍，視為0
                        totalRedX += 0 * Gx[di + 1][dj + 1];
                        totalGreenX += 0 * Gx[di + 1][dj + 1];
                        totalBlueX += 0 * Gx[di + 1][dj + 1];

                        totalRedY += 0 * Gy[di + 1][dj + 1];
                        totalGreenY += 0 * Gy[di + 1][dj + 1];
                        totalBlueY += 0 * Gy[di + 1][dj + 1];
                    }
                }
            }
            int finalRed = round(sqrt(totalRedX * totalRedX + totalRedY * totalRedY));
            int finalGreen = round(sqrt(totalGreenX * totalGreenX + totalGreenY * totalGreenY));
            int finalBlue = round(sqrt(totalBlueX * totalBlueX + totalBlueY * totalBlueY));

            if (finalRed > 255)
                finalRed = 255;
            if (finalGreen > 255)
                finalGreen = 255;
            if (finalBlue > 255)
                finalBlue = 255;

            // 設置臨時圖像的值
            temp_image[i][j].rgbtRed = finalRed;
            temp_image[i][j].rgbtGreen = finalGreen;
            temp_image[i][j].rgbtBlue = finalBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }

    // 釋放臨時圖像數組的內存
    free(temp_image);
}

