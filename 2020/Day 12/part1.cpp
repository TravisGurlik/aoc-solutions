#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Day 12: Rain Risk (https://adventofcode.com/2020/day/12)
 * This seems like a poor way to navigate a boat (you could at least be consistent with it),
 *   but I suppose if your boat can move sideways without turning its a bit necessary.
 * Anyways, welcome to "switch statement, the program."
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int north  = 0, // North/South position (+ = N, - = S)
        east   = 0, // East/West position (+ = E, - = W)
        facing = 1; // Direction the boat is facing (0123 = NESW)

    while(getline(input, inputVal)) {
        // Do different things depending on the exact instruction:
        switch(inputVal[0]) {
            case 'N':
                // North - go north:
                north += stoi(inputVal.substr(1));
                break;
            case 'S':
                // South - go south:
                north -= stoi(inputVal.substr(1));
                break;
            case 'E':
                // East - go east:
                east += stoi(inputVal.substr(1));
                break;
            case 'W':
                // West - go west:
                east -= stoi(inputVal.substr(1));
                break;
            case 'L':
                // Left - turn left (decrement facing):
                facing -= stoi(inputVal.substr(1)) / 90;
                facing %= 4;
                facing = facing < 0 ? 4 + facing : facing;
                break;
            case 'R':
                // Right - turn right (increment facing):
                facing += stoi(inputVal.substr(1)) / 90;
                facing %= 4;
                facing = facing < 0 ? 4 + facing : facing;
                break;
            case 'F':
                // Forward - move in direction boat is facing:
                switch(facing) {
                    case 0:
                        // 0 = North:
                        north += stoi(inputVal.substr(1));
                        break;
                    case 2:
                        // 2 = South:
                        north -= stoi(inputVal.substr(1));
                        break;
                    case 1:
                        // 1 = East:
                        east += stoi(inputVal.substr(1));
                        break;
                    case 3:
                        // 3 = West:
                        east -= stoi(inputVal.substr(1));
                        break;
                } // switch(facing)
                break;
        } // switch(inputVal[0])
        cout << "North = " << north << "; East = " << east << "; Facing = " << facing << endl;
    } // while
    input.close();

    // Print MD to final location:
    cout << abs(north) + abs(east) << endl;
} // main()