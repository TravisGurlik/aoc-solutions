/*
 * This is basically the same as Part 1, with one minor addition.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <map>
#include <vector>

using namespace std;

/**
 * @brief Recursively finds paths through the cave network
 * 
 * @param rooms The list of rooms and connections
 * @param visited Which rooms have been visited already
 * @param next The room we're currently visiting
 * @param total The total number of paths found thus far
 * @param usedExtra Whether our extra room visit has been used
 */
void findPathsHelper(map<string, vector<string>>& rooms, map<string, bool> visited, string next, int& total, bool usedExtra) {
    visited[next] = true;
    for(auto i = rooms[next].begin(); i != rooms[next].end(); i++) {
        if(*i == "end") {
            total++;
        } // if
        else if(!visited[*i] || (i->at(0) >= 'A' && i->at(0) <= 'Z')) {
            findPathsHelper(rooms, visited, *i, total, usedExtra);
        } // else if
        // If we haven't used our extra visit (and the next room isn't start), use it:
        else if(!usedExtra && *i != "start") {
            findPathsHelper(rooms, visited, *i, total, true);
        } // else if
    } // for
} // findPathsHelper()

int findPaths(map<string, vector<string>>& rooms) {
    map<string, bool> visited;
    for(auto i = rooms.begin(); i != rooms.end(); i++) {
        visited[i->first] = 0;
    } // for
    visited["start"] = true;
    int total = 0;
    findPathsHelper(rooms, visited, "start", total, false);
    return total;
} // findPaths()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int split;
    string first,
           second;
    map<string, vector<string>> rooms;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        split = inputVal.find("-");
        first = inputVal.substr(0, split);
        second = inputVal.substr(split + 1);
        rooms[first].push_back(second);
        rooms[second].push_back(first);
    } // while
    input.close();

    //Print final solution:
    cout << findPaths(rooms) << endl;
} // main()