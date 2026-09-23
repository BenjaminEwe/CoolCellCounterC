#include "cbmp.h"

void detectSpots(unsigned char binaryImage[BMP_WIDTH][BMP_HEIGHT], unsigned int (*outputCoordinates)[2], int* foundSpots);