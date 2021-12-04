/*
 * This part followed pretty smoothly from the last; most of the code is the
 *   same as part 1.
 * It did take me a bit to figure out how I wanted to store stuff though.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

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
    string calls;
    int lineNum = 0;
    vector<Board> boards;
    Board board;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        if(lineNum == 0) {
            calls = inputVal;
        } // if
        else if(inputVal.length() == 0) {
            if(lineNum > 1) {
                boards.push_back(board);
            } // if(lineNum...)
            board = Board();
        } // else if
        else {
            vector<int> lineNums;
            for(int i = 0; i < inputVal.length(); i += 3) {
                lineNums.push_back(stoi(inputVal.substr(i, 2)));
            } // for
            board.nums.push_back(lineNums);
        } // else
        lineNum++;
    } // while
    input.close();

    bool marked = false;
    int prev = 0,
        next = calls.find(","),
        callNum = -1;
    vector<bool> wins(boards.size(), false);    // Whether each board has won yet (for quicker lookup)
    vector<int> winningBoards;                  // The boards in the order they win
    while(next != calls.npos && winningBoards.size() < boards.size()) {
        callNum = stoi(calls.substr(prev,next-prev));
        for(int b = 0; b < boards.size(); b++) {
            if(!wins[b]) { // Only continue if this board hasn't won already
                marked = false;
                for(int row = 0; row < 5; row++) {
                    for(int col = 0; col < 5; col++) {
                        if(boards[b].nums[row][col] == callNum) {
                            boards[b].called[row][col] = true;
                            marked = true;
                            if((boards[b].called[row][0] && boards[b].called[row][1] && boards[b].called[row][2] && boards[b].called[row][3] && boards[b].called[row][4]) ||
                                (boards[b].called[0][col] && boards[b].called[1][col] && boards[b].called[2][col] && boards[b].called[3][col] && boards[b].called[4][col])) {
                                    wins[b] = true; // Mark this board as a winner
                                    winningBoards.push_back(b); // Add this board to the list of winners
                                    break;
                                } // if(win)
                        } // if(match)
                    } // for(col)
                    if(marked) break;
                } // for(row)
            } // if(!wins[b])
        } // for(b)
        prev = next + 1;
        next = calls.find(",", prev);
    } // while

    int lastBoard = winningBoards.back(); // The last board in the list was the last to win
    int unmarked = 0;
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 5; col++) {
            if(!boards[lastBoard].called[row][col]) {
                unmarked += boards[lastBoard].nums[row][col];
            }
        }
    }

    //Print final solution:
    cout << "Board " << lastBoard << " won last." << endl;
    cout << unmarked * callNum << endl;
} // main()