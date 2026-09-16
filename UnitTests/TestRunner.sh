cd ..

# MarkerTests
gcc UnitTests/MarkerAdderTest.c markerAdder.c cbmp.c -o test
./test.exe

if [ $? -eq 0 ]; then
    echo "All tests passed."
else
    echo "Tests failed."
fi

rm test.exe

# Other:

gcc UnitTests/spotDetectorTest.c spotDetector.c markerAdder.c cbmp.c -o test
./test.exe

if [ $? -eq 0 ]; then
    echo "All tests passed."
else
    echo "Tests failed."
fi

rm test.exe