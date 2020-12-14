#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    vector<string> ops;
    while(getline(input, inputVal)) {
        ops.push_back(inputVal);
    }
    input.close();
    int lastChanged = 0, acc = 0, pointer = 0;
    while(lastChanged < ops.size()) {
        pointer = 0;
        acc = 0;
        while(ops[lastChanged].substr(0, 3) == "acc") lastChanged++;
        if(ops[lastChanged].substr(0, 3) == "nop") ops[lastChanged] = "jmp" + ops[lastChanged].substr(3);
        else ops[lastChanged] = "nop" + ops[lastChanged].substr(3);
        cout << "New start. Changed line " << lastChanged << endl;
        vector<bool> run(ops.size(), false);
        while(pointer < ops.size()) {
            run[pointer] = true;
            string op = ops[pointer].substr(0, 3);
            string val = ops[pointer].substr(4);
            if(op == "nop") {
                pointer++;
            }
            else if(op == "acc") {
                cout << "\tops[" << pointer << "] = " << ops[pointer] << endl;
                acc += stoi(val);
                cout << "\tacc = " << acc << endl;
                pointer++;
            }
            else if(op == "jmp") {
                cout << "\tops[" << pointer << "] = " << ops[pointer] << endl;
                pointer += stoi(val);
            }
            if(run[pointer] == true) {
                break;
            }
        }
        if(pointer == ops.size()) break;
        if(ops[lastChanged].substr(0, 3) == "nop") ops[lastChanged] = "jmp" + ops[lastChanged].substr(3);
        else ops[lastChanged] = "nop" + ops[lastChanged].substr(3);
        lastChanged++;
    }
    if(lastChanged == ops.size()) {
        cout << "Failure" << endl;
        return 1;
    }
    cout << acc << endl;
}