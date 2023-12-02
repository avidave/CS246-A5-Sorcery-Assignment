#ifndef _SPELL_H_
#define _SPELL_H_

#include "card.h"
#include <string>

using namespace std;

class Spell : public Card {

    public:
	    Spell(string name, int cost);
	    Spell(string name, int cost, string ability_txt);
	    string getType() override;
	    card_template_t display() override;
        //bool activate();
        //void setActions(int a);
};

#endif
