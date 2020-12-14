#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    string pass = "";
    vector<string> tags;
    int numValid = 0;
    while(getline(input, inputVal)) {
        if(inputVal.length() == 1) {
            stringstream ss(pass);
            string val;
            while(ss >> val) {
                tags.push_back(val.substr(0, 3));
            }
            if(tags.size() == 7) {
                cout << "Seven tags present. Checking for cid..." << endl;
                for(string s : tags) {
                    if(s == "cid") {
                        cout << "\tInvalid: missing tag" << endl;
                        numValid--;
                        break;
                    }
                }
                numValid++;
            }
            else if(tags.size() == 8) {
                cout << "All tags present; passport is valid" << endl;
                numValid++;
            }
            else {
                cout << "Invalid: multiple tags missing" << endl;
            }
            tags.clear();
            pass = "";
        }
        else {
            pass += inputVal;
        }
    }
    if(pass != "") {
        stringstream ss(pass);
        string val;
        while(ss >> val) {
            tags.push_back(val.substr(0, 3));
        }
        if(tags.size() == 7) {
            cout << "Seven tags present. Checking for cid..." << endl;
            for(string s : tags) {
                if(s == "cid") {
                    cout << "\tInvalid: missing tag" << endl;
                    numValid--;
                    break;
                }
            }
            numValid++;
        }
        else if(tags.size() == 8) {
            cout << "All tags present; passport is valid" << endl;
            numValid++;
        }
        else {
            cout << "Invalid: multiple tags missing" << endl;
        }
    }
    cout << numValid << endl;
    input.close();
}