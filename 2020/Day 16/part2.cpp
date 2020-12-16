#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <list>
#include <vector>
#include <map>
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
    map<string, pair<int, int>[2]> fields;
    vector<vector<int>> validTickets;
    vector<int> ticket,
                myTicket;
    int inputArea = 0,
        indexS,
        indexE,
        valA,
        valB;
    bool valid;
    string fieldName;

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
                fieldName = inputVal.substr(0, indexS - 2);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                indexE = inputVal.find(" ", indexS);
                valB = stoi(inputVal.substr(indexS, indexE - indexS));
                fields[fieldName][0] = make_pair(valA, valB);
                indexS = inputVal.find(" ", indexE + 1) + 1;
                indexE = inputVal.find("-", indexS);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                valB = stoi(inputVal.substr(indexS));
                fields[fieldName][1] = make_pair(valA, valB);
                break;
            case 1:
                if(inputVal[0] != 'y') {
                    indexS = 0;
                    indexE = inputVal.find(",");
                    while(indexE != inputVal.npos) {
                        myTicket.push_back(stoi(inputVal.substr(indexS, indexE - indexS)));
                        indexS = indexE + 1;
                        indexE = inputVal.find(",", indexS);
                    }
                    myTicket.push_back(stoi(inputVal.substr(indexS, indexE - indexS)));
                }
                break;
            case 2:
                if(inputVal[0] == 'n') {
                    break;
                }
                ticket.clear();
                indexS = 0;
                indexE = inputVal.find(",");
                while(indexE != inputVal.npos) {
                    valA = stoi(inputVal.substr(indexS, indexE - indexS));
                    valid = false;
                    for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                        valid = (valA >= fi->second[0].first && valA <= fi->second[0].second)
                                || (valA >= fi->second[1].first && valA <= fi->second[1].second);
                    }
                    if(!valid) {
                        break;
                    }
                    ticket.push_back(valA);
                    indexS = indexE + 1;
                    indexE = inputVal.find(",", indexS);
                }
                if(!valid) {
                    continue;
                }
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                valid = false;
                for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                    valid = (valA >= fi->second[0].first && valA <= fi->second[0].second)
                            || (valA >= fi->second[1].first && valA <= fi->second[1].second);
                }
                if(valid) {
                    ticket.push_back(valA);
                    validTickets.push_back(ticket);
                }
                break;
        }
    } // while
    input.close();

    int target = fields.size(),
        orderedFields = 0;
    vector<string> fieldOrder(target, "");
    while(orderedFields < target) {
        for(int vi = 0; vi < validTickets[0].size(); vi++) {
            if(fieldOrder[vi] != "") {
                continue;
            }
            map<string, bool> posssibleFields;
            int fieldsLeft = fields.size();
            for(int ti = 0; ti < validTickets.size(); ti++) {
                for(auto fi = fields.begin(); fi != fields.end(); fi++) {
                    if(!((validTickets[ti][vi] >= fi->second[0].first && validTickets[ti][vi] <= fi->second[0].second)
                            || (validTickets[ti][vi] >= fi->second[1].first && validTickets[ti][vi] <= fi->second[1].second))) {
                        posssibleFields[fi->first] = false;
                        fieldsLeft--;
                    }
                    else if(posssibleFields.count(fi->first) == 0) {
                        posssibleFields[fi->first] = true;
                    }
                    if(fieldsLeft == 1) {
                        break;
                    }
                }
                if(fieldsLeft == 1) {
                    break;
                }
            }
            if(fieldsLeft != 1) {
                continue;
            }
            for(auto fi = fields.begin(); fi != fields.end(); fi++) {
                if(posssibleFields[fi->first]) {
                    fieldOrder[vi] = fi->first;
                    orderedFields++;
                    fields.erase(fi);
                    break;
                }
            }
            if(orderedFields == target) {
                break;
            }
        }
    }

    long result = 1;
    int destCount = 0;
    for(int i = 0; i < fieldOrder.size(); i++) {
        if(fieldOrder[i].substr(0, 9) == "departure") {
            result *= myTicket[i];
            destCount++;
            if(destCount == 6) {
                break;
            }
        }
    }

    //Print final solution:
    cout << result << endl;
} // main()