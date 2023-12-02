#include <string>
#include "owner.h"
#include "deck.h"
#include "card.h"
#include "minion.h"
#include "spell.h"
#include <memory>
#include <fstream>
#include <iostream>

Owner::Owner(string name, int num): name{name}, num{num} {
	deck = Deck{};
}
Owner::~Owner() {}

unique_ptr<Card> Owner::create_card(vector<string> info) {
	if (info.size() >= 3 && info[2] == "Minion") {
		// unique_ptr<Card> temp = make_unique<Minion>()
		// cout << "Minion" << endl;
		if (info.size() == 5) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4])});
		else if (info.size() == 6) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5]});
		else if (info.size() == 7) return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4]), info[5], stoi(info[6])});
		else return make_unique<Minion>(Minion{info[0], stoi(info[1]), stoi(info[3]), stoi(info[4])});
	}
	if (info.size() >= 3 && info[2] == "Spell") {
		return make_unique<Spell>(Spell{info[0], stoi(info[1]), info[3]});
	}
	// return make_unique<Card>(Card{info[0], stoi(info[1])});
	return make_unique<Spell>(Spell{info[0], stoi(info[1])});
	
}

void Owner::import_deck(string file) { 
	ifstream names {file};
	if (!names.is_open()) {
		cerr << "Provided .deck file cannot be found for " << name << endl;
	}

	string n;

	while (getline(names, n)) {

		// string fName = name;
		// fName.at(0) += 32;
		// ifstream card{fName + ".txt"};
		// string input;
		// int cost;
		// string type;
		// // while(card >> l) {
		// // 	cout << l << endl;
		// // }
		// card.ignore();
		// card.ignore();
		// card.ignore();
		// card.ignore();

		// card >> cost;

		// card.ignore();
		// card.ignore();
		// card.ignore();

		// card >> type;

		// if (type == "Spell") {

		// } else if (type == "Minion") {

		// } else if (type == "Enchantment") {

		// } else if (type == "Ritual")

		//cout << n << endl;
		ifstream card {"./cards/" + n + ".txt"};
		string info;
		vector<string> card_info;
		card_info.emplace_back(n);
		while (getline(card, info)) {
			card_info.emplace_back(info);
		}

		if (card_info.size() == 1) card_info.emplace_back("1");
		auto c = create_card(card_info);
		allCards.emplace_back(move(c));
		deck.add(allCards.back().get());
		card_info.clear();

		//auto c = unique_ptr<Card> {new Card{n, 1}};
		// unique_ptr<Card> c = make_unique(cd);
		//allCards.emplace_back(move(c));
		//deck.add(allCards.back().get());
		//allCards.emplace_back(move(c));
		//cout << allCards.back().get()->display();	
		
	}

	// cout << deck.display();
}

void Owner::display_deck() {
	cout << deck.display();
}

string Owner::getName() { return name; }
int Owner::getNum() { return num; }
