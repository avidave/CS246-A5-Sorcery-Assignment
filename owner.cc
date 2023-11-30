#include <string>
#include "owner.h"
#include "deck.h"
#include <memory>
#include <fstream>
#include <iostream>

Owner::Owner(string name, int num): name{name}, num{num} {
	deck = Deck{};
}
Owner::~Owner() {}

void Owner::import_deck(string file) { 
	ifstream names {file};
	string name;

	while (getline(names, name)) {
		Card *p = new Card{name, 1};
		// unique_ptr<Card> c{new Card{name, 1}};
		deck.add(p);
		// cout << c.get()->display();	
	}

	// cout << deck.display();
}

void Owner::display_deck() {
	cout << deck.display();
}

string Owner::getName() { return name; }
int Owner::getNum() { return num; }
