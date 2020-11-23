/*
Header file for single linked list class library
*/

#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct Airport {
    char code[5]{};
    double longitude{};
    double latitude{};

    Airport() = default;

    [[maybe_unused]] Airport(const char* cod, double lat, double lon) {
        strcpy(code, cod);
        latitude = lat;
        longitude = lon;
    }

    void dsp() {cout << "{" << code << ", (" << latitude << ", " << longitude << ")}" << endl;}
};

struct Node {
    Airport* dat;
    Node* next;
};

class slist {
public:
    int length{};
    Node* head{};
    Node* tail{};

    slist();
    slist(slist* s, int i1, int i2); //added in to help with sublist method
    ~slist();
    void add(Airport* a);
    //void remove(char cod[], double lat, double lon);
    [[maybe_unused]] void clear();
    [[maybe_unused]] [[nodiscard]] bool equals(const slist& s) const;
    [[nodiscard]] Node* get(int idx) const;
    [[maybe_unused]] void insert(int idx, Airport* a);
    void exchg(int i1, int i2) const;
    [[maybe_unused]] void swap(int i1, int i2);
    [[maybe_unused]] [[nodiscard]] bool isEmpty() const;
    [[maybe_unused]] Node* remove(int idx);
    [[maybe_unused]] void set(int idx, Airport* a) const;
    [[nodiscard]] int size() const;
    [[maybe_unused]] slist subList(int s, int e);
    [[maybe_unused]] [[nodiscard]] string toString() const;
};