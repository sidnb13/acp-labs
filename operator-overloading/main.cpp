#include <iostream>
#include <fstream>
#include <cstdlib>
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

    void operator +(const SALESREC& r) {units++;}

    bool operator ==(const SALESREC& r) {
        return r.item == this->item && r.date == this->date && r.rep == this->rep;
    }
};

ostream &operator <<(ostream &o, const SALESREC& r) {
    return o << "Record: " << r.date << ", " << r.region << ", "
               << r.rep << ", " << r.item << ", " << r.units << ", "
               << r.getUnitCost() << ", " << r.Total() << endl;
}

void simpleSortTotal(SALESREC* s[], int c);

int main() {
    ifstream infile;
    char cNum[10];
    SALESREC* salesArr[40];
    int salesArrayCount = 0;
    SALESREC* s[40];

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

    cout << " Unsorted Sales Record Array\n" ;
    for (int i=0; i < salesArrayCount; i++)
        cout << *salesArr[i];

    for (int i {}; i < salesArrayCount; ++i) {
        for (int j {}; j < salesArrayCount; ++j) {
            if (salesArr[i] == salesArr[j] && i != j) {
                salesArr[i]->units += salesArr[j]->units;
                salesArr[i]->setUnitCost(salesArr[i]->getUnitCost() + salesArr[j]->getUnitCost());
                delete salesArr[j];
            }
        }
    }

    for (int i=0; i < salesArrayCount; i++)
        s[i] = salesArr[i];

    simpleSortTotal (s, salesArrayCount);
    cout << " - - - - - - - - - - - -\n" ;
    cout << " Sorted Sales Record Array\n";
    for (int i=0; i < salesArrayCount; i++)
        cout << *s[i];

    for (int i=0; i < salesArrayCount; i++)
        delete salesArr[i];
}

void simpleSortTotal(SALESREC* s[], int c) {
    for (int i=0; i < c; i++)
        for (int j=i; j < c; j++)
            if (s[i]->Total() > s[j]->Total())
                swap(s[i], s[j]);
}