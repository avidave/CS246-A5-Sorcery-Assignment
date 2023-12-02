#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
#include "deck.h"
#include "card.h"
#include <memory>
using namespace std;

class Owner {
	string name;
	int num;
	Deck deck;
	vector<unique_ptr<Card>> allCards;

	public:
		Owner(string name, int num);
		~Owner();
		Owner(const Owner& o) = delete;
		Owner &operator=(const Owner &o) = delete;
		Owner(Owner&& o) = default;
		Owner &operator=(Owner &&o) = default;
		unique_ptr<Card> create_card(vector<string> info);
		void import_deck(string file="default.deck");
		void display_deck();
		string getName();
		int getNum();
};

#endif
