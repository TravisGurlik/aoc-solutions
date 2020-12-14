#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<int> expenses;
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    while(getline(input, inputVal)) {
        expenses.push_back(stoi(inputVal));
    }
    input.close();

    sort(expenses.begin(), expenses.end());

    auto lowVal = expenses.begin();
    auto highVal = expenses.rbegin();
    while(*lowVal + *highVal != 2020 && *lowVal != *highVal) {
        if(*lowVal + *highVal > 2020) {
            highVal++;
        }
        else {
            lowVal++;
        }
    }
    if(*lowVal + *highVal == 2020) {
        cout << (*lowVal * *highVal) << endl;
    }
    else {
        cout << "No pair found" << endl;
    }
    return 0;
}