#include "markerAdder.h"

#define COLOR_MAIN_RED 255
#define COLOR_MAIN_GREEN 19
#define COLOR_MAIN_BLUE 19

#define COLOR_DARK_RED 187
#define COLOR_DARK_GREEN 19
#define COLOR_DARK_BLUE 19

#define COLOR_LIGHT_RED 255
#define COLOR_LIGHT_GREEN 200
#define COLOR_LIGHT_BLUE 200

void addMarker(int xCoord, int yCoord, unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS]);

void addMarkersToImage(unsigned char rgbImage[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], const unsigned int (*spotCoordinates)[2], unsigned count) {
    for (int i = 0; i < count; i++) {
        addMarker(spotCoordinates[i][0], spotCoordinates[i][1], rgbImage);
    }
}

void addMarker(int xCoord, int yCoord, unsigned char image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS]) {
    /*
    We want to print a heart, so the pixels are
    _ _ k k _ k k _ _
    _ k r r k r r k _
    k r l r r r r r k
    k r r r r r r r k
    k d r r c r r d k
    _ k d r r r d k _
    _ _ k d r d k _ _
    _ _ _ k d k _ _ _
    _ _ _ _ k _ _ _ _
    where 
    k = black = 0,
    r = main red = 1,
    d = dark red = 2,
    l = light red = 3,
    c = center pixel (main red) = 1,
    _ = transparent
    */

    // x offset, y offset, colorType
    unsigned mask[][3] = {
                                  {-2, -4, 0}, {-1, -4, 0},             {1, -4, 0}, {2, -4, 0},
                     {-3, -3, 0}, {-2, -3, 1}, {-1, -3, 1}, {0, -3, 0}, {1, -3, 1}, {2, -3, 1}, {3, -3, 0},
        {-4, -2, 0}, {-3, -2, 1}, {-2, -2, 3}, {-1, -2, 1}, {0, -2, 1}, {1, -2, 1}, {2, -2, 1}, {3, -2, 1}, {4, -2, 0}, 
        {-4, -1, 0}, {-3, -1, 1}, {-2, -1, 1}, {-1, -1, 1}, {0, -1, 1}, {1, -1, 1}, {2, -1, 1}, {3, -1, 1}, {4, -1, 0}, //
        {-4, 0, 0},  {-3, 0, 2},  {-2, 0, 1},  {-1, 0, 1},  {0, 0, 1},  {1, 0, 1},  {2, 0, 1},  {3, 0, 2},  {4, 0, 0},
                     {-3, 1, 0},  {-2, 1, 2},  {-1, 1, 1},  {0, 1, 1},  {1, 1, 1},  {2, 1, 2},  {3, 1, 0},
                                  {-2, 2, 0},  {-1, 2, 2},  {0, 2, 1},  {1, 2, 2},  {2, 2, 0},
                                               {-1, 3, 0},  {0, 3, 2},  {1, 3, 0},
                                                            {0, 4, 0}
       
        
    };

    for (int i = 0; i < sizeof(mask) / sizeof(mask[0]); i++) {
        int x = xCoord + mask[i][0];
        int y = yCoord + mask[i][1];
        
        switch(mask[i][2]) {
            case 0: // black
                image[x][y][0] = 0;
                image[x][y][1] = 0;
                image[x][y][2] = 0;
                break;
            case 1: // main red
                image[x][y][0] = COLOR_MAIN_RED;
                image[x][y][1] = COLOR_MAIN_GREEN;
                image[x][y][2] = COLOR_MAIN_BLUE;
                break;
            case 2: // dark red
                image[x][y][0] = COLOR_DARK_RED;
                image[x][y][1] = COLOR_DARK_GREEN;
                image[x][y][2] = COLOR_DARK_BLUE;
                break;
            case 3: // light red
                image[x][y][0] = COLOR_LIGHT_RED;
                image[x][y][1] = COLOR_LIGHT_GREEN;
                image[x][y][2] = COLOR_LIGHT_BLUE;
                break;
        }
    }
}