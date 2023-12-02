#include <vector>
#include <memory>
#include "hand.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Hand::Hand() : Collection{} {}

bool Hand::add(Card *c) {
   	if (Cards.size() >= 5) return false;
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}

vector<card_template_t> Hand::display() {
	string s;
	vector<card_template_t> hand;
	for (int i = 0; i < Cards.size(); ++i) {
		hand.emplace_back(Cards.at(i)->display());
	}

	return hand;
}