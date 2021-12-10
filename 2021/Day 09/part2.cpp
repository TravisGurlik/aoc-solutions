/*
 * This part looked kinda of intimidating, but wasn't that bad with some smart recursion.
 * A good instance of spending memory to save time.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Recursively expands a pre-existing basin to its edges
 * 
 * @param heights The matrix of heights
 * @param x The x value to check from
 * @param y The y value to check from
 * @param inBasin The positions that have already been added to this basin
 * @param basinSize The total size of this basin (passed by reference)
 */
void findBasinHelper(vector<vector<int>>& heights, int x, int y, vector<vector<bool>>& inBasin, int& basinSize) {
    // Up:
    if((y > 0 && !inBasin[y-1][x]) && heights[y-1][x] != 9) {
        inBasin[y-1][x] = true;
        basinSize++;
        findBasinHelper(heights, x, y-1, inBasin, basinSize);
    } // if
    // Down:
    if((y < heights.size() - 1 && !inBasin[y+1][x]) && heights[y+1][x] != 9) {
        inBasin[y+1][x] = true;
        basinSize++;
        findBasinHelper(heights, x, y+1, inBasin, basinSize);
    } // if
    // Left:
    if((x > 0 && !inBasin[y][x-1]) && heights[y][x-1] != 9) {
        inBasin[y][x-1] = true;
        basinSize++;
        findBasinHelper(heights, x-1, y, inBasin, basinSize);
    } // if
    // Right:
    if((x < heights[0].size() - 1 && !inBasin[y][x+1]) && heights[y][x+1] != 9) {
        inBasin[y][x+1] = true;
        basinSize++;
        findBasinHelper(heights, x+1, y, inBasin, basinSize);
    } // if
} // findBasinHelper()

/**
 * @brief Determines the size of a basin containing the given point
 * 
 * @param heights The matrix of heights
 * @param x The starting x value
 * @param y The starting y value
 * @return int The size of the basin
 */
int findBasin(vector<vector<int>>& heights, int x, int y) {
    vector<vector<bool>> inBasin(heights.size(), vector<bool>(heights[0].size(), false)); // Stores which positions were already added to the basin
    // Add the starting position to the basin:
    inBasin[y][x] = true;
    int basinSize = 1;
    findBasinHelper(heights, x, y, inBasin, basinSize); // Recursively find the size of the basin
    return basinSize;
} // findBasin()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<int>> heights;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vector<int> row;
        for(char c : inputVal) {
            row.push_back(c - '0');
        } // for
        heights.push_back(row);
    } // while
    input.close();

    // Find low points, and add them to the list:
    vector<pair<int, int>> lowPoints;
    for(int y = 0; y < heights.size(); y++) {
        for(int x = 0; x < heights[y].size(); x++) {
            if((y == 0 || heights[y][x] < heights[y-1][x]) &&
                    (y == heights.size() - 1 || heights[y][x] < heights[y+1][x]) &&
                    (x == 0 || heights[y][x] < heights[y][x-1]) &&
                    (x == heights[y].size() - 1 || heights[y][x] < heights[y][x+1])) {
                lowPoints.push_back(make_pair(x, y));
            } // if
        } // for(x)
    } // for(y)

    // Determing the size of each basin:
    vector<int> basinSizes; // All the basin sizes
    for(auto i : lowPoints) {
        basinSizes.push_back(findBasin(heights, i.first, i.second));
    } // for

    // Get the three largest basins and multiply their sizes together:
    sort(basinSizes.begin(), basinSizes.end());
    int product = basinSizes.back();
    basinSizes.pop_back();
    product *= basinSizes.back();
    basinSizes.pop_back();
    product *= basinSizes.back();

    //Print final solution:
    cout << product << endl;
} // main()