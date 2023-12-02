#include <vector>
#include <memory>
#include "board.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Board::Board() : Collection{} {}

bool Board::add(Card *c) {
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}
