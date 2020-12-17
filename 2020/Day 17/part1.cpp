#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * Day 17: Conway Cubes (https://adventofcode.com/2020/day/17)
 * Conway's Game of Life in higher dimensions? Well, it looks like a mess but isn't that bad.
 * That said, there were a lot of minor mistakes I made on this one that took me awhile to resolve.
 * This is actually exactly 3D CGL; the notation is S23/B3.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    // The first is our array of cubes. The dimensions in order are (z, y, x).
    vector<vector<vector<bool>>> cubes(13, vector<vector<bool>>(20, vector<bool>(20, false)));
    int rowNum = 6, // The current input row
        zMin = 5,   // The minimum possible z value for this iteration
        zMax = 7,   // The maximum possible z value for this iteration
        xyMin = 5,  // The minimum possible x/y value for this iteration
        xyMax = 14; // The maximum possible x/y value for this iteration

    while(getline(input, inputVal)) {
        // First, just read in the input and enable the proper cells:
        for(int i = 0; i < inputVal.length(); i++) {
            cubes[6][rowNum][i + 6] = inputVal[i] == '#';
        } // for
        rowNum++;
    } // while
    input.close();

    // Next, perform the typical CGL routine; for each cube, add up its living neighbors.
    // Then, determine the cubes next state and save it to the buffer.
    // Once all cubes have been checked, replace the main grid with the buffer.
    // Repeat as many times as needed.
    for(int count = 0; count < 6; count++) {
        vector<vector<vector<bool>>> buffer(cubes);
        for(int z = zMin; z <= zMax; z++) {
            for(int y = xyMin; y <= xyMax; y++) {
                for(int x = xyMin; x <= xyMax; x++) {
                    int adj = 0; // The number of living adjacent cubes
                    for(int za = z - 1; za <= z + 1 && adj <= 3; za++) {
                        for(int ya = y - 1; ya <= y + 1 && adj <= 3; ya++) {
                            for(int xa = x - 1; xa <= x + 1 && adj <= 3; xa++) {
                                if(za >= 0 && za < cubes.size()) {
                                    if(ya >= 0 && ya < cubes[za].size()) {
                                        if(xa >= 0 && xa < cubes[za][ya].size()) {
                                            if(!(za == z && ya == y && xa == x)) {
                                                // Booleans cast to int as 1 for true and 0 for false,
                                                //   so we can just add the value to our counter directly:
                                                adj += cubes[za][ya][xa];
                                            } // if(!(za...))
                                        } // if(xa...)
                                    } // if(ya...)
                                } // if(za...)
                            } // for(xa)
                        } // for(ya)
                    } // for(za)

                    // Update cube state for next generation:
                    if(cubes[z][y][x]) {
                        // Cube currently active:
                        buffer[z][y][x] = adj == 2 || adj == 3;
                    } // if(cubes...)
                    else {
                        // Cube currently inactive:
                        buffer[z][y][x] = adj == 3;
                    } // else
                } // for(x)
            } // for(y)
        } // for(z)

        // Swap the buffer into the main array:
        cubes = buffer;

        // Update bounds:
        zMin--;
        zMax++;
        xyMin--;
        xyMax++;
    } // for(count)

    // Count up the total number of active cubes:
    // (p = plane, r = row, c = cube)
    int total = 0;
    for(auto p : cubes) {
        for(auto r : p) {
            for(bool c : r) {
                total += c;
            } // for(c)
        } // for(r)
    } // for(p)

    //Print final solution:
    cout << total << endl;
} // main()