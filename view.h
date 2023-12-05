#ifndef _VIEW_H_
#define _VIEW_H_

#include "observer.h"
#include "ascii_graphics.h"
#include "owner.h"
#include "minion.h"

using namespace std;

class View : public Observer {
    Owner *p1;
    Owner *p2;

    public:
        View(Owner *p1, Owner *p2);
        virtual void notify() = 0;
        virtual void notify(int n) = 0;
        virtual void notify(int p, int n) = 0;
        string board();
        string hand(int p);
        string inspect(int p, int n);
};

#endif
