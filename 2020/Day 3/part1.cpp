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
    int currentIndex = 3, totalTrees = 0;
    getline(input, inputVal);
    while(getline(input, inputVal)) {
        if(inputVal[currentIndex] == '#') {
            totalTrees++;
        }
        currentIndex += 3;
        currentIndex %= inputVal.length() - 1;
    }
    cout << totalTrees << endl;
    input.close();
}