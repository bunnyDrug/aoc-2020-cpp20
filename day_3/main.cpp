#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long howManyTreesV2(int horizon, int vertical, std::vector<std::string> input);
std::vector<std::string> readFile(std::ifstream file);

using namespace std;


int main() {

    // READ FILE.
    auto input = readFile(ifstream("../input.txt"));

    auto pass1V2 = howManyTreesV2(1, 1, input);
    auto pass2V2 = howManyTreesV2(3, 1, input);
    auto pass3V2 = howManyTreesV2(5, 1, input);
    auto pass4V2 = howManyTreesV2(7, 1, input);
    auto pass5V2 = howManyTreesV2(1, 2, input);

    cout << "Pass1 Version 2: " << pass1V2 << endl;
    cout << "Pass2 Version 2: " << pass2V2 << endl;
    cout << "Pass3 Version 2: " << pass3V2 << endl;
    cout << "Pass4 Version 2: " << pass4V2 << endl;
    cout << "Pass5 Version 2: " << pass5V2 << endl;

    auto x = pass1V2 * pass2V2 * pass3V2 * pass4V2 * pass5V2;
    cout << x;
    return 0;
}


long howManyTreesV2(int horizon, int vertical, std::vector<std::string> input) {
    long treesEncountered = 0;
    // (an array index)
    int tobogganPos = 0;

    // set the line start to the toboggan vertical value. no point checking 0
    for ( int lineNum = vertical; lineNum < input.size(); lineNum += vertical ) {

        // the current map line.
        auto thisLine = input[lineNum];

        // grid index + the map move
        auto newPosition = (tobogganPos + horizon);

        // Don't 'generate' a visual map. If it's a repeating pattern we can
        // just move the toboggan (index) to where it would be on a visual map.

        // If the new position would take us over the array index
        if (newPosition > (thisLine.length() -1) ) {
            // find out the new index by subtracting the line length over the
            // number of times it goes into the new position without remainders.
            // Example: lineLength = 11,
            //          shift = 3
            //          currentIndex = 9
            //          newPosition = 3+9 = 12
            //          12 - (11 * (12 / 11)) = 1
            // 0 1 2 3 4 5 6 7 8 9 10
            // ->^               ^-->
            newPosition = newPosition - (thisLine.length() * (newPosition / thisLine.length()));
        }
        tobogganPos = newPosition;
        treesEncountered += (thisLine.at(tobogganPos) == '#');
    }
    return treesEncountered;
}

std::vector<std::string> readFile(std::ifstream file) {
    string line;
    vector<string> v;
    while (getline(file, line)) {
        v.push_back(line);
    }
    file.close();
    return v;
}