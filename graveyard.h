#ifndef _GRAVEYARD_H_
#define _GRAVEYARD_H_

#include <vector>
#include <string>
#include <memory>
#include "collection.h"
#include "card.h"

using namespace std;

class Graveyard : public Collection {
	public:
		Graveyard();
		bool add(Card *c) override;
		vector<card_template_t> display() override;
};


#endif
