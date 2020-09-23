#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

struct SALESREC {
    char     date[10];
    char     region[10];
    char     rep[10];
    char     item[10];
    int      units;
    float    unitCost;
    float    Total;
};

void simpleSortTotal(SALESREC* s[40], int c);

int main() {
    ifstream infile;
    int i=0;
    char cNum[10];
    SALESREC salesArr[40];
    int salesArrayCount = 0;
    SALESREC* s[40];

    infile.open("SalesData.txt", ifstream::in);

    if (infile.is_open()) {
        int   c=0;
        while (infile.good()) {
            infile.getline(salesArr[c].date, 256, ',');
            infile.getline(salesArr[c].region, 256, ',');
            infile.getline(salesArr[c].rep, 256, ',');
            infile.getline(salesArr[c].item, 256, ',');
            infile.getline(cNum, 256, ',');
            salesArr[c].units = (int) strtol(cNum, nullptr, 10);
            infile.getline(cNum, 256, ',');
            salesArr[c].unitCost = (float) strtod(cNum, nullptr);
            infile.getline(cNum, 256, '\n');
            salesArr[c].Total = (float) strtod(cNum, nullptr);

            i++;
            c++;
        }
        salesArrayCount = c-1;
        infile.close();
    }
    else {
        cout << "Error opening file";
    }

    // Initialize the sort array pointers
    for (i = 0; i < salesArrayCount; i++)
        s[i] = &salesArr[i];

    simpleSortTotal(s, salesArrayCount);

    for (i = 0; i < salesArrayCount; i++)
        cout << "Record: " << s[i]->date <<", " << s[i]->region << ", "
        << s[i]->rep << ", " << s[i]->item << ", " << s[i]->units
        << ", " << s[i]->unitCost << ", " << s[i]->Total << endl;

}

// arguments will be an array of pointers and a count
void simpleSortTotal(SALESREC* s[40], int c) {
    int minIdx = 0;
    for (int i = 0; i < c; i++) {
        for (int j = i+1; j < c; j++)
            // total pointed at by i < total pointed at by j
            if (s[j] < s[minIdx])
                minIdx = j;
        // swap pointer to record I with pointer to record j
        SALESREC * temp = s[minIdx];
        *s[minIdx] = *s[i];
        *s[i] = *temp;
    }
}