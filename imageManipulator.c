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
            outputImage[x][y] = rgbImage[x][y][0];
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
    double p[256] = {0};
    int totalPixels = BMP_WIDTH * BMP_HEIGHT;
    unsigned char threshold = 0;
    double max = 0;
    int nrOfMaxVals = 1;
    double P1 = 0;
    double mk = 0;
    double mG = 0;
    double sigmaB;

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            p[image[x][y]]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        p[i] /= totalPixels;
        mG += i * p[i];
    }

    for (int i = 0; i < 256; i++) {
        P1 += p[i];
        mk += i * p[i];
        sigmaB = (mG * P1 - mk) * (mG * P1 - mk) / (P1 * (1 - P1));

        if (sigmaB > max) {
            max = sigmaB;
            threshold = i;
            nrOfMaxVals = 1;
        }
        else if (sigmaB == max) {
            threshold += i;
            nrOfMaxVals++;
        }
    }
    
    threshold /= nrOfMaxVals;

    printf("Threshold = %d\n", threshold);

    return threshold;
}