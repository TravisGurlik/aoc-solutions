#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    map<char, int> yeses;
    int sum = 0, people = 0;
    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            for(auto i = yeses.begin(); i != yeses.end(); ++i) {
                if(i->first >= 97 && i->second == people) {
                    sum++;
                }
            }
            yeses.clear();
            people = 0;
        }
        else {
            for(char c : inputVal) {
                yeses[c]++;
            }
            people++;
        }
    }
    for(auto i = yeses.begin(); i != yeses.end(); ++i) {
        if(i->second == people) {
            sum++;
        }
    }
    cout << sum << endl;
    input.close();
}