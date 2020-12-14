#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    set<char> yeses;
    int sum = 0;
    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            sum += yeses.size() - 1;
            yeses.clear();
        }
        else {
            for(char c : inputVal) {
                yeses.insert(c);
            }
        }
    }
    sum += yeses.size() - 1;
    cout << sum << endl;
    input.close();
}