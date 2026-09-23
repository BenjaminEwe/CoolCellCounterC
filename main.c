// To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
// To run (linux/mac): ./main.out example.bmp example_inv.bmp

// To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
// To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
  unsigned int (*spotCoordinates)[2] = malloc(sizeof(unsigned int[1000][2]));
#if defined(TIME_GRAY) || defined(TIME_BINARY) || defined(TIME_EROSION_SPOTS) || defined(TIME_MARKERS) || defined(TIME_ALL)
  clock_t start, end;
  double cpu_time_used;
#endif
  if (spotCoordinates == NULL)
  {
    printf("Insufficient heap space\n");
    return 1;
  }

  // Checking that 2 arguments are passed
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
    exit(1);
  }

  printf("Example program - 02132 - A1\n");

  // Load image from file
  read_bitmap(argv[1], input_image);

#ifdef TIME_ALL
  start = clock();
#endif

#ifdef TIME_GRAY
  start = clock();
#endif
  convertRgbToGray(input_image, binaryImage);
#ifdef TIME_GRAY
  end = clock();

  cpu_time_used = end - start;
  printf("RGB to gray conversion time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif

#ifdef TIME_BINARY
  start = clock();
#endif
  binaryThreshold(binaryImage);
#ifdef TIME_BINARY
  end = clock();

  cpu_time_used = end - start;
  printf("Binary threshold time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif

#ifdef TIME_EROSION_SPOTS
  start = clock();
#endif
  while (erodeImage(binaryImage))
  {
    detectSpots(binaryImage, spotCoordinates, &foundSpots);
  }
#ifdef TIME_EROSION_SPOTS
  end = clock();

  cpu_time_used = end - start;
  printf("Erosion and spot detection time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif

#ifdef TIME_MARKERS
  start = clock();
#endif
  addMarkersToImage(input_image, spotCoordinates, foundSpots);
#ifdef TIME_MARKERS
  end = clock();

  cpu_time_used = end - start;
  printf("Adding markers time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif

#ifdef TIME_ALL
  end = clock();

  cpu_time_used = end - start;
  printf("Total time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif

  // Save image to file
  write_bitmap(input_image, argv[2]);

  printf("Done!\n");
  printf("%d cells detected.\n", foundSpots);
  for (int i = 0; i < foundSpots; i++)
  {
    printf("(%d, %d)\n", spotCoordinates[i][0], spotCoordinates[i][1]);
  }

  free(spotCoordinates);

  return 0;
}
