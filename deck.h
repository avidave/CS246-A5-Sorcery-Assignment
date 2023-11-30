#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <string>
#include <memory>
#include "collection.h"
#include "card.h"

using namespace std;

class Deck : public Collection {
	public:
		Deck();
		bool add(Card *c) override;
};


#endif
