#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "imageManipulator.h"

// Removes color from image, turning it to grayscale, outputs a 2-dimensional array with the greyscale average of the colors of each pixel
void convertRgbToGray(const unsigned char rgbImage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], unsigned char outputImage[BMP_WIDTH][BMP_HEIGHT]) {
    for (int x = 0; x < BMP_WIDTH; x++) {
        for (int y = 0; y < BMP_HEIGHT; y++) {
            unsigned char red   = rgbImage[x][y][0];
            unsigned char green = rgbImage[x][y][1];
            unsigned char blue  = rgbImage[x][y][2];

            outputImage[x][y] = (red + green + blue) / 3;
        }
    }
}

// Converts the grey-scale image into a binary image, where every pixel can only have 2 colors, fully black or fully white
<<<<<<< Updated upstream
void binaryThreshold(unsigned char grayImage[BMP_WIDTH][BMP_HEIGHT]) {
    int threshold = 90;

    for (int x = 0; x < BMP_WIDTH; x++) {
        for (int y = 0; y < BMP_HEIGHT; y++) {
            if (grayImage[x][y] <= threshold) {
                grayImage[x][y] = 0;
            }
            else {
                grayImage[x][y] = 1;
            }
        }
    }
=======
void binaryThreshold(unsigned char grayImage[BMP_WIDTH][BMP_HEIGHT], unsigned char outputImage[BMP_1D_SIZE])
{
    int threshold = findThreshold(grayImage);
    char bit = 0;
    int i = 0;

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            i = (x + y * BMP_WIDTH) / 8;
            bit = (x + y * BMP_WIDTH) % 8;
            
            if (grayImage[x][y] <= threshold)
            {
                outputImage[i] &= ~(1 << bit); // Set the bit to 0
            }
            else
            {
                outputImage[i] |= 1 << bit; // Set the bit to 1
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

    for (int i = 0; i < 256; i++)
    {
        p[i] /= totalPixels;
        mG += i * p[i];
    }

    for (int i = 0; i < 256; i++)
    {
        P1 += p[i];
        mk += i * p[i];
        sigmaB = (mG * P1 - mk) * (mG * P1 - mk) / (P1 * (1 - P1));

        if (sigmaB > max)
        {
            max = sigmaB;
            threshold = i;
            nrOfMaxVals = 1;
        }
        else if (sigmaB == max)
        {
            threshold += i;
            nrOfMaxVals++;
        }
    }

    threshold /= nrOfMaxVals;

    printf("Threshold = %d\n", threshold);

    return threshold;
>>>>>>> Stashed changes
}