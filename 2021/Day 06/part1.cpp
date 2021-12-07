/*
 * Day 06: Lanternfish (https://adventofcode.com/2021/day/06)
 * A straightforward day, as long as you think to account for efficiency.
 * Instead of trying to store all the fish individually, take advantage of
 *   the fact that there are only 9 possible states by storing the number
 *   of fish in each state.
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
    vector<int> fish(9, 0); // The number of fish in each state
    
    // Input loop:
    while(getline(input, inputVal)) {
        fish[stoi(inputVal)]++; // Add the fish to the databank
    } // while
    input.close();

    // Simulate each day:
    for(int days = 0; days < 80; days++) {
        vector<int> buffer(9, 0); // Buffer modifying while reading
        // For each state, shift the timer down one:
        for(int i = 8; i > 0; i--) {
            buffer[i-1] = fish[i];
        } // for(i)
        // For fish at 0, add the same number to day 8, then add them to day 6:
        buffer[8] = fish[0];
        buffer[6] += fish[0];
        // Move the buffer into the main database:
        fish = buffer;
    } // for(days)

    // Count the number of fish at the end:
    int sum = 0;
    for(int n : fish) {
        sum += n;
    } // for(n)

    //Print final solution:
    cout << sum << endl;
} // main()