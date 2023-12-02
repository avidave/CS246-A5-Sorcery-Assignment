#include "view.h"
#include <iostream>

using namespace std;

View::View(Owner *p1, Owner *p2) : p1{p1}, p2{p2} {}

void View::hand(int p) {
    vector<card_template_t> cards;
    if (p == 1) cards = p1->display_hand();
    else cards = p2->display_hand();

    string s;

    int height = cards.at(0).size();

    for (int i = 0; i < height; ++i) {
        for (auto card : cards) {
            s += card.at(i);
        }

        s += "\n";
    }

    cout << s;
}