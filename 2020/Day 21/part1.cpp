/*
 * Day 21: Allergen Assessment (https://adventofcode.com/2020/day/21)
 * Today was a nice breatehr from the chaos of yesterday.
 * (Though my solution was still a bit of a mess).
 * Program flow: read dishes, identify which ingredients can have which allergens,
 *   find any ingredients not in these lists, count their occurances.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <list>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<pair<vector<string>, vector<string>>> dishes; // Dishes in the form of (ingredients, allergens)
    set<string> allIs;                                   // All listed ingredients
    unordered_map<string, list<string>> allergens;       // Maps allergens to possible ingredients
    unordered_map<string, vector<int>> hasA;             // Maps each allergen to the dishes it is in
    vector<string> is,                                   // Ingredients for the current dish
                   as;                                   // Allergens for the current dish
    string word;                                         // The current word
    int lineNum = 0;                                     // The current line number (or dish number)
    bool readIs;                                         // All ingredients read? (Reading allergens?)

    while(getline(input, inputVal)) {
        // Reading words from input means stringstreams:
        istringstream readIn(inputVal);
        readIs = false;

        // Read each word in the dish:
        while(readIn >> word) {
            // '(' only shows up at the start of the allergen list:
            if(word[0] == '(') {
                readIs = true;
                continue;
            } // if(...'(')
            // Read allergen:
            if(readIs) {
                word.pop_back(); // remove ',' & ')'
                as.push_back(word);
                allergens[word] = list<string>(0);
                hasA[word].push_back(lineNum);
            } // if(readIs)
            // Read ingredient:
            else {
                is.push_back(word);
                allIs.insert(word);
            } // else
        } // while(readIn...)

        // Update variables:
        dishes.push_back(make_pair(is, as));
        is.clear();
        as.clear();
        lineNum++;
    } // while
    input.close();

    // First dish - add all ingredients to list as possible allergen sources:
    for(auto i = hasA.begin(); i != hasA.end(); i++) {
        for(auto di = dishes[i->second[0]].first.begin(); di != dishes[i->second[0]].first.end(); di++) {
            allergens[i->first].push_back(*di);
        } // for(di)
    } // for(i)

    // Other dishes - if ingredient is not in every dish with an allergen, it cannot be that allergen's source:
    // (Loops allergens, dishes, and possible sources in that order)
    for(auto i = hasA.begin(); i != hasA.end(); i++) {
        for(auto ni = i->second.begin()+1; ni != i->second.end(); ni++) {
            // Since we're changing a list we're iterating over, we need ot use a buffer:
            list<string> newPos;
            for(auto ai = allergens[i->first].begin(); ai != allergens[i->first].end(); ai++) {
                if(count(dishes[*ni].first.begin(), dishes[*ni].first.end(), *ai) > 0) {
                    newPos.push_back(*ai);
                } // if
            } // for(ai)
            allergens[i->first] = newPos;
        } // for(ni)
    } // for(i)

    // Now that the lists only contain possible allergen sources, we can identify the other ingredients:
    vector<string> impossible; // The list of ingredients that cannot be allergen sources
    bool possible;             // Can this ingredient be an allergen source?
    for(auto i = allIs.begin(); i != allIs.end(); i++) {
        possible = false;
        for(auto ai = allergens.begin(); ai != allergens.end(); ai++) {
            if(count(ai->second.begin(), ai->second.end(), *i) > 0) {
                // If the ingredient is a posible source for any allergen, skip it:
                possible = true;
                break;
            } // if(count...)
        } // for(ai)

        // If the ingredient is not a possible source for any allergen, add it to the list:
        if(!possible) {
            impossible.push_back(*i);
        } // if(!possible)
    } // for(i)

    // Count how many times each impossible ingredient appears:
    int countI = 0;
    for(auto i = impossible.begin(); i != impossible.end(); i++) {
        for(auto di = dishes.begin(); di != dishes.end(); di++) {
            countI += count(di->first.begin(), di->first.end(), *i);
        } // for(di)
    } // for(i)

    //Print final solution:
    cout << countI << endl;
} // main()