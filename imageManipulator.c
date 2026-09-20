#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

// Removes color from image, turning it to grayscale, outputs a 2-dimensional array
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
}