/*
 * Day 19: Monster Messages (https://adventofcode.com/2020/day/19)
 * Does this count as a brute force solution? I think this might count as a brute force solution.
 * I decided to just go ahead and generate every valid string for every rule.
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
 * Recursively finds all valid strings for a given rule
 * @param ruleNum The ID of the rule to generate strings for
 * @param rules The map of rules
 * @param valids The map of valid strings for each rule
 */
void findValids(int ruleNum, unordered_map<int, vector<vector<int>>>& rules, unordered_map<int, set<string>>& valids) {
    // If we've already generated the strings for this rule, don't do it again:
    if(valids.count(ruleNum) == 1) {
        return;
    } // if

    vector<vector<int>> rule = rules[ruleNum]; // A copy of the rule to avoid excessive accessing
    // Iterate through each subrule (split by ORs):
    for(auto i = rule.begin(); i != rule.end(); i++) {
        vector<vector<string>> vals; // Stores the valid strings for each rule in this subrule
        // Iterate through each rule in this subrule:
        for(auto ri = i->begin(); ri != i->end(); ri++) {
            // Recursively get the valid strings for this rule:
            findValids(*ri, rules, valids);
            
            // Pull the strings out of the valids map:
            vector<string> subvals;
            for(auto vi = valids[*ri].begin(); vi != valids[*ri].end(); vi++) {
                subvals.push_back(*vi);
            } // for(vi)
            // Add all the strings to our subrule vector:
            vals.push_back(subvals);
        } // for(ri)

        // Iterate through the possibilities for the first rule:
        for(int a = 0; a < vals[0].size(); a++) {
            // If there's a second rule to check (my input never had more than 2 at once), do so:
            if(vals.size() > 1) {
                for(int b = 0; b < vals[1].size(); b++) {
                    // Add the combination of the two strings:
                    valids[ruleNum].insert(vals[0][a] + vals[1][b]);
                } // for(b)
            } // if
            else {
                // Add the string to this rule:
                valids[ruleNum].insert(vals[0][a]);
            } // else
        } // for(a)
    } // for(i)
} // findValids()

int main() {
    string inputVal;
    ifstream input;
    input.open("input1.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    unordered_map<int, vector<vector<int>>> rules;  // Stores all of the rules; maps rule number to sets of subrules
    unordered_map<int, set<string>> valids;         // Stores the valid strings for each rule
    int indexA,                                     // Starting index for rule parsing (I should have used a stringstream)
        indexB,                                     // Ending index for rule parsing
        ruleNum,                                    // Number of the current rule
        matchCount = 0;                             // Total number of lines that match rule 0
    bool messages = false;                          // Are we reading messages yet?

    while(getline(input, inputVal)) {
        // Blank line; we're done with rules:
        if(inputVal.length() == 1) {
            // Generate the valid strings for rule 0:
            findValids(0, rules, valids);
            messages = true;
            continue;
        } // if(...1)
        // Read rule:
        if(!messages) {
            inputVal.pop_back();
            vector<int> subrules; // Holds the rules for each subrule

            // Get rule number:
            indexA = inputVal.find(":");
            ruleNum = stoi(inputVal.substr(0, indexA));

            // Handle primitive rules:
            if(inputVal.find("\"") != inputVal.npos) {
                valids[ruleNum].insert(inputVal.substr(inputVal.find("\"") + 1, 1));
                continue;
            } // if(inputVal...)

            // Handle recursive rules:
            indexA += 2;
            // Loop until we run out of child rules:
            while((indexB = inputVal.find(" ", indexA)) != inputVal.npos) {
                // When hitting a divider, complete the subrule and start another:
                if(inputVal[indexA] == '|') {
                    rules[ruleNum].push_back(subrules);
                    subrules.clear();
                    indexA = indexB + 1;
                    continue;
                } // if(...'|')

                // Otherwise, add this rule to the list:
                subrules.push_back(stoi(inputVal.substr(indexA, indexB - indexA)));

                // Update starting index:
                indexA = indexB + 1;
            } // while(...npos)

            // Add the last child rule and subrule:
            subrules.push_back(stoi(inputVal.substr(indexA)));
            rules[ruleNum].push_back(subrules);
        } // if(!messages)
        // Read input string:
        else {
            // Remove the newline (when present):
            if(inputVal.back() == '\r') {
                inputVal.pop_back();
            } // if(...'\r')
            
            // Increment matchCount if this string is in the set of valid strings for rule 0:
            matchCount += valids[0].count(inputVal);
        } // else
    } // while
    input.close();

    //Print final solution:
    cout << matchCount << endl;
} // main()