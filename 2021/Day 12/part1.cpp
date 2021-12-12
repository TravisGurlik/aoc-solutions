/*
 * Day 12: Passage Pathing (https://adventofcode.com/2021/day/12)
 * This looked horrible, but honestly wasn't that bad.
 * C++'s optional passing by reference came in handy here.
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
 */
void findPathsHelper(map<string, vector<string>>& rooms, map<string, bool> visited, string next, int& total) {
    visited[next] = true; // Set this room as visited
    // For each connection from this room...
    for(auto i = rooms[next].begin(); i != rooms[next].end(); i++) {
        // If this room connects to end, we've found a new path:
        if(*i == "end") {
            total++;
        } // if
        // Otherwise, see if we can move to this next room:
        else if(!visited[*i] || (i->at(0) >= 'A' && i->at(0) <= 'Z')) {
            // If we can visit it, do so:
            findPathsHelper(rooms, visited, *i, total);
        } // else if
    } // for
} // findPathsHelper()

/**
 * @brief Finds the number of paths that go from start to end in the cave network
 * 
 * @param rooms The list of rooms and connections
 * @return int The number of viable paths
 */
int findPaths(map<string, vector<string>>& rooms) {
    map<string, bool> visited; // Which rooms have been vistied
    // Initialize the value for each room:
    for(auto i = rooms.begin(); i != rooms.end(); i++) {
        visited[i->first] = false;
    } // for
    // Recurse!
    int total = 0;
    findPathsHelper(rooms, visited, "start", total);
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
    int split;                          // Where to split the input string
    string first,                       // The first room
           second;                      // The second room
    map<string, vector<string>> rooms;  // The full list of rooms and conenctions
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        split = inputVal.find("-"); // Find split point
        // Get both rooms:
        first = inputVal.substr(0, split);
        second = inputVal.substr(split + 1);
        // Add connection to map:
        rooms[first].push_back(second);
        rooms[second].push_back(first);
    } // while
    input.close();

    //Print final solution:
    cout << findPaths(rooms) << endl;
} // main()