#include "textview.h"
#include <iostream>

using namespace std;

TextView::TextView (Owner *p1, Owner *p2) : View{p1, p2} {}

void TextView::notify() {
    board();
}

void TextView::notify(int n) {
    hand(n);
}

void TextView::print() {}