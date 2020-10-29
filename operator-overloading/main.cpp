#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
using namespace std;

class SalesRep {
public:
    char rep[50];
    char region[50];
};

class ItemCatalog {
    friend class SALESREC;
public:
    char item[50];
private:
    float unitCost;

};

class SALESREC: public SalesRep, public ItemCatalog {
    friend ostream& operator << (ostream&, const SALESREC&);
public:
    char date[10];
    int units;

    void setUnitCost(float nc) {unitCost = nc;}
    [[nodiscard]] float getUnitCost() const {return unitCost;}
    [[nodiscard]] float Total() const {return  unitCost * (float) units;}
    void operator +(const SALESREC& r) {units += r.units;}
    bool operator ==(const SALESREC& r) {
        return r.item == this->item && r.date == this->date && r.rep == this->rep;
    }
};

ostream &operator <<(ostream &o, const SALESREC& r) {
    return o << "Record: " << r.date << ", " << r.region << ", "
        << r.rep << ", " << r.item << ", " << r.units << ", "
               << r.getUnitCost() << ", " << r.Total() << endl;
}

int main() {
    ifstream infile;
    char cNum[10];
    int i {};
    SALESREC* salesArr[40];
    int salesArrayCount = 0;

    infile.open ("SalesDataP5.csv");
    if (infile.is_open()) {
        int c {};
        float inputUnitCost;
        while (infile.good()) {
            salesArr[c] = new SALESREC();
            infile.getline(salesArr[c]->date, 256, ',');
            infile.getline(salesArr[c]->region, 256, ',');
            infile.getline(salesArr[c]->rep, 256, ',');
            infile.getline(salesArr[c]->item, 256, ',');
            infile.getline(cNum, 256, ',');
            salesArr[c]->units = atoi(cNum); //NOLINT
            infile.getline(cNum, 256, '\n');
            inputUnitCost = atof(cNum); //NOLINT
            salesArr[c]->setUnitCost(inputUnitCost);
            c++;
        }
        salesArrayCount = c-1;
        infile.close();
    } else {cout << "Error opening file";}

    [[maybe_unused]] auto comp = [](SALESREC l, SALESREC r) {
        return l.Total() < r.Total();
    };
    set<SALESREC, decltype(comp)> set;

    cout << " Unsorted Sales Record Array\n" ;
    for (i=0; i < salesArrayCount; i++)
        cout << *salesArr[i];
    for (i = 0; i < salesArrayCount; ++i) {
        for (int j {}; j < salesArrayCount; ++j)
            if (salesArr[i] == salesArr[j] && i != j)
                *salesArr[i] + *salesArr[j];
        set.insert(*salesArr[i]);
    }

    SALESREC tempArr[set.size()];
    copy(set.begin(), set.end(), tempArr);
    SALESREC* s[set.size()];
    for (i = 0; i < set.size(); ++i) {s[i] = &tempArr[i];}

    cout << " - - - - - - - - - - - -\n" ;
    cout << " Sorted Sales Record Array\n";
    for (i=0; i < set.size(); i++)
        cout << *s[i];
    for (i=0; i < salesArrayCount; i++)
        delete salesArr[i];
}