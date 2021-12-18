/*
 * Day 17: Trick Shot (https://adventofcode.com/2021/day/17)
 * This took way too many tries.
 * I don't want to talk about it.
 * 
 * Actual strategy came from realizing that the y value will always be 0
 *   at least once when firing upwards, so the maximum speed the probe can have
 *   at that point is equal to the depth of the bottom of the target area.
 * The starting speed is thus -minY - 1.
 * The height caluclation is from summing all of the numbers from 1 to that
 *   initial speed (using the proper formula this time).
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int minY,   // The minimum Y value of the target area
        yStart, // The start of the Y values in the input
        ySplit; // Where to split the Y values in the input
    
    // Get minY:
    getline(input, inputVal);
    yStart = inputVal.find("y") + 2;
    ySplit = inputVal.find(".", yStart);
    minY = stoi(inputVal.substr(yStart, ySplit - yStart));
    input.close();

    //Print final solution:
    cout << (-minY)*(-minY-1)/2 << endl;
} // main()