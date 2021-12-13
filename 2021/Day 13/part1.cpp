/*
 * Day 13: Transparent Origami (https://adventofcode.com/2021/day/13)
 * Not too difficult, to be honest.
 * I decided to go ahead and include logic for performing all the folds, since it
 *   wasn't too much extra effort.
 * A boolean matrix makes the process of not double-counting overlaps very easy,
 *   since it makes it literally impossible to double count them.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * @brief Counts the number of trues in a boolean matrix
 * 
 * @param m The matrix
 * @return int How many values are true
 */
int countTrue(vector<vector<bool>>& m) {
    int output = 0;
    for(auto y = m.begin(); y != m.end(); y++) {
        for(auto x = y->begin(); x != y->end(); x++) {
            if(*x) output++;
        } // for(x)
    } // for(y)
    return output;
} // countTrue()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    // We start with the boolean matrix representing the paper.
    // Since we're placing individual points, I decided to just cheat and
    //   manually set the sizes based off of the first two instructions in my input.
    // There are other ways I could have done this programmatically, but this was
    //   the easiest.
    vector<vector<bool>> paper(895, vector<bool>(1311, false)); // The paper. True means there's a dot there.
    int split,              // Where to split the input
        x,                  // The x coordinate when placing dots
        y,                  // The y coordinate when placing dots
        val,                // The value to fold at (separate for readability)
        line = 0;           // What line of the input we're on
    bool folding = false;   // Whether we're placing dots (false) or folding (true)
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        line++; // Increment line count

        // When we hit the blank line, prepare for folding:
        if(inputVal == "") {
            folding = true;
            line = 0;
            cout << "Total dots on unfolded paper: " << countTrue(paper) << endl;
            continue;
        } // if
        
        // Folding:
        if(folding) {
            // Get important values:
            split = inputVal.find("=");
            val = stoi(inputVal.substr(split + 1));

            // Vertical line:
            if(inputVal[split - 1] == 'x') {
                vector<vector<bool>> newPaper(paper.size(), vector<bool>(val, false)); // Buffer of the new size
                // Loop through each value on one side of the fold:
                for(int y = 0; y < paper.size(); y++) {
                    for(int xd = 1; xd + val < paper[y].size(); xd++) {
                        // Avoid accessing negative indexes:
                        if(val - xd < 0) {
                            cout << "ERROR: horizontal fold too large for instruction " << line << endl;
                            return 1;
                        } // if
                        // There's a dot at a given location if it's there on either side of the fold:
                        newPaper[y][val - xd] = paper[y][val - xd] || paper[y][val + xd];
                    } // for(xd)
                } // for(y)
                paper = newPaper; // Move buffer into actual paper
            } // if
            // Horizontal line:
            else if(inputVal[split - 1] == 'y') {
                vector<vector<bool>> newPaper(val, vector<bool>(paper[0].size(), false)); // Buffer of the new size
                // Loop through each value on one side of the fold:
                for(int yd = 1; yd + val < paper.size(); yd++) {
                    for(int x = 0; x < paper[yd + val].size(); x++) {
                        // Avoid accessing negative indexes:
                        if(val - yd < 0) {
                            cout << "ERROR: vertical fold too large for instruction " << line << endl;
                            return 1;
                        } // if
                        // There's a dot at a given location if it's there on either side of the fold:
                        newPaper[val - yd][x] = paper[val - yd][x] || paper[val + yd][x];
                    } // for(xd)
                } // for(y)
                paper = newPaper; // Move buffer into actual paper
            } // else if
            // Something somewhere went horribly wrong:
            else {
                cout << "ERROR: Invalid fold direction for instruction " << line << endl;
                return 1;
            } // else
            // Print current progress:
            cout << "Total dots after instruction " << line << ": " << countTrue(paper) << endl;
        } // if(folding)
        // Placing dots:
        else {
            split = inputVal.find(",");             // Find the comma
            x = stoi(inputVal.substr(0, split));    // Get x value
            y = stoi(inputVal.substr(split + 1));   // Get y value
            paper[y][x] = true;                     // Place dot
        } // else
    } // while
    input.close();

    //Print final solution:
    cout << "Done!" << endl;
} // main()