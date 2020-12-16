#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <map>
#include <utility>

using namespace std;

/**
 * I knew something like this would be coming for Part 2, but I still had a lot of restructuring to do.
 * Now that the names of the fields actually matter, they have to be stored somewhere.
 * I used a map, which made the last bit a little more interesting.
 * Most of my time on this Part was spent getting the field identification to work properly.
 *   There were a lot of small mistakes that needed fixing in there.
 */

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    //Variables:
    map<string, pair<int, int>[2]> fields;  // Maps field names to their allowable ranges (as an array of pairs)
    vector<vector<int>> validTickets;       // The values for each valid ticket
    vector<int> ticket,                     // The values for the ticket currently being read
                myTicket;                   // The values for my ticket
    int inputArea = 0,                      // The area of the input currently being read
        indexS,                             // The start index for a substring
        indexE,                             // The end index for a substring
        valA,                               // Holds a numeric value read from the input
        valB;                               // Holds a numeric value read from the input
    bool valid;                             // Is the current value valid (when checking tickets)
    string fieldName;                       // The name of the current field

    while(getline(input, inputVal)) {
        // Again, use empty lines to divide sections:
        if(inputVal.length() == 1) {
            inputArea++;
            continue;
        } // if

        switch(inputArea) {
            case 0: // Fields and valid ranges
                // Same reading as Part 1, but the data is stored differently:
                indexS = inputVal.find(":") + 2;
                indexE = inputVal.find("-");
                fieldName = inputVal.substr(0, indexS - 2);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                indexE = inputVal.find(" ", indexS);
                valB = stoi(inputVal.substr(indexS, indexE - indexS));
                fields[fieldName][0] = make_pair(valA, valB);

                indexS = inputVal.find(" ", indexE + 1) + 1;
                indexE = inputVal.find("-", indexS);
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                indexS = indexE + 1;
                valB = stoi(inputVal.substr(indexS));
                fields[fieldName][1] = make_pair(valA, valB);
                break;
            case 1: // My ticket
                // Skip the header line:
                if(inputVal[0] != 'y') {
                    // Read each value from the ticket and store it:
                    // (There no need to check my ticket for validity)
                    indexS = 0;
                    indexE = inputVal.find(",");
                    while(indexE != inputVal.npos) {
                        myTicket.push_back(stoi(inputVal.substr(indexS, indexE - indexS)));
                        indexS = indexE + 1;
                        indexE = inputVal.find(",", indexS);
                    } // while(indexE...)
                    myTicket.push_back(stoi(inputVal.substr(indexS, indexE - indexS)));
                } // if
                break;
            case 2: // Nearby tickets
                // Skip the header line:
                if(inputVal[0] == 'n') {
                    break;
                }  // if

                // Read each value from the ticket, check for validity, and save the ticket (if valid):
                // (This is the same as Part 1, but tickets are only saved if
                //   each of their values are valid for at least one field)
                ticket.clear();
                indexS = 0;
                indexE = inputVal.find(",");

                while(indexE != inputVal.npos) {
                    valA = stoi(inputVal.substr(indexS, indexE - indexS));
                    valid = false;
                    for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                        // Due to the change in how fields are stored, only one for loop is used:
                        valid = (valA >= fi->second[0].first && valA <= fi->second[0].second)
                                || (valA >= fi->second[1].first && valA <= fi->second[1].second);
                    } // for(fi)
                    if(!valid) {
                        break;
                    } // if

                    ticket.push_back(valA);
                    indexS = indexE + 1;
                    indexE = inputVal.find(",", indexS);
                } // while(indexE...)
                if(!valid) {
                    // If the ticket was not valid, skip it:
                    continue;
                } // if

                // Again, the last value must be checked separately:
                valA = stoi(inputVal.substr(indexS, indexE - indexS));
                valid = false;
                for(auto fi = fields.begin(); fi != fields.end() && !valid; fi++) {
                    valid = (valA >= fi->second[0].first && valA <= fi->second[0].second)
                            || (valA >= fi->second[1].first && valA <= fi->second[1].second);
                } // for(fi)
                if(valid) {
                    // If the entire ticket was valid, add it to the ticket vector:
                    ticket.push_back(valA);
                    validTickets.push_back(ticket);
                } // if
                break;
        } // switch
    } // while(getline...)
    input.close();

    // Now that we have all the data, it's time to determine the order of the fields

    // More variables:
    int target = fields.size(),             // The number of fields to order
        orderedFields = 0;                  // The number of fields that have been ordered
    vector<string> fieldOrder(target, "");  // The name of each field in order

    // Loop until every field has been ordered:
    while(orderedFields < target) {
        // Iterate through field positions first:
        for(int vi = 0; vi < validTickets[0].size(); vi++) {
            // If this field has already been identified, skip this iteration:
            if(fieldOrder[vi] != "") {
                continue;
            } // if

            // Per-loop variables:
            map<string, bool> posssibleFields;  // Maps each field to whether it matches these values
            int fieldsLeft = fields.size();     // Stores how many fields are still possible

            // Now iterate through each ticket:
            for(int ti = 0; ti < validTickets.size(); ti++) {
                // Iterate through each field:
                for(auto fi = fields.begin(); fi != fields.end(); fi++) {
                    // If the current value doesn't match this field, this field remove this field as a possibility:
                    if(!((validTickets[ti][vi] >= fi->second[0].first && validTickets[ti][vi] <= fi->second[0].second)
                            || (validTickets[ti][vi] >= fi->second[1].first && validTickets[ti][vi] <= fi->second[1].second))) {
                        posssibleFields[fi->first] = false;
                        fieldsLeft--;

                        // If there's only one possibility left, end the loop:
                        if(fieldsLeft == 1) {
                            break;
                        }
                    } // if
                    // If this field has not been added already, add it as possible:
                    else if(posssibleFields.count(fi->first) == 0) {
                        posssibleFields[fi->first] = true;
                    } // else if
                } // for(fi)

                // If there's only one possibility left, don't bother with the rest of the tickets:
                // (Each value must match at least one field, so there should never be 0 possible fields)
                if(fieldsLeft == 1) {
                    break;
                } // if
            } // for(ti)

            // If there's more than one possible field, skpi this position for now:
            if(fieldsLeft != 1) {
                continue;
            } // if

            // Otherwise, find the last possible field:
            for(auto fi = fields.begin(); fi != fields.end(); fi++) {
                if(posssibleFields[fi->first]) {
                    // Once found, save the name of this field:
                    fieldOrder[vi] = fi->first;
                    orderedFields++;
                    // Remove this field from the map; it isn't needed any more:
                    fields.erase(fi);
                    break;
                } // if
            } // for(fi)

            // If the last field was just identified, we're done:
            if(orderedFields == target) {
                break;
            } // if
        } // for(vi)
    } // while

    // Now that all the fields are identified, calculate the result:

    // Final variables:
    long result = 1;    // The final answer
    int destCount = 0;  // The number of "destination" fields found so far

    // Loop through each field (by index so we can also iterate through the ticket):
    for(int i = 0; i < fieldOrder.size(); i++) {
        if(fieldOrder[i].substr(0, 9) == "departure") {
            // For each departure field, add it to the final product:
            result *= myTicket[i];
            destCount++;
            if(destCount == 6) {
                // Once all destination fields have been found, skip the rest:
                break;
            } // if(destCount...)
        } // if(fieldOrder...)
    } // for

    //Print final solution:
    cout << result << endl;
} // main()