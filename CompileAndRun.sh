#!/bin/bash

# Remember to run it with bash
if [ $# -le 0 ]; then
    gcc main.c cbmp.c erosion.c imageManipulator.c markerAdder.c spotDetector.c -std=c99 -o main
else
    gcc main.c cbmp.c erosion.c imageManipulator.c markerAdder.c spotDetector.c -std=c99 -o main -D $1
fi

echo "Easy"
./main "samples/easy/1EASY.bmp" "results/1EASY_RESULT.bmp"
echo "Medium"
./main "samples/medium/1MEDIUM.bmp" "results/1MEDIUM_RESULT.bmp"
echo "Hard"
./main "samples/hard/1HARD.bmp" "results/1HARD_RESULT.bmp"
# ./main "samples/impossible/1IMPOSSIBLE.bmp" "results/1IMPOSSIBLE_RESULT.bmp"