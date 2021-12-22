/*
 * Part 2 barely even resembled the first part.
 * I got to learn about bitsets though, so that was nice.
 * The main insight is that there will be way too many universes to simulate them all,
 *   but there will also be a lot of duplicates.
 * So it's best to store how many games are in a given state, and simulate them all as one.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <bitset>

using namespace std;

/**
 * @brief Stores a state of the game (ignoring current turn, which is handled elsewhere)
 */
struct GameState {
    short p1Space, // The space player 1 is on
          p2Space, // The space player 2 is on
          p1Score, // Player 1's score
          p2Score; // Player 2's score

    // Initial constructor with just spaces:
    GameState(short space1, short space2) :
        p1Space(space1), p2Space(space2), p1Score(0), p2Score(0) {}

    // Full constructor:
    GameState(short space1, short space2, short score1, short score2) :
        p1Space(space1), p2Space(space2), p1Score(score1), p2Score(score2) {}
}; // GameState

/**
 * @brief Compares two GameStates for equivalency, member by member
 * 
 * @param lhs The first GameState
 * @param rhs The second GameState
 * @return true if the GameStates are equivalent
 */
bool operator==(const GameState& lhs, const GameState& rhs) {
    if(lhs.p1Space != rhs.p1Space) return false;
    if(lhs.p2Space != rhs.p2Space) return false;
    if(lhs.p1Score != rhs.p1Score) return false;
    if(lhs.p2Score != rhs.p2Score) return false;
    return true;
} // operator==()

/**
 * @brief Generates a unique value for each possible GameState
 */
struct HashGame {
    /**
     * @brief Generates a unique value for each possible GameState
     * 
     * @param game The GameState to hash
     * @return size_t The corresponding value
     */
    size_t operator()(const GameState& game) const {
        string val = "";
        val += bitset<4>(game.p1Space).to_string(); // Value is [0, 9]
        val += bitset<4>(game.p2Space).to_string(); // Value is [0, 9]
        val += bitset<6>(game.p1Score).to_string(); // Value is [0, 20]
        val += bitset<6>(game.p1Score).to_string(); // Value is [0, 20]
        return stoi(val, nullptr, 2);
    } // operator()()
}; // HashGame

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int player1,                                    // Player 1's starting space
        player2;                                    // Player 2's starting space
    long p1Wins = 0,                                // How many universes player 1 has won in
         p2Wins = 0;                                // How many universes player 2 has won in
    unordered_map<GameState, long, HashGame> games; // The current set of games and how many of each exists
    long turn = 1;                                  // The current turn number
    long rolls[7] = {1, 3, 6, 7, 6, 3, 1};          // How many ways each value can be rolled (starting at 3)
    
    // Get input:
    getline(input, inputVal);
    inputVal.pop_back();
    player1 = inputVal.back() - '0' - 1;
    getline(input, inputVal);
    inputVal.pop_back();
    player2 = inputVal.back() - '0' - 1;
    input.close();

    games[GameState(player1, player2)] = 1; // Create initial GameState

    // Loop until all games in all universes have been won:
    // (Each outcome occurs in a number of universes equal to the number of ways to roll that value.)
    // (As these compound on one another, this is multiplied by the current number of universes for each outcome every step.)
    while(games.size() > 0) {
        unordered_map<GameState, long, HashGame> buffer; // The glorious return of the buffer
        // Loop through each existant GameState:
        for(auto i = games.begin(); i != games.end(); i++) {
            // Loop through each possible outcome of the roll:
            for(int roll = 3; roll <= 9; roll++) {
                GameState nextState = i->first; // An editable copy of the current GameState
                // Player 1's turn:
                if(turn % 2 == 1) {
                    nextState.p1Space += roll;
                    nextState.p1Space %= 10;
                    nextState.p1Score += (nextState.p1Space + 1);
                    // Player 1 wins:
                    if(nextState.p1Score >= 21) {
                        p1Wins += (i->second * rolls[roll - 3]);
                        continue;
                    } // if(nextState...)
                } // if(turn...)
                // Player 2's turn:
                else {
                    nextState.p2Space += roll;
                    nextState.p2Space %= 10;
                    nextState.p2Score += (nextState.p2Space + 1);
                    // Player 2 wins:
                    if(nextState.p2Score >= 21) {
                        p2Wins += (i->second * rolls[roll - 3]);
                        continue;
                    } // if(nextState...)
                } // else
                // If the current player didn't win, saves these games for the next loop:
                buffer[nextState] += (i->second * rolls[roll - 3]);
            } // for(roll)
        } // for(i)

        // Update values:
        games = buffer;
        turn++;
    } // while

    //Print final solution:
    cout << max(p1Wins, p2Wins) << endl;
} // main()