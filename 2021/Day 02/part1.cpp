/*
 * Day 02: Drive! (https://adventofcode.com/2021/day/02)
 * Hm, this feels familiar somehow...
 * I almost used a stringstream for this. Almost.
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
    int depth = 0;  // Our current depth
    int pos = 0;    // Our current position
    char direction; // The direction to move in
    int distance;   // The distance ot move
    
    // Input loop:
    while(getline(input, inputVal)) {
        // Get the important bits out of the instructions:
        direction = inputVal[0];                                // We only need the first character of the direction to differentiate them
        distance = stoi(inputVal.substr(inputVal.find(" ")+1)); // The distance is everything after the space
        // Update variables based on direction:
        switch(direction) {
            case 'f': // Forward
                pos += distance;
                break;
            case 'u': // Up
                depth -= distance;
                break;
            case 'd': // Down
                depth += distance;
                break;
        } // switch
    } // while
    input.close();

    //Print final solution:
    cout << pos * depth << endl;
} // main()