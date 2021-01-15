#include <algorithm>
#include <iostream>
#include <stack.h>

using namespace std;

Stack::Stack() {
    pTop = new Node;
}

Stack::~Stack() {
    if (pTop == nullptr)
        return;
    Node *n = pTop;
    Node *curr;
    while (n != nullptr) {
        curr = n;
        delete curr;
        n = n->pNext;
    }
}

void Stack::push(Disc *in) {
    if (pTop == nullptr)
        pTop = new Node;
    Node *tmp = new Node;
    tmp->data = in;
    tmp->pNext = pTop;
    pTop = tmp;
}

Disc* Stack::pop() {
    if (pTop == nullptr)
        return nullptr;
    Node *tmp = pTop;
    pTop = pTop->pNext;
    tmp->pNext = nullptr;
    Disc *ret = tmp->data;
    delete tmp;
    return ret;
}

[[maybe_unused]] Disc* Stack::top() const {
    return pTop->data;
}

[[maybe_unused]] bool Stack::empty() const {
    return pTop == nullptr;
}

void Stack::display() const {
    cout << "[";
    Node *n = pTop;
    while (n->pNext != nullptr) {
        cout << n->data->getSize();
        n = n->pNext;
        cout << (n->pNext == nullptr ? "" : ", ");
    }
	cout << "]" << endl;
}
