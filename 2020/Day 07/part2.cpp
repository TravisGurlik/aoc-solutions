/*
 * Do the same thing as in Part 1, but in the other direction.
 * But this time, the numbers actually matter.
 * I probably could have done a map of string to pair instead of string to map to save some overhead.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <map>
#include <sstream>

using namespace std;

/**
 * Recursively determines how many bags a given bag color holds.
 * @param bags The map of bags to their contents
 * @param bagContentTotals A map for tracking previously calculated values
 * @param targetColor The color of bag to use as the base
 * @return The number of bags contained within the base bag
 */
int getContentsHelper(map<string, map<string, int>> &bags, map<string, int> &bagContentTotals, string targetColor) {
    // An explicit base case isn't needed, as the for loop handles it anyways.

    // Variables:
    int total = 0; // The total number of bags contained within this one

    // Loop through each bag contained in this one:
    for(auto i = bags[targetColor].begin(); i != bags[targetColor].end(); ++i) {
        // Add the number of bags this bag contains to the total:
        // (Use the previously calculated value if there is one to avoid excessive recursive calls)
        int got = bagContentTotals.count(i->first) == 0 ? getContentsHelper(bags, bagContentTotals, i->first) : bagContentTotals[i->first];
        // Add all instances of this bag and its contents to the total:
        total += i->second * (got + 1);
    } // for

    // Update previously calculated values and return the result:
    bagContentTotals[targetColor] = total;
    return total;
} // getContentsHelper()

/**
 * Determines how many bags a bag of a given color holds
 * @param bags The map of bags to their contents
 * @param targetColor The color of the bags to ue as the base
 * @return The total number of bags within a bag of the base color
 */
int getContents(map<string, map<string, int>> &bags, string targetColor) {
    // Construct the totals map and call the helper function to do the rest:
    map<string, int> bagContentTotals;
    return getContentsHelper(bags, bagContentTotals, targetColor);
} // getContents()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    map<string, map<string, int>> bags; // Maps bags to another map, which maps each contained bag to its quantity

    while(getline(input, inputVal)) {
        // The reading of the bags is almost exactly the same as Part 1:
        istringstream readRule(inputVal);
        string readIn;
        string bagColor;

        readRule >> bagColor >> readIn;
        bagColor += " " + readIn;

        readRule >> readIn >> readIn >> readIn;
        if(readIn == "no") {
            continue;
        } // if

        // The only difference is in how the contents are handled:
        while(!readRule.eof()) {
            // readIn contains the quantity of the next bag, so store that:
            int num = stoi(readIn);

            // Read the color of the contained bag:
            string newColor;
            readRule >> newColor >> readIn;
            newColor += " " + readIn;

            // Create the appropriate map values:
            bags[bagColor][newColor] = num;

            // Skip to the next number:
            readRule >> readIn >> readIn;
        } // while(readRule...)
    } // while(getline...)
    input.close();

    // Now that we've got our map, do the primary work recursively:
    cout << getContents(bags, "shiny gold") << endl;
} // main()