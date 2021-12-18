/*
 * This is the same as Part 1, just with the storage and adding updated.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>

using namespace std;

void appendValues(vector<int>& nums, string input) {
    string temp = "";
    for(char c : input) {
        if(c != '[' && c != ']') {
            temp.push_back(c);
        }
    }
    for(int i = 0; i < temp.length(); i += 2) {
        nums.push_back(temp[i] - '0');
    }
}

string denumber(string input) {
    int i = -1;
    while((i = input.find_first_of("0123456789")) != input.npos) {
        input[i] = '#';
    }
    return input;
}

string snailAdd(string lhs, string rhs) {
    return "[" + lhs + "," + rhs + "]";
}

string makeNumber(string input, vector<int>& nums) {
    int i = -1;
    auto next = nums.begin();
    while((i = input.find("#", i+1)) != input.npos) {
        input = input.substr(0, i) + to_string(*next) + input.substr(i+1);
        next++;
    }
    return input;
}

void printError(int pos, string input, vector<int>& nums, string error) {
    cout << "Whoops, something went wrong while " << error << " at position " << pos << endl;
    cout << "Current string: " << input << endl;
    cout << "Values:" << endl;
    for(int i = 0; i < nums.size(); i++) {
        cout << "\t[" << i << "]: " << nums[i] << endl;
    }
    cout << "Assembled string: " << makeNumber(input, nums) << endl;
}

int calcMagnitude(string input, vector<int>& nums, int& start, int& pos) {
    int output = 0;
    start++;
    if(input[start] == '#') {
        output = nums[pos] * 3;
        pos++;
    }
    else if(input[start] == '[') {
        output = 3 * calcMagnitude(input, nums, start, pos);
    }
    start += 2;
    if(input[start] == '#') {
        output += nums[pos] * 2;
        pos++;
    }
    else if(input[start] == '[') {
        output += 2 * calcMagnitude(input, nums, start, pos);
    }
    start++;
    return output;
}

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<string> vals;            // The list of denumbered numbers
    vector<vector<int>> allNums;    // The list of lists of values

    // Input loop (add each number to the storage containers):
    while(getline(input, inputVal)) {
        inputVal.pop_back(); // Remove newline
        vals.push_back(inputVal);
        allNums.push_back(vector<int>());
        appendValues(allNums.back(), inputVal);
    } // while

    // Try every pair to find the one that gives the largest magnitude:
    int maxMagnitude = -1;  // The maximum magnitude thus far
    for(int a = 0; a < vals.size(); a++) {
        for(int b = 0; b < vals.size(); b++) {
            if(a == b) continue; // Don't add numbers to themselves
            // Construct number:
            string val = snailAdd(denumber(vals[a]), denumber(vals[b]));
            vector<int> nums = allNums[a];
            appendValues(nums, vals[b]);

            // All of this is the same as Part 1:
            bool done = false;
            while(!done) {
                done = true;
                // Check for explodes:
                int depth = 0,
                    pos = 0;
                for(int i = 0; i < val.length(); i++) {
                    if(val[i] == '[') {
                        depth++;
                        if(depth > 4) {
                            // Update nums:
                            if(pos > 0) {
                                nums[pos-1] += nums[pos];
                            }
                            nums[pos] = 0;
                            if(pos < nums.size() - 2) {
                                nums[pos+2] += nums[pos+1];
                            }
                            nums[pos+1] = -1;
                            vector<int> buffer;
                            for(int n : nums) {
                                if(n >= 0) {
                                    buffer.push_back(n);
                                }
                            }
                            if(buffer.size() != nums.size() - 1) {
                                printError(pos, val, nums, "exploding numbers");
                                return 1;
                            }
                            nums = buffer;

                            // Update val:
                            val = val.substr(0, i) + "#" + val.substr(val.find("]", i)+1);
                            if(val[i-1] == ']' || val[i-1] == '#' || val[i+1] == '[' || val[i+1] == '#') {
                                printError(i, val, nums, "exploding strings");
                                return 1;
                            }

                            done = false;
                            break;
                        }
                    }
                    else if(val[i] == ']') {
                        depth--;
                    }
                    else if(val[i] == ',') {
                        pos++;
                    }
                }
                if(!done) continue;

                // Check for splits:
                pos = 0;
                for(int i = 0; i < val.length(); i++) {
                    if(val[i] == ',' || i == val.length() - 1) {
                        if(nums[pos] > 9) {
                            // Update nums:
                            vector<int> buffer;
                            for(int i = 0; i < nums.size(); i++) {
                                if(i == pos) {
                                    buffer.push_back(nums[i] / 2);
                                    buffer.push_back(nums[i] / 2 + (nums[i] % 2));
                                }
                                else {
                                    buffer.push_back(nums[i]);
                                }
                            }
                            if(buffer.size() != nums.size() + 1) {
                                printError(pos, val, nums, "splitting numbers");
                                return 1;
                            }
                            nums = buffer;

                            // Update val:
                            while(val[i] != '#') i--;
                            val = val.substr(0, i) + "[#,#]" + val.substr(i+1);
                            if(val[i-1] == ']' || val[i-1] == '#' || val[i+5] == '[' || val[i+5] == '#') {
                                printError(i, val, nums, "splitting strings");
                                return 1;
                            }

                            done = false;
                            break;
                        }
                        pos++;
                    }
                }
            }
            
            // Update maxMagnitude if needed:
            int start = 0,
                pos = 0;
            maxMagnitude = max(maxMagnitude, calcMagnitude(val, nums, start, pos));
        } // for(b)
    } // for(a)
    input.close();

    //Print final solution:
    cout << maxMagnitude << endl;
} // main()