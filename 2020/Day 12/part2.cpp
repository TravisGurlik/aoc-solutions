/*
 * Apparently turning is really, really hard.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int wayNorth  = 1,  // Waypoint North value
        wayEast   = 10, // Waypoint East value
        shipNorth = 0,  // Ship North value
        shipEast  = 0,  // Ship East value
        lineNum   = 0;  // Current line number (for debugging)

    while(getline(input, inputVal)) {
        ++lineNum;
        int count = stoi(inputVal.substr(1)); // The value to move/turn
        int temp = 0; // Storage for swapping coordinates
        switch(inputVal[0]) {
            case 'N':
                // North - move waypoint north:
                wayNorth += count;
                break;
            case 'S':
                // South - move waypoint south:
                wayNorth -= count;
                break;
            case 'E':
                // East - move waypoint east:
                wayEast += count;
                break;
            case 'W':
                // West - move waypoint west:
                wayEast -= count;
                break;
            case 'L':
                // Left - rotate waypoint left:
                // (Converts to a right turn and runs that instead)
                count = 360 - count;
            case 'R':
                // Right - rotate waypoint right:
                if(count == 180) {
                    // 180 degree turn = negate both values:
                    wayNorth = -wayNorth;
                    wayEast = -wayEast;
                } // if
                else {
                    // Any other turn requires values to be swapped:
                    temp = wayNorth;
                    wayNorth = (count == 270 ? 1 : -1) * wayEast;
                    wayEast = (count == 90 ? 1 : -1) * temp;
                } // else
                break;
            case 'F':
                // Forward - move ship to waypoint count times:
                for(int i = 0; i < count; ++i) {
                    shipNorth += wayNorth;
                    shipEast += wayEast;
                } // for
                break;
        } // switch(inputVal[0])
        cout << "Line #" << lineNum << ": Way North = " << wayNorth << "; Way East = " << wayEast << "; Ship North = " << shipNorth << "; Ship East = " << shipEast << endl;
    } // while
    input.close();

    // Print final MD to ship:
    cout << abs(shipNorth) + abs(shipEast) << endl;
}