#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    list<int> vals;
    int lineNum = 0;
    while(getline(input, inputVal)) {
        if(lineNum < 25) {
            vals.push_back(stoi(inputVal));
        }
        else {
            int target = stoi(inputVal);
            list<int> sortedVals(vals);
            sortedVals.sort();
            bool valid = false;
            auto frontVal = sortedVals.begin();
            auto backVal = sortedVals.rbegin();
            while(*frontVal != *backVal) {
                int sum = *frontVal + *backVal;
                if(sum == target) {
                    valid = true;
                    break;
                }
                if(sum < target) {
                    frontVal++;
                }
                else {
                    backVal++;
                }
            }
            if(!valid) {
                cout << target << endl;
                input.close();
                return 0;
            }
            vals.pop_front();
            vals.push_back(target);
        }
        lineNum++;
    }
    cout << "No invalid values found" << endl;
    input.close();
}