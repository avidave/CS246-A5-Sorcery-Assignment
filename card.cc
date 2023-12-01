#include "card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string name, int cost) : name{name}, cost{cost},
attack{0}, defense{0} {}

string Card::display() {
	return name + " " + to_string(cost);

}

int Card::getCost() { return cost; }
int Card::getStrength() { return attack; }
int Card::getDefense() { return defense; }