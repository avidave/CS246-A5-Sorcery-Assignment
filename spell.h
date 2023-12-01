#ifndef _SPELL_H_
#define _SPELL_H_

#include "card.h"
#include <string>

using namespace std;

class Spell : public Card {

    public:
        bool activate();
        void setActions(int a);
};

#endif