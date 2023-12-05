#ifndef _GRAPHICALVIEW_H_
#define _GRAPHICALVIEW_H_

#include <iostream>
#include "view.h"
#include "ascii_graphics.h"
#include "window.h"
#include "owner.h"
using namespace std;

class Xwindow;

class GraphicalView : public View {
    Xwindow *window;

    public:
        GraphicalView(Owner *p1, Owner *p2);
        void notify() override;
        void notify(int n) override;
        void notify(int p, int n) override;
        //void print();
};

#endif