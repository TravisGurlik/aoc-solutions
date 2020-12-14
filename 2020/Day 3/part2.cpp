#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    int currentIndex[] = {1, 3, 5, 7, 1}, totalTrees[] = {0, 0, 0, 0, 0};
    int lineNum = 1;
    getline(input, inputVal);
    while(getline(input, inputVal)) {
        for(int i = 0; i < 4; i++) {
            if(inputVal[currentIndex[i]] == '#') {
                totalTrees[i]++;
            }
            currentIndex[i] += (i*2 + 1);
            currentIndex[i] %= inputVal.length() - 1;
        }
        if(lineNum % 2 == 0) {
            if(inputVal[currentIndex[4]] == '#') {
                totalTrees[4]++;
            }
            currentIndex[4]++;
            currentIndex[4] %= inputVal.length() - 1;
        }
        lineNum++;
    }
    int total = 1;
    for(int n : totalTrees) {
        cout << n << endl;
        total *= n;
    }
    cout << total << endl;
    input.close();
}