#ifndef _MINION_H_
#define _MINION_H_

#include "card.h"
#include <string>

using namespace std;

class Minion : public Card {
	public:
		Minion(string name, int cost, int attack, int defense);
		Minion(string name, int cost, int attack, int defense, string ability_txt);
		Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost);
		int getStrength() override;
		int getDefense() override;
		string getType() override;
		card_template_t display() override;
};

#endif
