/*
 * Day 20: Trench Map (https://adventofcode.com/2021/day/20)
 * The return of the "infinite" "cellular automata".
 * This uses a bit of a strange ruleset, but it's not too bad to deal with.
 * The main insight is that there's only a certain area (around the input) that matters;
 *   everything else can be ignored as just off (or toggling, based on the rules).
 * Each step, this area grows by 1 in each direction.
 * 
 * Part 2 was just the same thing but with extra steps, so I didn't bother making a separate file.
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
    const int STEPS = 50; // The number of steps to run for (set to 2 for part 1)
    string enhancement;   // The "enhancement" string (our ruleset)
    getline(input, enhancement); // Get the enhancement string

    getline(input, inputVal); // Toss the empty line

    // Use the first line of the input to determine the maximum size of the area we'll look at:
    getline(input, inputVal);
    inputVal.pop_back();
    const int SIZE = inputVal.length() + STEPS * 2;             // The size of the final image
    vector<vector<char>> image(SIZE, vector<char>(SIZE, '.'));  // The image data (Yes I used characters. Yes bools would have ultimately been better. It's not worth fixing.)
    
    int lineNum = 0; // The line number of the current line in the image
    // Input loop (due to the adjustments above this needs to use a pretty weird structure):
    while(true) {
        // Add each character to the appropriate place in the matrix:
        for(int i = 0; i < inputVal.length(); i++) {
            image[lineNum + STEPS][i + STEPS] = inputVal[i];
        } // for

        // Stop once we run out of input:
        if(!getline(input, inputVal)) {
            break;
        } // if

        // Adjust values for next loop:
        inputVal.pop_back();
        lineNum++;
    } // while
    input.close();

    // Perform the enhancement:
    const bool TOGGLE_EXTRAS = enhancement[0] == '#'; // Whether the "outside" pixels toggle (they can't just stay on or the answer would be infinity)
    for(int cntSteps = 0; cntSteps < STEPS; cntSteps++) {
        bool extrasOn = TOGGLE_EXTRAS && (cntSteps % 2 == 1); // If the "outside" pixels are on for this step
        int minCare = STEPS - cntSteps,                       // The minimum index with different values
            maxCare = SIZE - 1 - STEPS + cntSteps;            // The maximum index with different values
        vector<vector<char>> buffer(image);                   // A buffer, to store the new image in while we loop

        // Loop over each pixel of the image:
        for(int y = minCare - 1; y <= maxCare + 1; y++) {
            for(int x = minCare - 1; x <= maxCare + 1; x++) {
                string val = ""; // The binary string corresponding to the value of the pixels around this pixel
                // Loop through the 9 pixels around this one:
                for(int ya = y - 1; ya <= y + 1; ya++) {
                    for(int xa = x - 1; xa <= x + 1; xa++) {
                        // If this pixel is outside of the relevant range, use the default value for this step:
                        if((ya < minCare || ya > maxCare) || (xa < minCare || xa > maxCare)) {
                            val += extrasOn ? "1" : "0";
                        } // if
                        // Otherwise, get the value from the image:
                        else {
                            val += (image[ya][xa] == '#' ? "1" : "0");
                        } // else
                    } // for(xa)
                } // for(ya)

                int index = stoi(val, nullptr, 2); // Convert the binary string to an integer index
                buffer[y][x] = enhancement[index]; // Use that index to get the replacement pixel
            } // for(x)
        } // for(y)
        image = buffer; // Move the buffer into the image
    } // for(cntSteps)

    // Count the number of lit pixels:
    int numLit = 0;
    for(auto line : image) {
        for(char c : line) {
            numLit += (c == '#' ? 1 : 0);
        } // for(c)
    } // for(line)

    //Print final solution:
    cout << numLit << endl;
} // main()