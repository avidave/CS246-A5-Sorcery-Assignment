#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_

#include "view.h"
#include "ascii_graphics.h"
#include "owner.h"

using namespace std;

class TextView : public View {

    public:
        TextView(Owner *p1, Owner *p2);
        void notify();
        void notify(int n);
        //void print();
};

#endif