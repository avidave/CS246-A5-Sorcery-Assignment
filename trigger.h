#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "subject.h"

using namespace std;

class Trigger : public Subject {
    const int triggerState;

    public:
        Trigger(int triggerState);
        int getState();
};

#endif
