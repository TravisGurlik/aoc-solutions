/*
 * Day 22: Crab Combat (https://adventofcode.com/2020/day/22)
 * This Part was a nice breather from some of the previous puzzles.
 * Nothing like a good game of War to pass the time.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <list>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    list<int> player1;   // Player 1's deck
    list<int> player2;   // Player 2's deck
    bool p1Done = false; // Are we done reading Player 1's deck?

    while(getline(input, inputVal)) {
        // Skip deck labels:
        if(inputVal[0] == 'P') {
            continue;
        } // if(...'P')
        // An empty line means we're done with Player 1's deck:
        else if(inputVal.length() == 1) {
            p1Done = true;
        } // else if(inputVal...)
        // Read card for Player 1:
        else if(p1Done) {
            player2.push_back(stoi(inputVal));
        } // else if(p1Done)
        // Read card for Player 2:
        else {
            player1.push_back(stoi(inputVal));
        } // else
    } // while
    input.close();

    // Play Combat
    // -----------
    // Loop until one player is out of cards:
    while(player1.size() > 0 && player2.size() > 0) {
        // If Player 1's card is higher:
        if(player1.front() > player2.front()) {
            // Add both cards to Player 1's deck:
            player1.push_back(player1.front());
            player1.push_back(player2.front());
        } // if
        // If Player 2's card is higher:
        else {
            // Add both cards to player 2's deck:
            player2.push_back(player2.front());
            player2.push_back(player1.front());
        } // else
        // Remove both cards from the top of each player's deck:
        player1.pop_front();
        player2.pop_front();
    } // for

    // Calculate winning Player's score:
    long score = 0; // The player's score
    int count = 1;  // The number of cards counted thus far
    // If Player 1 won:
    if(player1.size() > 0) {
        // Loop through Player 1's cards in reverse:
        for(auto i = player1.rbegin(); i != player1.rend(); i++) {
            score += (count * *i);
            count++; // Increment count with each card
        } // for
    } // if
    // If Player 2 won:
    else {
        // Same as Player 1, but with Player 2:
        for(auto i = player2.rbegin(); i != player2.rend(); i++) {
            score += (count * *i);
            count++;
        } // for
    } // else

    //Print final solution:
    cout << score << endl;
} // main()