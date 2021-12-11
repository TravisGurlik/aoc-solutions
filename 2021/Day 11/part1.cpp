/*
 * Day 11: Dumbo Octopus (https://adventofcode.com/2021/day/11)
 * I love me some cellular automata (kinda).
 * Not much to this one; just need to make sure you don't multi-flash an octopus.
 * A boolean matrix does a pretty good job at that.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
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
    vector<vector<int>> octopuses; // The energy level of each octopus
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vector<int> row; // The row to add
        // Add each octopus to the row:
        for(char c : inputVal) {
            row.push_back(c - '0');
        } // for
        octopuses.push_back(row); // Add the row to the matrix
    } // while
    input.close();

    // Simulate!
    int flashes = 0; // How many flashes we've encountered
    // Loop for 100 steps:
    for(int step = 0; step < 100; step++) {
        vector<vector<bool>> flashed(10, vector<bool>(10, false)); // Tracks which octopuses have already been marked to flash
        vector<pair<int, int>> toFlash; // Tracks which octopuses still need to flash
        // Increase each octopus' energy by one:
        for(int y = 0; y < 10; y++) {
            for(int x = 0; x < 10; x++) {
                octopuses[y][x]++;
                // If the octopus has more than 9 energy, mark it as a flasher:
                if(octopuses[y][x] > 9) {
                    toFlash.push_back(make_pair(x, y));
                    flashed[y][x] = true;
                } // if
            } // for(x)
        } // for(y)
        // Flash those octopuses (continue until there are none left to flash):
        while(toFlash.size() > 0) {
            // Pull out the coordinates for easier referencing:
            int y = toFlash.back().second,
                x = toFlash.back().first;
            toFlash.pop_back(); // Remove this octopus from the list
            flashes++; // Increment the flash count
            // Increase the energy of each adjacent octopus (avoiding edges):
            // (This will increase the energy of the current octopus, but it doesn't
            // affect functionality since the value gets reset afterwards anyway.)
            for(int y1 = y - 1; y1 <= y + 1; y1++) {
                if(y1 != -1 && y1 != 10) {
                    for(int x1 = x - 1; x1 <= x + 1; x1++) {
                        if(x1 != -1 && x1 != 10) {
                            octopuses[y1][x1]++;
                            // If this octopus now needs to flash, add it to the list:
                            if(octopuses[y1][x1] > 9 && !flashed[y1][x1]) {
                                toFlash.push_back(make_pair(x1, y1));
                                flashed[y1][x1] = true;
                            } // if
                        } // if(x1)
                    } // for(x1)
                } // if(y1)
            } // for(y1)
        } // while
        // Reset any flashed octopuses to 0:
        for(int y = 0; y < 10; y++) {
            for(int x = 0; x < 10; x++) {
                if(octopuses[y][x] > 9) {
                    octopuses[y][x] = 0;
                } // if
            } // for(x)
        } // for(y)
    } // for(step)

    //Print final solution:
    cout << flashes << endl;
} // main()