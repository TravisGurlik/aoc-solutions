#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <map>
#include <sstream>
#include <set>

using namespace std;

/**
 * Day 7: Handy Haversacks (https://adventofcode.com/2020/day/7)
 * This was the first major roadblock for a lot of people.
 * I took a recursive approach because this task practically demands it.
 * Both Parts for today include lots of print statements for debugging.
 */

/**
 * Determines which bags hold a given target bag, both directly and transitively
 * @param bags The list of bags and their parents
 * @param targetColor The bag color to find the parents of
 * @return A set of all of the target bag's ancestors
 */
set<string> getParents(map<string, vector<string>> &bags, string targetColor) {
    cout << "Finding parents for " << targetColor << " bags" << endl;
    set<string> output; // The output set

    // An explicit base case isn't needed, as the for loop handles it anyways.

    // Iterate through each parent:
    for(string s : bags[targetColor]) {
        // Add the bag to the set:
        output.insert(s);
        // Get the bag's parents recursively and add them all to the set:
        cout << "Added 1 bag, now at " << output.size() << endl;
        set<string> got = getParents(bags, s);
        cout << "Back to " << targetColor << endl;
        for(string gs : got) {
            output.insert(gs);
        } // for(gs...)
        cout << "Added " << got.size() << " bags; now at " << output.size() << endl;
    } // for(s...)

    // Return the final set:
    cout << "Finished " << targetColor << " bags with " << output.size() << " parents" << endl;
    return output;
} // getParents()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    map<string, vector<string>> bags; // The list of bags; maps bag color to colors of direct parents

    while(getline(input, inputVal)) {
        // More variables:
        istringstream readRule(inputVal); // Stringstreams are useful for reading individual contents
        string readIn;                    // The string to store new words in
        string bagColor;                  // The color of the current bag

        // Read the color of the current bag (colors are two words, so we need two variables):
        readRule >> bagColor >> readIn;
        bagColor += " " + readIn;

        // Skip ahead to the first number:
        readRule >> readIn >> readIn >> readIn;
        if(readIn == "no") {
            // If this word is "no" instead of a number, this bag doesn't contain any other bags:
            continue;
        } // if

        // Read each contained bag (eof in this case is end of line, since this is a stringstream):
        while(!readRule.eof()) {
            // Read in the color of the next bag:
            string newColor;
            readRule >> newColor >> readIn;
            newColor += " " + readIn;

            // Add this bag to that bag's list of parents:
            bags[newColor].push_back(bagColor);

            //Skip to the next number:
            readRule >> readIn >> readIn;
        } // while(readRule...)
    } // while(getline...)
    input.close();

    // Now that we've filled in the map, perform the recursive calculation:
    cout << getParents(bags, "shiny gold").size() << endl;
} // main()