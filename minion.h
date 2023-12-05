#ifndef _MINION_H_
#define _MINION_H_

#include "card.h"
#include "enchantment.h"
#include <string>
#include <vector>

using namespace std;

class Minion : public Card {
	Enchantment *enchantment;
	vector<string> ability;
	
	public:
		Minion(string name, int cost, int attack, int defense);
		Minion(string name, int cost, int attack, int defense, string ability_txt);
		Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost);
		Minion(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers);
		Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost, vector<string> ability);
		Minion(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers, vector<string> ability);
		int getStrength() override;
		int getDefense() override;
		string getType() override;
		int get_actions() override;
		int getAbilityCost() override;
		card_template_t display() override;
		void setEnchantment(Enchantment *e);
		Enchantment *getEnchantment();
		vector<string> ability_type();
		bool removeEnchantment();
};

#endif
