/*
 * [[DESCRIPTION OF PUZZLE AND SOLUTION]]
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
    
    vector<string> values;
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        values.push_back(inputVal);
    } // while
    input.close();

    vector<string> buffer;
    int digit = 0;
    vector<string> oxygen(values);
    while(oxygen.size() > 1) {
        int count = 0;
        for(string s : oxygen) {
            if(s[digit] == '1') {
                count++;
            }
            else {
                count--;
            }
        }
        char target = count >= 0 ? '1' : '0';
        buffer.clear();
        for(string s : oxygen) {
            if(s[digit] == target) {
                buffer.push_back(s);
            }
        }
        oxygen = buffer;
        ++digit;
    }

    digit = 0;
    vector<string> co2(values);
    while(co2.size() > 1) {
        int count = 0;
        for(string s : co2) {
            if(s[digit] == '1') {
                count++;
            }
            else {
                count--;
            }
        }
        char target = count < 0 ? '1' : '0';
        buffer.clear();
        for(string s : co2) {
            if(s[digit] == target) {
                buffer.push_back(s);
            }
        }
        co2 = buffer;
        ++digit;
    }

    //Print final solution:
    cout << "Oxygen:  " << oxygen[0] << endl;
    cout << "CO2:     " << co2[0] << endl;
    cout << "Product: " << stoi(oxygen[0], nullptr, 2) * stoi(co2[0], nullptr, 2) << endl;
} // main()