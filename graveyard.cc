#include <vector>
#include <memory>
#include "graveyard.h"
#include "collection.h"
#include "card.h"
#include <iostream>

Graveyard::Graveyard() : Collection{} {}

bool Graveyard::add(Card *c) {
    if (c->getType() != "Minion") return false;
	this->Cards.emplace_back(c);
	return true;
}
