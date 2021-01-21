#include "disc.h"

using namespace std;

//
// Created by Sid Baskaran on 1/14/21.
//

Disc::Disc(const int &size) {
    this->setSize(size);
}

bool Disc::setSize(const int &s) {
    this->size = s;
    return true;
}

int Disc::getSize() const {
    return this->size;
}

string Disc::toString() const {
    return std::to_string(this->getSize());
}