#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Day 10: Adapter Array (https://adventofcode.com/2020/day/10)
 * Why exactly would you ever need over 100 adapters?
 * Part 1 is another problem made simple via sorting.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<int> adapts;  // The list of "adapters" (will include the wall and computer)
    adapts.push_back(0); // Add the wall to the list

    // Nothing fancy this time; just add the adpaters to the list:
    while(getline(input, inputVal)) {
        adapts.push_back(stoi(inputVal));
    } // while
    input.close();

    // Sort the list, then add the computer:
    sort(adapts.begin(), adapts.end());
    adapts.push_back(adapts.back() + 3);

    // Count the number of each difference separately:
    int diffCounts[3] = {0, 0, 0};
    for(int i = 1; i < adapts.size(); i++) {
        diffCounts[adapts[i] - adapts[i-1] - 1]++;
    } // for

    // Print the final product:
    cout << diffCounts[0] * diffCounts[2] << endl;
} // main()