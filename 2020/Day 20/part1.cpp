/*
 * Day 20: Jurassic Jigsaw (https://adventofcode.com/2020/day/20)
 * Today is all about shortcuts and being too lazy to solve for the general case.
 * Actually putting the image together seemed like a lot of work, so I didn't.
 * I correctly assumed that each edge would match exactly one other edge (there are a
 *   lot of possible edges, so I felt this was safe).
 * This meant the corner tiles could be found by just looking for the ones that only
 *   had twwo valid neighbors.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <map>
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
    map<int, vector<vector<bool>>> tiles; // Maps tile ID to the edges of that tile
    vector<vector<bool>> tile;                      // Used for contructing tiles
    int lineNum = 0,                                // The current line number within the current tile
        tileID = 0;                                 // The ID of the current tile

    while(getline(input, inputVal)) {
        // Skip any empty lines:
        if(inputVal.length() == 1) {
            continue;
        } // if(...1)
        // Tile header:
        else if(inputVal[0] == 'T') {
            // Get (and save) the tile ID:
            tileID = stoi(inputVal.substr(inputVal.find(" ") + 1, 4));

            // Reset some variable to prepare for reading the tile:
            lineNum = 0;
            tile = vector<vector<bool>>(4, vector<bool>(10, false));
        } // else if(...'T')
        // Tile data:
        else {
            // Remove that pesky newline:
            inputVal.pop_back();

            // The first line is an edge, so we need to save it:
            if(lineNum == 0) {
                for(int i = 0; i < 10; i++) {
                    tile[0][i] = inputVal[i] == '#';
                } // for
            } // if(...0)
            // Same with the last line:
            else if(lineNum == 9) {
                for(int i = 0; i < 10; i++) {
                    tile[2][i] = inputVal[i] == '#';
                } // for
            } // else if(...9)

            // The first and last columns are both edges, so construct those as we go:
            tile[3][lineNum] = inputVal.front() == '#';
            tile[1][lineNum] = inputVal.back() == '#';

            // Increment our location in the tile:
            lineNum++;
            // Once the full tile has been read, save it to the tile map:
            if(lineNum == 10) {
                tiles[tileID] = tile;
            } // if(...10)
        } // else
    } // while
    input.close();

    // Now that we have our tiles, we can find which other tiles each tile is adjacent to.
    // We can use the number of matches for the edges of a given tile to determine where
    //   in the image the tile is.
    //   4 matches = center tile
    //   3 matches = edge tile
    //   2 matches = corner tile
    // This allow us to "easily" identify the corner tiles and determine the final product.

    // Placement variables:
    long product = 1;   // The product of the IDs of the corner tiles
    int numCorners = 0; // The number of corners found thus far
    // Check each tile:
    for(auto i = tiles.begin(); i != tiles.end(); i++) {
        int numMatches = 0; // The number of edges on this tile that matched another edge

        // Check each edge:
        for(auto si = i->second.begin(); si != i->second.end(); si++) {
            bool matchFound = false; // Used to short-circuit the loop once a match is found
            vector<bool> sr(*si);    // The reverse of the current edge (reversed on the next line)
            reverse(sr.begin(), sr.end());

            // Check every other tile:
            for(auto ci = tiles.begin(); ci != tiles.end(); ci++) {
                // Don't allow matching a tile to itself:
                if(ci != i) {
                    // Check each of this second tile's edges:
                    for(auto csi = ci->second.begin(); csi != ci->second.end(); csi++) {
                        // If the edges match (forward or backward), add another match to the count:
                        if(*si == *csi || sr == *csi) {
                            numMatches++;
                            matchFound = true;
                            break;
                        } // if(*si...)
                    } // for(csi)
                } // if(ci...)
                if(matchFound) {
                    break;
                } // if(matchFound)
            } // for(ci)
        } // for(si)

        // If only two edges matched, this is an edge tile; update the product:
        if(numMatches == 2) {
            numCorners++;
            product *= i->first;
            // Once 4 edges have been found, we can stop looking for more:
            if(numCorners == 4) {
                break;
            } // if(numCorners...)
        } // if(numMatches...)
    } // for(i)

    //Print final solution:
    cout << product << endl;
} // main()