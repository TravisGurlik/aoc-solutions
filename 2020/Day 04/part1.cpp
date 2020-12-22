/*
 * Day 4: Passport Processing (https://adventofcode.com/2020/day/4)
 * This is where things started getting interesting.
 * Multiple-line input is not overly easy to manage, and led to some minor issues.
 * Luckily, finding the tags for each value was made simple for this problem.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <vector>
#include <sstream>

using namespace std;

/** 
 * Tests a passport for validity
 * @param pass The passport data
 * @return 1 if the passport is valid, 0 otherwise
 */
int testPass(string pass) {
    // Variables:
    stringstream ss(pass); // We want to read in individual "word" while ignoring whitespace, so a stringstream is a good solution
    string val;            // The current tag/value pairing
    vector<string> tags;   // The list of tags in this passport

    // Read each tag/value pair from the passport:
    while(ss >> val) {
        // For now, we only care about the tags:
        tags.push_back(val.substr(0, 3));
    } // while
    
    // Once we have all the tags, the first step is to check how many there are:
    if(tags.size() == 7) {
        // If the are 7 tags, we have to see if the one we're missing is cid.
        cout << "Seven tags present. Checking for cid..." << endl;
        // Check each tag:
        for(string s : tags) {
            // If we find cid, then another tag must be missing, so the passport is invalid:
            if(s == "cid") {
                cout << "\tInvalid: missing tag" << endl;
                return 0;
                break;
            } // if(s...)
        } // for
        return 1;
    } // if(tags...)
    else if(tags.size() == 8) {
        // If there are 8 tags, then all tags are present and the passport is valid:
        cout << "All tags present; passport is valid" << endl;
        return 1;
    } // else if
    // If there's any other number of tags, the passport is invalid:
    cout << "Invalid: multiple tags missing" << endl;
    return 0;
} // testPass()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    string pass = ""; // The data for the current passport
    int numValid = 0; // The total count of valid passports

    while(getline(input, inputVal)) {
        // Due to some passports' data being spread acros multiple lines, we must check
        //   if the current line is more data or a break between passports.
        if(inputVal.length() == 1) {
            // This is a break between passport (the one character is the new line character).
            // Test the passport data, then reset it:
            numValid += testPass(pass);
            pass = "";
        } // if
        else {
            // There's more data for this passport, so add it on:
            pass += inputVal;
        } // else
    } // while
    input.close();

    // Since the only way we have to tell when all of a passport's data has been given is with
    //   an empty and the file may not end with one, we have to check the data we have upon
    //   reaching the end of the file for validity:
    if(pass != "") {
        numValid += testPass(pass);
    } // if

    // Print the final count:
    cout << numValid << endl;
} // main()