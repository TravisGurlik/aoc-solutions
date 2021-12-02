/*
 * Day 01: Sonar Sweep (https://adventofcode.com/2021/day/01)
 * As per usual, this first part was very simple.
 * Just save the last value and compare.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int depthIncreases = 0; // The number of times the depth has increased
    int currentDepth;       // The current depth
    int lastDepth = -1;     // The previous depth

    // Input loop:
    while(getline(input, inputVal)) {
        // Get the current depth (converting the string to an int):
        currentDepth = stoi(inputVal);
        // Compare to the previous depth and increase the counter if needed:
        if(lastDepth != -1 && currentDepth > lastDepth) {
            ++depthIncreases;
        } // if
        // Update the previous depth:
        lastDepth = currentDepth;
    } // while
    input.close();

    //Print final solution:
    cout << depthIncreases << endl;
} // main()