/*
 * Day 14: Extended Polymerization (https://adventofcode.com/2021/day/14)
 * This really wasn't that bad.
 * Using a double map made it easy to store and look up pair rules.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    string polymer;                                         // The polymer
    unordered_map<char, unordered_map<char, char>> rules;   // Maps first character -> second character -> insertion

    // Get polymer template:
    getline(input, inputVal);
    inputVal.pop_back();
    polymer = inputVal;

    getline(input, inputVal); // Get rid of the blank line
    
    // Get rules:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        rules[inputVal[0]][inputVal[1]] = inputVal[6]; // Add the new rule
    } // while
    input.close();

    // Perform polymerization:
    for(int iters = 0; iters < 10; iters++) {
        string newPolymer; // Buffer string to store new polymer in
        // For each pair, add the first character and any insertion to the buffer:
        for(int i = 0; i < polymer.length() - 1; i++) {
            newPolymer += polymer[i];
            if(rules.count(polymer[i]) > 0 && rules[polymer[i]].count(polymer[i+1]) > 0) {
                newPolymer += rules[polymer[i]][polymer[i+1]];
            } // if
        } // for(i)
        newPolymer += polymer[polymer.length() - 1]; // Add the last character
        polymer = newPolymer; // Move buffer into main string
    } // for(iters)

    // Count how many times each letter appears:
    unordered_map<char, int> countsMap; // Maps letter -> # of occurances
    for(char c : polymer) {
        countsMap[c]++;
    } // for
    // Get the counts in something we can sort:
    vector<int> counts;
    cout << "Final counts:" << endl;
    for(auto i = countsMap.begin(); i != countsMap.end(); i++) {
        cout << "\t" << i->first << ": " << i->second << endl;
        counts.push_back(i->second);
    } // for
    sort(counts.begin(), counts.end()); // Sort the counts

    //Print final solution (last value minus the first):
    cout << counts.back() - counts[0] << endl;
} // main()