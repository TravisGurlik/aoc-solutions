#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>

using namespace std;

/**
 * Second verse, literally exactly the same as the first.
 * My initial solution was very slow; it was sped up by removing all the print statements and
 *   switching to an unordered_map.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables (same as Part 1):
    unordered_map<int, int> nums;
    int turn = 1,
        last = 0,
        next = 0;
    
    getline(input, inputVal);
    last = stoi(inputVal);
    while(getline(input, inputVal)) {
        next = stoi(inputVal);
        nums[last] = turn;
        last = next;
        turn++;
    } // while
    input.close();

    for(; turn < 30000000; turn++) {
        if(nums[last] == 0) {
            next = 0;
        } // if
        else {
            next = turn - nums[last];
        } // else
        nums[last] = turn;
        last = next;
    } // for

    cout << last << endl;
} // main()