#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int testPass(string passport) {
    stringstream ss(passport);
    string in, field, value, extra;
    int num, numFields = 0, pos;
    while(ss >> in) {
        numFields++;
        field = in.substr(0, 3);
        value = in.substr(4);
        if(field == "cid") {
            numFields--;
            continue;
        }
        else if(field == "byr") {
            if(value.length() != 4) {
                return 0;
            }
            else {
                num = stoi(value);
                if(num < 1920 || num > 2002) {
                    return 0;
                }
            }
        }
        else if(field == "iyr") {
            if(value.length() != 4) {
                return 0;
            }
            else {
                num = stoi(value);
                if(num < 2010 || num > 2020) {
                    return 0;
                }
            }
        }
        else if(field == "eyr") {
            if(value.length() != 4) {
                return 0;
            }
            else {
                num = stoi(value);
                if(num < 2020 || num > 2030) {
                    return 0;
                }
            }
        }
        else if(field == "hgt") {
            pos = value.find_first_of("ic");
            if(pos == value.npos) {
                return 0;
            }
            num = stoi(value.substr(0, pos));
            extra = value.substr(pos);
            if(extra == "cm") {
                if(num < 150 || num > 193) {
                    return 0;
                }
            }
            else if(extra == "in") {
                if(num < 59 || num > 76) {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        else if(field == "hcl") {
            if(value.length() != 7 || value[0] != '#') {
                return 0;
            }
            pos = value.find_first_not_of("1234567890abcdef", 1);
            if(pos != value.npos) {
                return 0;
            }
        }
        else if(field == "ecl") {
            if(value != "amb" && value != "blu" && value != "brn" && value != "gry" && value != "grn" && value != "hzl" && value != "oth") {
                return 0;
            }
        }
        else if(field == "pid") {
            if(value.length() != 9) {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    if(numFields != 7) {
        return 0;
    }
    return 1;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    string pass = "";
    int numValid = 0, testResult;
    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            testResult = testPass(pass);
            cout << testResult << endl;
            numValid += testResult;
            pass = "";
        }
        else {
            pass += inputVal;
        }
    }
    if(pass != "") {
        testResult = testPass(pass);
        cout << testResult << endl;
        numValid += testResult;
    }
    cout << numValid << endl;
    input.close();
}