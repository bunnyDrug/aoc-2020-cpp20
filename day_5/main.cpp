#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// The seat partition is a binary representation.
// I can create the seat number by shifting bits and then
// adding the totals of each bit shifted.
// Start from the least significant bit (shift by that index);
int btoi(string binaryChars, char bitChar) {
    int result = 0;
    std::reverse(std::begin(binaryChars), std::end(binaryChars));
    for (int i = 0; i < binaryChars.length(); i++) {
        if (binaryChars[i] == bitChar) {
            result += 1 << i;
        }
    }
    return result;
}

// Input reader...
vector<string> getBoardingPasses() {
    fstream inputFile("../input.txt");
    string line;
    vector<string> boardingPasses;
    // create vector of maps for each passport
    while (getline(inputFile, line)) {
        boardingPasses.push_back(line);
    }
    inputFile.close();
    return boardingPasses;
}

int main() {
    int IDFACTOR = 8;

    vector<string> boardingPasses = getBoardingPasses();
    vector<int> seatIDs;

    for (auto line: boardingPasses) {

        string seatRow_bin = line.substr(0, 7);
        string seatColumn_bin = line.substr(7);

        auto seatRow = btoi(seatRow_bin, 'B');
        auto seatColumn = btoi(seatColumn_bin, 'R');

        auto seatNum = (seatRow * IDFACTOR) + seatColumn;
        seatIDs.push_back(seatNum);

    }

    // Part 1
    sort(seatIDs.begin(), seatIDs.end());
    cout << "Max Seats: " << seatIDs[seatIDs.size() -1] << endl;

    // Part 2
    // find missing seat
    for (int i = 0; i < seatIDs.size(); i++) {
        if (seatIDs[i]+1 != seatIDs[i+1]) { // missing seat won't be in sequence
            cout << "Your seat is: " << seatIDs[i] + 1 << endl;
            break;
        }
    }
}
