#include "textview.h"
#include <iostream>

using namespace std;

TextView::TextView (Owner *p1, Owner *p2) : View{p1, p2} {}

void TextView::notify() {
    cout << board();
}

void TextView::notify(int n) {
    cout << hand(n);
}

void TextView::notify(int p, int n) {
    cout << inspect(p, n);
}
