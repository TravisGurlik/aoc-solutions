#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<int> expenses;
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    }
    while(getline(input, inputVal)) {
        expenses.push_back(stoi(inputVal));
    }
    input.close();

    sort(expenses.begin(), expenses.end());

    auto lowVal = expenses.begin();
    auto midVal = lowVal+1;
    auto highVal = expenses.rbegin();
    for(auto low = expenses.begin(); low != expenses.begin()+(expenses.size()-1); low++) {
        for(auto mid = low+1; mid != expenses.begin()+expenses.size(); mid++) {
            if(*low + *mid + *(mid+1) > 2020) break;
            for(auto high = mid+1; high != expenses.end(); high++) {
                int sum = *low + *mid + *high;
                if(sum > 2020) break;
                else if(sum == 2020) {
                    cout << (*low * *mid * *high) << endl;
                    return 0;
                }
            }
        }
    }
    cout << "No set found" << endl;
    return 0;
}