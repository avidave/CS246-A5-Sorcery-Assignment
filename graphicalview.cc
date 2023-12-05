#include "graphicalview.h"
#include <iostream>
#include <sstream>

using namespace std;

GraphicalView::GraphicalView (Owner *p1, Owner *p2) : View{p1, p2}, window{new Xwindow{1020, 700}} {
    window->fillRectangle(0, 0, 1020, 700, Xwindow::White);
    string s = board();
    int i = 0;
    string line;
    istringstream iss{s};

    while(getline(iss, line, '\n')) {
        window->drawString(10, i * 10 + 10, line);
        ++i;
    }

    int height = CARD_TEMPLATE_BORDER.size();

    for (int i = 0; i < height; ++i) {
        s.clear();
        for (int v = 0; v < 5; ++v) s += CARD_TEMPLATE_BORDER.at(i);
        window->drawString(16, i * 10 + 575, s);
    }
}

void GraphicalView::notify() {
    string s = board();
    int i = 0;
    string line;
    istringstream iss{s};

    window->fillRectangle(10, 10, 1020, 550, Xwindow::White);

    while(getline(iss, line, '\n')) {
        window->drawString(10, i * 10 + 10, line);
        ++i;
    }
}

void GraphicalView::notify(int n) {
    string s = hand(n);
    int i = 0;
    string line;
    istringstream iss{s};

    window->fillRectangle(10, 565, 1020, 200, Xwindow::White);

    while(getline(iss, line, '\n')) {
        window->drawString(16, i * 10 + 575, line);
        ++i;
    }
}

void GraphicalView::notify(int p, int n) {}
