#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <sstream>
#include <list>

using namespace std;

/**
 * New math. New-hoo-hoo math.
 * The only difference between this Part and the last is in the actual evaluation.
 */

/**
 * Evaluates an Advanced New Math expression.
 * @param expression The ANM expression to evaluate
 * @return The result of evaluating the expression
 */
long eval(string expression) {
    if(expression.find(" ") == expression.npos) {
        return stol(expression);
    } // if

    // Parenthetical variables:
    int parenA, parenB;      // The indexes of the first 2 parenthesis in the expression
    string subA, subB, subC; // Various substrings (for stitching things back togetehr after evaluation)

    while((parenA = expression.find_first_of("()")) != expression.npos) {
        parenB = expression.find_first_of("()", parenA + 1);
        while(parenB != expression.npos && expression[parenB] != ')') {
            parenA = parenB;
            parenB = expression.find_first_of("()", parenA + 1);
        } // while(parenB...)

        subA = expression.substr(0, parenA);
        subB = expression.substr(parenA + 1, parenB - parenA - 1);
        subC = expression.substr(parenB + 1);

        expression = subA + to_string(eval(subB)) + subC;
    } // while(parenA...)

    // Evaluation variables:
    istringstream readEx(expression);   // Stringstream for reading the expression
    list<long> nums;                    // The list of numbers in the expression
    long val,                           // Used for temporary result storage
         result = 1;                    // The final result of the expression
    
    // Read the first value of the expression:
    readEx >> subA;
    nums.push_back(stol(subA));

    // Read each operator & value pair and Do Math:
    while(readEx >> subB >> subA) {
        if(subB == "+") {
            // For addition, add the current number to the last one, then replace
            //   the last value in the list with the result:
            val = nums.back() + stol(subA);
            nums.pop_back();
            nums.push_back(val);
        } // if
        else {
            // For multiplication, just add the value to the list for now:
            nums.push_back(stol(subA));
        } // else
    } // while

    // All that's left to do is multiplication, so multiply each remaing value together:
    for(long n : nums) {
        result *= n;
    } // for
    
    // Return the result:
    return result;
} // eval()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    long result = 0; // The sum of all results

    while(getline(input, inputVal)) {
        inputVal.pop_back();
        result += eval(inputVal);
    } // while
    input.close();

    //Print final solution:
    cout << result << endl;
} // main()