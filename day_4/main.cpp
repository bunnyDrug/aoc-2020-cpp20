#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

int main() {

    // read input
    vector<map<string, string>> vector1;
    map<std::string, std::string> m;
    fstream inputFile("../input.txt");
    string line;
    // create vector of maps for each passport
    while (getline(inputFile, line)) {
        if (line[0] == 0) {
            vector1.push_back(m);
            m.clear();
        }
        // take each line and process each entry split by spaces
        // empty lines mean a new passport
        while (line.find(' ') != -1) {  // if there are new elements - process from back to front
            int space = line.find_last_of(' ');
            string poppedString = line.substr(space + 1);
            int delim = poppedString.find_last_of(':');
            string key = poppedString.substr(0, delim);
            string value = poppedString.substr(delim + 1);
            m.emplace(key, value);
            line.erase(space);
        }
        int delim = line.find(':');
        string key = line.substr(0, delim);
        string value = line.substr(delim + 1);
        m.emplace(key, value);
    }
    vector1.push_back(m);
    m.clear();

    cout << "Loaded input file and found " << vector1.size() << " passports" << endl;
    cout << "Processing..." << endl << endl;


    int validPassports = 0;
    for (const auto& passport: vector1){
        string securityPolicy[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
        int policyMatches = 0;
        for (const auto& p: securityPolicy) {
            if (passport.contains(p)) {

                auto passportElement = passport.find(p);

                if (passportElement->first == "byr") {
                    if (stoi(passportElement->second) >= 1920 && stoi(passportElement->second) <= 2002) {
                        policyMatches ++;
                        continue;
                    }
                }

                if (passportElement->first == "iyr") {
                    if (stoi(passportElement->second) >= 2010 && stoi(passportElement->second) <= 2020) {
                        policyMatches ++;
                        continue;
                    }
                }

                if (passportElement->first == "eyr") {
                    if (stoi(passportElement->second) >= 2020 && stoi(passportElement->second) <= 2030) {
                        policyMatches ++;
                        continue;
                    }
                }

                if (passportElement->first == "hgt") {
                    regex cmHeightRegex("\d*(cm)");
                    if (regex_search(passportElement->second, cmHeightRegex)) {
                        if (stoi(passportElement->second) >= 150 && stoi(passportElement->second) <= 193) {
                            policyMatches++;
                            continue;
                        }
                    }
                    regex inchHeightRegex("\d*(in)");
                    if (regex_search(passportElement->second, inchHeightRegex)) {
                        if (stoi(passportElement->second) >= 59 && stoi(passportElement->second) <= 76) {
                            policyMatches++;
                            continue;
                        }
                    }
                }

                if (passportElement->first == "hcl") {
                    regex hairColour("#([a-f0-9]{6})");
                    if (regex_search(passportElement->second, hairColour)) {
                        policyMatches++;
                        continue;
                    }
                }

                if (passportElement->first == "ecl") {
                    string eyeColour[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                    int counter = 0;
                    for (auto colour: eyeColour) {
                        if (passportElement->second == colour) {
                            counter ++;
                        }
                    }
                    if (counter == 1) {
                        policyMatches ++;
                        continue;
                    }
                }

                if (passportElement->first == "pid") {
                    if (passportElement->second.length() == 9) {
                        regex ds("([0-9]{9})");
                        if (regex_search(passportElement->second, ds)) {
                            policyMatches ++;
                            continue;
                        }
                    }
                }

            }
        }
        if (policyMatches == 7) {
            validPassports ++;
        }
        policyMatches = 0;
    }

    cout << "valid passports = " << validPassports << endl;

    return 0;
}
