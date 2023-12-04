#ifndef _VIEW_H_
#define _VIEW_H_

#include "observer.h"
#include "ascii_graphics.h"
#include "owner.h"

using namespace std;

class View : public Observer {
    Owner *p1;
    Owner *p2;

    public:
        View(Owner *p1, Owner *p2);
        virtual void notify() = 0;
        virtual void print() = 0;
        void board();
        void hand(int p);
        void inspect(int n);
};

#endif
