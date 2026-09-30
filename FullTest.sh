#!/bin/bash

# Remember to run it with bash
if [ $# -le 0 ]; then
    gcc main.c cbmp.c erosion.c imageManipulator.c markerAdder.c spotDetector.c -std=c99 -o main
else
    gcc main.c cbmp.c erosion.c imageManipulator.c markerAdder.c spotDetector.c -std=c99 -o main -D $1
fi

for file in samples/easy/*.bmp; do
    echo "Processing $file"
    ./main "$file" "results/$(basename "$file" .bmp)_RESULT.bmp"
done

for file in samples/medium/*.bmp; do
    echo "Processing $file"
    ./main "$file" "results/$(basename "$file" .bmp)_RESULT.bmp"
done

for file in samples/hard/*.bmp; do
    echo "Processing $file"
    ./main "$file" "results/$(basename "$file" .bmp)_RESULT.bmp"
done

for file in samples/impossible/*.bmp; do
    echo "Processing $file"
    ./main "$file" "results/$(basename "$file" .bmp)_RESULT.bmp"
done

echo "Done."