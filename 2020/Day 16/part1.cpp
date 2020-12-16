#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <utility>

using namespace std;

/**
 * Day 16: [[DAY TITLE]] (https://adventofcode.com/2020/day/16)
 * [[DESCRIPTION OF PUZZLE AND SOLUTION]]
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    vector<vector<pair<int, int>>> fields;
    vector<pair<int, int>> fieldVals;
    int errorRate = 0,
        inputArea = 0,
        indexS,
        indexE,
        valA,
        valB;
    bool valid;

    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            inputArea++;
            continue;
        }
        switch(inputArea) {
            case 0:
                // Fields and valid ranges
                indexS = inputVal.find(":") + 2;
                indexE = inputVal.find("-");
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                indexE = inputVal.find(" ", indexS);
                valB = stoi(inputVal.substr(indexS, indexE - indexS));
                fieldVals.push_back(make_pair(valA, valB));
                indexS = inputVal.find(" ", indexE + 1) + 1;
                indexE = inputVal.find("-", indexS);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                valB = stoi(inputVal.substr(indexS));
                fieldVals.push_back(make_pair(valA, valB));
                fields.push_back(fieldVals);
                fieldVals.clear();
                break;
            case 1:
                break;
            case 2:
                if(inputVal[0] == 'n') {
                    break;
                }
                indexS = 0;
                indexE = inputVal.find(",");
                while(indexE != inputVal.npos) {
                    valA = stoi(inputVal.substr(indexS, indexE - indexS));
                    valid = false;
                    for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                        for(auto ri = fi->begin(); ri != fi->end() && !valid; ri++) {
                            valid = valA >= ri->first && valA <= ri->second;
                        }
                    }
                    if(!valid) {
                        errorRate += valA;
                    }
                    indexS = indexE + 1;
                    indexE = inputVal.find(",", indexS);
                }
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                valid = false;
                for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                    for(auto ri = fi->begin(); ri != fi->end() && !valid; ri++) {
                        valid = valA >= ri->first && valA <= ri->second;
                    }
                }
                if(!valid) {
                    errorRate += valA;
                }
                break;
        }
    } // while
    input.close();

    //Print final solution:
    cout << errorRate << endl;
} // main()