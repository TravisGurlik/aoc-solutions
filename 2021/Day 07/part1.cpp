/*
 * Day 07: The Treachery of Whales (https://adventofcode.com/2021/day/07)
 * This ended up being a real fancy way of asking "find the median
 *   of this list of numbers, then calculate the total distance to it."
 * Yes, it turns out that the median is always the ideal target for this.
 * Why?
 * 
 * 
 * I have no idea.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<int> crabs; // Our list of crabs
    
    // Input loop:
    while(getline(input, inputVal)) {
        crabs.push_back(stoi(inputVal)); // Add the crab to the list
    } // while
    input.close();

    // Find target (median):
    int target; // The target position
    sort(crabs.begin(), crabs.end()); // Sort the crabs from left to right
    // Find the median:
    target = crabs.size() % 2 == 0 ?
        crabs[crabs.size() / 2] :
        (crabs[crabs.size() / 2] + crabs[crabs.size() / 2 + 1]) / 2;

    // Calculate fuel:
    int fuel = 0; // The amount of fuel we'll need to use
    for(int crab : crabs) {
        // Each crabs spends fueld equal to the distance between it and the target:
        fuel += abs(crab - target);
    } // for

    //Print final solution:
    cout << fuel << endl;
} // main()