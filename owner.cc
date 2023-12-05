#include <string>
#include "owner.h"
#include "deck.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "ritual.h"
#include <memory>
#include <fstream>
#include <iostream>

vector<string> split(string s) {
	vector<string> vec;
	string temp = "";
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == ' ') {
			vec.emplace_back(temp);
			temp = "";
		}
		else {
			temp += s[i];
		}
	}
	vec.emplace_back(temp);

	return vec;
}


Owner::Owner(string name, int num): name{name}, num{num}, life{20}, magic{3} {}
Owner::~Owner() {}

void Owner::shuffle_deck() {
	deck.shuffle();
}

void Owner::reverse_deck() {
	deck.reverse();
}

void Owner::add_to_all_cards(unique_ptr<Card> c) {
	allCards.emplace_back(std::move(c));
}

Card *Owner::get_newly_added() {
	return allCards[allCards.size() - 1].get();
}

unique_ptr<Card> Owner::create_card(vector<string> info) {
	if (info.size() >= 3 && info[2] == "Minion") {
		if (info.size() == 5) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4])});
		else if (info.size() == 6) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5]});
		else if (info.size() == 7) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5], stoi(info[6])});
		else if (info.size() == 8) {
			vector<string> ability = split(info[7]);
			return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5], stoi(info[6]), ability});
		}
		else if (info.size() == 9) {
			if (info[6] == "Trigger") {
				vector<string> triggers = split(info[7]);
				vector<string> ability = split(info[8]);
				return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5], triggers, ability});
			}
		}
		else return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4])});
	}
	if (info.size() >= 3 && info[2] == "Spell") {
		vector<string> type = split(info[4]);
		vector<string> targets = split(info[5]);
		if (targets.size() > 0 && targets[0] == "Enchantment") {
			type.emplace_back("Enchantment");
		}
		return make_unique<Spell>(Spell{info[0], stoi(info[1]), info[3], type});
	}

	if (info.size() >= 3 && info[2] == "Ritual") {
		if (info.size() == 9 && info[6] == "Trigger") {
				vector<string> triggers = split(info[7]);
				vector<string> ability = split(info[8]);
				return make_unique<Ritual>(Ritual{info[0], stoi(info[1]), info[3], stoi(info[4]), stoi(info[5]), triggers, ability});
		}

		return make_unique<Ritual>(Ritual{info[0], stoi(info[1]), info[3], stoi(info[4]), stoi(info[5])});
	}
	if (info.size() >= 3 && info[2] == "Enchantment") {
		if (info.size() == 4) return make_unique<Enchantment>(Enchantment{nullptr, info[0], stoi(info[1]), info[3]});
		if (info.size() == 6) {
			if (info[3] == "Multiply") return make_unique<Enchantment>(Enchantment{nullptr, info[0], stoi(info[1]), stoi(info[4]), stoi(info[5]), info[3]});
			if (info[3] == "Add") return make_unique<Enchantment>(Enchantment{nullptr, info[0], stoi(info[1]), stoi(info[4]), stoi(info[5]), info[3]});
			if (info[4] == "AbilityCost") return make_unique<Enchantment>(Enchantment{nullptr, info[0], stoi(info[1]), info[3], stoi(info[5]), info[4]});
			if (info[4] == "Action") return make_unique<Enchantment>(Enchantment{nullptr, info[0], stoi(info[1]), info[3], stoi(info[5]), info[4]});
		}
	}
	return make_unique<Spell>(Spell{info[0], stoi(info[1])});
	
}

void Owner::import_deck(string file) { 
	ifstream names {file};
	if (!names.is_open()) {
		cerr << "Provided .deck file cannot be found for " << name << endl;
	}

	string n;

	while (getline(names, n)) {

		ifstream card {"./cards/" + n + ".txt"};
		string info;
		vector<string> card_info;
		card_info.emplace_back(n);
		while (getline(card, info)) {
			card_info.emplace_back(info);
		}

		if (card_info.size() == 1) card_info.emplace_back("1");
		auto c = create_card(card_info);
		allCards.emplace_back(std::move(c));
		deck.add(allCards.back().get());
		card_info.clear();	
		
	}
}

int Owner::get_magic() { return magic; }
void Owner::set_magic(int i) { magic = i; }
int Owner::get_life() { return life; }

bool Owner::take_damage(int i) {
	life -= i;
	if (life < 0) return true;
	else return false;
}	

void Owner::reset_minion_actions() {
	board.reset_minion_actions();
}

bool Owner::draw(int i) {
	for (int x = 0; x < i; x++) {
	// Note, we remove from the back of a deck
		if (deck.numCards() <= 0) return false;
		if (hand.add(deck.find(deck.numCards() - 1))) {
			deck.pop_back();
		} else {
			return false;
		}
	}

	return true;
}

bool Owner::move(Card *c, int pos, Collection &col1, Collection &col2) {
	// Move Card from col1 to col2
	cout << c->getName() << endl;
	if (col2.add(c)) {
		col1.remove(pos);
		return true;
	}
	else {
		cerr << "Cannot make that move" << endl;
		return false;
	}
	
}

void Owner::add_magic(int i) {
	magic += i;
}

void Owner::spend_magic(int i) {
	magic -= i;
}

Hand &Owner::get_hand() { return hand; }
Board &Owner::get_board() { return board; }
Graveyard &Owner::get_graveyard() { return graveyard; }

vector<card_template_t> Owner::display_deck() {
	return deck.display();
}

vector<card_template_t> Owner::display_hand() {
	return hand.display();
}

vector<card_template_t> Owner::display_board() {
	return board.display();
}

vector<card_template_t> Owner::display_graveyard() {
	return graveyard.display();
}

string Owner::getName() { return name; }
int Owner::getNum() { return num; }

void Owner::setTrigger(vector<Trigger> &t, Card *c) {
	vector<string> triggers = c->getTriggers();

	for (string trig : triggers) {
			int state = stoi(trig);
			if (state == t[0].getState()) t[0].attach(c);
			if (state == t[1].getState()) t[1].attach(c);
			if (state == t[2].getState()) t[2].attach(c);
			if (state == t[3].getState()) t[3].attach(c);
	}
}

void Owner::removeTrigger(vector<Trigger> &t, Card *c) {
	vector<string> triggers = c->getTriggers();

	for (string trig : triggers) {
			int state = stoi(trig);
			if (state == t[0].getState()) t[0].detach(c);
			if (state == t[1].getState()) t[1].detach(c);
			if (state == t[2].getState()) t[2].detach(c);
			if (state == t[3].getState()) t[3].detach(c);
	}
}
