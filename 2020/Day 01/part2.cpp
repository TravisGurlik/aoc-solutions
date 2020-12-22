/*
 * Part 2 was a little bit harder ot optimize.
 * Since we're now checking 3 values, we could no longer use the same method as before.
 * I resorted to brute force for this part, but I attempted to optimize it where I could:
 *  - The list is still sorted so values can be considering in increasing order.
 *  - Loops are broken out of as soon as the sum gets too large.
 */

#include <algorithm>
#include <iostream>
#include <fstream>
// Additional libraries for this part:
#include <vector>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<int> expenses;

    while(getline(input, inputVal)) {
        // Once again, we can jsut add the numeric equivalent of each line to our vector:
        expenses.push_back(stoi(inputVal));
    } // while
    input.close();

    // Sort the vector:
    sort(expenses.begin(), expenses.end());

    // Loop through all possible combinations, starting with the smallest:
    for(auto low = expenses.begin(); low != expenses.begin()+(expenses.size()-2); low++) {
        for(auto mid = low+1; mid != expenses.begin()+(expenses.size()-1); mid++) {
            // If the first possible sum is too high, skip to increasing the smallest value:
            if(*low + *mid + *(mid+1) > 2020) break;
            for(auto high = mid+1; high != expenses.end(); high++) {
                // Calculate the sum of the values and compare it against our target:
                int sum = *low + *mid + *high;
                // If the sum is too high, increase the middle value:
                if(sum > 2020) break;
                // If the sum matches the target, print the product of the values:
                else if(sum == 2020) {
                    cout << (*low * *mid * *high) << endl;
                    return 0;
                } // else if
            } // for(high)
        } // for(mid)
    } // for(low)
    // If the program reaches this point, no valid set was found:
    cout << "No set found" << endl;
    return 0;
} // main()