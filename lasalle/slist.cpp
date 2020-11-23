#include "slist.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

slist::slist() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

slist::slist(slist *s, int i1, int i2) {
    this->head = s->get(i1);
    for(int i = i1 + 1; i < i2; i++)
        this->add(s->get(i1)->dat);
    tail = get(i2 - i1 - 1);
}

slist::~slist() {
    Node* current = this->head;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        free(current);
        current = next;
    }
}

void slist::add(Airport* a) {
    Node* toAdd = new Node;
    toAdd->dat = a;
    toAdd->next = nullptr;
    if (length != 0) get(length-1)->next = toAdd;
    else head = toAdd;
    toAdd->next = tail;
    length++;
}

[[maybe_unused]] void slist::clear() {
    Node* current = this->head;
    while(current->next != nullptr) {
        Node* tmp = current;
        delete tmp;
        current = current->next;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

[[maybe_unused]] bool slist::equals(const slist& s) const {
    if(s.length != length) return false;
    Node* cThis = this->head;
    Node* cOther = s.head;
    while(cThis->next != nullptr) {
        Airport* a = cThis->dat;
        Airport* b = cOther->dat;
        if(!(a->code == b->code && a->longitude == b->longitude && a->latitude == b->latitude))
            return false;
        cThis = cThis->next;
        cOther = cOther->next;
    }
    if(cThis->next != cOther->next)
        return false;
    else return true;
}

Node* slist::get(int idx) const {
    Node* curr = this->head;
    for (int i = 0; i < idx; ++i)
        curr = curr->next;
    return curr;
}

[[maybe_unused]] void slist::insert(int idx, Airport* a) {
    Node *n = new Node;
    n->dat = a;
    if (idx == 0) {
        n->next = this->head;
        head = n;
    } else {
        n->next = get(idx);
        get(idx-1)->next = n;
    }
    length++;
}

void slist::exchg(int i1, int i2) const {
    Airport* a = get(i1)->dat;
    get(i1)->dat = get(i2)->dat;
    get(i2)->dat = a;
}

[[maybe_unused]] void slist::swap(int i1, int i2) {
    Node *n1, *n2, *p1, *p2, *t;

    if ((i1 <= 0 || i1 > this->size()) || (i2 <= 0 || i2 > this->size()))
        return;
    if (i1 == i2)
        return;

    n1 = get(i1);
    p1 = i1 > 0 ? get(i1 - 1) : nullptr;
    n2 = get(i2);
    p2 = i2 > 0 ? get(i2 - 1) : nullptr;

    if (!(n1 == nullptr || n2 == nullptr)) {
        if (p1 != nullptr)
            p1->next = n2;
        if (p2 != nullptr)
            p2->next = n1;
        t = n1->next;
        n1->next = n2->next;
        n2->next = t;

        if (p1 == nullptr)
            head = n2;
        else if (p2 == nullptr)
            head = n1;
    }
}

[[maybe_unused]] bool slist::isEmpty() const {return this->length == 0 && this->head == nullptr && this->tail == nullptr;}

[[maybe_unused]] Node* slist::remove(int idx) {
    if (idx != 0) {
        Node* temp = get(idx);
        get(idx-1)->next = get(idx+1);
        length--;
        return temp;
    } else {
        Node* temp = head;
        head = get(1);
        length--;
        return temp;
    }
}

[[maybe_unused]] void slist::set(int idx, Airport* a) const {get(idx)->dat = a;}

int slist::size() const {return length;}

[[maybe_unused]] slist slist::subList(int s, int e) {return slist(this, s, e);}

[[maybe_unused]] string slist::toString() const {
    if (this->length == 0)
        return "\n";
    Node *curr = this->head;
    stringstream s;
    int c = 1;
    for (int i = 0; i < length; ++i) {
        Airport* data = curr->dat;
        s << c << ": {" << data->code << ", (" << data->latitude << ", " << data->longitude << ")}" << endl;
        curr = curr->next;
        c++;
    }
    return s.str();
}