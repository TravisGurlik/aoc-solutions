#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int getContentsHelper(map<string, map<string, int>> &bags, map<string, int> &bagContentTotals, string targetColor) {
    cout << "Finding contents for " << targetColor << " bags" << endl;
    if(bags[targetColor].size() == 0) {
        return 0;
    }
    int total = 0;
    for(auto i = bags[targetColor].begin(); i != bags[targetColor].end(); ++i) {
        cout << " - Next content: " << i->second << " " << i->first << " bags" << endl;
        int got = bagContentTotals.count(i->first) == 0 ? getContentsHelper(bags, bagContentTotals, i->first) : bagContentTotals[i->first];
        cout << "Back to " << targetColor << endl;
        total += i->second * (got + 1);
        cout << "Added " << i->second * (got + 1) << " bags; now at " << total << endl;
    }
    cout << "Finished " << targetColor << " bags with " << total << " contents" << endl;
    bagContentTotals[targetColor] = total;
    return total;
}

int getContents(map<string, map<string, int>> &bags, string targetColor) {
    cout << "Finding contents for " << targetColor << " bags" << endl;
    if(bags[targetColor].size() == 0) {
        return 0;
    }
    map<string, int> bagContentTotals;
    int total = 0;
    for(auto i = bags[targetColor].begin(); i != bags[targetColor].end(); ++i) {
        cout << " - Next content: " << i->second << " " << i->first << " bags" << endl;
        int got = getContentsHelper(bags, bagContentTotals, i->first);
        cout << "Back to " << targetColor << endl;
        total += i->second * (got + 1);
        cout << "Added " << i->second * (got + 1) << " bags; now at " << total << endl;
    }
    cout << "Finished " << targetColor << " bags with " << total << " contents" << endl;
    return total;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    map<string, map<string, int>> bags;
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
            int num = stoi(readIn);
            string newColor;
            readRule >> newColor >> readIn;
            newColor += " " + readIn;
            bags[bagColor][newColor] = num;
            readRule >> readIn >> readIn;
        }
    }
    cout << getContents(bags, "shiny gold") << endl;
    input.close();
}