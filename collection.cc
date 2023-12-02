#include "collection.h"
#include "card.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Collection::~Collection() {
	// for (int i = 0; i < Cards.size(); ++i) {
	// 	delete Cards[i];
	// }

	//Cards.clear();
}

// string Collection::display() {
// 	string s;
// 	for (int i = 0; i < Cards.size(); ++i) {
// 		s += Cards[i]->display() + "\n\n";
// 	}

// 	return s;
// }

bool Collection::remove(int i) {
	Cards.erase(Cards.begin() + i);
	return true;
}

void Collection::pop_back() {
	Cards.pop_back();
}

Card* Collection::find(int n) {
	return Cards[n];
}

int Collection::numCards() {
	return Cards.size();
}
