#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Part 2 was even easier than Part 1.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if
    
    // Variables:
    int valid = 0,   // Total count of valid passwords
        posA,        // First position to check
        posB,        // Second position to check
        dashLoc;     // Location of dash in input row
    char target;     // The target character
    string password; // The actual password

    while(getline(input, inputVal)) {
        // Divide up the input line and set values:
        dashLoc = inputVal.find('-');
        posA = stoi(inputVal.substr(0, dashLoc));
        posB = stoi(inputVal.substr(dashLoc+1, inputVal.find(' ')-dashLoc));
        target = inputVal[inputVal.find(':')-1];
        password = inputVal.substr(inputVal.find(':')+2);

        // The password is valid if exactly one of the two positions has the target character:
        // (Remember that the passwords are 1-indexed)
        // ("Exactly one of A or B" is the same as "A XOR B", which is what ^ means)
        if(password[posA-1] == target ^ password[posB-1] == target) {
            valid++;
        } // if
    } // while
    input.close();
    
    // Print the final total:
    cout << valid << endl;
} // main()