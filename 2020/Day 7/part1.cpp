#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>

using namespace std;

set<string> getContents(map<string, vector<string>> &bags, string targetColor) {
    cout << "Finding parents for " << targetColor << " bags" << endl;
    set<string> output;
    if(bags[targetColor].size() == 0) {
        return output;
    }
    for(string s : bags[targetColor]) {
        output.insert(s);
        cout << "Added 1 bag, now at " << output.size() << endl;
        set<string> got = getContents(bags, s);
        cout << "Back to " << targetColor << endl;
        for(string gs : got) {
            output.insert(gs);
        }
        cout << "Added " << got.size() << " bags; now at " << output.size() << endl;
    }
    cout << "Finished " << targetColor << " bags with " << output.size() << " parents" << endl;
    return output;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    map<string, vector<string>> bags;
    while(getline(input, inputVal)) {
        inputVal.pop_back();
        istringstream readRule(inputVal);
        string readIn;
        string bagColor;
        readRule >> bagColor >> readIn;
        bagColor += " " + readIn;
        readRule >> readIn >> readIn >> readIn;
        if(readIn == "no") {
            continue;
        }
        while(!readRule.eof()) {
            // readIn has number
            string newColor;
            readRule >> newColor >> readIn;
            newColor += " " + readIn;
            bags[newColor].push_back(bagColor);
            readRule >> readIn >> readIn;
        }
    }
    cout << getContents(bags, "shiny gold").size() << endl;
    input.close();
}