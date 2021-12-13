/*
 * Wow, it's the exact same as Part 1 with the addition of actually printing the result.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

int countTrue(vector<vector<bool>>& m) {
    int output = 0;
    for(auto y = m.begin(); y != m.end(); y++) {
        for(auto x = y->begin(); x != y->end(); x++) {
            if(*x) output++;
        }
    }
    return output;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<bool>> paper(895, vector<bool>(1311, false));
    int split,
        x,
        y,
        val,
        line = 0;
    bool folding = false;
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        line++;

        if(inputVal == "") {
            folding = true;
            line = 0;
            cout << "Total dots on unfolded paper: " << countTrue(paper) << endl;
            continue;
        }
        
        if(folding) {
            split = inputVal.find("=");
            val = stoi(inputVal.substr(split + 1));

            // Vertical line:
            if(inputVal[split - 1] == 'x') {
                vector<vector<bool>> newPaper(paper.size(), vector<bool>(val, false));
                for(int y = 0; y < paper.size(); y++) {
                    for(int xd = 1; xd + val < paper[y].size(); xd++) {
                        if(val - xd < 0) {
                            cout << "ERROR: horizontal fold too large for instruction " << line << endl;
                            return 1;
                        }
                        newPaper[y][val - xd] = paper[y][val - xd] || paper[y][val + xd];
                    }
                }
                paper = newPaper;
            }
            // Horizontal line:
            else if(inputVal[split - 1] == 'y') {
                vector<vector<bool>> newPaper(val, vector<bool>(paper[0].size(), false));
                for(int yd = 1; yd + val < paper.size(); yd++) {
                    for(int x = 0; x < paper[yd + val].size(); x++) {
                        if(val - yd < 0) {
                            cout << "ERROR: vertical fold too large for instruction " << line << endl;
                            return 1;
                        }
                        newPaper[val - yd][x] = paper[val - yd][x] || paper[val + yd][x];
                    }
                }
                paper = newPaper;
            }
            else {
                cout << "ERROR: Invalid fold direction for instruction " << line << endl;
                return 1;
            }
            cout << "Total dots after instruction " << line << ": " << countTrue(paper) << endl;
        }
        else {
            split = inputVal.find(",");
            x = stoi(inputVal.substr(0, split));
            y = stoi(inputVal.substr(split + 1));
            paper[y][x] = true;
        }
    } // while
    input.close();

    //Print final solution:
    for(auto y = paper.begin(); y != paper.end(); y++) {
        for(auto x = y->begin(); x != y->end(); x++) {
            if(*x) cout << "#";
            else cout << ".";
        }
        cout << endl;
    }
} // main()