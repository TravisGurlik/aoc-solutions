/*
 * Day 15: Chiton (https://adventofcode.com/2021/day/15)
 * Ah, the innocence of part 1. Where everything looks fine and any method works.
 * This is basically Dijkstra's Algorithm, though not quite, since the "distances"
 *   are associated with leaving a node rather than following a path.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <limits>
#include <set>

using namespace std;

/**
 * @brief Calculates the minimum risk values for each space adjacent to the current one, then recurses on the unvisited space with the smallest risk.
 * 
 * @param risks The matrix of risks
 * @param minRisks The matrix of minimum risks to reach each location
 * @param visited The matrix of which cells have been visited
 * @param x The x coordinate of the space to calculate from
 * @param y The y coordinate of the space to calculate from
 * @param next The set of spaces to visit
 * @return int The minimum risk required to reach the bottom right corner of the risks matrix
 */
int getDistanceHelper(vector<vector<int>>& risks, vector<vector<int>>& minRisks, vector<vector<bool>>& visited, int x, int y, set<pair<int, int>>& next) {
    // Base case - when we are visiting the lower right, we are done:
    if(x == 99 && y == 99) {
        return minRisks[99][99];
    } // if

    // Otherwise, calculate:
    // For each unvisited adjacent space, if it would be "cheaper" to travel there through this
    //   space, update the value there and attempt to add it to the set of spaces to visit.
    visited[y][x] = true; // Mark this space as visited
    // Up:
    if(y > 0 && !visited[y-1][x]) {
        minRisks[y-1][x] = min(minRisks[y][x] + risks[y-1][x], minRisks[y-1][x]);
        next.insert(make_pair(x, y-1));
    } // if
    // Down:
    if(y < 99 && !visited[y+1][x]) {
        minRisks[y+1][x] = min(minRisks[y][x] + risks[y+1][x], minRisks[y+1][x]);
        next.insert(make_pair(x, y+1));
    } // if
    // Left:
    if(x > 0 && !visited[y][x-1]) {
        minRisks[y][x-1] = min(minRisks[y][x] + risks[y][x-1], minRisks[y][x-1]);
        next.insert(make_pair(x-1, y));
    } // if
    // Right:
    if(x < 99 && !visited[y][x+1]) {
        minRisks[y][x+1] = min(minRisks[y][x] + risks[y][x+1], minRisks[y][x+1]);
        next.insert(make_pair(x+1, y));
    } // if

    // Determine which space to visit next:
    pair<int, int> minLoc = *(next.begin()); // The minimum distance
    int minDist = minRisks[minLoc.second][minLoc.first];
    for(auto i = next.begin(); i != next.end(); i++) {
        if(minRisks[i->second][i->first] < minDist) {
            minLoc = *i;
            minDist = minRisks[i->second][i->first];
        } // if
    } // for
    next.erase(minLoc); // Remove the next space from the set
    return getDistanceHelper(risks, minRisks, visited, minLoc.first, minLoc.second, next); // Recurse
} // getDistanceHelper()

/**
 * @brief Calculate the minimum risk necessary to move from the upper left of a matrix to the lower right
 * 
 * @param risks The matrix of risk values
 * @return int The minimum risk to travel fromt he upper left of the matrix to the lower right
 */
int getPathDistance(vector<vector<int>>& risks) {
    vector<vector<int>> minRisks(risks.size(), vector<int>(risks[0].size(), numeric_limits<int>::max()));
    vector<vector<bool>> visited(risks.size(), vector<bool>(risks[0].size(), false));
    set<pair<int, int>> next;
    minRisks[0][0] = 0;
    return getDistanceHelper(risks, minRisks, visited, 0, 0, next);
} // getPathDistance()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<int>> risks; // The matrix of risk values
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Add each character as a digit to the risk matrix:
        vector<int> row;
        for(char c : inputVal) {
            row.push_back(c - '0');
        } // for
        risks.push_back(row);
    } // while
    input.close();

    //Print final solution:
    cout << getPathDistance(risks) << endl;
} // main()