/*
 * Day 11: Seating System (https://adventofcode.com/2020/day/11)
 * Having some experience with cellular automata made this a lot easier for me.
 * This looks relly messy, but that's just how CA looks.
 * This particular CA is B0/S0123, with a third "always dead" state.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <vector>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<char>> spaces; // The state of each space

    while(getline(input, inputVal)) {
        // Construct the row vector:
        vector<char> row;
        for(char c : inputVal) {
            // pop_back() removes the last character from the last row, so this is
            //   the first way I thought of to avoid that:
            if(c == '.' || c == 'L' || c == '#') {
                row.push_back(c);
            }
        }
        // Add the row vector to the main vector:
        spaces.push_back(row);
    } // while
    input.close();

    // Repeat the automation until nothing changes:
    bool changed;
    do {
        // Reset variables:
        changed = false;
        // A buffer vector is needed to hold the next state to avoid interferring with the current updates:
        vector<vector<char>> newSpaces(spaces);
        // Loop through every cell:
        for(int y = 0; y < spaces.size(); ++y) {
            for(int x = 0; x < spaces[y].size(); ++x) {
                // If it's a floor cell, don't do anything with it:
                if(spaces[y][x] == '.') continue;
                // Otherwise, determine how many alive neighbors this cell has:
                int adjacent = 0;
                for(int ya = y-1; ya <= y+1; ++ya) {
                    for(int xa = x-1; xa <= x+1; ++xa) {
                        // Ensure the neighbor is inbounds:
                        if(ya >= 0 && ya < spaces.size()) {
                            if(xa >= 0 && xa < spaces[ya].size()) {
                                // Ensure the neighbor isn't the current cell:
                                if(!(ya == y && xa == x)) {
                                    // If the neighbor is filled, increment the count:
                                    if(spaces[ya][xa] == '#') {
                                        adjacent++;
                                    } // if(spaces...)
                                } // if(!(ya...))
                            } // if(xa...)
                        } // if(ya...)
                    } // for(xa)
                } // for(ya)
                if(spaces[y][x] == 'L') {
                    // Fill an empty seat only if it has no alive neighbors:
                    if(adjacent == 0) {
                        newSpaces[y][x] = '#';
                        changed = true;
                    } // if(adjacent...)
                } // if(spaces...)
                else if(spaces[y][x] == '#') {
                    // Empty a filled seat if it has too many neighbors:
                    if(adjacent >= 4) {
                        newSpaces[y][x] = 'L';
                        changed = true;
                    } // if(adjacent...)
                } // else if(spaces...)
            } // for(x)
        } // for(y)
        // Swap the buffer into the main vector:
        spaces = newSpaces;
    } while(changed);

    // Once the simulation stabilizes, count the number of filled seats:
    int filled = 0;
    for(vector<char> v : spaces) {
        for(char c : v) {
            cout << c;
            if(c == '#') {
                filled++;
            } // if
        } // for(c)
        cout << endl;
    } // for(v)

    // Print the final total:
    cout << endl << filled << endl;
} // main()