/*
 * I didn't generalize my solution for Part 1, so I had ot do some adjustments for Part 2.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int currentIndex[] = {1, 3, 5, 7, 1}, // Our set of current locations for each slope (skip line 1 again)
        totalTrees[]   = {0, 0, 0, 0, 0}, // The number of tree each slope has encountered
        lineNum        = 1;               // Which line was just read in

    // Once again, we can skip line 1:
    getline(input, inputVal);

    while(getline(input, inputVal)) {
        // Check each of the "1 Down" slopes:
        for(int i = 0; i < 4; i++) {
            if(inputVal[currentIndex[i]] == '#') {
                totalTrees[i]++;
            } // if
            currentIndex[i] += (i*2 + 1); // The slopes can be calculated based on the index
            currentIndex[i] %= inputVal.length() - 1;
        } // for
        // Check the "2 Down" slope (if needed):
        if(lineNum % 2 == 0) {
            if(inputVal[currentIndex[4]] == '#') {
                totalTrees[4]++;
            } // if(inputVal...)
            currentIndex[4]++;
            currentIndex[4] %= inputVal.length() - 1;
        } // if(lineNum...)
        // Increment the line number:
        lineNum++;
    } // while
    input.close();

    // Determine our final answer (multiply our totals together):
    int total = 1;
    for(int n : totalTrees) {
        cout << n << endl;
        total *= n;
    } // for
    cout << total << endl;
} // main()