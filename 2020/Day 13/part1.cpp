/*
 * Day 13: Shuttle Search (https://adventofcode.com/2020/day/13)
 * I really wish buses were this consistent in real life.
 * The most complicated part of this was getting each bus ID from the single massive input row.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <cmath>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int leave;           // The time we would like to leave
    vector<int> departs; // The list of bus IDs (only the numbers)

    // There's only two lines, so we can get them both individually:
    getline(input, inputVal);
    leave = stoi(inputVal);
    getline(input, inputVal);
    input.close();

    // More variables:
    int lastIndex = -1, // The last index we were at within the input line
        nextIndex = 0;  // The index of the next ','
    nextIndex = inputVal.find(","); // Set initial value for nextIndex

    // Loop through each index:
    while(nextIndex != inputVal.npos) {
        cout << lastIndex << " -> " << nextIndex << " = ";
        // Get the ID:
        string val = inputVal.substr(lastIndex+1, nextIndex - lastIndex - 1);
        cout << val << endl;
        if(val != "x") {
            // If the ID is actually an ID, add it to the list:
            departs.push_back(stoi(val));
        } // if
        // Update variables:
        lastIndex = nextIndex;
        nextIndex = inputVal.find(",", nextIndex+1);
    } // while

    // Get the last index (skipped since there's no ',' after it):
    cout << lastIndex << " -> " << nextIndex << " = ";
    string val = inputVal.substr(lastIndex+1);
    cout << val << endl;
    if(val != "x") {
        departs.push_back(stoi(val));
    } // if
    
    // Even more variables:
    int minTime = (1 + (leave / departs[0])) * departs[0], // The earliest time we can leave
        minI    = 0;                                       // The ID of the earliest bus we can get on
    
    // Find the earliest bus we can get on:
    for(int i = 1; i < departs.size(); ++i) {
        int time = (1 + (leave / departs[i])) * departs[i];
        if(time < minTime) {
            minTime = time;
            minI = i;
        } // if
    } // for

    // Print the results:
    cout << "minI = " << minI << "; " << departs[minI] << " * (" << minTime << " - " << leave << ") = ";
    cout << (departs[minI] * (minTime - leave)) << endl;
} // main()