/*
 * Day 25: Combo Breaker (https://adventofcode.com/2020/day/25)
 * Thanks to my experience with cryptography and number theory, I managed to
 *   misread the last part of the puzzle and lose precious minutes figuring
 *   out where i went wrong.
 * Otherwisse, this was fairly straightforward.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Performs a transformation on a subject number per the encryption rules
 * @param sub The subject number
 * @param loop The loop value
 * @return The encoded value
 */
long transform(long sub, long loop) {
    long output = 1; // Start at 1
    // Loop [loop] times:
    for(long i = 0; i < loop; i++) {
        output *= sub;
        output %= 20201227;
    } // for
    return output;
} // transform()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    long pub1,      // The first public key
         pub2;      // The second public key
    int loop1 = -1, // The first loop value
        loop2 = -1; // The second loop value

    // There only two values, so we don't need a loop:
    getline(input, inputVal);
    pub1 = stol(inputVal);
    getline(input, inputVal);
    pub2 = stol(inputVal);
    input.close();

    // Start from 1 and start encoding until we get something that matches:
    long val = 1;
    for(long n = 1; loop1 == -1 || loop2 == -1; n++) {
        val *= 7;
        val %= 20201227;
        if(loop1 == -1 && val == pub1) {
            // The value matches the first public key:
            loop1 = n;
        } // if(loop1...)
        if(loop2 == -1 && val == pub2) {
            // The value matches the second public key:
            loop2 = n;
        } // if(loop2...)
    } // for

    //Print final solution:
    cout << "Key = " << transform(pub1, loop2) << endl;
} // main()