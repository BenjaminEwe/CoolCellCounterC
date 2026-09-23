#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

unsigned char findThreshold(const unsigned char image[BMP_WIDTH][BMP_HEIGHT]);

// Removes color from image, turning it to grayscale, outputs a 2-dimensional array with the greyscale average of the colors of each pixel
void convertRgbToGray(const unsigned char rgbImage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], unsigned char outputImage[BMP_WIDTH][BMP_HEIGHT])
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            unsigned char red = rgbImage[x][y][0];
            unsigned char green = rgbImage[x][y][1];
            unsigned char blue = rgbImage[x][y][2];

            outputImage[x][y] = (red + green + blue) / 3;
        }
    }
}

// Converts the grey-scale image into a binary image, where every pixel can only have 2 colors, fully black or fully white
void binaryThreshold(unsigned char grayImage[BMP_WIDTH][BMP_HEIGHT])
{
    int threshold = findThreshold(grayImage);

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            if (grayImage[x][y] <= threshold)
            {
                grayImage[x][y] = 0;
            }
            else
            {
                grayImage[x][y] = 1;
            }
        }
    }
}

// Otsu's Method for finding a threshold value
unsigned char findThreshold(const unsigned char image[BMP_WIDTH][BMP_HEIGHT])
{
    double hists[256][256] = {0};
    double max = 0;
    unsigned int threshold = 0;
    unsigned int total = BMP_WIDTH * BMP_HEIGHT;
    unsigned int neighborhood;
    unsigned int neighboringPixels;
    double p0[256][256] = {0};
    double trace;
    double mu_i[256][256] = {0}, mu_j[256][256] = {0};
    double mu_Ti = 0, mu_Tj = 0;

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            neighborhood = 0;
            neighboringPixels = 0;
            for (int i = (x - 1 < 0) ? 0 : x - 1; i <= x + 1 && i < BMP_WIDTH; i++)
            {
                for (int j = (y - 1 < 0) ? 0 : y - 1; j <= y + 1 && j < BMP_HEIGHT; j++)
                {
                    neighborhood += image[x][y];
                    neighboringPixels++;
                }
            }
            hists[image[x][y]][neighborhood / neighboringPixels]++;
        }
    }

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            hists[i][j] = hists[i][j] / total;
            mu_Ti += i * hists[i][j];
            mu_Tj += j * hists[i][j];
        }
    }

    total = 256 * 256;

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            if (j == 0)
            {
                if (i == 0)
                {
                    p0[0][0] = hists[0][0];
                }
                else
                {
                    p0[i][0] = p0[i - 1][0] + hists[i][0];
                    mu_i[i][0] = mu_i[i - 1][0] + (i - 1) * hists[i][0];
                    mu_j[i][0] = mu_j[i - 1][0];
                }
            }
            else
            {
                if (i > 0)
                {
                    p0[i][j] = p0[i][j - 1] + p0[i - 1][j] - p0[i - 1][j - 1] + hists[i][j];
                    mu_i[i][j] = mu_i[i][j - 1] + mu_i[i - 1][j] - mu_i[i - 1][j - 1] + (i - 1) * hists[i][j];
                    mu_j[i][j] = mu_j[i][j - 1] + mu_j[i - 1][j] - mu_j[i - 1][j - 1] + (j - 1) * hists[i][j];
                }
            }

            if (p0[i][j] == 0)
                continue;
            else if (p0[i][j] == total)
                break;

            trace = ((mu_i[i][j] - p0[i][j] * mu_Ti) * (mu_i[i][j] - p0[i][j] * mu_Ti) + (mu_j[i][j] - p0[i][j] * mu_Tj) * (mu_j[i][j] - p0[i][j] * mu_Tj)) / (p0[i][j] * (total - p0[i][j]));

            if (trace > max)
            {
                threshold = i;
                max = trace;
            }
        }
    }

    printf("Threshold = %d\n", threshold);

    return threshold;
}