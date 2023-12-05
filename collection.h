#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <vector>
#include <memory>
#include "card.h"
#include "ascii_graphics.h"

using namespace std;

class Collection {
	protected:
		vector<Card*> Cards;

	public:
		~Collection();
		virtual bool add(Card *c) = 0;
		virtual vector<card_template_t> display() = 0;
		bool remove(int n);
		void pop_back();
		Card* find(int n);
		bool find(Card *c);
		int numCards();
};

#endif
