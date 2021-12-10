/*
 * Ew. Ew. Ew. Ew. Ew.
 * This is awful spaghetti code but it's the best way I could think of to do this:
 *   This is a complete recreation of the logic I used to do this by hand.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * @brief Compares two strings by length only
 */
struct CompStringByLength {
    bool operator()(string lhs, string rhs) {
        return lhs.length() < rhs.length();
    }
}; // CompStringByLength

/**
 * @brief Prints error information for debugging
 * 
 * @param lineNum The line number the error occurred on
 * @param newDigit The resultant digit string
 * @param samples The set of sample digits
 * @param outputs The set of output digits
 * @param segments The segment mapping
 * @param encToNormal The reverse segment mapping
 */
void printError(int lineNum, string newDigit, vector<string>& samples, vector<string>& outputs, map<char, string>& segments, map<char, char>& encToNormal) {
    cout << "ERROR: Attempted to decrypt invalid digit " << newDigit << " on line " << lineNum << endl << endl;
    cout << "Current state" << endl;
    cout << "-------------" << endl;
    cout << "Samples:" << endl;
    for(int i = 0; i < samples.size(); i++) {
        cout << "\t[" << i << "]: " << samples[i] << endl;
    }
    cout << "Outputs:" << endl;
    for(int i = 0; i < outputs.size(); i++) {
        cout << "\t[" << i << "]: " << outputs[i] << endl;
    }
    cout << "Segment mappings:" << endl;
    for(auto i = segments.begin(); i != segments.end(); i++) {
        cout << "\t" << i->first << " = " << i->second << endl;
    }
    cout << "Reverse mappings:" << endl;
    for(auto i = encToNormal.begin(); i != encToNormal.end(); i++) {
        cout << "\t" << i->first << " -> " << i->second << endl;
    }
    cout << endl << "Exiting..." << endl;
} // printError()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<string> samples; // The list of sample digits
    vector<string> outputs; // The list of output digits
    string samplesIn,       // The sample string
           outputsIn,       // The output string
           part;            // An individual digit
    int split,              // Where to split the string
        total = 0,          // The sum of the outputs
        line = 0;           // The line number (for debugging)

    // The digits that correspond to each normal set of segments:
    map<string, char> digits;
    digits["abcefg"] = '0';
    digits["cf"] = '1';
    digits["acdeg"] = '2';
    digits["acdfg"] = '3';
    digits["bcdf"] = '4';
    digits["abdfg"] = '5';
    digits["abdefg"] = '6';
    digits["acf"] = '7';
    digits["abcdefg"] = '8';
    digits["abcdfg"] = '9';
    
    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Clear input vectors:
        samples.clear();
        outputs.clear();
        
        // Split string into sampels and outputs:
        split = inputVal.find("|");
        samplesIn = inputVal.substr(0, split - 1);
        outputsIn = inputVal.substr(split + 2);

        // Create sample vector:
        for(int i = samplesIn.find(" "); i != samplesIn.npos; i = samplesIn.find(" ")) {
            samples.push_back(samplesIn.substr(0, i));
            samplesIn = samplesIn.substr(i + 1);
        } // for
        samples.push_back(samplesIn); // Don't forget the last one

        // Create output vector:
        for(int i = outputsIn.find(" "); i != outputsIn.npos; i = outputsIn.find(" ")) {
            outputs.push_back(outputsIn.substr(0, i));
            outputsIn = outputsIn.substr(i + 1);
        } // for
        outputs.push_back(outputsIn); // Don't forget the last one

        sort(samples.begin(), samples.end(), CompStringByLength()); // Sort the sample digits by length

        // More variables:
        map<char, string> segments;     // The scrambled segment mapping (segment -> input wire)
        string placed = "";             // Which input wires have been placed already
        const string all = "abcdefg";   // A string with all input wires
        char temp,                      // A temporary string storage
             in;                        // Which wire from a pair is in this digit

        // Length 2 (1; add both wires to c and f):
        segments['c'] = samples[0];
        segments['f'] = samples[0];

        // Length 3 (7; add wire not in 1 as a):
        temp = samples[1][samples[1].find_first_not_of(samples[0])];
        segments['a'] = temp;
        placed += temp;

        // Length 4 (4; add wires not in 1 to b and d):
        for(char c : samples[2]) {
            if(samples[0].find(c) == samples[0].npos) {
                segments['b'] += c;
                segments['d'] += c;
            } // if
        } // for

        // Length 5:
        if(samples[3].find_first_of(segments['c']) != samples[3].find_last_of(segments['c'])) {
            // This is a three (contains both wires from the 1).
            // Determine which wire from the 4 is in this digit:
            in = samples[3][samples[3].find_first_of(segments['d'])];
            // Add it as segment d, and the other as segment b:
            placed += segments['d'];
            segments['d'] = in;
            segments['b'] = segments['b'][segments['b'].find_first_not_of(in)];
            // Find the wire we haven't seen before and add it as segment g:
            temp = samples[3][samples[3].find_first_not_of(placed + segments['c'])];
            segments['g'] = temp;
            placed += temp;
            // Find the only wire we haven't encountered and add it as segment e:
            segments['e'] = all[all.find_first_not_of(placed + segments['c'])];

            // Next number:
            if(samples[4].find(segments['e']) == samples[4].npos) {
                // Next is a five (contains the bottom right segment):
                // Determine which wire from the 1 is in this digit:
                in = samples[4][samples[4].find_first_of(segments['c'])];
                // Add that wire as segment f and the other as c:
                segments['f'] = in;
                segments['c'] = segments['c'][segments['c'].find_first_not_of(in)];
            } // if(samples[4]...)
            else {
                // Next is a two (does not contain the bottom right segment):
                // Determine which wire from the 1 is in this digit:
                in = samples[4][samples[4].find_first_of(segments['f'])];
                // Add that wire as segment c and the other as f:
                segments['c'] = in;
                segments['f'] = segments['f'][segments['f'].find_first_not_of(in)];
            } // else
        } // if(samples[3]...)
        else if(samples[3].find_first_of(segments['b']) != samples[3].find_last_of(segments['b'])) {
            // This is a five (contains both wires from the 4):
            // Determine which wire from the 1 is in this digit:
            in = samples[3][samples[3].find_first_of(segments['f'])];
            // Add it as segment f and the other as segment c:
            placed += segments['f'];
            segments['f'] = in;
            segments['c'] = segments['c'][segments['c'].find_first_not_of(in)];
            // Find the wire we haven't seen before and add it as segment g:
            temp = samples[3][samples[3].find_first_not_of(placed + segments['b'])];
            segments['g'] = temp;
            placed += temp;
            // Find the only wire we haven't encountered and add it as segment e:
            segments['e'] = all[all.find_first_not_of(placed + segments['b'])];

            // Next number (it doesn't matter what it is; both have segment d and not b):
            // Find which of the wires is in this digit:
            in = samples[4][samples[4].find_first_of(segments['b'])];
            // Add that wire as segment d and the other as segment b:
            segments['d'] = in;
            segments['b'] = segments['b'][segments['b'].find_first_not_of(in)];
        } // else if
        else {
            // This is a two (only other digit with 5 segments):
            // Determine which of the wires in the 1 is in this digit:
            char inA = samples[3][samples[3].find_first_of(segments['c'])];
            // Add that wire as segment c and the other as segment f:
            placed += segments['c'];
            segments['c'] = inA;
            segments['f'] = segments['f'][segments['f'].find_first_not_of(inA)];
            // Determine which of the wires in the 4 is in this digit:
            char inB = samples[3][samples[3].find_first_of(segments['d'])];
            // Add that wire as segment d and the other as segment b:
            placed += segments['d'];
            segments['d'] = inB;
            segments['b'] = segments['b'][segments['b'].find_first_not_of(inB)];

            // Next number (it doesn't matter what it is; both have segment g but not e):
            // Determine which wire is in this digit:
            temp = samples[4][samples[4].find_first_not_of(placed)];
            // Add it as segment g and the last remaining wire as segment e:
            segments['g'] = temp;
            placed += temp;
            segments['e'] = all[all.find_first_not_of(placed)];
        } // else

        // Get a reverse map for easier lookup:
        map<char, char> encDigitToNormal; // Maps wires to segments
        for(auto i = segments.begin(); i != segments.end(); i++) {
            encDigitToNormal[i->second[0]] = i->first;
        } // for

        // Determine the output digits:
        string encDigits;   // The output number
        // Loop through each output digit:
        for(string s : outputs) {
            string newDigit = ""; // The segments of the output digit
            // For each wire, get its matching segment:
            for(char c : s) {
                newDigit += encDigitToNormal[c];
            } // for(c)
            sort(newDigit.begin(), newDigit.end()); // Sort the segments to match the lookup
            // Error handling for debugging (if the digit does not exist):
            if(digits.count(newDigit) == 0) {
                printError(line, newDigit, samples, outputs, segments, encDigitToNormal);
                return 1;
            } // if
            encDigits += digits[newDigit]; // Add the decoded digit to the output number
        } // for(s)
        // More error handling (if we somehow missed a digit):
        if(encDigits.length() < 4) {
            printError(line, encDigits, samples, outputs, segments, encDigitToNormal);
            return 1;
        } // if

        line++; // Increment the line number
        total += stoi(encDigits); // Add the output number to our total
    } // while
    input.close();

    //Print final solution:
    cout << total << endl;
} // main()