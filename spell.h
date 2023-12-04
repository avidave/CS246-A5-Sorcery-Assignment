#ifndef _SPELL_H_
#define _SPELL_H_

#include "card.h"
#include "ability.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Spell : public Card {
	unique_ptr<Ability> ability;
    public:
	    Spell(string name, int cost);
	    Spell(string name, int cost, string ability_txt);
	    Spell(string name, int cost, string ability_txt, vector<string> ability_type, vector<string> targets);
	    string getType() override;
	    card_template_t display() override;
            Ability* get_ability();
        //void setActions(int a);
};

#endif
