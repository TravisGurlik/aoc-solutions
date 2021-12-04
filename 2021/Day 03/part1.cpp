/*
 * Day 03: Binary Diagnostic (https://adventofcode.com/2021/day/03)
 * This part wasn't too bad; just count the 1s for each digit as the numbers come in,
 *   then construct the numbers from those counts.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int count = 0;                                          // How many numbers we've read
    int bits[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    // The number of 1s in each position
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove that pesky newline
        ++count; // Increment the count
        // For each position, increment the corresponding count if there's a 1 there:
        for(int i = 0; i < inputVal.length(); ++i) {
            if(inputVal[i] == '1') {
                (bits[i])++;
            } // if
        } // for
    } // while
    input.close();

    // Construct our two values:
    string epsilon = "",
           gamma   = "";
    // For each bit, determine the most common digit:
    for(int n : bits) {
        if(n > count/2) {
            // Gamma and Epsilon are opposite each other:
            epsilon += "0";
            gamma += "1";
        } // if
        else {
            epsilon += "1";
            gamma += "0";
        } // else
    } // for

    //Print final solution:
    cout << "Gamma:   " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Product: " << stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2) << endl;
} // main()