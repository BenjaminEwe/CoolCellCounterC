#include "../markerAdder.h"
#include <stdio.h>

unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS] = {0};
unsigned char garbage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS] = {0};


unsigned int spotCoordinates[][2] = {
    {10, 10},
    {20, 20},
    {30, 30}
};

unsigned int count = sizeof(spotCoordinates) / sizeof(spotCoordinates[0]);

int main() {
    addMarkersToImage(image, spotCoordinates, count);

    // Check if the markers were added correctly
    for (int i = 0; i < count; i++) {
        int x = spotCoordinates[i][0];
        int y = spotCoordinates[i][1];
        if (image[x][y][0] != 255) {
            return 1;
            printf("Test failed at coordinate (%d, %d)\n", x, y);
        }
    }

    read_bitmap("../TestResources/example.bmp", garbage);
    write_bitmap(image, "output.bmp");
    return 0;
}