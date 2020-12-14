#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    vector<vector<char>> spaces;
    while(getline(input, inputVal)) {
        vector<char> row;
        for(char c : inputVal) {
            if(c == '.' || c == 'L' || c == '#') {
                row.push_back(c);
            }
        }
        spaces.push_back(row);
    }
    input.close();
    bool changed;
    do {
        changed = false;
        vector<vector<char>> newSpaces(spaces);
        for(int y = 0; y < spaces.size(); ++y) {
            for(int x = 0; x < spaces[y].size(); ++x) {
                if(spaces[y][x] == '.') continue;
                int adjacent = 0;
                for(int ya = y-1; ya <= y+1; ++ya) {
                    for(int xa = x-1; xa <= x+1; ++xa) {
                        if(ya >= 0 && ya < spaces.size()) {
                            if(xa >= 0 && xa < spaces[ya].size()) {
                                if(!(ya == y && xa == x)) {
                                    if(spaces[ya][xa] == '#') {
                                        adjacent++;
                                    }
                                }
                            }
                        }
                    }
                }
                if(spaces[y][x] == 'L') {
                    if(adjacent == 0) {
                        newSpaces[y][x] = '#';
                        changed = true;
                    }
                }
                else if(spaces[y][x] == '#') {
                    if(adjacent >= 4) {
                        newSpaces[y][x] = 'L';
                        changed = true;
                    }
                }
            }
        }
        spaces = newSpaces;
    } while(changed);
    int filled = 0;
    for(vector<char> v : spaces) {
        for(char c : v) {
            cout << c;
            if(c == '#') {
                filled++;
            }
        }
        cout << endl;
    }
    cout << endl << filled << endl;
}