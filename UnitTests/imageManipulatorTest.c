#include "../imageManipulator.h"
#include <stdio.h>

unsigned char rgbImage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char outputImage[BMP_WIDTH][BMP_HEIGHT];

int main() {
    read_bitmap("../TestResources/example.bmp", rgbImage);

    convertRgbToGray(rgbImage, outputImage);

    // RGB test here?

    binaryThreshold(outputImage);

    // Binary  threshold test here?

    write_bitmap(outputImage, "manipulatorOutput.bmp");

    return 0;
}