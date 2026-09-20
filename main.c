// To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
// To run (linux/mac): ./main.out example.bmp example_inv.bmp

// To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
// To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "imageManipulator.h"
#include "erosion.h"
#include "spotDetector.h"
#include "markerAdder.h"

// Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];

// Main function
int main(int argc, char **argv)
{
  // argc counts how may arguments are passed
  // argv[0] is a string with the name of the program
  // argv[1] is the first command line argument (input image)
  // argv[2] is the second command line argument (output image)

  unsigned char binaryImage[BMP_WIDTH][BMP_HEIGHT];
  int foundSpots = 0;
  unsigned int spotCoordinates[10000][2];

  // Checking that 2 arguments are passed
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
    exit(1);
  }

  printf("Example program - 02132 - A1\n");

  // Load image from file
  read_bitmap(argv[1], input_image);

  convertRgbToGray(input_image, binaryImage);
  binaryThreshold(binaryImage);

  while (erodeImage(binaryImage))
  {
    detectSpots(binaryImage, spotCoordinates, &foundSpots);
  }

  addMarkersToImage(input_image, spotCoordinates, foundSpots);

  // Save image to file
  write_bitmap(input_image, argv[2]);

  printf("Done!\n");
  printf("%d cells detected.\n", foundSpots);
  for (int i = 0; i < foundSpots; i++)
  {
    printf("(%d, %d)\n", spotCoordinates[i][0], spotCoordinates[i][1]);
  }

  return 0;
}
