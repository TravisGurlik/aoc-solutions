/*
 * Day 23: Crab Cups (https://adventofcode.com/2020/day/23)
 * This first Part wasn't too bad; the most difficult part was picking a container.
 * Since all of the labels were only one digit, I figured I could use a string as my container.
 * This actually worked pretty well.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int currentI = 0, // The index of the current cup
        currentL;     // The label of the current cup
    string cups;      // Our "circle" of cups

    // We can jsut read the input straight into the "container":
    getline(input, cups);
    input.close();

    // Start with the first cup as our current:
    currentL = cups[0] - 48;
    // Run for 100 turns:
    for(int turn = 0; turn < 100; turn++) {
        // Get our substring (accounting for looping off the end):
        string sub = cups.substr(currentI + 1, 3); // The removed cups in order
        int startLen = 0;                          // The number of cups to remove from the front of the string (when looping)
        if(sub.length() < 3) {
            startLen = 3 - sub.length();
            sub += cups.substr(0, startLen);
        } // if(sub...)

        // Remove the picked up cups:
        cups.erase(currentI + 1, 3);
        if(startLen > 0) {
            cups.erase(0, startLen);
        } // if(startLen)

        // Find our destination label (accounting for looping and the removed cups):
        int destL = currentL - 1;
        if(destL < 1) destL = 9;
        while(sub.find(to_string(destL)) != sub.npos) {
            destL--;
            if(destL < 1) destL = 9;
        } // while

        // Get the index of the destination and add the removed cups back in:
        int destI = cups.find(to_string(destL)) + 1;
        if(destI == cups.size()) {
            cups += sub;
        } // if(destI...)
        else {
            cups.insert(destI, sub);
        } // else

        // Update our current cup to the next in the circle:
        currentI = cups.find(to_string(currentL)) + 1;
        currentI %= cups.size();
        currentL = cups[currentI] - 48;
    } // for

    // Get our output, starting from after cup 1:
    string output = "";
    int outI = cups.find("1") + 1;
    if(outI == cups.size()) outI = 0;
    while(output.size() < cups.size() - 1) {
        output += cups[outI];
        outI++;
        if(outI == cups.size()) outI = 0;
    } // while

    //Print final solution:
    cout << output << endl;
} // main()