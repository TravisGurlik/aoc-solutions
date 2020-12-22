/*
 * This is the first Part 2 that doesn't resuse the previous Part's code.
 * I already had my value (and allowing for command line input would have taken a little bit),
 *   so the target value is simply hardcoded in.
 * Since the ordering of the numbers needed to be preserved, I once again had to resort to brute force.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    const long TARGET = 85848519; // The target sum
    vector<long> vals;            // The list of values

    while(getline(input, inputVal)) {
        // No need to do anything fancy this time, just add the values to the vector:
        vals.push_back(stol(inputVal));
    } // while
    input.close();

    // Iterate through all possible starting values:
    // (This structure was designed to ensure at least 2 values were added together)
    for(int i = 0; vals[i] != TARGET; ++i) {
        long sum = vals[i];
        // Keep adding numbers until the sum reaches the target:
        // (j is defined outside the loop so it can be used for the final calculation)
        int j = i + 1;
        for(; sum < TARGET; ++j) {
            sum += vals[j];
        } // for(j)
        // Check if the sum is exactly the target:
        if(sum == TARGET) {
            // Get the range of values:
            vector<long> range(vals.begin() + i, vals.begin() + j);
            // To avoid messing with iterators, jsut sort the list and pull out the
            //   front and back values:
            sort(range.begin(), range.end());
            cout << range.front() + range.back() << endl;
            return 0;
        } // if
    } // for(i)

    // No range was found that added to the target:
    cout << "No valid range found" << endl;
}