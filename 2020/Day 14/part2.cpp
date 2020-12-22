/*
 * Second verse pretty similar to the first, but iterating through all possible masks was not fun.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this part:
#include <cstdint>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Same as in Part 1, but adds a length parameter
 * @param length The desired length of the output string
 */
string toBinary(uint64_t val, int length = 36) {
    // cout << val;
    if(val == 0) {
        return "0";
    } // if

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

    // Pad the value to the inputted length:
    while(sval.length() < length) {
        sval += '0';
    } // while(sval...)

    string output = "";
    for(auto i = sval.rbegin(); i != sval.rend(); i++) {
        output += *i;
    } // for
    // cout << " = " << output << endl;
    return output;
} // toBinary()

/**
 * Returns a list of all adresses that match the inputted adress and mask
 * @param addr The address to mask
 * @param mask The bitmask to use
 * @return A vector of addresses
 */
vector<uint64_t> maskAddr(uint64_t addr, string mask) {
    // Convert the address to binary to allow easier bit manipulation:
    string newAddr = toBinary(addr);
    // cout << newAddr;
    // Apply the mask to each digit:
    for(int i = 0; i < mask.length(); i++) {
        if(mask[i] == '0') {
            continue;
        } // if
        newAddr[i] = mask[i];
    } // for
    // cout << " masked as " << newAddr;

    // Identify the location of each floating digit:
    vector<int> floatIs; // Stores the index of each floating digit
    int xi = -1;
    while((xi = newAddr.find('X', xi+1)) != newAddr.npos) {
        floatIs.push_back(xi);
    } // while

    // Iterate through every possible combination of floating values:
    // (Count up in binary)
    int target = pow(2, floatIs.size());
    vector<uint64_t> output;
    for(int count = 0; count < target; count++) {
        string binC = toBinary(count, floatIs.size());
        // Update each floating value:
        for(int i = 0; i < binC.length(); ++i) {
            newAddr[floatIs[i]] = binC[i];
        } // for(i)
        // cout << "\t" << newAddr << endl;
        // Push the resulting address to the vector:
        output.push_back(stol(newAddr, nullptr, 2));
    } // for(count)
    return output;
} // maskAddr()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables (same as Part 1):
    map<uint64_t, uint64_t> mem;
    string mask = "";

    while(getline(input, inputVal)) {
        // Avoid newline issues:
        if(inputVal.back() == 13) {
            inputVal.pop_back();
        } // if(...13)
        if(inputVal[1] == 'a') {
            // Update mask:
            mask = inputVal.substr(7);
            // cout << "New mask: " << mask << endl;
        } // if(...'a')
        else {
            // Get address and value from line:
            uint64_t addr = (uint64_t)stoi(inputVal.substr(4, inputVal.find("]")-4));
            uint64_t val = (uint64_t)stoi(inputVal.substr(inputVal.find("=")+2));
            // cout << "Read value: " << val << " at address " << addr << endl;
            // Get list of masked addresses:
            vector<uint64_t> maskedAddrs = maskAddr(addr, mask);
            // cout << "Placed value: " << val << endl;
            // Update the value at each address:
            for(uint64_t a : maskedAddrs) {
                mem[a] = val;
            } // for
        } // else
    } // while
    input.close();

    // Add up aal the stored values and print the result:
    long sum = 0;
    for(auto i = mem.begin(); i != mem.end(); i++) {
        sum += i->second;
    } // for
    cout << sum << endl;
} // main()