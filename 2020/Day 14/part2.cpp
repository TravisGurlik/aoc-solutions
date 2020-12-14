#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

string toBinary(uint64_t val, int length = 36) {
    // cout << val;
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
    while(sval.length() < length) {
        sval += '0';
    }
    string output = "";
    for(auto i = sval.rbegin(); i != sval.rend(); i++) {
        output += *i;
    }
    // cout << " = " << output << endl;
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

vector<uint64_t> maskAddr(uint64_t addr, string mask) {
    string newAddr = toBinary(addr);
    // cout << newAddr;
    for(int i = 0; i < mask.length(); i++) {
        if(mask[i] == '0') {
            continue;
        }
        newAddr[i] = mask[i];
    }
    // cout << " masked as " << newAddr;
    vector<int> floatIs;
    int xi = -1;
    while((xi = newAddr.find('X', xi+1)) != newAddr.npos) {
        floatIs.push_back(xi);
    }
    int target = pow(2, floatIs.size());
    vector<uint64_t> output;
    for(int count = 0; count < target; count++) {
        string binC = toBinary(count, floatIs.size());
        for(int i = 0; i < binC.length(); ++i) {
            newAddr[floatIs[i]] = binC[i];
        }
        // cout << "\t" << newAddr << endl;
        output.push_back(toDecimal(newAddr));
    }
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
            // cout << "New mask: " << mask << endl;
        }
        else {
            uint64_t addr = (uint64_t)stoi(inputVal.substr(4, inputVal.find("]")-4));
            uint64_t val = (uint64_t)stoi(inputVal.substr(inputVal.find("=")+2));
            // cout << "Read value: " << val << " at address " << addr << endl;
            vector<uint64_t> maskedAddrs = maskAddr(addr, mask);
            // cout << "Placed value: " << val << endl;
            for(uint64_t a : maskedAddrs) {
                mem[a] = val;
            }
        }
    }
    input.close();

    long sum = 0;
    for(auto i = mem.begin(); i != mem.end(); i++) {
        sum += i->second;
    }
    cout << sum << endl;
}