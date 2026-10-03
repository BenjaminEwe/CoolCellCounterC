#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "imageManipulator.h"

unsigned char findThreshold(const unsigned char image[BMP_WIDTH][BMP_HEIGHT]);

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
void binaryThreshold(unsigned char grayImage[BMP_WIDTH][BMP_HEIGHT], unsigned char outputImage[BMP_1D_SIZE])
{
    unsigned char threshold = findThreshold(grayImage);
    char bit = 0;
    int i = 0;

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            i = (x + y * BMP_WIDTH) >> 3;
            bit = (x + y * BMP_WIDTH) & 7;
            
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
    double p[256] = {0};    // p[i] will store the probability of choosing a pixel with a value of i
    int totalPixels = BMP_WIDTH * BMP_HEIGHT;
    unsigned char threshold = 0;
    double max = 0;         // The maximum value of the difference in the mean of the pixel values under the threshold vs over the threshold
    int nrOfMaxVals = 1;    // The number of values with the maximum difference
    double P1 = 0;          // The probability of choosing a pixel with a value equal to or less than the current value
    double mk = 0;          // The mean of the pixel values that are less than or equal to the current value
    double mG = 0;          // The global mean (the mean of all the pixel values)
    double sigmaB;          // The difference between the mean of the pixel values under the current value vs over the current value

    // Populate the probability array with the number of times each value appears
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            p[image[x][y]]++;
        }
    }

    // Make the elements in the probability array be the probabilities and calculate the global mean 
    for (int i = 0; i < 256; i++)
    {
        p[i] /= totalPixels;
        mG += i * p[i];
    }

    // Go through all possible threshold values and check the difference
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

    // Make the threshold the mean of the possible thresholds
    threshold /= nrOfMaxVals;

    return threshold;
}