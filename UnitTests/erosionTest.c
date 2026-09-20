#include "../erosion.h"
#include <stdio.h>

char* input_file_path = "results_example/step_0.bmp";
unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char flatImage[BMP_WIDTH][BMP_HEIGHT];

void print_coordinates(const unsigned int coords[20][2], int count);
void flattenImage(const unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], unsigned char flatImage[BMP_WIDTH][BMP_HEIGHT]);
void deepenImage(unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], const unsigned char flatImage[BMP_WIDTH][BMP_HEIGHT]);

int main() {
    read_bitmap(input_file_path, image);

    flattenImage(image, flatImage);
    
    erodeImage(flatImage);

    deepenImage(image, flatImage);

    write_bitmap(image, "erosionResult.bmp");

    return 0;
}

void print_coordinates(const unsigned int coords[20][2], int count) {
    for (size_t i = 0; i < count; i++) {
        printf("[%2zu] (%u, %u)\n", i, coords[i][0], coords[i][1]);
    }
    printf("--------------------------\n");
}

void flattenImage(const unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], unsigned char flatImage[BMP_WIDTH][BMP_HEIGHT]) {
    for (int i = 0; i < BMP_WIDTH; i++) {
        for (int j = 0; j < BMP_HEIGHT; j++) {
            flatImage[i][j] = image[i][j][0];
        }
    }
}

void deepenImage(unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], const unsigned char flatImage[BMP_WIDTH][BMP_HEIGHT]) {
    for (int i = 0; i < BMP_WIDTH; i++) {
        for (int j = 0; j < BMP_HEIGHT; j++) {
            image[i][j][0] = flatImage[i][j] * 255;
            image[i][j][1] = flatImage[i][j] * 255;
            image[i][j][2] = flatImage[i][j] * 255;
        }
    }
}