#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cctype>

using namespace std;

struct tpl {
    string name;
    double age{};
};

struct compare {
    inline bool operator() (tpl& one, tpl& two) {
        return (one.age > two.age);
    }
};

string getStringAtLoc(const string& s, int idx);
bool isUpperString(const string& s);

int main() {
    fstream csv ("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv");
    if (!(csv.is_open() && csv.good()))
        exit(1);

    string token {};
    for (int i{}; i <= 28; i++) getline(csv, token);

    const vector<string> developedRegions = {"\"NORTHERN AMERICA\"",
                                             "\"EUROPE\"","\"Australia/New Zealand\"","\"Japan\"",
                                             "\"United States of America\""};
    // replaces a hash map as would be used in Java
    vector<tpl> developedCountries;
    vector<tpl> allCountries;

    bool isUnderDevelop;
    // get all countries into appropriate vectors
    while (getline(csv, token)) {
        tpl c = {getStringAtLoc(token, 2), stod(getStringAtLoc(token, 15))};
        bool isRegion = isUpperString(c.name);
        if (isRegion)
            isUnderDevelop = count(developedRegions.begin(), developedRegions.end(), c.name);
        if (!isRegion) {
            allCountries.push_back(c);
            if (isUnderDevelop || count(developedRegions.begin(), developedRegions.end(), c.name))
                developedCountries.push_back(c);
        }
    }
    csv.close();
    /*for (const tpl& t : developedCountries)
        cout << t.name << endl;*/
    // sorting
    sort(developedCountries.begin(), developedCountries.end(), compare());
    sort(allCountries.begin(), allCountries.end(), compare());

    for (int i = 0; i < developedCountries.size(); i++) {
        if (developedCountries.at(i).name == "\"United States of America\"")
            printf("The US is rank #%d of all developed countries.\n", i+1);
    }
    for (int i = 0; i < allCountries.size(); i++) {
        if (allCountries.at(i).name == "\"United States of America\"")
            printf("The US is rank #%d of all countries.\n", i+1);
    }
}

bool isUpperString(const string& s) {
    bool t;
    for (const char& c : s) {
        if (isupper(c) || c == ' ' || c == '"')
            t = true;
        else return false;
    }
    return t;
}

string getStringAtLoc(const string& s, int idx) {
    stringstream ip(s);
    string res{};
    for (int i{}; i <= idx; i++)
        getline(ip, res, ',');
    return res;
}