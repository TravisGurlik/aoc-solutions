/*
 * In which I switch to a much more sensible container.
 * To be honest, I only did this as the most obvious fix to the issue of
 *   checking non-initialized tiles.
 * This uses a 2D vector where all accesses are modified to instead "index" from
 *   the center of the vector.
 * Indexes are the same as the keys from the previous Part.
 *   This leaves about half the matrix unused, which would be one way to make this
 *     a bit more efficient.
 *   I lucked out a little with this not affecting the answer; since none of the
 *     "fake" tiles are initially flipped, it's impossible for any of them to get flipped.
 * Funny story: as an exercise for my high school robotics team, I once programmed a game of
 *   Hexsweeper (Minesweeper with a hex grid). While I could have drawn on that for this,
 *   I was hopeful I could find a better way to do it.
 *   I don't know if I succeeded.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <utility>

using namespace std;

/**
 * Counts the number of trues in the given matrix
 * @param tiles The matrix to count values from
 * @return The count of trues in the matrix
 */
int getCount(const vector<vector<bool>>& tiles) {
    int output = 0;
    for(auto ia = tiles.begin(); ia != tiles.end(); ia++) {
        for(auto ib = ia->begin(); ib != ia->end(); ib++) {
            output += *ib;
        } // for(ib)
    } // for(ia)
    return output;
} // getCount()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<bool>> tiles(501, vector<bool>(501, false)); // The matrix of tiles
    int xVal,                                                  // The X value of the tile to change
        yVal;                                                  // The Y value of the tile to change
    const int MID = 250;                                       // The middle of the matrix, used for adjusting indexes
    const int ADJ[6][2] = {                                    // The moves needed to reach each adjacent hex, [xChange, yChange]
        {2, 0},
        {1, -1},
        {-1, -1},
        {-2, 0},
        {-1, 1},
        {1, 1}
    }; // ADJ

    // Reading input same as Part 1:
    while(getline(input, inputVal)) {
        xVal = 0;
        yVal = 0;
        inputVal.pop_back();

        for(int i = 0; i < inputVal.size(); i++) {
            if(inputVal[i] == 'n') {
                yVal++;
                i++;
                if(inputVal[i] == 'e') {
                    xVal++;
                }
                else {
                    xVal--;
                }
            }
            else if(inputVal[i] == 's') {
                yVal--;
                i++;
                if(inputVal[i] == 'e') {
                    xVal++;
                }
                else {
                    xVal--;
                }
            }
            else if(inputVal[i] == 'e') {
                xVal += 2;
            }
            else {
                xVal -= 2;
            }
        }
        // Updating values looks a little different:
        tiles[MID + xVal][MID + yVal] = !tiles[MID + xVal][MID + yVal];
    } // while
    input.close();

    // Do the hexagonal CA (B2/S12):
    int xBound = 37, // The minimum/maximum X value to check
        yBound = 19; // The minimum/maximum Y value to check
    // Run each iteration:
    for(int day = 0; day < 100; day++) {
        vector<vector<bool>> buffer(tiles); // This is CA, so we need a buffer
        // Iterate through each tile within the bounds:
        for(int x = -xBound; x <= xBound; x++) {
            for(int y = -yBound; y <= yBound; y++) {
                int neighbors = 0; // The number of black neighbor tiles
                // Iterate through each neighbor (via the ADJ array):
                for(int n = 0; n < 6; n++) {
                    neighbors += tiles[MID + x + ADJ[n][0]][MID + y + ADJ[n][1]];
                } // for(n)

                // Update tiles as needed:
                if(tiles[MID + x][MID + y]) {
                    // Tile is black:
                    if(neighbors == 0 || neighbors > 2) {
                        // Flip tile if needed:
                        buffer[MID + x][MID + y] = false;
                    } // if(neighbors...)
                } // if(tiles...)
                else {
                    // Tile is white:
                    if(neighbors == 2) {
                        buffer[MID + x][MID + y] = true;
                    } // if(neighbors...)
                } // else
            } // for(y)
        } // for(x)

        // Swap buffer into matrix and update values:
        tiles = buffer;
        xBound += 2;
        yBound++;
    } // for(day)

    //Print final solution:
    cout << getCount(tiles) << endl;
} // main()