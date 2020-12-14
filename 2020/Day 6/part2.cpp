#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <map>

using namespace std;

/**
 * Swap the set for a map for easy counting with uniqueness.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    map<char, int> yeses; // How many people in the group said "yes" to each question
    int sum    = 0,       // Total sum of all unanimous "yes"es
        people = 0;       // Total number of people in the current group

    while(getline(input, inputVal)) {
        // Multi-line input:
        if(inputVal.length() == 1) {
            // Iterate through each question that got at least one yes:
            for(auto i = yeses.begin(); i != yeses.end(); ++i) {
                // If this isn't the newline and everyone said yes, increment the total:
                if(i->first >= 97 && i->second == people) {
                    sum++;
                } // if(i->first...)
            } // for
            // Reset values:
            yeses.clear();
            people = 0;
        } // if(inputVal...)
        else {
            // More data to add:
            for(char c : inputVal) {
                yeses[c]++;
            } // for
            // Increment the number of people in the group:
            people++;
        } // else
    } // while
    input.close();

    // Add data for the last group:
    for(auto i = yeses.begin(); i != yeses.end(); ++i) {
        if(i->second == people) {
            sum++;
        } // if
    } // for

    // Print the final total:
    cout << sum << endl;
} // main()