/*
 * Day 08: Seven Segment Search (https://adventofcode.com/2021/day/08)
 * This first part was suspiciously simple.
 * Split a string then count the ones with certain lengths. Nice and easy.
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
    string outputsIn,       // The output digits for each line
           part;            // The individual digits
    int specialCount = 0;   // Our count of special output digits
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        outputsIn = inputVal.substr(inputVal.find("|") + 2); // Get output digits

        // Loop over each output digit:
        for(int i = outputsIn.find(" "); i != outputsIn.npos; i = outputsIn.find(" ")) {
            part = outputsIn.substr(0, i); // Get the digit
            // cout << part << " " << part.length() << endl;
            // Count the special length digits:
            switch(part.length()) {
                case 2:
                case 3:
                case 4:
                case 7:
                    specialCount++;
                    break;
            } // switch
            outputsIn = outputsIn.substr(i + 1); // Remove the digit
        } // for
        // We still have to do the last digit:
        switch(outputsIn.length()) {
            case 2:
            case 3:
            case 4:
            case 7:
                specialCount++;
                break;
        } // switch
    } // while
    input.close();

    //Print final solution:
    cout << specialCount << endl;
} // main()