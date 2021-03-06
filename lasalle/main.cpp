#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "slist.h"
#include <cmath>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

double deg2rad(double deg) {return (deg * 3.14159265358979323846 / 180);}

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double distToAUS(Airport* a) {return distanceEarth(a->latitude, a->longitude, 30.1944, 97.67);}

void simpleSortTotal(slist * s) {
    for (int i {}; i < s->size(); i++) {
        for (int j = i; j < s->size(); j++)
            if (distToAUS(s->get(i)->dat) > distToAUS(s->get(j)->dat))
                s->exchg(i, j);
    }
}

int main() {
    ifstream infile;
    char cNum[10];
    auto* airportArr = new slist();

    infile.open ("USAirportCodes.csv", ifstream::in);
    auto maxApt = new Airport("TST", 30, 98);
    if (infile.is_open()) {
        while (infile.good()) {
            auto a = new Airport();
            infile.getline(a->code, 256, ',');
            infile.getline(cNum, 256, ',');
            a->latitude = atof(cNum); //NOLINT
            infile.getline(cNum, 256, '\n');
            a->longitude = atof(cNum); //NOLINT

            if (distToAUS(a) > distToAUS(maxApt) && a->longitude != 0 && a->latitude != 0)
                maxApt = a;

            if (distToAUS(a) <= 100.0 * 1.609)
                airportArr->add(a);
        }
        infile.close();
    }
    else cout << "Error opening file";

    simpleSortTotal(airportArr);

    cout << "Farthest airport from KAUS: " << maxApt->code << " at " << distToAUS(maxApt) << " km" << endl;
    cout << "Airports within 100 mi * 1.609 km/mi: " << endl << airportArr->toString();
}