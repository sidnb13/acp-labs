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

    Rec() = default;

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
    int i;

    vector<Rec> list;

    fstream txt("SalesDataDyn.csv");
    getline(txt, tkn);
    tkn.erase(remove(tkn.begin(), tkn.end(), ' '), tkn.end());

    cout << "Record: " << parse(tkn,0) << ", " << parse(tkn,1) << ", " << parse(tkn,2) << ", "
        << parse(tkn,3) << ", 0, 0, 0" << endl;

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

    std::sort(list.begin(), list.end(), [](const Rec& a, const Rec& b) {
        return a.total < b.total;
    });

    Rec ** arr = new Rec * [list.size()];
    Rec x;

    for (i = 0; i < list.size(); ++i) {
        x = list.at(i);
        arr[i] = new Rec(x.date, x.region, x.rep, x.item, x.units, x.unitCost);
        arr[i]->total = x.total;
    }

    for (i = 0; i < list.size() - 1; ++i)
        if (arr[i]->rep == "Kivell" && arr[i+1]->rep == "Howard")
            std::swap(arr[i], arr[i+1]);

    for (i = 0; i < list.size(); ++i) {
        cout << "Record: " << arr[i]->date << ", " << arr[i]->region << ", " << arr[i]->rep << ", "
             << arr[i]->item << ", " << arr[i]->units << ", " << arr[i]->unitCost << ", " << arr[i]->total << endl;
        delete arr[i];
    }
    delete[] arr;
}