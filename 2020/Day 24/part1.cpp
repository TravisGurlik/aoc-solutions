/*
 * Day 24: Lobby Layout (https://adventofcode.com/2020/day/24)
 * I amde a... very questionable choice for my storage container for this part.
 * I have no idea why I thought this was a good idea.
 * For containers, X value changes by 2 with 'w' and 'e' and by 1 with all other directions.
 *   Y value changes by 1 for directions starting with 'n' and 's'.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    unordered_map<int, unordered_map<int, bool>> tiles; // Our tiles, maps x-coord -> (y-coord -> state); true = black, false = white
    int xVal,                                           // The X offset of the tile to change
        yVal;                                           // The Y value of the tile to change

    while(getline(input, inputVal)) {
        // Reset offsets:
        xVal = 0;
        yVal = 0;
        // Remove newline:
        inputVal.pop_back();

        // Get all directions from the input line:
        for(int i = 0; i < inputVal.size(); i++) {
            if(inputVal[i] == 'n') {
                // North directions:
                yVal++;
                // For vertical movement, we also need the next character:
                i++;
                if(inputVal[i] == 'e') {
                    // Northeast:
                    xVal++;
                } // if(...'e')
                else {
                    // Northwest:
                    xVal--;
                } // else
            } // if(...'n')
            else if(inputVal[i] == 's') {
                // South directions:
                yVal--;
                i++;
                if(inputVal[i] == 'e') {
                    // Southeast:
                    xVal++;
                } // if(...'e')
                else {
                    // Southwest:
                    xVal--;
                } // else
            } // else if(...'s')
            else if(inputVal[i] == 'e') {
                // East:
                xVal += 2;
            } // else if(...'e')
            else {
                // West:
                xVal -= 2;
            } // else
        } // for
        tiles[xVal][yVal] = !tiles[xVal][yVal];
    } // while
    input.close();

    // Count how many tiles are black:
    int black = 0;
    for(auto ia = tiles.begin(); ia != tiles.end(); ia++) {
        for(auto ib = ia->second.begin(); ib != ia->second.end(); ib++) {
            black += ib->second;
        } // for(ib)
    } // for(ia)

    //Print final solution:
    cout << black << endl;
} // main()