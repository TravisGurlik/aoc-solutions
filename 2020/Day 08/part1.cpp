#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * Day 8: Handheld Halting (https://adventofcode.com/2020/day/8)
 * This assembly language is even easier than the one we used in EECS 370.
 * Finding a loop isn't too tricky; just store which instructions have already been run.
 * I used a boolean vector because it was smaller and easier to check than a list of run instructions.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    int acc     = 0,    // The current accumulator value.
        pointer = 0;    // The current program pointer (the line number of the next instruction)
    vector<string> ops; // The list of instructions

    // Since we might jump around a bit, we want to get all of the instructions before
    //   trying to run anything:
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        ops.push_back(inputVal);
    } // while
    input.close();

    // Construct a boolean vector with the same length as the instructions list,
    //   and initialize each value to false:
    vector<bool> run(ops.size(), false);
    // Run the program until it loops:
    while(true) {
        // Update run lsit and divide up instruction:
        run[pointer] = true;
        string op = ops[pointer].substr(0, 3);
        string val = ops[pointer].substr(4);

        // Run instruction:
        if(op == "nop") {
            // Do nothing & move to the next instruction:
            pointer++;
        } // if(..."nop")
        else if(op == "acc") {
            // Update accumulator and move ot next instruction:
            acc += stoi(val);
            pointer++;
        } // else if(..."acc")
        else if(op == "jmp") {
            // Update pointer:
            pointer += stoi(val);
        } // else if(..."jmp")
        if(run[pointer] == true) {
            // If the next instruction has been run already, we just entered a loop:
            break;
        } // if(run...)
    } // while

    // Print the current accumulator value:
    cout << acc << endl;
} // main()