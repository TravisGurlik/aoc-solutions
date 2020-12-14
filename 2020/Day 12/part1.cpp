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
    int north = 0,
        east = 0,
        facing = 1;
    while(getline(input, inputVal)) {
        switch(inputVal[0]) {
            case 'N':
                north += stoi(inputVal.substr(1));
                break;
            case 'S':
                north -= stoi(inputVal.substr(1));
                break;
            case 'E':
                east += stoi(inputVal.substr(1));
                break;
            case 'W':
                east -= stoi(inputVal.substr(1));
                break;
            case 'L':
                facing -= stoi(inputVal.substr(1)) / 90;
                facing %= 4;
                facing = facing < 0 ? 4 + facing : facing;
                break;
            case 'R':
                facing += stoi(inputVal.substr(1)) / 90;
                facing %= 4;
                facing = facing < 0 ? 4 + facing : facing;
                break;
            case 'F':
                switch(facing) {
                    case 0:
                        north += stoi(inputVal.substr(1));
                        break;
                    case 2:
                        north -= stoi(inputVal.substr(1));
                        break;
                    case 1:
                        east += stoi(inputVal.substr(1));
                        break;
                    case 3:
                        east -= stoi(inputVal.substr(1));
                        break;
                }
                break;
        }
        cout << "North = " << north << "; East = " << east << "; Facing = " << facing << endl;
    }
    cout << abs(north) + abs(east) << endl;
    input.close();
    
}