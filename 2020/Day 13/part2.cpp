#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

long modularInverse(long n, long m) {
    n %= m;
    for(long i = 1; i < m; ++i) {
        if((i * n) % m == 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    getline(input, inputVal);
    vector<long> departs;
    getline(input, inputVal);
    input.close();
    int lastIndex = -1,
        nextIndex = 0;
    nextIndex = inputVal.find(",");
    while(nextIndex != inputVal.npos) {
        string val = inputVal.substr(lastIndex+1, nextIndex - lastIndex - 1);
        if(val != "x") {
            departs.push_back(stol(val));
        }
        else {
            departs.push_back(-1);
        }
        lastIndex = nextIndex;
        nextIndex = inputVal.find(",", nextIndex+1);
    }

    string val = inputVal.substr(lastIndex+1);
    if(val != "x") {
        departs.push_back(stol(val));
    }

    vector<pair<int, int>> vals; // value, index
    for(int i = 0; i < departs.size(); ++i) {
        if(departs[i] != -1) {
            int val = -i;
            while(val < 0) val += departs[i];
            vals.push_back(make_pair(departs[i], val));
        }
    }

    long modulus = 1;
    for(pair<int, int> n : vals) {
        modulus *= n.first;
    }
    cout << modulus << endl << endl;

    long result = 0;
    for(auto i = vals.begin(); i != vals.end(); ++i) {
        long b = modulus / i->first;
        long bi = modularInverse(b, i->first);
        result += (i->second * b * bi) % modulus;
        result %= modulus;
    }

    cout << result << endl;
}