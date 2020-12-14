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
    int maxID = 0, row = 0, col = 0, id = 0;
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
        id = row * 8 + col;
        if(id > maxID) maxID = id;
    }
    cout << maxID << endl;
    input.close();
}