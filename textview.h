#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_

#include "view.h"
#include "ascii_graphics.h"
#include "owner.h"

using namespace std;

class TextView : public View {

    public:
        TextView(Owner *p1, Owner *p2);
        void notify() override;
        void notify(int n) override;
        void notify(int p, int n) override;
        //void print();
};

#endif