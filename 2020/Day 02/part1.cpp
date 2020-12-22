/*
 * Day 2: Password Philosophy (https://adventofcode.com/2020/day/2)
 * Today was all about string manipulation.
 * I don't have much to say about this one; my solution is fairly straightforward.
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
    int valid = 0,   // Count of valid passwords
        min,         // Minimum number of allowed letter occurances
        max,         // Maximum number of allowed letter occurances
        dashLoc,     // Location of the dash within the line
        count;       // Current count of target letter occurances
    char target;     // The target letter
    string password; // The actual password

    while(getline(input, inputVal)) {
        // Reset variables and divide up the input line:
        count = 0;
        dashLoc = inputVal.find('-');
        min = stoi(inputVal.substr(0, dashLoc));
        max = stoi(inputVal.substr(dashLoc+1, inputVal.find(' ')-dashLoc));
        target = inputVal[inputVal.find(':')-1];
        password = inputVal.substr(inputVal.find(':')+2);

        // For each character in the password, check it against the target character:
        for(char c : password) {
            // If it matches, increment the count:
            if(c == target) {
                count++;
            } // if
        } // for
        // The password is valid if the final count is in the range [min, max]:
        if(count >= min && count <= max) {
            valid++;
        } // if
    } // while
    input.close();
    
    // Print the final total:
    cout << valid << endl;
} // main()