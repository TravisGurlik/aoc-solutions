#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    int acc = 0, pointer = 0;
    vector<string> ops;
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        ops.push_back(inputVal);
    }
    input.close();
    vector<bool> run(ops.size(), false);
    while(true) {
        run[pointer] = true;
        string op = ops[pointer].substr(0, 3);
        string val = ops[pointer].substr(4);
        if(op == "nop") {
            pointer++;
        }
        else if(op == "acc") {
            acc += stoi(val);
            pointer++;
        }
        else if(op == "jmp") {
            pointer += stoi(val);
        }
        if(run[pointer] == true) {
            break;
        }
    }
    cout << acc << endl;
}