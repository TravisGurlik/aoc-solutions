/*
 * Day 18: Snailfish (https://adventofcode.com/2021/day/18)
 * Is this a bit of a mess? Kind of. But it's a *functional* mess.
 * This was honestly the easiest way I could think of to store this stuff.
 *   (Partially because I just didn't want to deal with trees.)
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * @brief Appends the numbers in a string to a vector
 * 
 * @param nums The vector to add the values to
 * @param input The string to get numbers from
 */
void appendValues(vector<int>& nums, string input) {
    // Easiest way to do this is to remove all the brackets, leaving
    //   a comma-separated list of values.
    // In retrospect, the commas could have gone too, since these are
    //   single digit numbers.
    string temp = "";
    for(char c : input) {
        if(c != '[' && c != ']') {
            temp.push_back(c);
        } // if
    } // for
    // From here, just get the values:
    for(int i = 0; i < temp.length(); i += 2) {
        nums.push_back(temp[i] - '0');
    } // for
} // appendValues()

/**
 * @brief Replaces all numbers in a string with # and returns the result
 * 
 * @param input The string to strip valeus from
 * @return string The inputted string with all digits replaced with '#'
 */
string denumber(string input) {
    int i = -1;
    while((i = input.find_first_of("0123456789")) != input.npos) {
        input[i] = '#';
    } // while
    return input;
} // denumber()

/**
 * @brief Appends two strings the snailfish way
 * 
 * @param lhs The left string
 * @param rhs The right string
 * @return string The two strings, appended as a snailfish pair
 */
string snailAdd(string lhs, string rhs) {
    return "[" + lhs + "," + rhs + "]";
} // snailAdd()

/**
 * @brief Constructs a complete snailfish number from a denumbered string and a list of values
 * 
 * @param input The denumbered snailfish string
 * @param nums The list of valeus to insert into the string
 * @return string The assembled snailfish number
 */
string makeNumber(string input, vector<int>& nums) {
    int i = -1;                 // The position in the string
    auto next = nums.begin();   // The position in the vector
    while((i = input.find("#", i+1)) != input.npos) {
        input = input.substr(0, i) + to_string(*next) + input.substr(i+1);
        next++;
    } // while
    return input;
} // makeNumber()

/**
 * @brief Prints error information for debugging
 * 
 * @param pos The position the error occurred
 * @param input The denumbered snailfish string
 * @param nums The list of values from the string
 * @param error A short message detailing what was happening when the error occurred
 */
void printError(int pos, string input, vector<int>& nums, string error) {
    cout << "Whoops, something went wrong while " << error << " at position " << pos << endl;
    cout << "Current string: " << input << endl;
    cout << "Values:" << endl;
    for(int i = 0; i < nums.size(); i++) {
        cout << "\t[" << i << "]: " << nums[i] << endl;
    } // for
    cout << "Assembled string: " << makeNumber(input, nums) << endl;
} // printError()

/**
 * @brief Recursively calculates the magnitude of a snailfish number
 * 
 * @param input The denumbered string
 * @param nums The list of values in the string
 * @param start Where to start from in the string
 * @param pos Where to strat from in the vector
 * @return int The magnitude of the number
 */
int calcMagnitude(string input, vector<int>& nums, int& start, int& pos) {
    int output = 0;
    start++; // We should have started on '[', so move to the next character
    // If it's a value, grab the right one from the vector:
    if(input[start] == '#') {
        output = nums[pos] * 3;
        pos++;
    } // if
    // If it's an open bracket, recurse:
    else if(input[start] == '[') {
        output = 3 * calcMagnitude(input, nums, start, pos);
    } // else if
    // At this point, start is at the last character of the first value
    //   (whether number of pair).
    // Move it two forward (past the ',') to the next value:
    start += 2;
    // If it's a number, get the proper one from the vector:
    if(input[start] == '#') {
        output += nums[pos] * 2;
        pos++;
    } // if
    // If it's another pair, recurse:
    else if(input[start] == '[') {
        output += 2 * calcMagnitude(input, nums, start, pos);
    } // else if
    start++; // Move start to the end of this pair
    return output;
} // calcMagnitude()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    string val;         // The denumbered string representing the snailfish number
    vector<int> nums;   // The list of values in the snailfish number
    
    // Get first line:
    getline(input, inputVal);
    inputVal.pop_back();
    val = denumber(inputVal);
    appendValues(nums, inputVal);

    // Input loop:
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        // Add the number to our current one:
        val = snailAdd(val, denumber(inputVal));
        appendValues(nums, inputVal);

        // Perform any needed reductions:
        bool done = false; // Done checking for reductions?
        while(!done) {
            done = true; // We're done unless we find something to do

            // Check for explodes:
            int depth = 0,  // The current pair depth
                pos = 0;    // The current position in the values vector
            // Loop through all characters in the number:
            for(int i = 0; i < val.length(); i++) {
                // Start of pair:
                if(val[i] == '[') {
                    depth++; // Increase depth
                    // If we're too deep, explode:
                    if(depth > 4) {
                        // Update nums (only add if there's a value to add to):
                        if(pos > 0) {
                            nums[pos-1] += nums[pos];
                        } // if
                        nums[pos] = 0;
                        if(pos < nums.size() - 2) {
                            nums[pos+2] += nums[pos+1];
                        } // if
                        nums[pos+1] = -1;
                        // Create new vector (minus the element being removed):
                        vector<int> buffer;
                        for(int n : nums) {
                            if(n >= 0) {
                                buffer.push_back(n);
                            } // if
                        } // for
                        // Check for an issue:
                        if(buffer.size() != nums.size() - 1) {
                            printError(pos, val, nums, "exploding numbers");
                            return 1;
                        } // if
                        nums = buffer; // Move buffer into main vector

                        // Update val (replace current pair with "#"):
                        val = val.substr(0, i) + "#" + val.substr(val.find("]", i)+1);
                        // Check for an issue:
                        if(val[i-1] == ']' || val[i-1] == '#' || val[i+1] == '[' || val[i+1] == '#') {
                            printError(i, val, nums, "exploding strings");
                            return 1;
                        } // if

                        done = false;   // Go again...
                        break;          // ...from the top
                    } // if(depth > 4)
                } // if(...'[')
                // End of pair:
                else if(val[i] == ']') {
                    depth--; // Decrease depth
                } // else if
                // Value split:
                else if(val[i] == ',') {
                    pos++; // Move to next value in the vector
                } // else if
            } // for(i)
            if(!done) continue; // Restart if we exploded

            // Check for splits:
            pos = 0;    // Restart from start of vector
            // Loop through string again:
            for(int i = 0; i < val.length(); i++) {
                // We only care about commas this time (and the end of the string):
                if(val[i] == ',' || i == val.length() - 1) {
                    // If the value is greater than 9, split it:
                    if(nums[pos] > 9) {
                        // Update nums (Construct new vector with the extra element):
                        vector<int> buffer;
                        for(int vi = 0; vi < nums.size(); vi++) {
                            if(vi == pos) {
                                buffer.push_back(nums[vi] / 2);
                                buffer.push_back(nums[vi] / 2 + (nums[vi] % 2));
                            } // if
                            else {
                                buffer.push_back(nums[vi]);
                            } // else
                        } // for(vi)
                        // Check for an issue:
                        if(buffer.size() != nums.size() + 1) {
                            printError(pos, val, nums, "splitting numbers");
                            return 1;
                        } // if
                        nums = buffer; // Move buffer into main vector

                        // Update val (replace value with a pair):
                        while(val[i] != '#') i--; // Move backwards until we're on the value
                        val = val.substr(0, i) + "[#,#]" + val.substr(i+1);
                        // Check for an issue:
                        if(val[i-1] == ']' || val[i-1] == '#' || val[i+5] == '[' || val[i+5] == '#') {
                            printError(i, val, nums, "splitting strings");
                            return 1;
                        } // if

                        done = false;   // Do it again...
                        break;          // ...from the top
                    } // if(...> 9)
                    pos++; // Increment the position
                } // if(...- 1)
            } // for(i)
        } // while(!done)
    } // while(getline...)
    input.close();

    //Print final solution:
    int start = 0,
        pos = 0;
    cout << calcMagnitude(val, nums, start, pos) << endl;
} // main()