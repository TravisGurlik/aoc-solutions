#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    const long TARGET = 85848519;
    vector<long> vals;
    while(getline(input, inputVal)) {
        vals.push_back(stol(inputVal));
    }
    input.close();
    for(int i = 0; vals[i] != TARGET; ++i) {
        long sum = vals[i];
        int j = i + 1;
        for(; sum < TARGET; ++j) {
            sum += vals[j];
        }
        if(sum == TARGET) {
            vector<long> range(vals.begin() + i, vals.begin() + j);
            sort(range.begin(), range.end());
            cout << range.front() + range.back() << endl;
            return 0;
        }
    }
    cout << "No valid range found" << endl;
}