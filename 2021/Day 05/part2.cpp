/*
 * This is basically the exact same as Part 1, but not ignoring diagonals.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

int sign(int n) {
    if(n < 0) return -1;
    if(n > 0) return 1;
    return 0;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<int>> vents(1000, vector<int>(1000, 0));
    int x1, x2, y1, y2,
        diffx, diffy;   // Directional differences
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        x1 = stoi(inputVal.substr(0, inputVal.find(",")));
        y1 = stoi(inputVal.substr(inputVal.find(",") + 1, inputVal.find(" ") - inputVal.find(",") - 1));
        x2 = stoi(inputVal.substr(inputVal.find_last_of(" ") + 1, inputVal.find_last_of(",") - inputVal.find_last_of(" ") - 1));
        y2 = stoi(inputVal.substr(inputVal.find_last_of(",") + 1));

        if(x1 == x2) {
            diffx = sign(y2 - y1);
            for(int n = y1; n != y2 + diffx; n += diffx) {
                vents[n][x1]++;
            }
        }
        else if(y1 == y2) {
            diffy = sign(x2 - x1);
            for(int n = x1; n != x2 + diffy; n += diffy) {
                vents[y1][n]++;
            }
        }
        // Diagonal line:
        else {
            diffx = sign(x2 - x1); // Get x direction
            diffy = sign(y2 - y1); // Get y direction
            // Update vents along the line:
            for(int x = x1, y = y1; x != x2 + diffx && y != y2 + diffy; x += diffx, y += diffy) {
                vents[y][x]++;
            } // for
        } // else
    } // while
    input.close();

    int overlaps = 0;
    for(int y = 0; y < 1000; y++) {
        for(int x = 0; x < 1000; x++) {
            //cout << vents[y][x];
            if(vents[y][x] > 1) {
                overlaps++;
            }
        }
        //cout << endl;
    }

    //Print final solution:
    cout << overlaps << endl;
} // main()