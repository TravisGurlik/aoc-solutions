/*
 * Wow, my part 1 solution was not efficient at all.
 * The main insight here is that we don't actually care about the order of the letters;
 *   all we really need are the pairs of letters that are present.
 * This allows us to avoid constructing the string, and just use numbers to abstract
 *   away from any massive containers we need to loop over (of any kind).
 * This also let me learn how awful constructing strings from multiple characters is.
 * So that was fun.
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
    unordered_map<string, long> pairs;                  // Maps pairs of consecutive letters -> # of occurances
    unordered_map<string, pair<string, string>> rules;  // Maps pairs of consecutive letters -> the new pairs after applying the rule

    // Get polymer template (as pairs):
    getline(input, inputVal);
    inputVal.pop_back();
    for(int i = 0; i < inputVal.length() - 1; i++) {
        pairs[inputVal.substr(i, 2)]++;
    } // for

    getline(input, inputVal); // Remove the empty line
    
    // Get rules:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Yes, this process of getting the output strings is awful.
        // I wish there was a better way.
        rules[inputVal.substr(0, 2)] = make_pair(
            string(1, inputVal[0]) + inputVal[6],
            string(1, inputVal[6]) + inputVal[1]
        );
    } // while
    input.close();

    // Perform polymerization:
    for(int iters = 0; iters < 40; iters++) {
        unordered_map<string, long> newPairs; // Buffer map
        // For each pair, add its outputs to the buffer:
        // (If you wanted to be robust, include a check for the rule
        //  before the addition, then add the existing pairs directly
        //  to the buffer if it doesn't exist)
        for(auto i = pairs.begin(); i != pairs.end(); i++) {
            newPairs[rules[i->first].first] += i->second;
            newPairs[rules[i->first].second] += i->second;
        } // for(i)
        pairs = newPairs; // Move buffer into main map
    } // for(iters)

    // Count them up:
    unordered_map<char, long> countsMap; // Maps letetrs -> # of occurances (in the pairs map)
    cout << "Pair counts:" << endl;
    for(auto i = pairs.begin(); i != pairs.end(); i++) {
        cout << "\t" << i->first << ": " << i->second << endl;
        countsMap[i->first.at(0)] += i->second;
        countsMap[i->first.at(1)] += i->second;
    } // for
    // Put the counts in something sortable:
    vector<long> counts;
    cout << "Final counts:" << endl;
    for(auto i = countsMap.begin(); i != countsMap.end(); i++) {
        cout << "\t" << i->first << ": " << i->second << endl;
        // We double counted all but the first and last letters above.
        // So we add half the values from above, and make sure to account for the first and last letters.
        // For robustness, check if there are no odd totals, and add one to the first character from the
        //   original string if so.
        counts.push_back(i->second / 2);
        if(i->second % 2 == 1) {
            counts.back()++;
        } // if
    } // for
    sort(counts.begin(), counts.end());

    // Print totals:
    cout << "Sorted values:" << endl;
    for(long n : counts) {
        cout << "\t" << n << endl;
    } // for

    //Print final solution:
    cout << counts.back() - counts[0] << endl;
} // main()