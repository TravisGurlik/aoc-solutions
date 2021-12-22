/*
 * Day 21: Dirac Dice (https://adventofcode.com/2021/day/21)
 * This first part wasn't too bad.
 * I probably could have simplified this further, but eh.
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
    int player1,         // Player 1's current space
        player2,         // Player 2's current space
        p1Score = 0,     // Player 1's current score
        p2Score = 0,     // Player 2's current score
        nextDieRoll = 1, // The next value that will be rolled on the die
        numRolls = 0;    // How many times the die has been rolled
    
    // Get input:
    getline(input, inputVal);
    inputVal.pop_back();
    player1 = inputVal.back() - '0' - 1;
    getline(input, inputVal);
    inputVal.pop_back();
    player2 = inputVal.back() - '0' - 1;
    input.close();

    // Play until someone wins:
    while(p1Score < 1000 && p2Score < 1000) {
        // Determine the outcome of the three rolls:
        int toAdd = 0;
        for(int n = 0; n < 3; n++) {
            toAdd += nextDieRoll;
            nextDieRoll++;
            nextDieRoll %= 10; // Since the board has 10 spaces, 81 is equivalent to 41 is equivalent to 1
            numRolls++;
        } // for

        // Player 1's turn:
        if(numRolls / 3 % 2 == 1) {
            player1 += toAdd;
            player1 %= 10;
            p1Score += (player1 + 1);
        } // if
        // Player 2's turn:
        else {
            player2 += toAdd;
            player2 %= 10;
            p2Score += (player2 + 1);
        } // else
    } // while

    //Print final solution:
    cout << min(p1Score, p2Score) * numRolls << endl;
} // main()