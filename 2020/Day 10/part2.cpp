#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Ordering adpaters isn't that difficult thanks to Dynamic Programming.
 * I did, however, lock up on how exactly to combine the subsolutions.
 * The first part (variables, reading, and sorting) is the same as Part 1.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if
    
    vector<int> adapts;
    adapts.push_back(0);
    
    while(getline(input, inputVal)) {
        adapts.push_back(stoi(inputVal));
    } // while
    input.close();

    sort(adapts.begin(), adapts.end());
    adapts.push_back(adapts.back() + 3);

    // Another variable:
    vector<long> arranges(adapts.size(), 0); // The number of arrangements ending in each adapter
    arranges[0] = 1;                         // There is one way to arrange {0}

    // For each adapter, check the 3 before it. If they are within 3 jolts of this one, add
    //   the number of arrangements ending in that adapter to this one.
    for(int i = 1; i < adapts.size(); i++) {
        for(int j = i-1; j > -1 && j > i - 4; j--) {
            // Minor optimization: once an adapter is more than 3 jolts less than the current
            //   one, we're done with this adapter:
            if(adapts[j] < adapts[i] - 3) {
                break;
            } // if
            arranges[i] += arranges[j];
        } // for(j)
    } // for(i)

    // Print the final value:
    cout << arranges.back() << endl;
} // main()