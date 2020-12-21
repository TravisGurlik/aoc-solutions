/*
 * This Part barely required any new code.
 * I ended up solving this by hand by just printing the allergens list from the last Part.
 * After the fact, I came back and added code to solve the problem automatically.
 * All code through line ### is the same as in Part 1.
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
#include <map>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<pair<vector<string>, vector<string>>> dishes;
    set<string> allIs;
    unordered_map<string, list<string>> allergens; // map allergen to possible ingredients
    unordered_map<string, vector<int>> hasA; // map allergens to dishes it is in
    vector<string> is, as;
    string word;
    int lineNum = 0;
    bool readIs;

    while(getline(input, inputVal)) {
        istringstream readIn(inputVal);
        readIs = false;
        while(readIn >> word) {
            if(word[0] == '(') {
                readIs = true;
                continue;
            } // if(...'(')
            if(readIs) {
                word.pop_back(); // remove ',' & ')'
                as.push_back(word);
                allergens[word] = list<string>(0);
                hasA[word].push_back(lineNum);
            } // if(readIs)
            else {
                is.push_back(word);
                allIs.insert(word);
            } // else
        } // while(readIn...)
        dishes.push_back(make_pair(is, as));
        is.clear();
        as.clear();
        lineNum++;
    } // while
    input.close();

    // First dish:
    for(auto i = hasA.begin(); i != hasA.end(); i++) {
        for(auto di = dishes[i->second[0]].first.begin(); di != dishes[i->second[0]].first.end(); di++) {
            allergens[i->first].push_back(*di);
        } // for(di)
    } // for(i)

    // Other dishes:
    for(auto i = hasA.begin(); i != hasA.end(); i++) {
        for(auto ni = i->second.begin()+1; ni != i->second.end(); ni++) {
            list<string> newPos;
            for(auto ai = allergens[i->first].begin(); ai != allergens[i->first].end(); ai++) {
                if(count(dishes[*ni].first.begin(), dishes[*ni].first.end(), *ai) > 0) {
                    newPos.push_back(*ai);
                } // if
            } // for(ai)
            allergens[i->first] = newPos;
        } // for(ni)
    } // for(i)

    // Figure out each allergen's source.
    // Find allergens with only one possible source, confirm them, then remove that source from the other lists.
    // Repeat until every allergen is confirmed.
    map<string, string> confirmedAs; // Maps allergens to their confirmed sources
    while(confirmedAs.size() < allergens.size()) {
        // Find confirmed sources:
        for(auto i = allergens.begin(); i != allergens.end(); i++) {
            if(i->second.size() == 1) {
                confirmedAs[i->first] = i->second.front();
            } // if
        } // for(i)
        // Removed confirmed sources from other lists:
        for(auto ai = allergens.begin(); ai != allergens.end(); ai++) {
            for(auto ci = confirmedAs.begin(); ci != confirmedAs.end(); ci++) {
                if(ci->first != ai->first) {
                    ai->second.remove(ci->second);
                } // if
            } // for(ci)
        } // for(ai)
    } // while

    // Determine output:
    // (Since maps store items alphabetically by key, we can just read the sources in order)
    string output = "";
    for(auto i = confirmedAs.begin(); i != confirmedAs.end(); i++) {
        output += i->second;
        output += ",";
    } // for
    output.pop_back();

    //Print final solution:
    cout << output << endl;
} // main()