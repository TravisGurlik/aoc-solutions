#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <utility>

using namespace std;

/**
 * Day 16: Ticket Translation (https://adventofcode.com/2020/day/16)
 * Passports 2 coming in hot.
 * Today was just a mess.
 * Due to the formatting of the input, I decided to split it into sections by empty lines.
 *   The data in each section must be parsed differently, hence some of the mess.
 * Since I wasn't exactly sure what kind of input we'd get for the first section (the fields),
 *   I overgeneralized a bit there (hence the vector of vectors for the fields).
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    vector<vector<pair<int, int>>> fields;  // The allowable ranges for each field
    vector<pair<int, int>> fieldVals;       // Used for adding a field to the above
    int errorRate = 0,                      // The ticket scanning error rate (sum of invalid values)
        inputArea = 0,                      // What area of the input we're in (0 = fields, 1 = my ticket, 2 = nearby tickets)
        indexS,                             // The start index for a substring
        indexE,                             // The end index for a substring
        valA,                               // Holds a numeric value read from the input
        valB;                               // Holds a numeric value read from the input
    bool valid;                             // Is the current value valid (when checking tickets)

    while(getline(input, inputVal)) {
        // Check for empty lines:
        if(inputVal.length() == 1) {
            // An empty line means we've moved to the next section:
            inputArea++;
            continue;
        } // if

        // Based on the current section, do different things with the input:
        switch(inputArea) {
            case 0: // Fields and valid ranges
                // I wish this could have been looped, but there's too many different characters to look for.
                // Reads both valid ranges for the current field:
                indexS = inputVal.find(":") + 2;
                indexE = inputVal.find("-");
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                indexE = inputVal.find(" ", indexS);
                valB = stoi(inputVal.substr(indexS, indexE - indexS));
                fieldVals.push_back(make_pair(valA, valB));

                indexS = inputVal.find(" ", indexE + 1) + 1;
                indexE = inputVal.find("-", indexS);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                valB = stoi(inputVal.substr(indexS));
                fieldVals.push_back(make_pair(valA, valB));
                fields.push_back(fieldVals);

                fieldVals.clear();
                break;
            case 1: // My ticket
                // My ticket doesn't matter ffor this part, so we can just ignore it
                break;
            case 2: // Nearby tickets
                // Skip the label line:
                if(inputVal[0] == 'n') {
                    break;
                } // if

                // Define the index range for the first value:
                indexS = 0;
                indexE = inputVal.find(",");
                while(indexE != inputVal.npos) {
                    // For every value on the ticket, read it and check for validity:
                    valA = stoi(inputVal.substr(indexS, indexE - indexS));
                    valid = false;
                    for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                        for(auto ri = fi->begin(); ri != fi->end() && !valid; ri++) {
                            // Since we only care if the value matches any field, we can break
                            //   the loops as soon as it finds one it fits:
                            valid = valA >= ri->first && valA <= ri->second;
                        } // for(ri)
                    } // for(fi)
                    // If the value didn't fit any fields:
                    if(!valid) {
                        // Increase the error rate:
                        errorRate += valA;
                    } // if

                    // Define the range for the next value:
                    indexS = indexE + 1;
                    indexE = inputVal.find(",", indexS);
                } // while(indexE...)
                // Once again, the last value in the line must be considered outside the main loop:
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                valid = false;
                for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                    for(auto ri = fi->begin(); ri != fi->end() && !valid; ri++) {
                        valid = valA >= ri->first && valA <= ri->second;
                    } // for(ri)
                } // for(fi)
                if(!valid) {
                    errorRate += valA;
                } // if

                break;
        } // switch
    } // while(getline...)
    input.close();

    //Print final solution:
    cout << errorRate << endl;
} // main()