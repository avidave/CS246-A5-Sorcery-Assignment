#ifndef _RITUAL_H_
#define _RITUAL_H_

// #include "card.h"
#include "ability.h"
#include <string>
#include <memory>

using namespace std;

class Ritual : public Card {
	unique_ptr<Ability> ability;

	public:
		Ritual(string name, int cost, string ability_txt, int ability_cost, int actions);
		Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers);
		Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers, vector<string> ability_type, vector<string> targets);

		string getType() override;
		card_template_t display() override;
		Ability *get_ability();
};

#endif
