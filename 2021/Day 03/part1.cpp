/*
 * Day 03: Binary Diagnostic (https://adventofcode.com/2021/day/03)
 * [[DESCRIPTION OF PUZZLE AND SOLUTION]]
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int count = 0;
    int bits[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        ++count;
        for(int i = 0; i < inputVal.length(); ++i) {
            if(inputVal[i] == '1') {
                (bits[i])++;
            }
        }
    } // while
    input.close();

    string epsilon = "",
           gamma   = "";
    for(int n : bits) {
        if(n > count/2) {
            epsilon += "0";
            gamma += "1";
        }
        else {
            epsilon += "1";
            gamma += "0";
        }
    }

    //Print final solution:
    cout << "Gamma:   " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Product: " << stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2) << endl;
} // main()