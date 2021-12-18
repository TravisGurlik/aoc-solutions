/*
 * It took me far too long to remember brute force is always an option.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:

using namespace std;

int sign(int n) {
    return n > 0 ? 1 : (n < 0 ? -1 : 0);
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int minX,   // The minimum x value of the target area
        minY,   // The minimum y value of the target area
        maxX,   // The maximum x value of the target area
        maxY,   // The maximum y value of the target area
        start,  // Where the value starts in the input
        split,  // Where to split the values in the input
        end;    // Where the values end in the input
    
    // Get input:
    getline(input, inputVal);
    // X values:
    start = inputVal.find("x") + 2;
    split = inputVal.find(".");
    end = inputVal.find(",");
    minX = stoi(inputVal.substr(start, split - start));
    start = split + 2;
    maxX = stoi(inputVal.substr(start, end - start));
    // Y values:
    start = inputVal.find("y") + 2;
    split = inputVal.find(".", start);
    minY = stoi(inputVal.substr(start, split - start));
    start = split + 2;
    maxY = stoi(inputVal.substr(start));
    input.close();

    // Calculate the minimum x velocity needed to reach the target area:
    // (We can start from 1 since it's equivalent to starting from the other end.)
    int minXV = 1,  // The minimum x value needed to reach the target area
        dist = 1;   // The total horizontal distance traveled thus far
    while(dist < minX) {
         dist += ++minXV;
    } // while

    // Brute force every possible combination of starting velocities:
    int numWays = 0,            // The number of starting velocity pairs that visit the target area
        maxSteps = -2*minY + 1; // The maximum number of steps the probe can take
    // Loop through each pair of possible velocities:
    for(int xv = minXV; xv <= maxX; xv++) {
        for(int yv = -minY; yv >= minY; yv--) {
            // Simulate the probe's movement:
            int xPos = 0, // The probe's x position
                yPos = 0, // The probe's y position
                pxv = xv, // The probe's x velocity
                pyv = yv; // The probe's y velocity
            for(int step = 0; step <= maxSteps; step++) {
                // Move the probe:
                xPos += pxv;
                yPos += pyv;
                // Update velocities:
                if(pxv != 0) {
                    pxv -= sign(pxv);
                } // if
                pyv--;
                // If the target area was passed, stop:
                if(xPos > maxX || yPos < minY) {
                    break;
                } // if
                // If the probe's in the target area, increment the counter and stop:
                if((xPos >= minX && xPos <= maxX) && (yPos >= minY && yPos <= maxY)) {
                    numWays++;
                    break;
                } // if
            } // for(step)
        } // for(yv)
    } // for(xv)

    //Print final solution:
    cout << numWays << endl;
} // main()