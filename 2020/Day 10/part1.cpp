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
    vector<int> adapts;
    adapts.push_back(0);
    while(getline(input, inputVal)) {
        adapts.push_back(stoi(inputVal));
    }
    input.close();
    sort(adapts.begin(), adapts.end());
    adapts.push_back(adapts.back() + 3);
    int diffCounts[3] = {0, 0, 0};
    for(int i = 1; i < adapts.size(); i++) {
        diffCounts[adapts[i] - adapts[i-1] - 1]++;
    }
    cout << diffCounts[0] * diffCounts[2] << endl;
}