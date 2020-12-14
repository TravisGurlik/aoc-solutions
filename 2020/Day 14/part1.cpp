#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <cstdint>
#include <map>

using namespace std;

/**
 * Day 14: Docking Data (https://adventofcode.com/2020/day/14)
 * Hooray for bit manipulation (kind of).
 * This one has some complicated parts, but the overall process is fairly simple.
 */


/**
 * Converts a decimal number to binary
 * @param val The number to convert
 * @return The binary equivalent of val as a string
 */
string toBinary(uint64_t val) {
    // "Base case" - if val is 0, just return "0":
    if(val == 0) {
        return "0";
    } // if

    // Construct the binary string:
    // (The ones place in a binary value is easy to identify, so we use that and
    //  some bitshifts (or the numeric equivalent) to construct the binary string
    //  in reverse. Then, we can just reverse the string to get the correct number.)
    string sval = "";
    while(val > 0) {
        if(val % 2 == 1) {
            sval += "1";
            val--;
        } // if
        else {
            sval += "0";
        } // else
        val /= 2;
    } // while(val > 0)

    // Pad the string to the needed length:
    while(sval.length() < 36) {
        sval += '0';
    } // while(sval...)

    // Reverse the string to get the correct answer:
    string output = "";
    for(auto i = sval.rbegin(); i != sval.rend(); i++) {
        output += *i;
    } // for
    return output;
} // toBinary()

/**
 * Applies a bitmask to the given number
 * @param val The number to mask
 * @param mask The bitmask to apply
 * @return The masked value
 */
uint64_t maskVal(uint64_t val, string mask) {
    // To mask the value, we first need it in binary:
    string binVal = toBinary(val);
    // cout << val << " (" << binVal << ")";
    cout << binVal;

    // For each digit, override it with the mask value as needed:
    for(int i = 0; i < mask.length(); ++i) {
        if(mask[i] != 'X') {
            binVal[i] = mask[i];
        } // if
    } // for
    
    // Convert the binary string back to a value:
    uint64_t output = stol(binVal, nullptr, 2);
    // cout << " masked as " << output << " (" << binVal << ")" << endl;
    cout << " masked as " << binVal << endl;
    return output;
} // maskVal()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    map<uint64_t, uint64_t> mem; // Map memory addresses to their contained values
    string mask = "";            // Stores the current mask

    while(getline(input, inputVal)) {
        // I finally figured out how to neatly handle the newline character:
        if(inputVal.back() == 13) {
            inputVal.pop_back();
        } // if(...13)
        // Since we know the exact input format, we can cheat a bit to determine
        //   which action to take:
        if(inputVal[1] == 'a') {
            // Update the mask:
            mask = inputVal.substr(7);
            cout << "New mask: " << mask << endl;
        } // if(...'a')
        else {
            // Store a value:
            // Get the address and the value from the line:
            uint64_t addr = (uint64_t)stoi(inputVal.substr(4, inputVal.find("]")-4));
            uint64_t val = (uint64_t)stoi(inputVal.substr(inputVal.find("=")+2));
            // cout << "Read value: " << val << " at address " << addr << endl;
            // Mask the value:
            val = maskVal(val, mask);
            // cout << "Placed value: " << val << endl;
            // Store the masked vlaue:
            mem[addr] = val;
        } // else
    } // while
    input.close();

    // Add up the stored values and print the result:
    long sum = 0;
    for(auto i = mem.begin(); i != mem.end(); i++) {
        sum += i->second;
    } // for
    cout << sum << endl;
} // main()