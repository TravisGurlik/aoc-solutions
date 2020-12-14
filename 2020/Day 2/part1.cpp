#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int valid = 0;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) return 1;
    string inputVal;
    int min, max, dashLoc, count;
    char target;
    string password;
    while(getline(input, inputVal)) {
        count = 0;
        dashLoc = inputVal.find('-');
        min = stoi(inputVal.substr(0, dashLoc));
        max = stoi(inputVal.substr(dashLoc+1, inputVal.find(' ')-dashLoc));
        target = inputVal[inputVal.find(':')-1];
        password = inputVal.substr(inputVal.find(':')+2);
        for(char c : password) {
            if(c == target) count++;
        }
        if(count >= min && count <= max) valid++;
    }
    input.close();
    cout << valid << endl;
}