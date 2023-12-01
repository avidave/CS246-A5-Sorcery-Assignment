#include <string>
#include "owner.h"
#include "deck.h"
#include <memory>
#include <fstream>
#include <iostream>

Owner::Owner(string name, int num): name{name}, num{num} {
	deck = Deck{};
}
//Owner::Owner(const Owner& o) : name{o.name}, num{o.num}, 
//deck{o.deck}, allCards{std::make_unique<Card>()} {}
Owner::~Owner() {}

void Owner::import_deck(string file) { 
	ifstream names;

	try {
		names = ifstream {file};
	} catch(...) {
		cerr << "Provided .deck file cannot be found" << endl;
	}

	string name;

	while (getline(names, name)) {

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

		auto c = unique_ptr<Card> {new Card{name, 1}};
		allCards.emplace_back(move(c));
		deck.add(allCards.back().get());
		//allCards.emplace_back(move(c));
		//cout << allCards.back().get()->display();	
		
	}

	//cout << deck.display();
}

void Owner::display_deck() {
	cout << deck.display();
}

string Owner::getName() { return name; }
int Owner::getNum() { return num; }
