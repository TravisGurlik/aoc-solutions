/*
 * There isn't really an easy way to verify a bunch of different fields with different rules.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <sstream>

using namespace std;

/**
 * Tests a passport's data for validity
 * @param passport The passport data to check
 * @return 1 if the passport is valid, 0 otherwise
 */
int testPass(string passport) {
    // Variables:
    stringstream ss(passport);  // Once again, a stringstream is a good way to read each field
    string in,                  // The current tag/value pair
           field,               // The tag
           value,               // The value
           extra;               // An extra info for the value (ie. "in" or "cm")
    int num,                    // The numeric equivalent of value
        numFields = 0,          // The total number of fields int he passport
        pos;                    // The index of certain characters in the value

    // Loop through each tag/value pair; for each, exit with a 0 if it's invalid:
    while(ss >> in) {
        // Update variables:
        numFields++;
        field = in.substr(0, 3);
        value = in.substr(4);
        
        // Country ID:
        if(field == "cid") {
            // We don't care about this field, so don't even count it:
            numFields--;
            continue;
        } // if(..."cid")
        // Birth Year:
        else if(field == "byr") {
            // Verify value length:
            if(value.length() != 4) {
                return 0;
            } // if(value...)
            else {
                // Verify value in range [1920, 2002]:
                num = stoi(value);
                if(num < 1920 || num > 2002) {
                    return 0;
                } // if(num...)
            } // else
        } // else if(..."byr")
        // Issue Year:
        else if(field == "iyr") {
            // Verify value length:
            if(value.length() != 4) {
                return 0;
            } // if(value...)
            else {
                // Verify value in range [2010, 2020]:
                num = stoi(value);
                if(num < 2010 || num > 2020) {
                    return 0;
                } // if(num...)
            } // else
        } // else if(..."iyr")
        // Expiration Year:
        else if(field == "eyr") {
            // Verify value length:
            if(value.length() != 4) {
                return 0;
            } // if(value...)
            else {
                // Verify value in range [2020, 2030]:
                num = stoi(value);
                if(num < 2020 || num > 2030) {
                    return 0;
                } // if(num...)
            } // else
        } // else if(..."eyr")
        // Height:
        else if(field == "hgt") {
            // Verify that "in" or "cm" is present:
            pos = value.find_first_of("ic");
            if(pos == value.npos) {
                return 0;
            } // if(pos...)

            // Get numeric value and units:
            num = stoi(value.substr(0, pos));
            extra = value.substr(pos);

            // Test value for appropriate range:
            if(extra == "cm") {
                // Verify value in range [150, 193]:
                if(num < 150 || num > 193) {
                    return 0;
                } // if(num...)
            } // if(extra...)
            else if(extra == "in") {
                // Verify value in range [59, 76]:
                if(num < 59 || num > 76) {
                    return 0;
                } // if(num...)
            } // else if(extra...)
            else {
                // Unit is invalid, so the passport is too:
                return 0;
            } // else
        } // else if(..."hgt")
        // Hair Color:
        else if(field == "hcl") {
            // Verify value length and initial character:
            if(value.length() != 7 || value[0] != '#') {
                return 0;
            } // if(value...)
            // Verify value contains only hexadecimal characters:
            pos = value.find_first_not_of("1234567890abcdef", 1);
            if(pos != value.npos) {
                return 0;
            } // if(pos...)
        } // else if(..."hcl")
        // Eye Color:
        else if(field == "ecl") {
            // Verify value is an allowed valueL
            if(value != "amb" && value != "blu" && value != "brn" && value != "gry" && value != "grn" && value != "hzl" && value != "oth") {
                return 0;
            } // if(value...)
        } // else if(..."ecl")
        // Passport ID:
        else if(field == "pid") {
            // Verify value length:
            // (This does not ensure the vlaue is a number, but eveidently it didn't need to)
            if(value.length() != 9) {
                return 0;
            } // if(value...)
        } // else if(..."pid")
        // Tag is invalid, so the passport is too:
        else {
            return 0;
        } // else
    } // while

    // Verify that every tag is present (cid doesn't matter and isn't counted):
    if(numFields != 7) {
        return 0;
    } // if

    // The passport has not been found to be invalid, so it is valid:
    return 1;
} // testPass()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    string pass  = "";  // The passport data
    int numValid = 0,   // The total number of valid passports
        testResult;     // The result of the possport verification (for debugging purposes)
    
    while(getline(input, inputVal)) {
        // As before, check the input length to determine if there's more data or not:
        if(inputVal.length() == 1) {
            // Test the passport data, increment the counter if needed, and reset the passport data:
            testResult = testPass(pass);
            cout << testResult << endl;
            numValid += testResult;
            pass = "";
        } // if
        else {
            // There's more data to add to this pasport:
            pass += inputVal;
        } // else
    } // while
    input.close();

    // Check data of final passport:
    if(pass != "") {
        testResult = testPass(pass);
        cout << testResult << endl;
        numValid += testResult;
    } // if

    // Print final total:
    cout << numValid << endl;
} // main()