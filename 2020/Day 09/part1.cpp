#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <list>

using namespace std;

/**
 * Day 9: Encoding Error (https://adventofcode.com/2020/day/9)
 * Take Day 1 and apply it to something.
 * This uses the same strategy as I used in Day 1 of sorting the list and
 *   moving in from both ends.
 * In this case, we simply repeat this until encountering the invalid number.
 * It was on this day that I discovered the wonder of lists, which made this
 *   problem much easier than it owuld have been with a vector.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    list<int> vals;  // The list of the last 25 values

    while(getline(input, inputVal)) {
        // For the first 25 values, just fill in the list:
        if(vals.size() < 25) {
            vals.push_back(stoi(inputVal));
        } // if
        // For the rest, determine the validity of the number:
        else {
            // Get number:
            int target = stoi(inputVal);
            // Create a sorted version of the current list:
            list<int> sortedVals(vals);
            sortedVals.sort();
            // Create variables and iterators:
            bool valid = false;
            auto frontVal = sortedVals.begin();
            auto backVal = sortedVals.rbegin();
            // Run the Day 1 solution:
            while(*frontVal != *backVal) {
                int sum = *frontVal + *backVal;
                if(sum == target) {
                    valid = true;
                    break;
                } // if(sum ==...)
                if(sum < target) {
                    frontVal++;
                } // if(sum <...)
                else {
                    backVal++;
                } // else
            } // while(frontVal...)
            // If this is the invalid number, print it and stop the program:
            if(!valid) {
                cout << target << endl;
                input.close();
                return 0;
            } // if(!valid)
            // Otherwise, update the list:
            vals.pop_front();
            vals.push_back(target);
        } // else
    } // while(getline)
    input.close();

    // None of the numbers were invalid:
    cout << "No invalid values found" << endl;
} // main()