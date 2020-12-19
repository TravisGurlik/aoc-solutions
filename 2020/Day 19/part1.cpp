#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <map>
#include <vector>
#include <set>

using namespace std;

/**
 * Day 19: [[DAY TITLE]] (https://adventofcode.com/2020/day/19)
 * [[DESCRIPTION OF PUZZLE AND SOLUTION]]
 */


void findValids(int ruleNum, map<int, vector<vector<int>>>& rules, map<int, set<string>>& valids) {
    if(valids.count(ruleNum) == 1) {
        return;
    }
    vector<vector<int>> rule = rules[ruleNum];
    for(auto i = rule.begin(); i != rule.end(); i++) {
        vector<vector<string>> vals;
        for(auto ri = i->begin(); ri != i->end(); ri++) {
            findValids(*ri, rules, valids);
            vector<string> subvals;
            for(auto vi = valids[*ri].begin(); vi != valids[*ri].end(); vi++) {
                subvals.push_back(*vi);
            }
            vals.push_back(subvals);
        }
        for(int a = 0; a < vals[0].size(); a++) {
            if(vals.size() > 1) {
                for(int b = 0; b < vals[1].size(); b++) {
                    valids[ruleNum].insert(vals[0][a] + vals[1][b]);
                }
            }
            else {
                valids[ruleNum].insert(vals[0][a]);
            }
        }
    }
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input1.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    map<int, vector<vector<int>>> rules;
    map<int, set<string>> valids;
    int indexA,
        indexB,
        valA,
        valB,
        ruleNum,
        matchCount = 0;
    bool messages = false;

    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            findValids(0, rules, valids);
            messages = true;
            continue;
        }
        if(!messages) {
            inputVal.pop_back();
            vector<int> subrules;
            indexA = inputVal.find(":");
            ruleNum = stoi(inputVal.substr(0, indexA));
            if(inputVal.find("\"") != inputVal.npos) {
                valids[ruleNum].insert(inputVal.substr(inputVal.find("\"") + 1, 1));
                continue;
            }
            indexA += 2;
            while((indexB = inputVal.find(" ", indexA)) != inputVal.npos) {
                if(inputVal[indexA] == '|') {
                    rules[ruleNum].push_back(subrules);
                    subrules.clear();
                    indexA = indexB + 1;
                    continue;
                }
                subrules.push_back(stoi(inputVal.substr(indexA, indexB - indexA)));
                indexA = indexB + 1;
            }
            subrules.push_back(stoi(inputVal.substr(indexA)));
            rules[ruleNum].push_back(subrules);
        }
        else {
            if(inputVal.back() == '\r') {
                inputVal.pop_back();
            }
            matchCount += valids[0].count(inputVal);
        }
    } // while
    input.close();

    //Print final solution:
    cout << matchCount << endl;
} // main()