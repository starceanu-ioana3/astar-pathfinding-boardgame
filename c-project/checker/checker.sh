#!/bin/bash

# Exec name
EXEC_NAME=./checker/main

POINTS_TEST=(
    10
    10
    10
    20
    20
    30
)

points=0

function compare_files {
    flag_diff=0
    diff -b -B -q $1 $2 > /dev/null 2>&1
    if [ $? -eq 0 ];
    then
        flag_diff=1
    else
        flag_diff=0
    fi
}

function add_points {
    if [ "$flag_diff" -eq 1 ]; then
        printf "Test %2d ................................. (+%2dpt)\n" $(($1 + 1)) $((POINTS_TEST[$1]))
        (( points += POINTS_TEST[$1] ))
    else
        printf "Test %2d ................................. (+%2dpt)\n" $(($1 + 1)) $((0))
    fi
}

rm -f "Step_1/test_1_1.csv"
rm -f "Step_1/test_1_2.txt"
rm -f "Step_1/test_1_3.csv"
rm -f "Step_2/test_2_1.txt"
rm -f "Step_2/test_2_2.txt"
rm -f "Step_3/test_3.txt"

/bin/bash -c 'cd .. && make clean' >/dev/null 2>&1
/bin/bash -c 'cd .. && make main'

if command -v timeout >/dev/null 2>&1; then
    timeout 60 ./main
    exec_code=$?
else
    ./main
    exec_code=$?
fi

if [ "$exec_code" -eq 124 ]; then
    echo "Execution exceeded the 60-second time limit!"
    echo -e "\nTotal: 0/100pt"
    exit
fi


compare_files "Step_1/test_1_1.csv" "Step_1/ref_test_1_1.csv"
add_points 0

compare_files "Step_1/test_1_2.txt" "Step_1/ref_test_1_2.txt"
add_points 1

compare_files "Step_1/test_1_3.csv" "Step_1/ref_test_1_3.csv"
add_points 2

compare_files "Step_2/test_2_1.txt" "Step_2/ref_test_2_1.txt"
add_points 3

compare_files "Step_2/test_2_2.txt" "Step_2/ref_test_2_2.txt"
add_points 4

compare_files "Step_3/test_3.txt" "Step_3/ref_test_3.txt"
add_points 5


echo -e "\nTotal: $points/100pt"
echo

