#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

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
    int i, c = 30, inc {};
    fstream txt("SalesDataDyn.csv");
    getline(txt, tkn);
    tkn.erase(remove(tkn.begin(), tkn.end(), ' '), tkn.end());
    cout << "Record: OrderDate, Region, Rep, Item, 0, 0, 0" << endl;

    Rec ** arr = new Rec * [c];

    if (!(txt.good() && txt.is_open())) exit(0);

    while (getline(txt, tkn)) {
        tkn.erase(remove(tkn.begin(), tkn.end(), ' '), tkn.end());
        for (i = 0; i < tkn.length() - 1; ++i)
            if (islower(tkn.at(i)) && isupper(tkn.at(i+1)))
                tkn.insert(i+1, " ");
        arr[inc] = new Rec(parse(tkn, 0),parse(tkn, 1),parse(tkn, 2),parse(tkn, 3),
                           stoi(parse(tkn, 4)),stof(parse(tkn, 5)));
        arr[inc]->initTotal();
        inc++;
    }

    for (i = 0; i < 30; i++)
        for (int j {}; j < 30; j++)
            if (arr[i]->total < arr[j]->total)
                swap(arr[i], arr[j]);

    for (i = 0; i < c; ++i) {
        cout << "Record: " << arr[i]->date << ", " << arr[i]->region << ", " << arr[i]->rep << ", "
             << arr[i]->item << ", " << arr[i]->units << ", " << arr[i]->unitCost << ", " << arr[i]->total << endl;
        delete arr[i];
    }
    delete[] arr;
}