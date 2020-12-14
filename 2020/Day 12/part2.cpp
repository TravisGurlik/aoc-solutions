#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    int wayNorth = 1,
        wayEast = 10,
        shipNorth = 0,
        shipEast = 0,
        lineNum = 0;
    while(getline(input, inputVal)) {
        ++lineNum;
        int count = stoi(inputVal.substr(1));
        int temp = 0;
        switch(inputVal[0]) {
            case 'N':
                wayNorth += count;
                break;
            case 'S':
                wayNorth -= count;
                break;
            case 'E':
                wayEast += count;
                break;
            case 'W':
                wayEast -= count;
                break;
            case 'L':
                count = 360 - count;
            case 'R':
                if(count == 180) {
                    wayNorth = -wayNorth;
                    wayEast = -wayEast;
                }
                else {
                    temp = wayNorth;
                    wayNorth = (count == 270 ? 1 : -1) * wayEast;
                    wayEast = (count == 90 ? 1 : -1) * temp;
                }
                break;
            case 'F':
                for(int i = 0; i < count; ++i) {
                    shipNorth += wayNorth;
                    shipEast += wayEast;
                }
                break;
        }
        cout << "Line #" << lineNum << ": Way North = " << wayNorth << "; Way East = " << wayEast << "; Ship North = " << shipNorth << "; Ship East = " << shipEast << endl;
    }
    cout << abs(shipNorth) + abs(shipEast) << endl;
    input.close();
}