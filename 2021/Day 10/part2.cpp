/*
 * Also pretty simple (once i realized that the issue I was having was with cout).
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    bool invalid;           // If this line is invalid
    long score = 0;         // This line's score
    stack<char> opens;      // The stack of openings
    vector<long> scores;    // The list of scores
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Reset variables:
        invalid = false;
        score = 0;

        // Weed out any invalid lines using Part 1's logic:
        for(char c : inputVal) {
            switch(c) {
                case '[':
                case '{':
                case '(':
                case '<':
                    opens.push(c);
                    break;
                case ']':
                    if(opens.top() != '[') {
                        invalid = true;
                        break;
                    } // if
                    opens.pop();
                    break;
                case '}':
                    if(opens.top() != '{') {
                        invalid = true;
                        break;
                    } // if
                    opens.pop();
                    break;
                case ')':
                    if(opens.top() != '(') {
                        invalid = true;
                        break;
                    } // if
                    opens.pop();
                    break;
                case '>':
                    if(opens.top() != '<') {
                        invalid = true;
                        break;
                    } // if
                    opens.pop();
                    break;
            } // switch
            if(invalid) break;
        } // for
        // Skip scoring invalid lines:
        if(invalid) {
            while(opens.size() > 0) opens.pop();
            continue;
        } // if

        // Calculate score using the remaining opens:
        while(opens.size() > 0) {
            score *= 5;
            switch(opens.top()) {
                case '<':
                    score++;
                case '{':
                    score++;
                case '[':
                    score++;
                case '(':
                    score++;
                    break;
            } // switch
            opens.pop();
        } // while
        scores.push_back(score);
    } // while
    input.close();

    sort(scores.begin(), scores.end());
    for(int s : scores) {
        cout << s << endl;
    }
    cout << endl;
    //Print final solution:
    cout << scores[scores.size() / 2] << endl;
} // main()