#include "cbmp.h"
#include <stdbool.h>

#define DETECTION_SIZE 12
#define EXCLUSION_SIZE 1

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
            }
        }
    }
}

bool scanForSpots(const unsigned char binaryImage[BMP_1D_SIZE], int x, int y) {
    bool whiteFound = false;

    for (int i = x - 5; i <= x + 6; i++) {
        for (int j = y - 5; j <= y + 6; j++) {
            if (i < 0 || i >= BMP_WIDTH || j < 0 || j >= BMP_HEIGHT) {
                continue;
            }
            if (binaryImage[(i + j * BMP_WIDTH) / 8] & (1 << ((i + j * BMP_WIDTH) % 8))) {
                whiteFound = true;
            }
        }
    }

    if (!whiteFound) { 
        return false; // We havent found a single white cell in the inclusion window
    }

    for (int i = x - 6; i <= x + 7; i++) {
        if (i < 0 || i >= BMP_WIDTH || y-6 < 0 || y+7 >= BMP_HEIGHT) {
            continue;
        }
        if (binaryImage[(i + (y-6) * BMP_WIDTH) / 8] & 1 << ((i + (y-6) * BMP_WIDTH) % 8) || binaryImage[(i + (y-7) * BMP_WIDTH) / 8] & (1 << ((i + (y-7) * BMP_WIDTH) % 8))) {
            return false;
        }
    }

    for (int i = y - 6; i <= y + 7; i++) {
        if (i < 0 || i >= BMP_WIDTH || x-6 < 0 || x+7 >= BMP_HEIGHT) {
            continue;
        }
        if (binaryImage[(x-6 + i * BMP_WIDTH) / 8] & 1 << ((x-6 + i * BMP_WIDTH) % 8) || binaryImage[(x-7 + i * BMP_WIDTH) / 8] & (1 << ((x-7 + i * BMP_WIDTH) % 8))) {
            return false;
        }
    }

    return true; // We havent found a single white pixel in the exclusion window
}

void eraseSpots(unsigned char binaryImage[BMP_1D_SIZE], int x, int y) {
    for (int i = x - 6; i < x + 7; i++) {
        for (int j = y - 6; j < y + 7; j++) {
            if (i < 0 || i >= BMP_WIDTH || j < 0 || j >= BMP_HEIGHT) {
                continue;
            }
            
            binaryImage[(i + j * BMP_1D_SIZE) / 8] &= ~(1 << ((i + j * BMP_1D_SIZE) % 8));
        }
    }
}