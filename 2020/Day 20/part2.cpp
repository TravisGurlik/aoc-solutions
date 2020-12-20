/*
 * Unfortunately, I couldn't use my shortcut of not putting the image together for this Part.
 * Solving this required drastic restructuring of my process from Part 1, though some aspects are
 *   still fairly similar.
 * I definitely ended up using a few too many steps in this process.
 * Edges of Tiles are now read clockwise around the tile.
 *   If we had the tile:
 *     .##
 *     ##.
 *     #..
 *   Our edges would be listed as:
 *     .##
 *     #..
 *     ..#
 *     ##.
 *   This makes determining which tiles are flipped fairly simple: if the adjacent edges are the
 *     same, the tiles have opposite flips and if one edge must be reverse they have the same flip.
 * Orientations are determined using the neighbors vector.
 *   Each element of the neighbors vector corresponds to the edge in the edges vector with the same index.
 *   Once we know the relative locations of two adjacent Tiles (and one of them is properly oriented),
 *     we can use this to tell which edge should be on which side of the Tile.
 * All flips are horizontal, and are performed before rotating the Tile.
 * All rotations are clockwise, and the values are the number of 90 degree turns.
 *   For example, a rotation of 3 means 3 90 degree turns, or a 270 degree turn.
 */

#include <iostream>
#include <fstream>
#include <string>
// Additional libraries for this Part:
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Transforms a matrix via flips and/or rotations
 * @param m The matrix to transform (can use any value type)
 * @param flip Flip the matrix?
 * @param rot The number of 90 degree clockwise rotations to perform
 */
template<class T>
void transformMatrix(vector<vector<T>>& m, bool flip, int rot) {
    vector<vector<T>> buffer; // Used for storage during 90 degree rotations

    // Filp the matrix:
    if(flip) {
        // Reverse each row:
        for(int i = 0; i < m.size(); i++) {
            reverse(m[i].begin(), m[i].end());
        } // for
    } // if(flip)

    // 180 degree rotation (does not require constructing a new matrix):
    if(rot == 2) {
        // A 180 degree rotation is equivalent to flipping the matrix vertically and horizontally:
        reverse(m.begin(), m.end());
        for(int i = 0; i < m.size(); i++) {
            reverse(m[i].begin(), m[i].end());
        } // for
    } // if(rot...)
    // Other rotations (do require constructing a new matrix):
    else if(rot != 0) {
        // Make the buffer the proper size:
        buffer = vector<vector<T>>(m[0].size(), vector<T>(m.size()));
        // Construct the buffer (transpose the matrix):
        for(int a = 0; a < m.size(); a++) {
            for(int b = 0; b < m[0].size(); b++) {
                buffer[b][a] = m[a][b];
            } // for(b)
        } // for(a)
        // Update the matrix to match the buffer:
        m = buffer;

        // A 90 degree turn requires a horizontal flip to correct the matrix:
        if(rot == 1) {
            for(int i = 0; i < m.size(); i++) {
                reverse(m[i].begin(), m[i].end());
            } // for
        } // if(rot...)
        // A 270 degree turn requires a vertical flip to correct the matrix:
        else {
            reverse(m.begin(), m.end());
        } // else
    } // else if(rot...)
} // transformMatrix()

/**
 * Stores the contents, orientation, and relative location of an image tile.
 */
struct Tile {
    /**
     * Initializes each variable in a Tile.
     */
    Tile() {
        edges = vector<vector<bool>>(4, vector<bool>(10, false));
        contents = vector<vector<bool>>(8, vector<bool>(8, false));
        neighbors = vector<int>(4, -1);
        rotation = 0;
        placed = false;
        flipped = false;
    } // Tile()

    // Variables:
    vector<vector<bool>> edges;     // The edges of the Tile (read clockwise from the upper-left)
    vector<vector<bool>> contents;  // The actual image data in this Tile
    vector<int> neighbors;          // The Tiles that are adjacent to this one (in clockwise order from the top relative to the edges vector)
    int rotation;                   // The rotation of this Tile (in 90 degree clockwise turns)
    bool placed,                    // Whether this Tile has been placed within the image
         flipped;                   // Whether this Tile has been flipped to fit in the image

    /**
     * Transforms this Tile based on its orientation.
     * Should only be called once per tile; additional calls may misorient the Tile.
     */
    void orient() {
        transformMatrix(contents, flipped, rotation);
    } // orient()

    /**
     * Prints the contents of this Tile.
     */
    // void print() {
    //     for(auto v : contents) {
    //         for(bool s : v) {
    //             cout << (s ? '#' : '.');
    //         } // for(s)
    //         cout << endl;
    //     } // for(v)
    //     cout << endl;
    // } // print()
}; // Tile

int main() {
    string inputVal;
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 1;
    } // if

    // Variables:
    unordered_map<int, Tile> tiles; // Maps IDs to Tiles
    int lineNum = 0,                // The current line num within the Tile being read
        tileID = 0,                 // The ID of the current Tile
        firstCorner = -1;           // The ID of the first corner tile

    while(getline(input, inputVal)) {
        // Skip blank lines:
        if(inputVal.length() == 1) {
            continue;
        } // if(...1)
        // Get tile ID from header:
        else if(inputVal[0] == 'T') {
            tileID = stoi(inputVal.substr(inputVal.find(" ") + 1, 4));
            lineNum = 0;
        } // else if(...'T')
        // Read Tile data:
        else {
            // Remove newline:
            inputVal.pop_back();

            // Save first line as an edge:
            if(lineNum == 0) {
                for(int i = 0; i < 10; i++) {
                    tiles[tileID].edges[0][i] = inputVal[i] == '#';
                } // for
            } // if(...0)
            // Save last line as an edge (reversed to maintain clockwise-ness):
            else if(lineNum == 9) {
                for(int i = 0; i < 10; i++) {
                    tiles[tileID].edges[2][9-i] = inputVal[i] == '#';
                } // for
            } // else if(...9)
            // Save Tile contents:
            else {
                for(int i = 1; i < 9; i++) {
                    tiles[tileID].contents[lineNum-1][i-1] = inputVal[i] == '#';
                } // for
            } // else
            // Create side edges (left edge reversed for clockwise-ness):
            tiles[tileID].edges[3][9-lineNum] = inputVal.front() == '#';
            tiles[tileID].edges[1][lineNum] = inputVal.back() == '#';

            // Increment the line number:
            lineNum++;
        } // else
    } // while
    input.close();

    // Use the same method as Part 1 to find matching edges, but actually save them:
    for(auto i = tiles.begin(); i != tiles.end(); i++) {
        int sideNum = 0,    // The index of the current edge
            numMatches = 0; // The number of matching edges (for finding the first corner)
        for(auto si = i->second.edges.begin(); si != i->second.edges.end(); si++) {
            // If we've already found the adjacent tile for this edge, we don't need to do anything else:
            if(i->second.neighbors[sideNum] != -1) {
                sideNum++;
                numMatches++;
                continue;
            } // if

            bool matchFound = false;        // Used to short-circuit the loop once a match is found
            vector<bool> sr(*si);           // Stores the reveres of the current edge
            reverse(sr.begin(), sr.end());

            for(auto ci = tiles.begin(); ci != tiles.end(); ci++) {
                if(ci != i) {
                    int compSideNum = 0; // The index of the matching edge
                    for(auto csi = ci->second.edges.begin(); csi != ci->second.edges.end(); csi++) {
                        if(*si == *csi || sr == *csi) {
                            // Save these tiles as neighbors of each other:
                            i->second.neighbors[sideNum] = ci->first;
                            ci->second.neighbors[compSideNum] = i->first;

                            // Mark this as a match found:
                            matchFound = true;
                            numMatches++;
                            break;
                        } // if(*si...)
                        compSideNum++;
                    } // for(csi)
                } // if(ci...)
                // If a match was found, we're done with this edge:
                if(matchFound) {
                    break;
                } // if(matchFound)
            } // for(ci)
            sideNum++;
        } // for(si)
        // If this is the first corner Tile we've found, save it:
        if(numMatches == 2 && firstCorner == -1) {
            firstCorner = i->first;
        } // if(numMatches...)
    } // for(i)

    // Now that we know which Tiles are adjacent, we can start putting the image together.
    // First, we determine where each Tile is in the image.
    // We use the upper-left corner (the first corner Tile we found) as an anchor for the rest.
    // (This step (placement) could like be combined with the next (orientation).
    //   Doing this would avoid a potential issue with the orientation of the first Tile.)

    // Placement variables:
    vector<vector<int>> locs(12, vector<int>(12, -1)); // The matrix of Tile IDs in the final image
    locs[0][0] = firstCorner;

    // Top edge:
    Tile currentTile = tiles[locs[0][0]];
    tiles[locs[0][0]].placed = true;
    // Find a Tile adjacent to the upper-left Tile:
    for(int i = 0; i < 4; i++) {
        if(currentTile.neighbors[i] != -1) {
            // Place this tile in the image:
            locs[0][1] = currentTile.neighbors[i];
            currentTile = tiles[locs[0][1]];
            tiles[locs[0][1]].placed = true;
            break;
        } // if
    } // for
    // Fill out the remainder of the top row:
    for(int currentPos = 2; currentPos < 12; currentPos++) {
        int nextI = -1; // The index of the next Tile in the neighbors vector
        // Find the edge that's adjacent to the previous Tile:
        for(int i = 0; i < 4 && nextI == -1; i++) {
            if(currentTile.neighbors[i] == locs[0][currentPos-2]) {
                nextI = i;
                break;
            } // if
        } // for(i)
        // Use this index to get the next Tile in the row and place it int he image:
        nextI = (nextI + 2) % 4;
        locs[0][currentPos] = currentTile.neighbors[nextI];
        currentTile = tiles[locs[0][currentPos]];
        tiles[locs[0][currentPos]].placed = true;
    } // for(currentPos)

    // Left edge:
    currentTile = tiles[locs[0][0]];
    // Find the other Tile adjacent to the upper-left Tile:
    for(int i = 0; i < 4; i++) {
        if(currentTile.neighbors[i] != -1 && currentTile.neighbors[i] != locs[0][1]) {
            // Place this Tile in the image:
            locs[1][0] = currentTile.neighbors[i];
            currentTile = tiles[locs[1][0]];
            tiles[locs[1][0]].placed = true;
            break;
        } // if
    } // for(i)
    // Fill out the remainder of the first column (same method as the first row):
    for(int currentPos = 2; currentPos < 12; currentPos++) {
        int nextI = -1;
        for(int i = 0; i < 4 && nextI == -1; i++) {
            if(currentTile.neighbors[i] == locs[currentPos-2][0]) {
                nextI = i;
                break;
            } // if
        } // for(i)
        nextI = (nextI + 2) % 4;
        locs[currentPos][0] = currentTile.neighbors[nextI];
        currentTile = tiles[locs[currentPos][0]];
        tiles[locs[currentPos][0]].placed = true;
    } // for(currentPos)
    // Remainder of image:
    for(int y = 1; y < 12; y++) {
        for(int x = 1; x < 12; x++) {
            bool tileFound = false; // Used to short-circuit the loop once the proper Tile is found
            // Each pair of Tiles that are diagonal to each other share two adjacent Tiles.
            // Use this fact to identify the remaining Tiles:
            for(int ea : tiles[locs[y-1][x]].neighbors) {
                // Skip Tiles that don't exist or are already in the image:
                if(ea == -1 || tiles[ea].placed) {
                    continue;
                } // if(ea...)
                for(int eb : tiles[locs[y][x-1]].neighbors) {
                    // Skip Tiles that don't exist or are already in the image:
                    if(eb == -1 || tiles[eb].placed) {
                        continue;
                    } // if(eb...)
                    // If these neighbors are the same, we've found the next tile; place it in the image:
                    if(ea == eb) {
                        locs[y][x] = ea;
                        tiles[ea].placed = true;
                        tileFound = true;
                        break;
                    } // if(ea == eb)
                } // for(eb)
                if(tileFound) {
                    break;
                } // if(tileFound)
            } // for(ea)
        } // for(x)
    } // for(y)

    // Now that all the Tiles are placed, they can be oriented.
    // Once again, use the upper-left Tile as an anchor.
    int lastE = -1; // Same purpose as nextI above

    // Orient the upper-left Tile:
    for(int i = 0; i < 4; i++) {
        // Ensure the two -1 neighbors are on the left and top of the Tile:
        if(tiles[locs[0][0]].neighbors[i] == -1 && tiles[locs[0][0]].neighbors[(i + 1) % 4] == -1) {
            tiles[locs[0][0]].rotation = 3 - i;
            lastE = (i + 2) % 4;
            tiles[locs[0][0]].orient();
            break;
        } // if
    } // for(i)
    // Orient the top row (use Tile to the left as an anchor):
    for(int x = 1; x < 12; x++) {
        // Get some references so we aren't accessing things a whole lot:
        Tile& currentTile  = tiles[locs[0][x]],
              previousTile = tiles[locs[0][x-1]];
        // Find the edge that's adjacent to the previous Tile:
        for(int i = 0; i < 4; i++) {
            if(currentTile.neighbors[i] == locs[0][x-1]) {
                // Determine if this Tile should be flipped:
                // (Explanation at top of file)
                if(currentTile.edges[i] == previousTile.edges[lastE]) {
                    currentTile.flipped = !previousTile.flipped;
                } // if(...[lastE])
                else {
                    currentTile.flipped = previousTile.flipped;
                } // else

                // Determine the orientation of this Tile:
                lastE = (i + 2) % 4;
                currentTile.rotation = currentTile.flipped ? (i + 3) % 4 : 3 - i;

                // Orient this Tile's contents:
                currentTile.orient();
            } // if(...[x-1])
        } // for(i)
    } // for(x)
    // Orient the remainder of the image (use the Tile above as an anchor):
    // (This uses the same method as above, but a different anchor direction)
    for(int y = 1; y < 12; y++) {
        for(int x = 0; x < 12; x++) {
            Tile& currentTile  = tiles[locs[y][x]],
                  previousTile = tiles[locs[y-1][x]];
            // Since the last oriented Tile isn't the anchor for this Tile, we have to reset lastE:
            lastE = previousTile.rotation % 2 == 0 || previousTile.flipped ? (previousTile.rotation + 2) % 4 : previousTile.rotation;
            for(int i = 0; i < 4; i++) {
                if(currentTile.neighbors[i] == locs[y-1][x]) {
                    if(currentTile.edges[i] == previousTile.edges[lastE]) {
                        currentTile.flipped = !previousTile.flipped;
                    } // if(...[lastE])
                    else {
                        currentTile.flipped = previousTile.flipped;
                    } // else
                    lastE = (i + 2) % 4;
                    currentTile.rotation = currentTile.flipped ? i : (4 - i) % 4;
                    currentTile.orient();
                } // if(...[x])
            } // for(i)
        } // for(x)
    } // for(y)

    // Now that everything's oriented properly, we can finally construct the image:
    vector<vector<bool>> img(96, vector<bool>(96, false)); // The actual image
    for(int y = 0; y < 96; y++) {
        for(int x = 0; x < 96; x++) {
            img[y][x] = tiles[locs[y/8][x/8]].contents[y%8][x%8];
        } // for(x)
    } // for(y)

    // Now all that's left to do is find (and remove) all the sea monsters:
    int monsterFound = false, // If we have found a sea monster (they all share an orientation, so we only need one)
        rotation = 0;         // The current rotation of the image in 90 degree clockwise turns
    while(true) {
        // Bounds are determined by the size of the sea monsters (they're 3 rows by 20 columns):
        for(int y = 1; y < 95; y++) {
            for(int x = 19; x < 96; x++) {
                // If there's a sea monster present, mark that we've found one and remove it:
                if(img[y][x-19] && img[y+1][x-18] &&
                        img[y+1][x-15] && img[y][x-14] &&
                        img[y][x-13] && img[y+1][x-12] &&
                        img[y+1][x-9] && img[y][x-8] &&
                        img[y][x-7] && img[y+1][x-6] &&
                        img[y+1][x-3] && img[y][x-2] &&
                        img[y-1][x-1] && img[y][x-1] && img[y][x]) {
                    monsterFound = true;
                    img[y][x-19] = false;
                    img[y+1][x-18] = false;
                    img[y+1][x-15] = false;
                    img[y][x-14] = false;
                    img[y][x-13] = false;
                    img[y+1][x-12] = false;
                    img[y+1][x-9] = false;
                    img[y][x-8] = false;
                    img[y][x-7] = false;
                    img[y+1][x-6] = false;
                    img[y+1][x-3] = false;
                    img[y][x-2] = false;
                    img[y-1][x-1] = false;
                    img[y][x-1] = false;
                    img[y][x] = false;
                } // if(img...)
            } // for(x)
        } // for(y)

        // Once we've found at least one monster, we can stop:
        if(monsterFound) {
            break;
        } // if(monsterFound)

        // If no monsters were found, transform the image and keep going:
        rotation++;
        transformMatrix(img, false, 1);
        // Once the image has been rotated 4 times, it needs to be flipped:
        if(rotation == 4) {
            transformMatrix(img, true, 0);
        } // if(...4)
        // If the image has been rotated 8 times and we still haven't found anything, go ahead and stop:
        else if(rotation == 8) {
            cout << "No monsters found" << endl;
            break;
        } // else if(...8)
    } // while

    // Determine how many spaces are still active:
    int result = 0;
    for(auto r : img) {
        for(bool c : r) {
            result += c;
        } // for(c)
    } // for(r)

    //Print final solution:
    cout << result << endl;
} // main()