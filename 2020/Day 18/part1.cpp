/*
 * Day 18: Operation Order (https://adventofcode.com/2020/day/18)
 * I distinctly remember solving a problem that required parsing parenthesis before,
 *   but I can't remember how I did it.
 * This solution basically finds the first ')' and the last '(' before it, evaluates
 *   the expression between them, then stitches the answer in place of the parenthetical
 *   into the original expression, then repeats.
 * Actual evaluation is done left to right, so we can jsut read each operator and
 *   value in and Do Math without worrying about anything else.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <sstream>

using namespace std;

/**
 * Evaluates a "New Math" expression
 * @param expression The expression to evaluate
 * @return The numeric result of evaluating the expression
 */
long eval(string expression) {
    // Base case - the expression is just a number:
    if(expression.find(" ") == expression.npos) {
        return stol(expression);
    } // if

    // Parenthetical variables:
    int parenA, parenB;      // The indexes of the first 2 parenthesis in the expression
    string subA, subB, subC; // Various substrings (for stitching things back togetehr after evaluation)

    // Find and evaluate each parenthetical in the expression:
    while((parenA = expression.find_first_of("()")) != expression.npos) {
        // Find the first ')' to find the first innermost parenthetical:
        parenB = expression.find_first_of("()", parenA + 1);
        while(parenB != expression.npos && expression[parenB] != ')') {
            parenA = parenB;
            parenB = expression.find_first_of("()", parenA + 1);
        } // while(parenB...)

        // Split the expression around the parenthetical:
        subA = expression.substr(0, parenA);
        subB = expression.substr(parenA + 1, parenB - parenA - 1);
        subC = expression.substr(parenB + 1);

        // Evaluate the parenthetical and stitch it back into the expression:
        expression = subA + to_string(eval(subB)) + subC;
    } // while(parenA...)

    // Evaluation variables:
    istringstream readEx(expression); // Stringstream for reading the expression
    long val;                         // The evaluation result

    // Read the first value:
    readEx >> subA;
    // Read each operation & value pair and Do Math:
    while(readEx >> subB >> subC) {
        if(subB == "+") {
            val += stol(subC);
        } // if
        else {
            val *= stol(subC);
        } // else
    } // while

    return val;
} // eval()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    long result = 0; // The sum of all evaluation results

    while(getline(input, inputVal)) {
        // Remove the newline:
        inputVal.pop_back();

        // Evaluate the expression and add the result to the total:
        result += eval(inputVal);
    } // while
    input.close();

    //Print final solution:
    cout << result << endl;
} // main()