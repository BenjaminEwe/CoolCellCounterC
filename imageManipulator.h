#include "cbmp.h"

void convertRgbToGray(const unsigned char rgbImage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], unsigned char outputImage[BMP_WIDTH][BMP_HEIGHT]);
void binaryThreshold(unsigned char grayImage[BMP_WIDTH][BMP_HEIGHT]);