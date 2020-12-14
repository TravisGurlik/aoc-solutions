#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

/**
 * Surprise! Hope you know number theory!
 * Knowing what Chinese Remainder Theorem is and how it works is extremelly useful for this Part.
 * Luckily for me, I had taken a number theory class just the previous semester to this.
 * That doesn't mean I was able to implement everything properly right away, though;
 *   I ended up using x = i (mod m) instead of x = -i (mod m) and was quite confused at how
 *   I was getting the same answer no matetr how I calculated it but was still wrong.
 * By the way, I hope you're prepared to wait some 6 billion years for this to happen.
 */


/**
 * Finds the inverse of n modulo m
 * @param n The number to find the inverse of
 * @param m The modulo to use
 * @return The inverse of n modulo m (n^(-1) (mod m))
 */
long modularInverse(long n, long m) {
    // Get n into the proper range:
    n %= m;
    // Brute force our way to the inverse:
    for(long i = 1; i < m; ++i) {
        if((i * n) % m == 1) {
            return i;
        } // if
    } // for
    // n does not have an inverse mod m:
    return -1;
} // modularInverse()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Once again, we can get both lines individually:
    // (We can just ignore the first one this time, though)
    getline(input, inputVal);
    vector<long> departs;
    getline(input, inputVal);
    input.close();

    // Variables (same as Part 1):
    int lastIndex = -1,
        nextIndex = 0;
    nextIndex = inputVal.find(",");

    // Get each ID (same as Part 1):
    while(nextIndex != inputVal.npos) {
        string val = inputVal.substr(lastIndex+1, nextIndex - lastIndex - 1);
        if(val != "x") {
            departs.push_back(stol(val));
        }
        else {
            departs.push_back(-1);
        }
        lastIndex = nextIndex;
        nextIndex = inputVal.find(",", nextIndex+1);
    }

    // Get last index (same as Part 1):
    string val = inputVal.substr(lastIndex+1);
    if(val != "x") {
        departs.push_back(stol(val));
    }

    // Map each ID to its index:
    vector<pair<int, int>> vals;
    for(int i = 0; i < departs.size(); ++i) {
        if(departs[i] != -1) {
            int val = -i;
            while(val < 0) val += departs[i];
            vals.push_back(make_pair(departs[i], val));
        } // if
    } // for

    // Determine the overall modulus to use with CRT:
    long modulus = 1;
    for(pair<int, int> n : vals) {
        modulus *= n.first;
    }
    cout << modulus << endl << endl;

    // Use CRT to get our answer:
    // (sum(a*b*bi) (mod M) where...
    //   a  = index
    //   M  = modulus from above
    //   b  = M/ID
    //   bi = b^(-1) (mod ID)
    //   ID = ID of the bus)
    long result = 0;
    for(auto i = vals.begin(); i != vals.end(); ++i) {
        long b = modulus / i->first;
        long bi = modularInverse(b, i->first);
        result += (i->second * b * bi) % modulus;
        result %= modulus;
    } // for

    // Print the final result:
    cout << result << endl;
} // main()