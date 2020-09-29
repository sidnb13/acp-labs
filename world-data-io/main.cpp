#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

string getStringAtLoc(const string& s, int idx);

int main() {
    fstream csv("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv");

    if (!csv.is_open())
        return EXIT_FAILURE;

    string token {};
    for (int i{}; i <= 28; i++)
        getline(csv, token);

    const vector<string> developedRegions = {"\"NORTHERN AMERICA\"", "\"EUROPE\"",
                                             "\"Australia/New Zealand\"",
                                             "\"Japan\"",
                                             "\"United States of America\""};

    // replaces a hash map as would be used in Java
    vector<pair<string, double>> developedCountries {};
    vector<pair<string, double>> allCountries {};

    // get all countries into appropriate vectors
    while (getline(csv, token)) {
        allCountries.emplace_back(getStringAtLoc(token, 2), stod(getStringAtLoc(token, 15)));
        if (count(developedRegions.begin(), developedRegions.end(), getStringAtLoc(token, 2)))
            developedCountries.emplace_back(getStringAtLoc(token, 2), stod(getStringAtLoc(token, 15)));
    }
    csv.close();
    // sorting
    sort(developedCountries.begin(), developedCountries.end(), [](const pair<string, double>& f, const pair<string, double>& s) {
        return f.second > s.second;
    });
    sort(allCountries.begin(), allCountries.end(), [](const pair<string, double>& f, const pair<string, double>& s) {
        return f.second > s.second;
    });
    /*for (pair<string, double>& p : developedCountries)
        cout << p.first << " " << p.second << endl;*/

    for (int i = 0; i < developedCountries.size(); i++) {
        if (developedCountries.at(i).first == "\"United States of America\"")
            cout << "The US is ranked " << i + 1 << "th " << "of all developed regions." << endl;
    }
    for (int i = 0; i < allCountries.size(); i++) {
        if (allCountries.at(i).first == "\"United States of America\"")
            cout << "The US is ranked " << i + 1 << "th " << "overall." << endl;
    }
}


string getStringAtLoc(const string& s, int idx) {
    stringstream ip(s);
    string res {};
    for (int i {}; i <= idx; i++)
        getline(ip, res, ',');
    return res;
}
