#!/bin/bash
g++ brute.cpp -o brute_force
g++ main.cpp -o main
g++ generator.cpp -o data_generator

echo "Tests Begin:"

for i in {1..100}; do
    echo "Test case $i:"
    ./data_generator
    ./brute_force
    ./main

    diff brute_output.txt main_output.txt
    if [ $? -ne 0 ]; then
        echo "Mismatch found in test case $i, input in input.txt, brute output in brute_output.txt, main output in main_output.txt"
        exit 1
    else
        echo "Test case $i passed!"
    fi
done

echo "All test cases passed!"
echo "Press Enter to continue..."
read -n 1 -s