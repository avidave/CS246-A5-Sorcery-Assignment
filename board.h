#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include <memory>
#include "collection.h"
#include "card.h"

using namespace std;

class Board : public Collection {
	public:
		Board();
		bool add(Card *c) override;
		vector<card_template_t> display() override;
};


#endif
