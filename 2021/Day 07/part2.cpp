/*
 * This was a fancy way of asking us to calculate the average then add up
 *   a whole bunch of triangular numbers;
 * Again, I don't know why the average.
 * Heck, I don't even know if that's technically correct.
 * I think needing to round to a whole number position makes it slightly
 *   not the average, but I don't know.
 * When I tried that it didn't work.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <cmath>

using namespace std;

/**
 * @brief Finds the nth triangular number
 *        The nth triangular number is the sum of all numbers from 1 to n
 *        (There's a formula for this, but I forgot about it until just now)
 * @param n Which triangular number to find
 * @return int The triangular number
 */
int triangle(int n) {
    int out = 0; // The output
    // Loop through each number in the range:
    for(int i = 1; i <= n; i++) {
        out += i; // Add to the output
    } // for
    return out;
} // triangle()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<int> crabs;
    
    // Input loop:
    while(getline(input, inputVal)) {
        crabs.push_back(stoi(inputVal));
    } // while
    input.close();

    // Find the target (mean):
    int target;
    // Add up all the positions:
    for(int crab : crabs) {
        target += crab;
    } // for
    target /= crabs.size(); // Divide to get the mean

    // Calculate fuel:
    int fuel = 0;
    for(int crab : crabs) {
        // Each crab uses fuel equal to the nth triangular number,
        // where n is the distance between it and the target:
        fuel += triangle(abs(crab - target));
    } // for

    //Print final solution:
    cout << "Target: " << target << endl;
    cout << "Fuel: " << fuel << endl;
} // main()