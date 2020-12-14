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
    int row = 0, col = 0;
    vector<int> ids;
    while(getline(input, inputVal)) {
        string rowCode = inputVal.substr(0, 7);
        for(int i = 0; i < rowCode.length(); i++) {
            if(rowCode[i] == 'F') rowCode[i] = '0';
            else rowCode[i] = '1';
        }
        row = stoi(rowCode, 0, 2);
        string colCode = inputVal.substr(7);
        for(int i = 0; i < colCode.length() - 1; i++) {
            if(colCode[i] == 'L') colCode[i] = '0';
            else colCode[i] = '1';
        }
        col = stoi(colCode, 0, 2);
        ids.push_back(row * 8 + col);
    }
    input.close();
    sort(ids.begin(), ids.end());
    for(int i = 0; i < ids.size(); i++) {
        if(ids[i] != ids[0] + i) {
            cout << ids[i]-1 << endl;
            break;
        }
    }
}