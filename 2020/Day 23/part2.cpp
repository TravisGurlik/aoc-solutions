/*
 * This Part was super awkward to find a suitable container for.
 * A standard list proved far too slow, but a conversation with some others in the RDL
 *   got me to try out an idea I had thought of but dismissed earlier: a doubly-linked
 *   list constructed via a map.
 * Surprisingly, this was way more efficient (though it took a bit to get working right).
 *   A common mistake for me was forgetting to convert ascii character values to the
 *     corresponding int values (getting 54 from '6' instead of 6, for instance).
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    int currentL;                            // The label of our current cup
    unordered_map<int, pair<int, int>> cups; // Maps each number to a pair of the number before it and the number after it

    getline(input, inputVal);
    input.close();

    // Link the first value to the next and the last:
    cups[inputVal.front() - 48] = make_pair(1000000, inputVal[1] - 48);
    // Link all values from the input:
    for(int i = 1; i < inputVal.length() - 1; i++) {
        cups[inputVal[i] - 48] = make_pair(inputVal[i-1] - 48, inputVal[i+1] - 48);
    } // for
    // Link the last value in the input:
    cups[inputVal.back() - 48] = make_pair(inputVal[inputVal.length() - 2] - 48, 10);
    // Create and link all other values:
    for(int i = 10; i < 1000000; i++) {
        cups[i] = make_pair(i-1, i+1);
    } // for
    // Link the last value to the first:
    cups[1000000] = make_pair(999999, inputVal.front() - 48);

    // Start with the first value from the input:
    currentL = inputVal.front() - 48;
    // Do ten million turns:
    for(long turn = 0; turn < 10000000; turn++) {
        // Add a print every hundred thousand turns so we know the program's running:
        if(turn % 100000 == 0) {
            cout << "Starting turn " << turn << endl;
        } // if

        // Get the first and last values in the range to be removed:
        int first = cups[currentL].second,
            last = cups[cups[first].second].second;
        // Remove the range from the loop:
        cups[currentL].second = cups[last].second;
        cups[cups[last].second].first = currentL;

        // Determine the destination label:
        int destL = currentL - 1;
        if(destL < 1) destL = 1000000;
        while(destL == first || destL == cups[first].second || destL == last) {
            destL--;
            if(destL < 1) destL = 1000000;
        } // while
        
        // Add the removed values back into the list at the destination:
        int next = cups[destL].second; // The value that will be after the newly inserted elements
        cups[destL].second = first;
        cups[first].first = destL;
        cups[next].first = last;
        cups[last].second = next;

        // Update the current label to the next in the sequence:
        currentL = cups[currentL].second;
    } // for

    // Get our result:
    long output =  cups[1].second;
    output *= cups[output].second;

    //Print final solution:
    cout << output << endl;
} // main()