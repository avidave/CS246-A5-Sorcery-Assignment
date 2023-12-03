#include <vector>
#include <memory>
#include "board.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Board::Board() : Collection{}, nMinions{0}, ritual{nullptr} {}

bool Board::add(Card *c) {
	if (c->getType() == "Minion") ++nMinions;
	if ((nMinions >= 5 && c->getType() != "Minion") || (c->getType() != "Minion" || c->getType() != "Ritual")) return false;
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}

Card *Board::get_ritual() { return ritual; }

void Board::set_ritual(Card *r) {
	if (ritual) delete ritual;
	ritual = r; 
}

void Board::reset_minion_actions() {
	for (int i = 0; i < Cards.size(); ++i) {
		Cards[i]->set_actions(1);
	}
}

vector<card_template_t> Board::display() { return {}; }
