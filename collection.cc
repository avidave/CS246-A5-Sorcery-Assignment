#include "collection.h"
#include "card.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

Collection::~Collection() {}

bool Collection::remove(int i) {
	if (i > Cards.size() || i < 0) return false;
	Cards.erase(Cards.begin() + i);
	return true;
}

void Collection::pop_back() {
	Cards.pop_back();
}

Card* Collection::find(int n) {
	if (n < Cards.size()) return Cards[n];
	else return nullptr;
}

bool Collection::find(Card *c) {
	if (std::find(Cards.begin(), Cards.end(), c) != Cards.end()) return true;
	else return false;
}

int Collection::numCards() {
	return Cards.size();
}
