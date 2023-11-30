#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <vector>
#include <memory>
#include "card.h"

using namespace std;

class Collection {
	protected:
		vector<Card*> Cards;

	public:
		~Collection();
		virtual bool add(Card *c) = 0;
		string display();
		bool remove(int n);
};

#endif
