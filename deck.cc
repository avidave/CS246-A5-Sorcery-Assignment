#include <vector>
#include <memory>
#include "deck.h"
#include "collection.h"
#include "card.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Deck::Deck() : Collection{} {}

void Deck::shuffle() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
	for (int i = 0; i < 1000; ++i) {
		std::shuffle(Cards.begin(), Cards.end(), rng);
	}

}

void Deck::reverse() {
	std::reverse(Cards.begin(), Cards.end());
}

vector<card_template_t> Deck::display() { return {}; }


bool Deck::add(Card *c) {
	this->Cards.emplace_back(c);
	//cout << c->display() << endl;
	return true;
}
