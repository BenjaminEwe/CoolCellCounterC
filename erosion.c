#include <stdio.h>
#include "cbmp.h"
#include "erosion.h"

#define STRUCTURING_ELEMENT_SIZE 3
const unsigned char STRUCTURING_ELEMENT[STRUCTURING_ELEMENT_SIZE][STRUCTURING_ELEMENT_SIZE] = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};

_Bool erodeImage(unsigned char binaryImage[BMP_1D_SIZE])
{
    int x, y;           // Used to traverse the image
    int i, j;           // Used to check with STRUCTURING_ELEMENT
    int checkX, checkY; // Also used to check with STRUCTURING_ELEMENT
    const int CHECK_DISPLACEMENT = -STRUCTURING_ELEMENT_SIZE / 2;
    unsigned char erodedImage[BMP_1D_SIZE];
    int currIndex = 0;
    int currBit = 0;
    _Bool shouldErode;
    _Bool erodedSomething = 0;

    for (x = 0; x < BMP_WIDTH; x++)
    {
        for (y = 0; y < BMP_HEIGHT; y++)
        {
            currIndex = (x + y * BMP_WIDTH) / 8;
            currBit = (x + y * BMP_WIDTH) % 8;
            if (binaryImage[currIndex] & (1 << currBit) == 0)
            {
                erodedImage[x + y * BMP_WIDTH] &= ~(1 << currBit);
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
                    if (STRUCTURING_ELEMENT[i][j] == 1 && binaryImage[(checkX + checkY * BMP_WIDTH) / 8] & (1 << ((checkX + checkY * BMP_WIDTH) % 8)) == 0)
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
                erodedImage[currIndex] &= ~(1 << currBit);
                erodedSomething = 1;
            }
            else
            {
                erodedImage[currIndex] |= 1 << currBit;
            }
        }
    }

    for (i = 0; i < BMP_1D_SIZE; i++)
    {
        binaryImage[i] = erodedImage[i];
    }

    return erodedSomething;
}