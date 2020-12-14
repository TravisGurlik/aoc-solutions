#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <vector>
#include <algorithm>

using namespace std;

/**
 * This is basically the same as the last part, but with a "find the missing element" bonus.
 * I opted for the sort and iterate solution
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int row = 0,     // The current row
        col = 0;     // The current column
    vector<int> ids; // The list of filled seats

    while(getline(input, inputVal)) {
        // Once again, calculate the seat ID from the row and column encoding and add it to the list:
        string rowCode = inputVal.substr(0, 7);
        for(int i = 0; i < rowCode.length(); i++) {
            if(rowCode[i] == 'F') rowCode[i] = '0';
            else rowCode[i] = '1';
        }
        row = stoi(rowCode, 0, 2);
        string colCode = inputVal.substr(7);
        for(int i = 0; i < colCode.length() - 1; i++) {
            if(colCode[i] == 'L') colCode[i] = '0';
            else colCode[i] = '1';
        }
        col = stoi(colCode, 0, 2);
        ids.push_back(row * 8 + col);
    } // while
    input.close();

    // Sort the seat vector:
    sort(ids.begin(), ids.end());
    // Iterate through the seats until finding the one that breaks the pattern:
    for(int i = 0; i < ids.size(); i++) {
        if(ids[i] != ids[0] + i) {
            // The previous seat to the current one is empty:
            cout << ids[i]-1 << endl;
            break;
        } // if
    } // for
} // main()