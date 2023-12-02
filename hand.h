#ifndef _HAND_H_
#define _HAND_H_

#include <vector>
#include <string>
#include <memory>
#include "collection.h"
#include "card.h"

using namespace std;

class Hand : public Collection {
	public:
		Hand();
		bool add(Card *c) override;
		vector<card_template_t> display() override;
};


#endif
