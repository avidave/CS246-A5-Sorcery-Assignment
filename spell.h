#ifndef _SPELL_H_
#define _SPELL_H_

#include "card.h"
#include <string>
#include <vector>

using namespace std;

class Spell : public Card {
	vector<string> ability;

    public:
	    Spell(string name, int cost);
	    Spell(string name, int cost, string ability_txt);
	    Spell(string name, int cost, string ability_txt, vector<string> ability);
	    string getType() override;
	    card_template_t display() override;
	    vector<string> ability_type();
};

#endif
