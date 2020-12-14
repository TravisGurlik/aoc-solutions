#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    int leave;
    getline(input, inputVal);
    leave = stoi(inputVal);
    vector<int> departs;
    getline(input, inputVal);
    input.close();
    int lastIndex = -1,
        nextIndex = 0;
    nextIndex = inputVal.find(",");
    while(nextIndex != inputVal.npos) {
        cout << lastIndex << " -> " << nextIndex << " = ";
        string val = inputVal.substr(lastIndex+1, nextIndex - lastIndex - 1);
        cout << val << endl;
        if(val != "x") {
            departs.push_back(stoi(val));
        }
        lastIndex = nextIndex;
        nextIndex = inputVal.find(",", nextIndex+1);
    }

    cout << lastIndex << " -> " << nextIndex << " = ";
    string val = inputVal.substr(lastIndex+1);
    cout << val << endl;
    if(val != "x") {
        departs.push_back(stoi(val));
    }
    
    int minTime = (1 + (leave / departs[0])) * departs[0];
    int minI = 0;
    for(int i = 1; i < departs.size(); ++i) {
        int time = (1 + (leave / departs[i])) * departs[i];
        if(time < minTime) {
            minTime = time;
            minI = i;
        }
    }
    cout << "minI = " << minI << "; " << departs[minI] << " * (" << minTime << " - " << leave << ") = ";
    cout << (departs[minI] * (minTime - leave)) << endl;
}