#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Rec {
    public:
        string date;
        string region;
        string rep;
        string item;
        int units{};
        double unitCost{};
        double total{};

    Rec (const string& d, const string& reg, const string& rp,
        const string& i, const int& u, const double& c) {
        date = d;
        region = reg;
        rep = rp;
        item = i;
        units = u;
        unitCost = c;
    }
    void initTotal() {total = unitCost * units;}
};

string parse(const string& s, const int& idx) {
    stringstream ss(s); string t {};
    for (int i {}; i <= idx; ++i) getline(ss, t, ',');
    return t;
}

int main() {
    string tkn {}, t {};
    vector<Rec> list;
    fstream txt("SalesData.txt");
    getline(txt, tkn);

    if (!(txt.good() && txt.is_open())) exit(0);

    while (getline(txt, tkn)) {
        Rec res(
                parse(tkn, 0),
                parse(tkn, 1),
                parse(tkn, 2),
                parse(tkn, 3),
                stoi(parse(tkn, 4)),
                stod(parse(tkn, 5))
        );
        res.initTotal();
        list.push_back(res);
    }

    sort(list.begin(), list.end(), [](const Rec& a, const Rec& b) {
        return a.total > b.total;
    });

    for (const Rec& x : list) {
        cout << "Record: " << x.date << "," << x.region << "," << x.rep << ","
        << x.item << ", " << x.units << ", " << x.unitCost << ", " << x.total << endl;
    }
}