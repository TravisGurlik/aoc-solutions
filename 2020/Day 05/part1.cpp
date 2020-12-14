#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Day 5: Binary Boarding (https://adventofcode.com/2020/day/5)
 * It's a set of binary searches. Not much else to add.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int maxID = 0, // The largest ID thus far
        row   = 0, // The current row
        col   = 0, // The current column
        id    = 0; // The current seat ID

    while(getline(input, inputVal)) {
        // Get and parse the row value:
        string rowCode = inputVal.substr(0, 7);
        for(int i = 0; i < rowCode.length(); i++) {
            if(rowCode[i] == 'F') rowCode[i] = '0';
            else rowCode[i] = '1';
        } // for
        row = stoi(rowCode, 0, 2);
        // Get and parse the column value:
        string colCode = inputVal.substr(7);
        for(int i = 0; i < colCode.length() - 1; i++) {
            if(colCode[i] == 'L') colCode[i] = '0';
            else colCode[i] = '1';
        } // for
        col = stoi(colCode, 0, 2);

        // Calculate ID & update max if needed:
        id = row * 8 + col;
        if(id > maxID) maxID = id;
    } // while
    input.close();

    // Print overall maximum:
    cout << maxID << endl;
} // main()