#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * Most of this part is the same as Part 1, with the exception of the neighbor detection.
 * (And the rule; it's now B0/S01234.)
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } //if

    vector<vector<char>> spaces;

    while(getline(input, inputVal)) {
        vector<char> row;
        for(char c : inputVal) {
            if(c == '.' || c == 'L' || c == '#') {
                row.push_back(c);
            } // if
        } // for
        spaces.push_back(row);
    } // while
    input.close();

    bool changed;
    do {
        changed = false;
        vector<vector<char>> newSpaces(spaces);
        for(int y = 0; y < spaces.size(); ++y) {
            for(int x = 0; x < spaces[y].size(); ++x) {
                if(spaces[y][x] == '.') continue;
                int adjacent = 0;
                // Neighbor calculation is bit more involved this time around.
                // If 4 is the current cell, directions are mapped as follows:
                // 012
                // 345
                // 678
                // Loop through each direction:
                for(int i = 0; i < 9; ++i) {
                    // Ignore 4 (the current cell):
                    if(i == 4) continue;
                    // Map the value to a direction:
                    int dy = (i / 3) - 1;
                    int dx = (i % 3) - 1;
                    // Determine the first cell to check:
                    int ya = y + dy;
                    int xa = x + dx;
                    // Loop until an invalid cell or a seat is found:
                    // (Yes, this is far messier than necessary)
                    while(true) {
                        // Ensure the cell being checked is inbounds:
                        if(ya >= 0 && ya < spaces.size()) {
                            if(xa >= 0 && xa < spaces[ya].size()) {
                                // Check the state of the cell:
                                if(spaces[ya][xa] == '#') {
                                    // Filled seat - increase counter & exit:
                                    adjacent++;
                                    break;
                                } // if(spaces...)
                                else if(spaces[ya][xa] == '.') {
                                    // Floor - move ot next cell:
                                    ya += dy;
                                    xa += dx;
                                } // else if(spaces...)
                                else {
                                    // Empty seat - exit:
                                    break;
                                } // else
                            } // if(xa...)
                            else {
                                break;
                            } // else
                        } // if(ya...)
                        else {
                            break;
                        } // else
                    } // while(true)
                } // for(i)
                if(spaces[y][x] == 'L') {
                    if(adjacent == 0) {
                        newSpaces[y][x] = '#';
                        changed = true;
                    } // if(adjacent...)
                } // if(spaces...)
                else if(spaces[y][x] == '#') {
                    if(adjacent >= 5) {
                        newSpaces[y][x] = 'L';
                        changed = true;
                    } // if(adjacent...)
                } // else if(spaces...)
            } // for(x)
        } // for(y)
        spaces = newSpaces;
    } while(changed);
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

    cout << endl << filled << endl;
} // main()