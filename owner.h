#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
#include "deck.h"
using namespace std;

class Owner {
	string name;
	int num;
	Deck deck;
	public:
		Owner(string name, int num);
		~Owner();
		void import_deck(string file="default.deck");
		void display_deck();
		string getName();
		int getNum();
};

#endif
