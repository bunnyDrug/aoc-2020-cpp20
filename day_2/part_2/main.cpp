#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    // READ FILE
    ifstream inputFile("../input.txt");
    string line;
    int N = 0;
    // Just do the work in the read file loop...
    while (getline(inputFile, line)) {
        // Split lines into useful stuff - the password, policy, min, max, etc.
        int deliminator = line.find_first_of(':');
        string passwd = line.substr(deliminator + 2 );
        string policy = line.substr(0, deliminator);
        string mandatoryChar = line.substr(deliminator - 1, 1);

        int pos1 = stoi(policy.substr(0, policy.find_first_of('-')));
        int pos2 = stoi(policy.substr(policy.find_first_of('-') + 1));

        int valid = 0;
                  // no concept of zero index
        valid += (passwd[pos1 - 1] == mandatoryChar[0]);
        valid += (passwd[pos2 - 1] == mandatoryChar[0]);

        // You can only have one match according to the policy.
        N += (valid == 1);
    }
    inputFile.close();
    cout << N;
}
