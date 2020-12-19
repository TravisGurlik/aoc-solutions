#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

/**
 * [[DESCRIPTION OF PUZZLE AND SOLUTION]]
 */


void findValids(int ruleNum, unordered_map<int, vector<vector<int>>>& rules, unordered_map<int, set<string>>& valids) {
    if(valids.count(ruleNum) == 1) {
        return;
    }
    vector<vector<int>> rule = rules[ruleNum];
    for(auto i = rule.begin(); i != rule.end(); i++) {
        if(ruleNum == 8 || ruleNum == 11) {
            break;
        }
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
    input.open("input2.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    unordered_map<int, vector<vector<int>>> rules;
    unordered_map<int, set<string>> valids;
    int indexA,
        indexB,
        valA,
        valB,
        ruleNum,
        matchCount = 0;
    bool messages = false;

    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            findValids(42, rules, valids);
            findValids(31, rules, valids);
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
            vector<int> ends42(1, 0);
            for(int i = 1; i < inputVal.size() - 1; i++) {
                if(valids[42].count(inputVal.substr(ends42.back(), i - ends42.back())) == 1) {
                    ends42.push_back(i);
                }
            }
            for(int last42I = ends42.size() / 2; last42I < ends42.size(); last42I++) {
                int count31 = 0;
                int last31 = ends42[last42I];
                for(int i = last31 + 1; i < inputVal.size() - 1; i++) {
                    if(valids[31].count(inputVal.substr(last31, i - last31)) == 1) {
                        last31 = i;
                        count31++;
                    }
                }
                if(count31 + 1 < last42I && valids[31].count(inputVal.substr(last31)) == 1) {
                    matchCount++;
                    break;
                }
            }
        }
    } // while
    input.close();

    //Print final solution:
    cout << matchCount << endl;
} // main()