#include "helpers.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++)
        for (int j = 0; j<width; j++)
        {
            int avg=round((float)(image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3);
            image[i][j].rgbtBlue=avg;
            image[i][j].rgbtRed=avg;
            image[i][j].rgbtGreen=avg;
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++)
        for (int j = 0; j<width; j++)
        {
            // Calculate Sepia RGB values
            int sepiaRed = round((float)0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round((float)0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round((float)0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Capps RGB value at 255 if Sepia formula returns a value > 255
            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            // Convert Image to Seipa
            image[i][j].rgbtRed=sepiaRed;
            image[i][j].rgbtGreen=sepiaGreen;
            image[i][j].rgbtBlue=sepiaBlue;
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i<height; i++)
        for (int j = 0, x = width-1; j<width; j++)
        {
            tmp[i][j]=image[i][j+x];
            x=x-2;
        }
    memcpy(image, tmp, sizeof(tmp));
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tmp[height][width];
    int n;
    int blurRed;
    int blurGreen;
    int blurBlue;
    int dy1;
    int dy2;
    int dx1;
    int dx2;


    for (int i = 0; i<height; i++)
        for (int j = 0; j<width; j++)
        {
            // Initialize RGB values to 0 for each loop (i.e. pixel)
            blurRed=0;
            blurGreen=0;
            blurBlue=0;
            n=0;

            // Top Row of image
            if (i==0)
            {
                // Top Left Pixel
                if (j==0)
                {
                    dx1=0;dx2=1;dy1=0;dy2=1;
                }
                // Top Right Pixel
                else if (j==width-1)
                {
                    dx1=-1;dx2=0;dy1=0;dy2=1;
                }
                // Remainder
                else
                {
                    dx1=-1;dx2=1;dy1=0;dy2=1;
                }
            }

            // Bottom Row of image
            else if (i==height-1)
            {
                // Bottom Left pixel
                if (j==0)
                {
                    dx1=0;dx2=1;dy1=-1;dy2=0;
                }
                // Bottom Right pixel
                else if (j==width-1)
                {
                    dx1=-1;dx2=0;dy1=-1;dy2=0;
                }
                // Bottom Row remainder pixels
                else
                {
                    dx1=-1;dx2=1;dy1=-1;dy2=0;

                }
            }

            // Left Column of image
            else if (j==0)
            {
                dx1=0;dx2=1;dy1=-1;dy2=1;
            }
            // Right Column of image
            else if (j==width-1)
            {
                dx1=-1;dx2=0;dy1=-1;dy2=1;
            }
            // Remainder of image
            else
            {
                dx1=-1;dx2=1;dy1=-1;dy2=1;
            }

            // Loop to add the surrounding pixels. Takes dx1, dx2, dy1, dy2 inputs to define bounds.
            for (int y=dy1; y<=dy2; y++)
            {
                for (int x=dx1; x<=dx2; x++)
                {
                    blurRed+=image[i+y][j+x].rgbtRed;
                    blurGreen+=image[i+y][j+x].rgbtGreen;
                    blurBlue+=image[i+y][j+x].rgbtBlue;
                    n++;
                }
            }

            // Assins blurr pixel to TMP image
            tmp[i][j].rgbtRed=round((float)blurRed/n);
            tmp[i][j].rgbtGreen=round((float)blurGreen/n);
            tmp[i][j].rgbtBlue=round((float)blurBlue/n);
        }
    memcpy(image, tmp, sizeof(tmp));
    return;
}
