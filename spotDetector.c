#include "cbmp.h"
#include <stdbool.h>
#include <stdio.h>

bool scanForSpots(const unsigned char binaryImage[BMP_1D_SIZE], int x, int y);
void eraseSpots(unsigned char binaryImage[BMP_1D_SIZE], int x, int y);

/// Returns the number found
/// Modifies the coordinate array
void detectSpots(unsigned char binaryImage[BMP_1D_SIZE], unsigned int (*outputCoordinates)[2], int* foundSpots) {
    for (int i = 0; i < BMP_WIDTH; i++) {
        for (int j = 0; j < BMP_HEIGHT; j++) {
            if (scanForSpots(binaryImage, i, j)) {
                outputCoordinates[*foundSpots][0] = i;
                outputCoordinates[*foundSpots][1] = j;
                (*foundSpots)++;
                eraseSpots(binaryImage, i, j);
                j += 6; // We have already erased the next 6 pixels, so we can skip them
            }
        }
    }
}

bool scanForSpots(const unsigned char binaryImage[BMP_1D_SIZE], int x, int y) {
    if (!(binaryImage[(x + y * BMP_WIDTH) >> 3] & (1 << ((x + y * BMP_WIDTH) & 7)))) { 
        return false; // We only check the centre one: If one of its neighbours have a white spot, we will process that later.
    }

    // Exclusion ring:
    for (int i = x - 6; i <= x + 7; i++) {
        if (i < 0 || i >= BMP_WIDTH) {
            continue;
        }

        if ((y-6 >= 0 && binaryImage[(i + (y-6) * BMP_WIDTH) >> 3] & (1 << ((i + (y-6) * BMP_WIDTH) & 7))) || (y+7 < BMP_HEIGHT && binaryImage[(i + (y+7) * BMP_WIDTH) >> 3] & (1 << ((i + (y+7) * BMP_WIDTH) & 7)))) {
            return false;
        }
    }

    for (int i = y - 6; i <= y + 7; i++) {
        if (i < 0 || i >= BMP_WIDTH) {
            continue;
        }
        
        if ((x-6 >= 0 && binaryImage[(x-6 + i * BMP_WIDTH) >> 3] & (1 << ((x-6 + i * BMP_WIDTH) & 7))) || (x+7 < BMP_WIDTH && binaryImage[(x+7 + i * BMP_WIDTH) >> 3] & (1 << ((x+7 + i * BMP_WIDTH) & 7)))) {
            return false;
        }
    }

    return true; // We havent found a single white pixel in the exclusion window
}

void eraseSpots(unsigned char binaryImage[BMP_1D_SIZE], int x, int y) {
    for (int i = x - 6; i < x + 7; i++) {
        if (i < 0) continue;
        if (i >= BMP_WIDTH) break;
        for (int j = y - 6; j < y + 7; j++) {
            if (j < 0) continue;
            if (j >= BMP_HEIGHT) break;
            binaryImage[(i + j * BMP_WIDTH) >> 3] &= ~(1 << ((i + j * BMP_WIDTH) & 7));
        }
    }
}