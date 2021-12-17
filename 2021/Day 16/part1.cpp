/*
 * Day 16: Packet Decoder (https://adventofcode.com/2021/day/16)
 * This day was basically a cross between a project I did in one of my college classes
 *   and the project I did during my internship with Ford AV.
 * It took me a bit to figure out how to handle the subpacckets, but I eventually
 *   landed on my ol' go to of recursion.
 */

#include <iostream>
#include <fstream>
#include <string>

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
        } // switch
    } // for
    return output;
} // string2Binary()

/**
 * @brief Parses a single packet from the input string
 * 
 * @param input The transmission as a binary string
 * @param index The starting index for this packet
 * @return int The total of all packet versions within this packet
 */
int parseOnePacket(string& input, int& index) {
    // Get packet version:
    int versionTotal = stoi(input.substr(index, 3), 0, 2);
    index += 3;

    // Get packet type:
    int type = stoi(input.substr(index, 3), 0, 2);
    index += 3;
    
    // Literal value:
    if(type == 4) {
        for(; input[index] != '0'; index += 5); // "Read" literal value
        index += 5;
    } // if
    // Everything else:
    else {
        // Get input type:
        bool inputType = input[index] == '1';
        index++;
        // Packet count:
        if(inputType) {
            // Get packet count:
            int numPackets = stoi(input.substr(index, 11), 0, 2);
            index += 11;
            // Get values from each packet:
            for(int countPackets = 0; countPackets < numPackets; countPackets++) {
                versionTotal += parseOnePacket(input, index);
            } // for
        } // if
        // Lengths of packets:
        else {
            // Get the length of all subpackets:
            int packetLength = stoi(input.substr(index, 15), 0, 2);
            index += 15;
            int startPos = index; // Save the starting index for later comparison
            // Get values from each packet:
            while(index < packetLength + startPos - 1) {
                versionTotal += parseOnePacket(input, index);
            } // while
        } // else
    } // else
    return versionTotal;
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

    // Convert input from hex to binary:
    inputVal = string2Binary(inputVal);
    int index = 0;

    //Print final solution:
    cout << parseOnePacket(inputVal, index) << endl;
} // main()