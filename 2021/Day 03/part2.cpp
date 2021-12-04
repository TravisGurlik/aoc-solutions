/*
 * This is one of those parts where you misread the instructions a couple times,
 *   then you have to make a few attempts as you make tiny changes that
 *   inexplicably give you different answers despite you thinking they should
 *   be identical.
 * We actually save the values this time, then do separate loops for each final
 *   value search, whittling down our options position by position.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<string> values; // The values read from the input

    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back();        // Get rid of the newline
        values.push_back(inputVal); // Save the value
    } // while
    input.close();

    // More variables:
    vector<string> buffer;          // A buffer for saving our next set of values while still looping
    int digit = 0;                  // What position we're currently checking
    vector<string> oxygen(values);  // Our list of valid values for the oxygen reading
    vector<string> co2(values);     // Our list of valid values for the CO2 reading

    // Find the oxygen reading (continue unitl there's one value left):
    while(oxygen.size() > 1) {
        int count = 0; // Reset the counter
        // For the current digit, count if there are more 1s (positive) or 0s (negative):
        for(string s : oxygen) {
            if(s[digit] == '1') {
                count++;
            } // if
            else {
                count--;
            } // else
        } // for

        char target = count >= 0 ? '1' : '0'; // Determine which digit was more plentiful (1s win ties)

        buffer.clear(); // Reset the buffer
        // For each value in the vector, add it to the buffer if it matches the target:
        for(string s : oxygen) {
            if(s[digit] == target) {
                buffer.push_back(s);
            } // if
        } // for
        oxygen = buffer; // Swap the buffer into the list of potential oxygen values
        
        ++digit; // Move to the next position
    } // while

    digit = 0; // Reset the position
    // Find the CO2 reading (basically the same process as above):
    while(co2.size() > 1) {
        int count = 0;
        for(string s : co2) {
            if(s[digit] == '1') {
                count++;
            } // if
            else {
                count--;
            } // else
        } // for

        char target = count < 0 ? '1' : '0'; // Determine which digit was less plentiful (0s win ties)

        buffer.clear();
        for(string s : co2) {
            if(s[digit] == target) {
                buffer.push_back(s);
            } // if
        } // for
        co2 = buffer;

        ++digit;
    } // while

    //Print final solution:
    cout << "Oxygen:  " << oxygen[0] << endl;
    cout << "CO2:     " << co2[0] << endl;
    cout << "Product: " << stoi(oxygen[0], nullptr, 2) * stoi(co2[0], nullptr, 2) << endl;
} // main()