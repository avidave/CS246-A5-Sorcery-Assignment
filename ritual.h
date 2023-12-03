#ifndef _RITUAL_H_
#define _RITUAL_H_

#include "card.h"
#include <string>

using namespace std;

class Ritual : public Card {

	public:
		Ritual(string name, int cost, string ability_txt, int ability_cost, int actions);

		string getType() override;
		card_template_t display() override;
};

#endif
