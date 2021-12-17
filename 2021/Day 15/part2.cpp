/*
 * I don't think I've ever gotten tail recursion to work as advertised.
 * This is basically the same logic as part 1, but not recursive.
 * The tiling logic was surprisingly weird.
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
 * @brief Calculate the minimum risk required to travel to the lower right of the risk matrix from the upper left
 * 
 * @param risks The matrix of risks to move through the cave
 * @return int The minimum risk required to travel to the lower right of the risk matrix from the upper left
 */
int getPathDistance(vector<vector<int>>& risks) {
    vector<vector<int>> minRisks(risks.size(), vector<int>(risks[0].size(), numeric_limits<int>::max()));
    vector<vector<bool>> visited(risks.size(), vector<bool>(risks[0].size(), false));
    set<int> next;
    minRisks[0][0] = 0;
    int x = 0,
        y = 0;
    while(x != risks[y].size() - 1 || y != risks.size() - 1) {
        visited[y][x] = true;
        if(y > 0 && !visited[y-1][x]) {
            minRisks[y-1][x] = min(minRisks[y][x] + risks[y-1][x], minRisks[y-1][x]);
            next.insert((y-1)*(risks[y-1].size())+x);
        }
        if(y < risks.size() - 1 && !visited[y+1][x]) {
            minRisks[y+1][x] = min(minRisks[y][x] + risks[y+1][x], minRisks[y+1][x]);
            next.insert((y+1)*(risks[y+1].size())+x);
        }
        if(x > 0 && !visited[y][x-1]) {
            minRisks[y][x-1] = min(minRisks[y][x] + risks[y][x-1], minRisks[y][x-1]);
            next.insert(y*(risks[y].size())+x-1);
        }
        if(x < risks[y].size() - 1 && !visited[y][x+1]) {
            minRisks[y][x+1] = min(minRisks[y][x] + risks[y][x+1], minRisks[y][x+1]);
            next.insert(y*(risks[y].size())+x+1);
        }

        int minPos = *(next.begin()),
            minDist = numeric_limits<int>::max();
        for(auto i = next.begin(); i != next.end(); i++) {
            int ya = *i / (risks[0].size()),
                xa = *i % (risks.size());
            if(minRisks[ya][xa] < minDist) {
                minPos = *i;
                minDist = minRisks[ya][xa];
            }
        }
        next.erase(minPos);
        x = minPos % (risks.size());
        y = minPos / (risks[0].size());
    }
    return minRisks.back().back();
} // getPathDistance()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<int>> oldRisks;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vector<int> row;
        for(char c : inputVal) {
            row.push_back(c - '0');
        }
        oldRisks.push_back(row);
    } // while
    input.close();

    // Tiling logic:
    // Start with horizontal tiling, then do the rest vertically.
    // Both loop by row, then column, then tile, determining the values for each tile from the last.
    vector<vector<int>> newRisks(oldRisks.size() * 5, vector<int>(oldRisks[0].size() * 5, -1));
    for(int y = 0; y < oldRisks.size(); y++) {
        for(int x = 0; x < oldRisks[y].size(); x++) {
            for(int xd = 0; xd < 5; xd++) {
                newRisks[y][x + xd * oldRisks[0].size()] = (oldRisks[y][x] + xd - 1) % 9 + 1;
            } // for(xd)
        } // for(x)
    } // for(y)
    for(int y = 0; y < oldRisks.size(); y++) {
        for(int x = 0; x < newRisks[y].size(); x++) {
            for(int yd = 0; yd < 5; yd++) {
                newRisks[y + yd * oldRisks.size()][x] = (newRisks[y][x] + yd - 1) % 9 + 1;
            } // for(yd)
        } // for(x)
    } // for(y)

    //Print final solution:
    cout << getPathDistance(newRisks) << endl;
} // main()