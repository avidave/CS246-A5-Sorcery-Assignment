#include <vector>
#include <memory>
#include "board.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Board::Board() : Collection{} {}

bool Board::add(Card *c) {
	if (Cards.size() >= 5 || c->getType() != "Minion") return false;
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}

void Board::reset_minion_actions() {
	for (int i = 0; i < Cards.size(); ++i) {
		Cards[i]->set_actions(1);
	}
}

vector<card_template_t> Board::display() { return {}; }
