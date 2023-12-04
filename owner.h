#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
#include "deck.h"
#include "hand.h"
#include "board.h"
#include "graveyard.h"
#include "card.h"
#include "trigger.h"
#include <memory>
#include "ascii_graphics.h"
using namespace std;

class Owner {
	string name;
	int num;
	int life;
	int magic;
	Deck deck;
	Hand hand;
	Board board;
	Graveyard graveyard;
	//unique_ptr<Card> ritual_slot;
	Card *ritual;
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
		int get_life();
		int get_magic();
		void reset_minion_actions();
		bool take_damage(int i);
		bool damage_minion(int p, int i);
		void damage_all_minions(int i);
		bool draw(int i);
		bool move(Card *c, int pos,  Collection &col1, Collection &col2);
		bool resurrect();
		void add_magic(int i);
		void spend_magic(int i);
		vector<card_template_t> display_deck();
		vector<card_template_t> display_hand();
		vector<card_template_t> display_board();
		vector<card_template_t> display_graveyard();
		Hand &get_hand();
		Board &get_board();
		Card *get_ritual();
		Graveyard &get_graveyard();
		string getName();
		int getNum();
		void setTrigger(Trigger &t);
};

#endif
