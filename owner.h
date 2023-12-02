#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
#include "deck.h"
#include "hand.h"
#include "card.h"
#include "trigger.h"
#include <memory>
using namespace std;

class Owner {
	string name;
	int num;
	int life;
	int magic;
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
		void add_magic(int i);
		void display_deck();
		void display_hand();
		string getName();
		int getNum();
		void setTrigger(Trigger &t);
};

#endif
