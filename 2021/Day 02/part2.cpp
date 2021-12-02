/*
 * Part 2 was a cakewalk today.
 * (Especially compared to what I tried to do yesterday.)
 * Almost all of the code is the same as Part 1.
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
    int depth = 0;
    int pos = 0;
    int aim = 0;    // Our current aim value
    char direction;
    int distance;
    
    // Input loop:
    while(getline(input, inputVal)) {
        direction = inputVal[0];
        distance = stoi(inputVal.substr(inputVal.find(" ")+1));
        // Do different things based on the instructions:
        switch(direction) {
            case 'f': // Forward
                pos += distance;            // Update position
                depth += aim * distance;    // Update depth
                break;
            case 'u': // Up
                aim -= distance;
                break;
            case 'd': // Down
                aim += distance;
                break;
        } // switch
    } // while
    input.close();

    //Print final solution:
    cout << pos * depth << endl;
} // main()