/*
 * Detecting a loop is easy. Fixing a loop is not.
 * Elegant solutions eluded me, so I used brute force again.
 * This does essentially the same thing as Part 1, but adds some extra steps.
 * My main sticking point here was forgetting to switch the changed command back to what
 *   it was initially upon failing to avoid the loop.
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

    // Variables (same as Part 1):
    vector<string> ops;

    // Just like in Part 1, we want to get our full set of instructions before proceeding:
    while(getline(input, inputVal)) {
        ops.push_back(inputVal);
    }
    input.close();

    // More variables (acc and pointer same as Part 1):
    int lastChanged = 0, // The line number of the last instruction that was changed
        acc         = 0,
        pointer     = 0;
    
    // Loop until there are no more instructions to change (or the loop is fixed):
    while(lastChanged < ops.size()) {
        // Reset variables:
        pointer = 0;
        acc = 0;

        // Increment lastChanged until a changeable instruction is found:
        while(ops[lastChanged].substr(0, 3) == "acc") lastChanged++;
        // Change the instruction:
        if(ops[lastChanged].substr(0, 3) == "nop") ops[lastChanged] = "jmp" + ops[lastChanged].substr(3);
        else ops[lastChanged] = "nop" + ops[lastChanged].substr(3);
        cout << "New start. Changed line " << lastChanged << endl;

        // Create our loop detecting vector:
        vector<bool> run(ops.size(), false);
        // Execute the program until it finishes or loops (contents are the same as Part 1):
        while(pointer < ops.size()) {
            run[pointer] = true;
            string op = ops[pointer].substr(0, 3);
            string val = ops[pointer].substr(4);
            if(op == "nop") {
                pointer++;
            } // if(..."nop")
            else if(op == "acc") {
                cout << "\tops[" << pointer << "] = " << ops[pointer] << endl;
                acc += stoi(val);
                cout << "\tacc = " << acc << endl;
                pointer++;
            } // else if(..."acc")
            else if(op == "jmp") {
                cout << "\tops[" << pointer << "] = " << ops[pointer] << endl;
                pointer += stoi(val);
            } // else if(..."jmp")
            if(run[pointer] == true) {
                break;
            } // if(run...)
        } // while(pointer...)

        // If the program finished, we're done:
        if(pointer == ops.size()) break;

        // Otherwise, reset the changed instruction:
        if(ops[lastChanged].substr(0, 3) == "nop") ops[lastChanged] = "jmp" + ops[lastChanged].substr(3);
        else ops[lastChanged] = "nop" + ops[lastChanged].substr(3);

        // Increment tot he next instruction:
        lastChanged++;
    } // while(lastChanged...)

    // If the program was not fixed, say so:
    if(lastChanged == ops.size()) {
        cout << "Failure" << endl;
        return 1;
    } // if
    // Otherwise, print the final accumulator value:
    cout << acc << endl;
} // main()