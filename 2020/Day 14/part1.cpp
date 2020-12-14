#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <map>

using namespace std;

string toBinary(uint64_t val) {
    if(val == 0) {
        return "0";
    }
    string sval = "";
    while(val > 0) {
        if(val % 2 == 1) {
            sval += "1";
            val--;
        }
        else {
            sval += "0";
        }
        val /= 2;
    }
    while(sval.length() < 36) {
        sval += '0';
    }
    string output = "";
    for(auto i = sval.rbegin(); i != sval.rend(); i++) {
        output += *i;
    }
    return output;
}

uint64_t toDecimal(string val) {
    uint64_t output = 0;
    uint64_t nextVal = 1;
    for(auto i = val.rbegin(); i != val.rend(); i++) {
        if(*i == '1') {
            output += nextVal;
        }
        nextVal *= 2;
    }
    return output;
}

uint64_t maskVal(uint64_t val, string mask) {
    string binVal = toBinary(val);
    // cout << val << " (" << binVal << ")";
    cout << binVal;
    for(int i = 0; i < mask.length(); ++i) {
        if(mask[i] != 'X') {
            binVal[i] = mask[i];
        }
    }
    uint64_t output = toDecimal(binVal);
    // cout << " masked as " << output << " (" << binVal << ")" << endl;
    cout << " masked as " << binVal << endl;
    return output;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    map<uint64_t, uint64_t> mem;
    string mask = "";
    while(getline(input, inputVal)) {
        if(inputVal.back() == 13) {
            inputVal.pop_back();
        }
        if(inputVal[1] == 'a') {
            mask = inputVal.substr(7);
            cout << "New mask: " << mask << endl;
        }
        else {
            uint64_t addr = (uint64_t)stoi(inputVal.substr(4, inputVal.find("]")-4));
            uint64_t val = (uint64_t)stoi(inputVal.substr(inputVal.find("=")+2));
            // cout << "Read value: " << val << " at address " << addr << endl;
            val = maskVal(val, mask);
            // cout << "Placed value: " << val << endl;
            mem[addr] = val;
        }
    }
    input.close();

    long sum = 0;
    for(auto i = mem.begin(); i != mem.end(); i++) {
        sum += i->second;
    }
    cout << sum << endl;
}