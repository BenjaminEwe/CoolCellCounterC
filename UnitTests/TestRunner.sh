cd ..

TEST_PATH=UnitTests/TestOutput
TEST_FILE_NAME=test.exe

did_test_pass() {
    if [ $? -eq 0 ]; then
        echo "---- $1 passed. ----"
    else
        echo "---- $1 failed. ----"
    fi
}

move_change_run() {
    mv test.exe $TEST_PATH/$TEST_FILE_NAME
    cd $TEST_PATH
    ./${TEST_FILE_NAME}
    rm $TEST_FILE_NAME
    cd ..
    cd ..
}

# Erosion Test
gcc UnitTests/erosionTest.c erosion.c cbmp.c -o test
move_change_run
did_test_pass "Erosion Tests"

# MarkerTests
gcc UnitTests/MarkerAdderTest.c markerAdder.c cbmp.c -o test
move_change_run
did_test_pass "MarkerAdder Tests"

# Spot Detection Tests
gcc UnitTests/spotDetectorTest.c spotDetector.c markerAdder.c cbmp.c -o test
move_change_run
did_test_pass "Spot Detection Tests"