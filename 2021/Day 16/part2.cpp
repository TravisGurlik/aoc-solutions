/*
 * Oh boy, time to actually care about values.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * @brief Converts a hexadecimal input string to a binary string
 * 
 * @param input A string containing the hexadecimal representation of a number
 * @return string The binary representation of the input number
 */
string string2Binary(string input) {
    string output = "";
    for(char c : input) {
        switch(c) {
            case '0':
                output += "0000";
                break;
            case '1':
                output += "0001";
                break;
            case '2':
                output += "0010";
                break;
            case '3':
                output += "0011";
                break;
            case '4':
                output += "0100";
                break;
            case '5':
                output += "0101";
                break;
            case '6':
                output += "0110";
                break;
            case '7':
                output += "0111";
                break;
            case '8':
                output += "1000";
                break;
            case '9':
                output += "1001";
                break;
            case 'A':
                output += "1010";
                break;
            case 'B':
                output += "1011";
                break;
            case 'C':
                output += "1100";
                break;
            case 'D':
                output += "1101";
                break;
            case 'E':
                output += "1110";
                break;
            case 'F':
                output += "1111";
                break;
        }
    }
    return output;
} // string2Binary()

/**
 * @brief Parses a single packet from the input string
 * 
 * @param input The transmission as a binary string
 * @param index The starting index for this packet
 * @return long The resulting value from parsing this packet
 */
long parseOnePacket(string& input, int& index) {
    index += 3; // Toss the version number

    // Get the type:
    int type = stol(input.substr(index, 3), nullptr, 2);
    index += 3;

    // Literal value:
    if(type == 4) {
        string val = ""; // Saves the actual data as we go
        for(; input[index] != '0'; index += 5) {
            val += input.substr(index+1, 4);
        } // for
        val += input.substr(index+1, 4);
        index += 5;
        return stol(val, nullptr, 2);
    } // if

    // For everything else, we need to get the subvalues:
    vector<long> values;                    // The list of values from the subpackets
    bool inputType = input[index] == '1';   // The input type of the packet
    index++;
    // Packet count:
    if(inputType) {
        int numPackets = stoi(input.substr(index, 11), nullptr, 2);
        index += 11;
        for(int countPackets = 0; countPackets < numPackets; countPackets++) {
            values.push_back(parseOnePacket(input, index));
        } // for
    } // if
    // Length of subpackets:
    else {
        int packetLength = stoi(input.substr(index, 15), nullptr, 2);
        index += 15;
        int startPos = index;
        while(index < packetLength + startPos - 1) {
            values.push_back(parseOnePacket(input, index));
        } // while
    } // else
    
    // Determine result based on packet type:
    long result;
    switch(type) {
        case 0: // Sum
            result = 0;
            for(long v : values) {
                result += v;
            } // for
            return result;
        case 1: // Product
            result = 1;
            for(long v : values) {
                result *= v;
            } // for
            return result;
        case 2: // Minimum
            return *(min_element(values.begin(), values.end()));
        case 3: // Maximum
            return *(max_element(values.begin(), values.end()));
        case 5: // Greater than
            return values[0] > values[1] ? 1 : 0;
        case 6: // Less than
            return values[0] < values[1] ? 1 : 0;
        case 7: // Equal to
            return values[0] == values[1] ? 1 : 0;
    } // switch
    // If we're here, we apparently broke binary or something:
    return numeric_limits<long>::min();
} // parseOnePacket()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if
    
    // Input:
    getline(input, inputVal);
    input.close();

    inputVal = string2Binary(inputVal);
    int index = 0;

    //Print final solution:
    cout << parseOnePacket(inputVal, index) << endl;
} // main()