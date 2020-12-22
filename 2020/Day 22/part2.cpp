/*
 * This Part was not quite as straightforward as the first.
 * One of the more difficult parts was understanding the new rules.
 * All code in main (with the exception of the part that runs the game) is
 *   the same as in Part 1.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <list>
#include <vector>
#include <utility>

using namespace std;

/**
 * Plays a game of Recursive Combat
 * @param p1 Player 1's deck
 * @param p2 Player 2's deck
 * @return True if Player 1 wins, false if Player 2 wins
 */
bool combat(list<int>& p1, list<int>& p2) {
    // Variables:
    vector<pair<list<int>, list<int>>> prevStates; // All previous states of this game
    list<int> new1, new2;                          // Buffers for constructing subdecks

    // Continue until a player runs out of cards:
    while(p1.size() > 0 && p2.size() > 0) {
        // Check the current gamestate against previous states:
        for(auto i = prevStates.begin(); i != prevStates.end(); i++) {
            // If this state matches a previous one, Player 1 wins:
            if(p1 == i->first && p2 == i->second) {
                return true;
            } // if
        } // for
        // Add this state to the list:
        prevStates.push_back(make_pair(p1, p2));

        // Store the top card of each deck, then remove them:
        int c1 = p1.front(),
            c2 = p2.front();
        p1.pop_front();
        p2.pop_front();

        // Recurse if we are able to:
        if(c1 <= p1.size() && c2 <= p2.size()) {
            // Reset the buffers:
            new1.clear();
            new2.clear();
            
            // Construct subdeck for Player 1:
            int count = 0;
            for(auto i = p1.begin(); count < c1; i++) {
                new1.push_back(*i);
                count++;
            } // for

            // Construct subdeck for Player 2:
            count = 0;
            for(auto i = p2.begin(); count < c2; i++) {
                new2.push_back(*i);
                count++;
            } // for

            // Run the subgame:
            if(combat(new1, new2)) {
                // If Player 1 wins, add the cards to their deck:
                p1.push_back(c1);
                p1.push_back(c2);
            } // if(combat...)
            else {
                // If Player 2 wins, add the cards to their deck:
                p2.push_back(c2);
                p2.push_back(c1);
            } // else
        } // if(c1 <=...)
        // Otherwise, do this round normally:
        else {
            if(c1 > c2) {
                // Player 1 wins:
                p1.push_back(c1);
                p1.push_back(c2);
            } // if(c1 > c2)
            else {
                // Player 2 wins:
                p2.push_back(c2);
                p2.push_back(c1);
            } // else
        } // else
    } // while
    // Wins by deck out:
    if(p1.size() > 0) {
        // Player 1 wins:
        return true;
    } // if
    // Player 2 wins:
    return false;
} // combat()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    list<int> player1;
    list<int> player2;
    bool p1Done = false;

    while(getline(input, inputVal)) {
        if(inputVal[0] == 'P') {
            continue;
        } // if(...'P')
        else if(inputVal.length() == 1) {
            p1Done = true;
        } // else if(...1)
        else if(p1Done) {
            player2.push_back(stoi(inputVal));
        } // else if(p1Done)
        else {
            player1.push_back(stoi(inputVal));
        } // else
    } // while
    input.close();

    // Run the game (call the recursive function):
    combat(player1, player2);

    long score = 0;
    int count = 1;
    if(player1.size() > 0) {
        for(auto i = player1.rbegin(); i != player1.rend(); i++) {
            score += (count * *i);
            count++;
        } // for
    } // if
    else {
        for(auto i = player2.rbegin(); i != player2.rend(); i++) {
            score += (count * *i);
            count++;
        } // for
    } // else

    //Print final solution:
    cout << score << endl;
} // main()