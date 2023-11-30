#include <vector>
#include <memory>
#include "deck.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Deck::Deck() : Collection{} {}

bool Deck::add(Card *c) {
	this->Cards.emplace_back(c);
	cout << c->display() << endl;
	return true;
}
