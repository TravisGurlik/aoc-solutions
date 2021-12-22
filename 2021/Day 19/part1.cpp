/*
 * Day 19: Beacon Scanner (https://adventofcode.com/2021/day/19)
 * So this was The One for this year, I suppose.
 * This took a lot of visualizing and manual calculations to figure out how to do all of this.
 * 
 * This also contains the code for part 2, since it just required tacking something onto the end.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <tuple>
#include <set>

using namespace std;

/**
 * @brief Stores information about two overlapping scanners
 * 
 */
struct Overlap {
    int oldScanner,             // The scanner being overlapped
        newScanner,             // The scanner doing the overlapping
        orientation;            // The orientation of newScanner that matches oldScanner's base orientation
    tuple<int, int, int> align; // The translation of newScanner needed to match oldScanner

    // Constructor:
    Overlap(int os, int ns, int o, tuple<int, int, int> a) : oldScanner(os), newScanner(ns), orientation(o), align(a) {}

    // Gets a string that can be used for printing this Overlap's info:
    string toString() {
        string output = "Scanner ";
        output += to_string(newScanner);
        output += " overlaps scanner ";
        output += to_string(oldScanner);
        output += " with orientation ";
        output += to_string(orientation);
        return output;
    } // toString()
}; // Overlap

/**
 * @brief Gets the sign of a number
 * 
 * @param input The input value
 * @return int 1 if input is positive, -1 if it's negative, and 0 if it's zero
 */
int sign(int input) {
    return input > 0 ? 1 : (input < 0 ? -1 : 0);
} // sign()

/**
 * @brief Gets the value corresponding to the value of an int variable from a tuple
 * 
 * @param from The tuple to get the value from
 * @param val Which value to get
 * @return int The value at that position in from
 */
int getMatchingValue(tuple<int, int, int>& from, int val) {
    switch(val) {
        case 0: return get<0>(from);
        case 1: return get<1>(from);
        case 2: return get<2>(from);
    } // switch
    return 0;
} // getMatchingValue()

/**
 * @brief Orients a tuple using the given orientation
 * For each position, put the corresponding value there and apply the sign sign.
 * For example, for (-5, 10, 15) and orientation (-2, 1, 3), for the first position
 * you get the second value (10) and invert it.
 * This would result in (-10, -5, 15).
 * 
 * @param input The tuple to reorient
 * @param orient The orientation tuple (see constructOrientations below)
 * @return The oriented version of input
 */
tuple<int, int, int> orientTuple(tuple<int, int, int>& input, tuple<int, int, int>& orient) {
    tuple<int, int, int> copy;
    get<0>(copy) = sign(get<0>(orient)) * getMatchingValue(input, abs(get<0>(orient)) - 1);
    get<1>(copy) = sign(get<1>(orient)) * getMatchingValue(input, abs(get<1>(orient)) - 1);
    get<2>(copy) = sign(get<2>(orient)) * getMatchingValue(input, abs(get<2>(orient)) - 1);
    return copy;
} // orientTuple()

/**
 * @brief Fills a vector with all possible scanenr orientations
 * 
 * These orientations are as follows:
 * ##|FW|Up|   Result
 * --------------------
 * 00| x| y|( x, -z,  y)
 * 01| x| z|( x,  y,  z)
 * 02| y| x|( y,  z,  x)
 * 03| y| z|( y, -x,  z)
 * 04| z| x|( z, -y,  x)
 * 05| z| y|( z,  x,  y)
 * 
 * 06| x|-y|( x,  z, -y)
 * 07| x|-z|( x, -y, -z)
 * 08| y|-x|( y, -z, -x)
 * 09| y|-z|( y,  x, -z)
 * 10| z|-x|( z,  y, -x)
 * 11| z|-y|( z, -x, -y)
 *  
 * 12|-x| y|(-x,  z,  y)
 * 13|-x| z|(-x, -y,  z)
 * 14|-y| x|(-y, -z,  x)
 * 15|-y| z|(-y,  x,  z)
 * 16|-z| x|(-z,  y,  x)
 * 17|-z| y|(-z, -x,  y)
 * 
 * 18|-x|-y|(-x, -z, -y)
 * 19|-x|-z|(-x,  y, -z)
 * 20|-y|-x|(-y,  z, -x)
 * 21|-y|-z|(-y, -x, -z)
 * 22|-z|-x|(-z, -y, -x)
 * 23|-z|-y|(-z,  x, -y)
 * 
 * @param orientations The vector to fill
 */
void constructOrientations(vector<tuple<int, int, int>>& orientations) {
    orientations.push_back(make_tuple(1, -3, 2));
    orientations.push_back(make_tuple(1, 2, 3));
    orientations.push_back(make_tuple(2, 3, 1));
    orientations.push_back(make_tuple(2, -1, 3));
    orientations.push_back(make_tuple(3, -2, 1));
    orientations.push_back(make_tuple(3, 1, 2));

    orientations.push_back(make_tuple(1, 3, -2));
    orientations.push_back(make_tuple(1, -2, -3));
    orientations.push_back(make_tuple(2, -3, -1));
    orientations.push_back(make_tuple(2, 1, -3));
    orientations.push_back(make_tuple(3, 2, -1));
    orientations.push_back(make_tuple(3, -1, -2));

    orientations.push_back(make_tuple(-1, 3, 2));
    orientations.push_back(make_tuple(-1, -2, 3));
    orientations.push_back(make_tuple(-2, -3, 1));
    orientations.push_back(make_tuple(-2, 1, 3));
    orientations.push_back(make_tuple(-3, 2, 1));
    orientations.push_back(make_tuple(-3, -1, 2));

    orientations.push_back(make_tuple(-1, -3, -2));
    orientations.push_back(make_tuple(-1, 2, -3));
    orientations.push_back(make_tuple(-2, 3, -1));
    orientations.push_back(make_tuple(-2, -1, -3));
    orientations.push_back(make_tuple(-3, -2, -1));
    orientations.push_back(make_tuple(-3, 1, -2));
} // constructOrientations()

/**
 * @brief Find the index of a given value within the given vector
 * 
 * @param vec The vector to search
 * @param val The value to search for
 * @return int The index of the value in the vector, or -1 if it isn't found
 */
int getIndexOf(vector<tuple<int, int, int>>& vec, tuple<int, int, int> val) {
    for(int i = 0; i < vec.size(); i++) {
        if(vec[i] == val) {
            return i;
        } // if
    } // for
    return -1;
} // getIndexOf()

/**
 * @brief Gets the orientation gotten by combining two orientations
 * 
 * @param a The first orientation (applied first)
 * @param b The second orientation (applied second)
 * @param orientations The set of orientations
 * @return int The number corresponding to the resulting orientation
 */
int addOrienations(int a, int b, vector<tuple<int, int, int>>& orientations) {
    tuple<int, int, int> oriented = orientTuple(orientations[a], orientations[b]);
    return getIndexOf(orientations, oriented);
} // addOrientations()

/**
 * @brief Adds two tuples
 * 
 * @param a The first tuple
 * @param b The second tuple
 * @return tuple<int, int, int> The sum of the two tuples
 */
tuple<int, int, int> addTuples(tuple<int, int, int>& a, tuple<int, int, int>& b) {
    tuple<int, int, int> output;
    get<0>(output) = get<0>(a) + get<0>(b);
    get<1>(output) = get<1>(a) + get<1>(b);
    get<2>(output) = get<2>(a) + get<2>(b);
    return output;
} // addTuples()

/**
 * @brief Subtracts two tuples
 * 
 * @param a The first tuple
 * @param b The second tuple
 * @return tuple<int, int, int> The difference of the two tuples
 */
tuple<int, int, int> subtractTuples(tuple<int, int, int>& a, tuple<int, int, int>& b) {
    tuple<int, int, int> output;
    get<0>(output) = get<0>(a) - get<0>(b);
    get<1>(output) = get<1>(a) - get<1>(b);
    get<2>(output) = get<2>(a) - get<2>(b);
    return output;
} // subtractTuples()

/**
 * @brief Gets the position of a particular value within a tuple
 * 
 * @param t The tuple to check
 * @param v The value to look for
 * @return int The position of the 
 */
int getPositionOf(tuple<int, int, int>& t, int v) {
    return abs(get<0>(t)) == v ? 1 :
            abs(get<1>(t)) == v ? 2 :
            abs(get<2>(t)) == v ? 3 :
            0;
} // getPositionOf()

/**
 * @brief Calculates the Manhattan Distance between two tuples
 * 
 * @param a The first tuple
 * @param b The second tuple
 * @return int The Manhattan Distance between the tuples
 */
int tupleDist(tuple<int, int, int> a, tuple<int, int, int> b) {
    return abs(get<0>(a) - get<0>(b)) + abs(get<1>(a) - get<1>(b)) + abs(get<2>(a) - get<2>(b));
} // tupleDist()

/**
 * @brief Inverts an orientation
 * The inversion of an orientation is the orientation that provides an output of (x, y, z)
 * when applied after the original orientation.
 * For example, the inversion of (-z, y, x) is (z, y, -x).
 * 
 * @param orient The orientation to invert
 * @param orientations The list of orientations
 * @return int The number corresponding to the inverted orientation
 */
int invertOrientation(int orient, vector<tuple<int, int, int>>& orientations) {
    tuple<int, int, int> inverted;
    // Get where each value is in the tuple:
    int posOf1 = getPositionOf(orientations[orient], 1),
        posOf2 = getPositionOf(orientations[orient], 2),
        posOf3 = getPositionOf(orientations[orient], 3);
    // Determine the proper inversion (position times sign of corresponding value):
    get<0>(inverted) = posOf1 * sign(getMatchingValue(orientations[orient], posOf1-1));
    get<1>(inverted) = posOf2 * sign(getMatchingValue(orientations[orient], posOf2-1));
    get<2>(inverted) = posOf3 * sign(getMatchingValue(orientations[orient], posOf3-1));
    return getIndexOf(orientations, inverted);
} // invertOrientation()

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    vector<vector<tuple<int, int, int>>> detections; // The inputted scanner locations
    vector<tuple<int, int, int>> thisScanner;        // The input for the current scanner
    int line = 0;                                    // The current line number

    // Input loop:
    while(getline(input, inputVal)) {
        line++; // Increment line number
        inputVal.pop_back(); // Remove newline
        // If we're at an empty line, we've finished the current scanner:
        if(inputVal.length() == 0) {
            detections.push_back(thisScanner);
            thisScanner = vector<tuple<int, int, int>>();
            continue;
        } // if
        // Skip the label lines:
        if(inputVal.back() == '-') {
            continue;
        } // if
        // Get the three values from each line:
        int splitA = inputVal.find(",");
        int x = stoi(inputVal.substr(0, splitA));
        int splitB = inputVal.find(",", splitA + 1);
        int y = stoi(inputVal.substr(splitA + 1, splitB - splitA - 1));
        int z = stoi(inputVal.substr(splitB + 1));
        // Add the resulting tuple to this scanner's detections:
        thisScanner.push_back(make_tuple(x, y, z));
    } // while
    detections.push_back(thisScanner); // Don't forget to add the last scanner
    input.close();

    // Prepare orientations vector:
    vector<tuple<int, int, int>> orientations;
    constructOrientations(orientations);

    // Identify all overlaps:
    vector<Overlap> overlaps; // The list of Overlap data
    // First, loop through all possible pairs of scanners:
    for(int baseScanner = 0; baseScanner < detections.size() - 1; baseScanner++) {
        // Direction doesn't matter, so we can skip any older scanners as already compared to:
        for(int compScanner = baseScanner + 1; compScanner < detections.size(); compScanner++) {
            // Then, loop through all possible orientations of the second scanner:
            for(int orient = 0; orient < orientations.size(); orient++) {
                bool overlapFound = false;                      // Whether this orientation leads to the sensors overlapping
                
                // Orient the beacons from the second scanner according to the test orientation:
                vector<tuple<int, int, int>> orientedBeacons; // The beacons detected by the second scanner oriented differently
                for(auto beacon : detections[compScanner]) {
                    orientedBeacons.push_back(orientTuple(beacon, orientations[orient]));
                } // for(beacon)

                // Determine if these sets of beacons overlap by aligning each possible pair of beacons (one from each set):
                for(int compAnchor = 0; compAnchor < detections[compScanner].size(); compAnchor++) {
                    for(int baseAnchor = 0; baseAnchor < detections[baseScanner].size(); baseAnchor++) {
                        // Adjust the beacons to match this alignment:
                        vector<tuple<int, int, int>> anchoredBeacons; // The oriented beacons, aligned to the chosen reference point:
                        for(int i = 0; i < orientedBeacons.size(); i++) {
                            anchoredBeacons.push_back(make_tuple(
                                get<0>(orientedBeacons[i]) - get<0>(orientedBeacons[compAnchor]) + get<0>(detections[baseScanner][baseAnchor]),
                                get<1>(orientedBeacons[i]) - get<1>(orientedBeacons[compAnchor]) + get<1>(detections[baseScanner][baseAnchor]),
                                get<2>(orientedBeacons[i]) - get<2>(orientedBeacons[compAnchor]) + get<2>(detections[baseScanner][baseAnchor])
                            ));
                        } // for(i)

                        // Count the number of aligned beacons:
                        int numMatches = 0; // How many beacons line up
                        for(auto compBeacon : anchoredBeacons) {
                            for(auto baseBeacon : detections[baseScanner]) {
                                if(baseBeacon == compBeacon) {
                                    numMatches++;
                                    break;
                                } // if
                            } // for(baseBeacon)
                        } // for(compBeacon)

                        // If there are at least 12 matches, we've found an overlap:
                        if(numMatches >= 12) {
                            overlapFound = true;

                            // Create the "forward" overlap (second overlaps first):
                            overlaps.emplace_back(baseScanner, compScanner, orient, make_tuple(
                                get<0>(detections[baseScanner][baseAnchor]) - get<0>(orientedBeacons[compAnchor]),
                                get<1>(detections[baseScanner][baseAnchor]) - get<1>(orientedBeacons[compAnchor]),
                                get<2>(detections[baseScanner][baseAnchor]) - get<2>(orientedBeacons[compAnchor])
                            ));

                            // Create the "inverted" overlap (first overlaps second):
                            int invertedOrientation = invertOrientation(orient, orientations);
                            cout << overlaps.back().toString() << " (" << invertedOrientation << " when inverted)" << endl; // Keep this so there's some feedback on the program's progress
                            // The inverted overlap requires our reference anchor from the first set to be transformed to match the second set:
                            tuple<int, int, int> invertedAnchor = orientTuple(detections[baseScanner][baseAnchor], orientations[invertedOrientation]);
                            overlaps.emplace_back(compScanner, baseScanner, invertedOrientation, make_tuple(
                                get<0>(detections[compScanner][compAnchor]) - get<0>(invertedAnchor),
                                get<1>(detections[compScanner][compAnchor]) - get<1>(invertedAnchor),
                                get<2>(detections[compScanner][compAnchor]) - get<2>(invertedAnchor)
                            ));
                            break;
                        } // if
                    } // for(baseAnchor)
                    if(overlapFound) break;
                } // for(compAnchor)
                if(overlapFound) break;
            } // for(orient)
        } // for(compScanner)
    } // for(baseScanner)

    // Now that we know which scanners overlap which and how, we can put them all together.
    // We use 0 as the base, and transform all the others to match it.

    // First, record which scanners overlap which (ex. over[3] is the list of scanners scanner 3 overlaps):
    vector<vector<tuple<int, int, tuple<int, int, int>>>> over(detections.size());  // Overlapping -> (overlapped, orientation, alignment)
    for(Overlap o : overlaps) {
        over[o.newScanner].push_back(make_tuple(o.oldScanner, o.orientation, o.align));
    } // for

    // Declare some more containers:
    vector<bool> mappedTo0(detections.size(), false);           // Which scanners have already been oriented to match scanner 0
    vector<int> scannerOrientations(detections.size(), -1);     // The final orientations of each scanner relative to scanner 0
    vector<tuple<int, int, int>> alignTo0(detections.size());   // The final position of each scanner relative to scanner 0

    // Set initial values for scanner 0:
    mappedTo0[0] = true;
    scannerOrientations[0] = 1;
    alignTo0[0] = make_tuple(0, 0, 0);

    // Continually loop through all the scanners (there's not very many, it's fine) until all are mapped to 0:
    int totalMapped = 1; // How many scanners have been mapped thus far
    while(totalMapped < detections.size()) {
        for(int i = 0; i < over.size(); i++) {
            if(mappedTo0[i]) continue; // If this scanner has already been mapped, we don't need to do anything else with it
            // Loop through all the scanners this scanner overlaps:
            for(int iOver = 0; iOver < over[i].size(); iOver++) {
                // If any of them are mapped to 0, use it to map this one to 0:
                if(mappedTo0[get<0>(over[i][iOver])]) {
                    // Some things had to be pulled out of expressions to make C++ happy:
                    int oldOrient = scannerOrientations[get<0>(over[i][iOver])]; // The orientation number matching the reference scanner's orientation
                    tuple<int, int, int> orientedAlign = orientTuple(get<2>(over[i][iOver]), orientations[oldOrient]); // The offset from the reference scanner to the current, aligned to 0

                    // Use these values to determine how to orient and align the current scanner:
                    scannerOrientations[i] = addOrienations(get<1>(over[i][iOver]), oldOrient, orientations);
                    alignTo0[i] = addTuples(alignTo0[get<0>(over[i][iOver])], orientedAlign);
                    mappedTo0[i] = true;

                    totalMapped++; // Update the total
                    break;
                } // if
            } // for(iOver)
        } // for(i)
    } // while

    // Now that everything's aligned, create the full set of beacons:
    set<tuple<int, int, int>> beacons; // The set of unique beacons
    // Loop through all the beacons from the input:
    for(int scanner = 0; scanner < detections.size(); scanner++) {
        for(int beacon = 0; beacon < detections[scanner].size(); beacon++) {
            tuple<int, int, int> newBeacon = orientTuple(detections[scanner][beacon], orientations[scannerOrientations[scanner]]); // Apply orientation
            newBeacon = addTuples(newBeacon, alignTo0[scanner]); // Apply alignment/translation
            beacons.insert(newBeacon); // Add to set (duplicates are automatically ignored)
        } // for(beacon)
    } // for(scanner)

    /* Verbose results for debugging:
    cout << endl << "Scanner locations:" << endl;
    for(int i = 0; i < alignTo0.size(); i++) {
        cout << "[" << i << "]: (" << get<0>(alignTo0[i]) << ", " << get<1>(alignTo0[i]) << ", " << get<2>(alignTo0[i]) << ")" << endl;
    }

    cout << endl << "Scanner orientations:" << endl;
    for(int i = 0; i < alignTo0.size(); i++) {
        cout << "[" << i << "]: " << scannerOrientations[i] << endl;
    }

    cout << endl << "Beacon locations:" << endl;
    for(auto i = beacons.begin(); i != beacons.end(); i++) {
        cout << "(" << get<0>(*i) << ", " << get<1>(*i) << ", " << get<2>(*i) << ")" << endl;
    }*/

    // For Part 2, compare all unique pairs of scanners to find the ones that are furthest apart:
    int maxDist = -1; // The maximum distance between two scanners:
    for(int a = 0; a < alignTo0.size() - 1; a++) {
        for(int b = a + 1; b < alignTo0.size(); b++) {
            maxDist = max(maxDist, tupleDist(alignTo0[a], alignTo0[b]));
        } // for(b)
    } // for(a)

    //Print final solutions:
    cout << endl << "Total beacons: " << beacons.size() << endl;
    cout << "Max distance between two beacons: " << maxDist << endl;
} // main()