#!/bin/bash

echo "Easy"
./Optimized.exe "samples/1EASY.bmp" "results/1EASY_RESULT_OPTIMIZED.bmp"
echo "Medium"
./Optimized.exe "samples/1MEDIUM.bmp" "results/1MEDIUM_RESULT_OPTIMIZED.bmp"
echo "Hard"
./Optimized.exe "samples/1HARD.bmp" "results/1HARD_RESULT_OPTIMIZED.bmp"

echo ""
echo ""

echo "Easy"
./UnOptimized.exe "samples/1EASY.bmp" "results/1EASY_RESULT_UNOPTIMIZED.bmp"
echo "Medium"
./UnOptimized.exe "samples/1MEDIUM.bmp" "results/1MEDIUM_RESULT_UNOPTIMIZED.bmp"
echo "Hard"
./UnOptimized.exe "samples/1HARD.bmp" "results/1HARD_RESULT_UNOPTIMIZED.bmp"