/*
 * Day 04: Giant Squid (https://adventofcode.com/2021/day/04)
 * Wow, this code is an absolute mess.
 * Thankfully this is early enough that we don't need to worry about performance yet.
 * Store all the boards, then check every space in every board for each call.
 *   I take some shortcuts, only checking for a win when a board matches a space,
 *     but otherwise there wasn't much to be done to simplify this.
 *   And yes, I kinda hard coded the wins checks. Sue me.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * @brief A representation of a bingo board
 * Contains the board's numbers and a "dab" board separately
 */
struct Board {
    vector<vector<int>> nums;
    vector<vector<bool>> called;

    Board() {
        called = vector<vector<bool>>(5, vector<bool>(5, false));
    }
};

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    string calls;           // The list of called numbers
    int lineNum = 0;        // The current line number (mainly just for handling the first few lines)
    vector<Board> boards;   // The list of boards
    Board board;            // The board currently being constructed
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // First line - store the calls for later:
        if(lineNum == 0) {
            calls = inputVal;
        } // if
        // Blank lines - save the board (when there is one) and start a new one:
        else if(inputVal.length() == 0) {
            if(lineNum > 1) {
                boards.push_back(board);
            } // if(lineNum...)
            board = Board();
        } // else if
        // All others - add the numbers to the board:
        else {
            vector<int> lineNums; // The row being constructed
            // I cheated a little; each number is in a 2 character space, so I hard coded the segments:
            for(int i = 0; i < inputVal.length(); i += 3) {
                lineNums.push_back(stoi(inputVal.substr(i, 2)));
            } // for
            board.nums.push_back(lineNums);
        } // else
        lineNum++; // Increment the lineNum
    } // while
    input.close();

    // Variables for playing bingo:
    bool marked = false;        // Whether the board has marked this space
    int prev = 0,               // The previous place in the calls list and the start of the next number
        next = calls.find(","), // The next comma, and the end of the next number
        callNum = -1,           // The number that was just called
        winBoard = -1;          // The winning board
    // Start calling numbers:
    while(next != calls.npos && winBoard == -1) {
        callNum = stoi(calls.substr(prev,next-prev)); // Get the next number
        for(int b = 0; b < boards.size(); b++) {    // Loop through all boards
            marked = false;
            for(int row = 0; row < 5; row++) {      // Loop through each row
                for(int col = 0; col < 5; col++) {  // Loop through each column
                    if(boards[b].nums[row][col] == callNum) {   // If there's a match...
                        boards[b].called[row][col] = true;      // Mark the space
                        marked = true;
                        // We just marked a new space, so check if this board wins (only the row and column with the newly marked space):
                        if((boards[b].called[row][0] && boards[b].called[row][1] && boards[b].called[row][2] && boards[b].called[row][3] && boards[b].called[row][4]) ||
                            (boards[b].called[0][col] && boards[b].called[1][col] && boards[b].called[2][col] && boards[b].called[3][col] && boards[b].called[4][col])) {
                                // If this board has won, save it as the winning board and break the loop:
                                winBoard = b;
                                break;
                            } // if(win)
                    } // if(match)
                } // for(col)
                if(marked) break; // Skip the rest if we've already found this number
            } // for(row)
            if(winBoard != -1) break; // Again, skip the rest if the game's already over
        } // for(b)
        // Update the positions:
        prev = next + 1;
        next = calls.find(",", prev);
    } // while

    // We have a winner! Time to calculate their score:
    int unmarked = 0; // The sum of unmarked spaces
    // Loop through each space, and add up the unmarked ones:
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 5; col++) {
            if(!boards[winBoard].called[row][col]) {
                unmarked += boards[winBoard].nums[row][col];
            } // if
        } // for(col)
    } // for(row)

    //Print final solution:
    cout << "Board " << winBoard << " won!" << endl;
    cout << unmarked * callNum << endl;
} // main()