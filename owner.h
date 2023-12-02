#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
#include "deck.h"
#include "hand.h"
#include "card.h"
#include <memory>
using namespace std;

class Owner {
	string name;
	int num;
	Deck deck;
	Hand hand;
	vector<unique_ptr<Card>> allCards;

	public:
		Owner(string name, int num);
		~Owner();
		Owner(const Owner& o) = delete;
		Owner &operator=(const Owner &o) = delete;
		Owner(Owner&& o) = default;
		Owner &operator=(Owner &&o) = default;
		void shuffle_deck();
		unique_ptr<Card> create_card(vector<string> info);
		void import_deck(string file="default.deck");
		bool draw(int i);
		void display_deck();
		void display_hand();
		string getName();
		int getNum();
};

#endif
