#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

/**
 * Second verse, same as the first but MORE.
 * This is definitely the pointiest program I have ever written.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    // Our vectors just add another dimension on the outside; the ordering is now (w, z, y, x).
    vector<vector<vector<vector<bool>>>> cubes(13, vector<vector<vector<bool>>>(13, vector<vector<bool>>(20, vector<bool>(20, false))));
    // Ints are unchanged from Part 1; the z bounds can be reused or w:
    int rowNum = 6,
        wzMin = 5,
        wzMax = 7,
        xyMin = 5,
        xyMax = 14;

    // Input is same as Part 1, but with an extra static dimension in front:
    while(getline(input, inputVal)) {
        for(int i = 0; i < inputVal.length(); i++) {
            cubes[6][6][rowNum][i + 6] = inputVal[i] == '#';
        } // for
        rowNum++;
    } // while
    input.close();

    // The main loops are also the same as Part 1, but with extra loops and ifs for the new dimension:
    for(int count = 0; count < 6; count++) {
        vector<vector<vector<vector<bool>>>> buffer(cubes);
        for(int w = wzMin; w <= wzMax; w++) {
            for(int z = wzMin; z <= wzMax; z++) {
                for(int y = xyMin; y <= xyMax; y++) {
                    for(int x = xyMin; x <= xyMax; x++) {
                        int adj = 0;
                        for(int wa = w - 1; wa <= w + 1 && adj <= 3; wa++) {
                            for(int za = z - 1; za <= z + 1 && adj <= 3; za++) {
                                for(int ya = y - 1; ya <= y + 1 && adj <= 3; ya++) {
                                    for(int xa = x - 1; xa <= x + 1 && adj <= 3; xa++) {
                                        if(wa >= 0 && wa < cubes.size()) {
                                            if(za >= 0 && za < cubes[wa].size()) {
                                                if(ya >= 0 && ya < cubes[wa][za].size()) {
                                                    if(xa >= 0 && xa < cubes[wa][za][ya].size()) {
                                                        if(!(wa == w && za == z && ya == y && xa == x)) {
                                                            adj += cubes[wa][za][ya][xa] ? 1 : 0;
                                                        } // if(!(wa...))
                                                    } // if(xa...)
                                                } // if(ya...)
                                            } // if(za...)
                                        } // if(wa...)
                                    } // for(xa)
                                } // for(ya)
                            } // for(za)
                        } // for(wa)

                        // Updating is also the same, but with an extra dimension:
                        if(cubes[w][z][y][x]) {
                            buffer[w][z][y][x] = adj == 2 || adj == 3;
                        } // if(cubes...)
                        else {
                            buffer[w][z][y][x] = adj == 3;
                        } // else
                    } // for(x)
                } // for(y)
            } // for(z)
        } // for(w)

        // Swap the buffer into the main array:
        cubes = buffer;

        // Update bounds:
        wzMin--;
        wzMax++;
        xyMin--;
        xyMax++;
    } // for(count)

    // Once again, counting is the same, but with one more dimension:
    // (s = slice)
    int total = 0;
    for(auto s : cubes) {
        for(auto p : s) {
            for(auto r : p) {
                for(bool c : r) {
                    total += c ? 1 : 0;
                } // for(c)
            } // for(r)
        } // for(p)
    } // for(s)
    
    //Print final solution:
    cout << total << endl;
} // main()