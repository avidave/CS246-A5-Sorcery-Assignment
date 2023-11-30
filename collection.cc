#include "collection.h"
#include "card.h"
#include <vector>
#include <string>
using namespace std;

Collection::~Collection() {
	for (int i = 0; i < Cards.size(); ++i) {
		delete Cards[i];
	}
}

string Collection::display() {
	string s;
	for (int i = 0; i < Cards.size(); ++i) {
		s += Cards[i]->display() + "\n";
	}

	return s;
}

bool Collection::remove(int i) {
	Cards.erase(Cards.begin() + i);
	return true;
}
