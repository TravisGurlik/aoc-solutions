#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Day 3: Toboggan Trajectory (https://adventofcode.com/2020/day/3)
 * This puzzle also wasn't too complicated.
 * The main difficulty came from the looping, which could be handled pretty easily
 *   via modular arithmatic.
 * My main stumbling point was forgetting that getline also gets the newline character
 *   at the end of a line of text.
 * This particualr problem would come back to haunt me a few times.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int currentIndex = 3, // Our current location (left/right) (start at 3 since we're skipping the first row)
        totalTrees = 0;   // The total tree count

    // Since the first row will never start with a tree, skip it:
    getline(input, inputVal);

    while(getline(input, inputVal)) {
        // If the current location has a tree, increment the counter:
        if(inputVal[currentIndex] == '#') {
            totalTrees++;
        } // if
        
        // Move to the next row:
        currentIndex += 3;
        currentIndex %= inputVal.length() - 1;
    } // while
    input.close();
    
    // Print the result:
    cout << totalTrees << endl;
} // main()