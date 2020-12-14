#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <set>

using namespace std;

/**
 * Day 6: Custom Customs (https://adventofcode.com/2020/day/6)
 * More mulit-line input, and more string manipulation.
 * Part 1 was just a matter of adding each question to a set and returning its size
 *   (as the set enforces uniqueness)
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    set<char> yeses; // The set of questions anyone in the group has answered "yes" to
    int sum = 0;     // The total number of questions someone answered "yes" to in each group

    while(getline(input, inputVal)) {
        // Multi-line input again; check for more data:
        if(inputVal.length() == 1) {
            // Our result for each group is just the length of the set (minus the newline):
            sum += yeses.size() - 1;
            // Clear the set for the next group:
            yeses.clear();
        } // if
        else {
            // Add each question to the set:
            for(char c : inputVal) {
                yeses.insert(c);
            } // for
        } // else
    } // while
    input.close();

    // Add result of last group:
    sum += yeses.size() - 1;

    // Print final total:
    cout << sum << endl;
}