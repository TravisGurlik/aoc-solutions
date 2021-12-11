/*
 * Day 10: Syntax Sorting (https://adventofcode.com/2021/day/10)
 * First time I've used a stack in a while.
 * Whatever was last opened must be the next one closed, so this fits a stack perfectly.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <stack>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    bool invalid;       // Whether the current line is invalid
    int score = 0;      // The total score
    stack<char> opens;  // The starts of all the blocks
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Reset variables:
        invalid = false;
        opens = stack<char>();

        // For each character...
        for(char c : inputVal) {
            switch(c) {
                // If it's an open, add it to the stack:
                case '[':
                case '{':
                case '(':
                case '<':
                    opens.push(c);
                    break;
                // If it's a close, compare it to the last open.
                // If they don't match, the line is invalid:
                case ']':
                    if(opens.top() != '[') {
                        invalid = true;
                        score += 57;
                        break;
                    } // if
                    opens.pop();
                    break;
                case '}':
                    if(opens.top() != '{') {
                        invalid = true;
                        score += 1197;
                        break;
                    } // if
                    opens.pop();
                    break;
                case ')':
                    if(opens.top() != '(') {
                        invalid = true;
                        score += 3;
                        break;
                    } // if
                    opens.pop();
                    break;
                case '>':
                    if(opens.top() != '<') {
                        invalid = true;
                        score += 25137;
                        break;
                    } // if
                    opens.pop();
                    break;
            } // switch
            if(invalid) break; // Skip the rest of the string if it's already invalid
        } // for
    } // while
    input.close();

    //Print final solution:
    cout << score << endl;
} // main()