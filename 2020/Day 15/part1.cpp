#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>

using namespace std;

/**
 * Day 15: Rambunctious Recitation (https://adventofcode.com/2020/day/15)
 * This one was pretty simple, but I struggled for a bit to order things properly.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    unordered_map<int, int> nums; // Maps each number to the last turn it was said
    int turn = 1,                 // Current turn
        last = 0,                 // Last number said
        next = 0;                 // Next number to say
    
    // Get the first number on its own so we can initialize last:
    getline(input, inputVal);
    last = stoi(inputVal);

    while(getline(input, inputVal)) {
        // Read each initial number and store in the map:
        next = stoi(inputVal);
        nums[last] = turn;
        last = next;
        turn++;
    } // while
    input.close();

    // Continue the game until we've reached the target turn:
    for(; turn < 2020; turn++) {
        if(nums[last] == 0) {
            // If the previous number had not been said before, the next number is 0:
            next = 0;
        } // if
        else {
            // Otherwise, calculate the time since the previous number was last said:
            next = turn - nums[last];
        } // else
        // Update values:
        nums[last] = turn;
        last = next;
    } // for

    // Print the final value:
    cout << last << endl;
} // main()