#include <stdio.h>
#include "cbmp.h"
#include "erosion.h"

#define STRUCTURING_ELEMENT_SIZE 3
const unsigned char STRUCTURING_ELEMENT[STRUCTURING_ELEMENT_SIZE][STRUCTURING_ELEMENT_SIZE] = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};

void erodeImage(unsigned char binaryImage[BMP_WIDTH][BMP_HEIGHT])
{
    int x, y;           // Used to traverse the image
    int i, j;           // Used to check with STRUCTURING_ELEMENT
    int checkX, checkY; // Also used to check with STRUCTURING_ELEMENT
    const int CHECK_DISPLACEMENT = -STRUCTURING_ELEMENT_SIZE / 2;
    unsigned char erodedImage[BMP_WIDTH][BMP_HEIGHT];
    _Bool shouldErode;

    for (x = 0; x < BMP_WIDTH; x++)
    {
        for (y = 0; y < BMP_HEIGHT; y++)
        {
            if (binaryImage[x][y] == 0)
            {
                erodedImage[x][y] = 0;
                continue;
            }

            shouldErode = 0;
            for (i = 0, checkX = x + CHECK_DISPLACEMENT; i < STRUCTURING_ELEMENT_SIZE && checkX < BMP_WIDTH; i++, checkX++)
            {
                if (checkX < 0)
                    continue;
                for (j = 0, checkY = y + CHECK_DISPLACEMENT; j < STRUCTURING_ELEMENT_SIZE && checkY < BMP_HEIGHT; j++, checkY++)
                {
                    if (checkY < 0)
                        continue;
                    if (STRUCTURING_ELEMENT[i][j] == 1 && binaryImage[checkX][checkY] == 0)
                    {
                        shouldErode = 1;
                        break;
                    }
                }
                if (shouldErode)
                    break;
            }

            if (shouldErode)
            {
                erodedImage[x][y] = 0;
            }
            else
            {
                erodedImage[x][y] = 1;
            }
        }
    }

    for (x = 0; x < BMP_WIDTH; x++)
    {
        for (y = 0; y < BMP_HEIGHT; y++)
        {
            binaryImage[x][y] = erodedImage[x][y];
        }
    }
}