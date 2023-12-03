#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include <memory>
#include "collection.h"
#include "ritual.h"
#include "card.h"

using namespace std;

class Board : public Collection {

	int nMinions;
	Card *ritual;

	public:
		Board();
		Card *get_ritual();
		void set_ritual(Card *r);
		bool add(Card *c) override;
		void reset_minion_actions();
		vector<card_template_t> display() override;
};


#endif
