#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

string getStringAtLoc(const string& s, int idx) {
    stringstream ip(s);
    string res{};
    for (int i{}; i <= idx; i++)
        getline(ip, res, ',');
    return res;
}

struct tpl {
    string regionName;
    double age{};
};

struct compare {
    inline bool operator() (tpl& one, tpl& two) {
        return (one.age > two.age);
    }
};

int main() {
    fstream csv ("WPP2015_MORT_F07_1_LIFE_EXPECTANCY_0_BOTH_SEXES.csv");
    if (!(csv.is_open() && csv.good()))
        exit(1);

    string token {};
    for (int i{}; i <= 28; i++) getline(csv, token);

    const vector<string> developedRegions =
            {"\"NORTHERN AMERICA\"", "\"EUROPE\"","\"Australia/New Zealand\"","\"Japan\"","\"United States of America\""};
    // replaces a hash map as would be used in Java
    vector<tpl> developedCountries;
    vector<tpl> allCountries;
    // get all countries into appropriate vectors
    while (getline(csv, token)) {
        tpl c;
        c.regionName = getStringAtLoc(token, 2);
        c.age = stod(getStringAtLoc(token, 15));
        allCountries.push_back(c);
        if (count(developedRegions.begin(), developedRegions.end(), c.regionName))
            developedCountries.push_back(c);
    }
    csv.close();
    // sorting
    std::sort(developedCountries.begin(), developedCountries.end(), compare());
    std::sort(allCountries.begin(), allCountries.end(), compare());

    for (int i = 0; i < developedCountries.size(); i++) {
        if (developedCountries.at(i).regionName == "\"United States of America\"")
            printf("The US is rank #%d of all developed regions.\n", i+1);
    }
    for (int i = 0; i < allCountries.size(); i++) {
        if (allCountries.at(i).regionName == "\"United States of America\"")
            printf("The US is rank #%d of all regions.\n", i+1);
    }
}
