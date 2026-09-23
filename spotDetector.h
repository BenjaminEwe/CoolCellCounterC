#include "cbmp.h"

void detectSpots(unsigned char binaryImage[BMP_WIDTH][BMP_HEIGHT], unsigned char (*outputCoordinates)[2], int* foundSpots);