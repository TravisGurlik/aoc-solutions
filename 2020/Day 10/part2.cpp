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
    vector<long> arranges(adapts.size(), 0);
    arranges[0] = 1;
    for(int i = 1; i < adapts.size(); i++) {
        for(int j = i-1; j > -1 && j > i - 4; j--) {
            if(adapts[j] < adapts[i] - 3) {
                break;
            }
            arranges[i] += arranges[j];
        }
    }
    cout << arranges.back() << endl;
}