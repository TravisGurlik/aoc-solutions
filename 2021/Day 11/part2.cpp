/*
 * This part was very easy to adapt from the last.
 * Ran into a minor snag when the step count got incremented one extra time after stopping.
 * Almost all the code is the same as Part 1.
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
    vector<vector<int>> octopuses;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vector<int> row;
        for(char c : inputVal) {
            row.push_back(c - '0');
        } // for
        octopuses.push_back(row);
    } // while
    input.close();

    int step = 1; // The number of steps that have elapsed
    // Abuse a for loop to increment our step counter along the way,
    // and continue until all the octopuses flash at once:
    for(bool allFlash = false; !allFlash; step++) {
        vector<vector<bool>> flashed(10, vector<bool>(10, false));
        vector<pair<int, int>> toFlash;
        for(int y = 0; y < 10; y++) {
            for(int x = 0; x < 10; x++) {
                octopuses[y][x]++;
                if(octopuses[y][x] > 9) {
                    toFlash.push_back(make_pair(x, y));
                    flashed[y][x] = true;
                } // if
            } // for(x)
        } // for(y)
        while(toFlash.size() > 0) {
            int y = toFlash.back().second,
                x = toFlash.back().first;
            toFlash.pop_back();
            for(int y1 = y - 1; y1 <= y + 1; y1++) {
                if(y1 != -1 && y1 != 10) {
                    for(int x1 = x - 1; x1 <= x + 1; x1++) {
                        if(x1 != -1 && x1 != 10) {
                            octopuses[y1][x1]++;
                            if(octopuses[y1][x1] > 9 && !flashed[y1][x1]) {
                                toFlash.push_back(make_pair(x1, y1));
                                flashed[y1][x1] = true;
                            } // if
                        } // if(x1)
                    } // for(x1)
                } // if(y1)
            } // for(y1)
        } // while
        allFlash = true; // Set up the all flash check
        cout << endl << "Step " << step << ":" << endl;
        // Reset octopuses that flashed, and check if any didn't flash:
        for(int y = 0; y < 10; y++) {
            for(int x = 0; x < 10; x++) {
                if(octopuses[y][x] > 9) {
                    octopuses[y][x] = 0;
                } // if
                // If any did not flash, then we're not done yet:
                if(!flashed[y][x]) {
                    allFlash = false;
                } // if
                cout << octopuses[y][x];
            } // for(x)
            cout << endl;
        } // for(y)
    } // for(allFlash)

    //Print final solution:
    cout << endl << --step << endl;
} // main()