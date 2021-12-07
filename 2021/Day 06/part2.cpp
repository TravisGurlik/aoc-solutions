/*
 * This is exactly the same as part 1, but withs longs instead of ints
 *   and more days.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<long> fish(9, 0);
    
    // Input loop:
    while(getline(input, inputVal)) {
        fish[stoi(inputVal)]++;
    } // while
    input.close();

    for(long days = 0; days < 256; days++) {
        vector<long> buffer(9, 0);
        for(long i = 8; i > 0; i--) {
            buffer[i-1] = fish[i];
        } // for(i)
        buffer[8] = fish[0];
        buffer[6] += fish[0];
        fish = buffer;
    } // for(days)

    long sum = 0;
    for(long n : fish) {
        sum += n;
    } // for(n)

    //Prlong final solution:
    cout << sum << endl;
} // main()