/*
 * Day 05: Hydrothermal Venture (https://adventofcode.com/2021/day/05)
 * This one wasn't too bad (barring a minor input formatting issue).
 * Read each number of each line, then increment each vent along the line.
 * Diagonal lines are pretty easy to just ignore.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * @brief Gets the sign of a number
 * @param n The number to get the sign of
 * @return int -1 if n is negative, 1 if n is positive, 0 otherwise
 */
int sign(int n) {
    if(n < 0) return -1;
    if(n > 0) return 1;
    return 0;
} // sign()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<int>> vents(1000, vector<int>(1000, 0));  // The vent map
    int x1, x2, y1, y2,                                     // Various input pieces
        diff;                                               // The difference between coordinates at the start and end of the line
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove the newline
        // Get the numbers out of the input:
        x1 = stoi(inputVal.substr(0, inputVal.find(",")));
        y1 = stoi(inputVal.substr(inputVal.find(",") + 1, inputVal.find(" ") - inputVal.find(",") - 1));
        x2 = stoi(inputVal.substr(inputVal.find_last_of(" ") + 1, inputVal.find_last_of(",") - inputVal.find_last_of(" ") - 1));
        y2 = stoi(inputVal.substr(inputVal.find_last_of(",") + 1));

        // Horizontal line:
        if(x1 == x2) {
            diff = sign(y2 - y1); // Determine the direction
            // Update the vents along the line:
            for(int n = y1; n != y2 + diff; n += diff) {
                vents[n][x1]++;
            } // for
        } // if
        // Vertical line:
        else if(y1 == y2) {
            diff = sign(x2 - x1); // Determine the direction
            // Update the vents along the line:
            for(int n = x1; n != x2 + diff; n += diff) {
                vents[y1][n]++;
            } // for
        } // else if
    } // while
    input.close();

    // Count the number of overlaps:
    int overlaps = 0;
    for(int y = 0; y < 1000; y++) {
        for(int x = 0; x < 1000; x++) {
            //cout << vents[y][x];
            if(vents[y][x] > 1) {
                overlaps++;
            } // if
        } // for(x)
        //cout << endl;
    } // for(y)

    //Print final solution:
    cout << overlaps << endl;
} // main()