#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Rec {
    public:
        string date;
        string region;
        string rep;
        string item;
        int units{};
        float unitCost{};
        float total{};

    Rec (const string& d, const string& reg, const string& rp,
        const string& i, const int& u, const float& c) {
        date = d;
        region = reg;
        rep = rp;
        item = i;
        units = u;
        unitCost = c;
    }
    void initTotal() {total = unitCost * (float) units;}
};

string parse(const string& s, const int& idx) {
    stringstream ss(s); string t {};
    for (int i {}; i <= idx; ++i) getline(ss, t, ',');
    return t;
}

int main() {
    string tkn {}, t {};
    int i {};
    vector<Rec> list;
    fstream txt("SalesDataPt2.csv");
    getline(txt, tkn);
    tkn.erase(remove(tkn.begin(), tkn.end(), ' '), tkn.end());

    cout << tkn << ",Total" << endl;

    if (!(txt.good() && txt.is_open())) exit(0);

    while (getline(txt, tkn)) {
        tkn.erase(remove(tkn.begin(), tkn.end(), ' '), tkn.end());

        for (i = 0; i < tkn.length() - 1; ++i)
            if (islower(tkn.at(i)) && isupper(tkn.at(i+1)))
                tkn.insert(i+1, " ");

        Rec res(parse(tkn, 0),parse(tkn, 1),parse(tkn, 2),parse(tkn, 3),
                stoi(parse(tkn, 4)),stof(parse(tkn, 5)));

        res.initTotal();
        list.push_back(res);
    }

    std::stable_sort(list.begin(), list.end(), [](const Rec& a, const Rec& b) {
        return a.total > b.total;
    });

    for (const Rec& x : list) {
        cout << x.date << "," << x.region << "," << x.rep << ","
        << x.item << "," << x.units << "," << x.unitCost << "," << x.total << endl;
    }
}