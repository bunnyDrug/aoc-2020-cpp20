#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    auto policyMatch = [](int z, int m, int x){return (z >= m && z <= x);};
    auto countAll = [](string p, char c){return count(p.begin(), p.end(), c);};

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
        int min = stoi(policy.substr(0, policy.find_first_of('-')));
        int max = stoi(policy.substr(policy.find_first_of('-') + 1));

        N +=  policyMatch(countAll(passwd, mandatoryChar[0]), min, max);
    }
    inputFile.close();
    cout << N;
}
