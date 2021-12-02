/*
 * You have no idea how complicated I tried to make this.
 * I refuse to elaborate any further on that.
 * The solution is basically the same as last part, but you need to store a few more values.
 * After all, checking if a+b+c>b+c+d is the same as checking if a>d.
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
    int depthIncreases = 0; // The number of times the depth has increased
    list<int> vals;         // Our list of depths (stores up to three previous values)

    // Input loop:
    while(getline(input, inputVal)) {
        // Add the next depth to the list:
        vals.push_front(stoi(inputVal));
        // Make sure we've recorded enough depths that we can compare them:
        if(vals.size() == 4) {
            // Compare the first and last values (a+b+c>b+c+d == a>d):
            if(vals.front() > vals.back()) {
                ++depthIncreases;
            } // if(vals.front()...)
            // Remove the oldest value:
            vals.pop_back();
        } // if(vals.size()...)
    } // while
    input.close();

    //Print final solution:
    cout << depthIncreases << endl;
} // main()