#include <algorithm>
#include <iostream>
#include <fstream>
// Additional libraries for this part:
#include <vector>
#include <string>

using namespace std;

/**
 * This is my first solution to any AoC problem.
 * You'll note that I quickly adopted a template for my solutions.
 * The parts of this template will only be explained in this file to avoid needless repetition.
 */

/**
 * Day 1: Report Repair (https://adventofcode.com/2020/day/1)
 * My main goal for Part 1 was to find a way to avoid using a brute force method.
 * This was achieved by sorting the list, then starting with the largest and smallest values.
 * From here, simply check if the sum is too large or too small.
 * If it's too large, move to the next largest value (from the top).
 * If it's too small, move to the next smallest value (from the bottom).
 * This continues until we converge at the target value of 2020.
 */

int main() {
    // The first part of my template is to open the input file for reading with an ifstream:
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        // If for some reason the program is unable to open the file, son't bother with the rest of the program:
        return 1;
    } // if

    // Variables:
    vector<int> expenses;

    // Next, we read in each line of the input and do something with it:
    while(getline(input, inputVal)) {
        // In this case, we convert it to a number and add it to our vector:
        expenses.push_back(stoi(inputVal));
    } // while
    // Close the input file once we're done with it:
    input.close();

    // Sort the list of values from smallest to larget:
    sort(expenses.begin(), expenses.end());

    // Create a forward iterator and a backward iterator for easy bidirectional traversal:
    auto lowVal = expenses.begin();
    auto highVal = expenses.rbegin();
    // Loop until we hit the target sum or the iterators meet:
    while(*lowVal + *highVal != 2020 && *lowVal != *highVal) {
        // If the sum is too large, decrease the larger value:
        if(*lowVal + *highVal > 2020) {
            highVal++;
        } // if
        // Otherwise (we already checked for equality in the loop condition), increase the smaller value:
        else {
            lowVal++;
        } // else
    } // while
    // Once we've left the loop, verify the final sum:
    if(*lowVal + *highVal == 2020) {
        cout << (*lowVal * *highVal) << endl;
    } // if
    // For debugging purposes, print if no pair was found:
    else {
        cout << "No pair found" << endl;
    } // else
    return 0;
} // main()