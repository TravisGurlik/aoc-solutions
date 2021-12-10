/*
 * Day 09: Smoke Basin (https://adventofcode.com/2021/day/09)
 * Another weirdly striaghtforward part 1.
 * Lots and lots of comparisons.
 * This could probably be optimized, but it doesn't need to be.
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
    vector<vector<int>> heights; // Our grid of heights
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vector<int> row; // The numbers in the row
        // For each value, convert it to a number and add it to the row:
        for(char c : inputVal) {
            row.push_back(c - '0');
        } // for
        heights.push_back(row); // Add the row to the grid
    } // while
    input.close();

    // Find low points and calculate risk:
    int risk = 0; // The total risk of the low points
    for(int y = 0; y < heights.size(); y++) { // Loop through rows
        for(int x = 0; x < heights[y].size(); x++) { // Loop through columns
            // If a position is less than all its neighbors (that exist), add its risk to the total:
            if((y == 0 || heights[y][x] < heights[y-1][x]) &&
                    (y == heights.size() - 1 || heights[y][x] < heights[y+1][x]) &&
                    (x == 0 || heights[y][x] < heights[y][x-1]) &&
                    (x == heights[y].size() - 1 || heights[y][x] < heights[y][x+1])) {
                cout << "Low point at (" << x << ", " << y << ") with value " << heights[y][x] << endl;
                risk += (heights[y][x] + 1);
            } // if
        } // for(x)
    } // for(y)

    //Print final solution:
    cout << risk << endl;
} // main()