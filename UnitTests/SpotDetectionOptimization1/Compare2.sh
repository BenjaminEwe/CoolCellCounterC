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
./Optimized2.exe "samples/1EASY.bmp" "results/1EASY_RESULT_OPTIMIZED2.bmp"
echo "Medium"
./Optimized2.exe "samples/1MEDIUM.bmp" "results/1MEDIUM_RESULT_OPTIMIZED2.bmp"
echo "Hard"
./Optimized2.exe "samples/1HARD.bmp" "results/1HARD_RESULT_OPTIMIZED2.bmp"