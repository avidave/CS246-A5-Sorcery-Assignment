#include <vector>
#include <memory>
#include "board.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Board::Board() : Collection{}, ritual{nullptr} {}

bool Board::add(Card *c) {
	if (c->getType() != "Minion" || c->getType() != "Minion" && Cards.size() >= 5) return false;
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}

Card *Board::get_ritual() { return ritual; }

void Board::set_ritual(Card *r) {
	// std::cout << "TO SET" << r->getName();
	ritual = r; 
}

void Board::reset_minion_actions() {
	for (int i = 0; i < Cards.size(); ++i) {
		Cards[i]->set_actions(1);
	}
}

void Board::add_to_all(int atk, int def) {
	for (int i = 0; i < Cards.size(); ++i) {
		Cards[i]->add_attack(atk);
		Cards[i]->add_defense(def);
	}
}

vector<card_template_t> Board::display() { return {}; }
