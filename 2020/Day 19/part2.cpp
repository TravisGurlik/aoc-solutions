/*
 * It took a lot of work to figure out the best way to do this.
 * I didn't really want to try and figure out a way to actually check strings against
 *   a given rule, so I had to try and figure out how to account for arbitrary depth recursion.
 * In the end, I didn't; the only rules that loop happen to only appear in rule 0's children,
 *   meaning they could be checked manually and I could keep using a list of valid strings for
 *   all the other rules.
 * Most code is the same as Part 1, except for rules 8 and 11 being skipped in findValids
 *   and how the strings are checked against rule 0.
 * I didn't know if every possible substring that matched rule 42 would be used in a valid
 *   rule 0 string, so I played it safe and checked from the end of each substring.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

/**
 * Recursively finds all valid strings for a given rule (except 8 & 11)
 * @param ruleNum The ID of the rule to generate strings for
 * @param rules The map of rules
 * @param valids The map of valid strings for each rule
 */
void findValids(int ruleNum, unordered_map<int, vector<vector<int>>>& rules, unordered_map<int, set<string>>& valids) {
    if(valids.count(ruleNum) == 1) {
        return;
    } // if
    
    vector<vector<int>> rule = rules[ruleNum];
    for(auto i = rule.begin(); i != rule.end(); i++) {
        // Skip rules 8 and 11 to avoid worrying about looping:
        if(ruleNum == 8 || ruleNum == 11) {
            break;
        } // if

        vector<vector<string>> vals;
        for(auto ri = i->begin(); ri != i->end(); ri++) {
            findValids(*ri, rules, valids);

            vector<string> subvals;
            for(auto vi = valids[*ri].begin(); vi != valids[*ri].end(); vi++) {
                subvals.push_back(*vi);
            } // for(vi)
            vals.push_back(subvals);
        } // for(ri)

        for(int a = 0; a < vals[0].size(); a++) {
            if(vals.size() > 1) {
                for(int b = 0; b < vals[1].size(); b++) {
                    valids[ruleNum].insert(vals[0][a] + vals[1][b]);
                } // for(b)
            } // if
            else {
                valids[ruleNum].insert(vals[0][a]);
            } // else
        } // for(a)
    } // for(i)
} // findValids()

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
        ruleNum,
        matchCount = 0;
    bool messages = false;

    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            findValids(42, rules, valids);
            findValids(31, rules, valids);
            messages = true;
            continue;
        } // if(...1)
        if(!messages) {
            inputVal.pop_back();
            vector<int> subrules;

            indexA = inputVal.find(":");
            ruleNum = stoi(inputVal.substr(0, indexA));

            if(inputVal.find("\"") != inputVal.npos) {
                valids[ruleNum].insert(inputVal.substr(inputVal.find("\"") + 1, 1));
                continue;
            } // if(inputVal...)

            indexA += 2;
            while((indexB = inputVal.find(" ", indexA)) != inputVal.npos) {
                if(inputVal[indexA] == '|') {
                    rules[ruleNum].push_back(subrules);
                    subrules.clear();
                    indexA = indexB + 1;
                    continue;
                } // if(...'|')

                subrules.push_back(stoi(inputVal.substr(indexA, indexB - indexA)));
                
                indexA = indexB + 1;
            } // while(...npos)

            subrules.push_back(stoi(inputVal.substr(indexA)));
            rules[ruleNum].push_back(subrules);
        } // if(!messages)
        else {
            if(inputVal.back() == '\r') {
                inputVal.pop_back();
            } // if(...'\r')

            // Rule 0 is "88 11", rule 8 is "42 | 42 8", and rule 11 is "42 31 | 42 11 31"
            // So, using regex notation, rule 0 is 42{2,} 31{1,}
            // This was my a-ha moment, as I realized only rules 42 and 31 were really needed.
            // It's important to note that there must be at least one fewer substring for rule 31
            //   than for rule 42 for the string to be valid.

            vector<int> ends42(1, 0); // Stores the index of the end of each substring that matches rule 42
            // Find all continguous substrings starting from the start of the string that matches rule 42:
            for(int i = 1; i < inputVal.size() - 1; i++) {
                if(valids[42].count(inputVal.substr(ends42.back(), i - ends42.back())) == 1) {
                    ends42.push_back(i);
                } // if
            } // for(i)
            
            // From each ending, attempt to find a series of substrings matching rule 31:
            for(int last42I = ends42.size() / 2; last42I < ends42.size(); last42I++) {
                int count31 = 0,              // The number of substrings that match rule 31
                    last31 = ends42[last42I]; // The last index we ended a substring at

                // Use same method as above to find rule 31 substrings:
                for(int i = last31 + 1; i < inputVal.size() - 1; i++) {
                    if(valids[31].count(inputVal.substr(last31, i - last31)) == 1) {
                        last31 = i;
                        count31++;
                    } // if
                } // for(i)

                // If the remainder of the string (through the end) matches rule 31, ensure there's
                //   more rule 42 substrings than rule 31 substrings:
                if(count31 + 1 < last42I && valids[31].count(inputVal.substr(last31)) == 1) {
                    // If both are true, this string is valid:
                    matchCount++;
                    break;
                } // if
            } // for(last42I)
        } // else
    } // while
    input.close();

    //Print final solution:
    cout << matchCount << endl;
} // main()