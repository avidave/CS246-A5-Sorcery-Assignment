#include "card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string name, int cost) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{""}, ability_cost{0} {}
Card::Card(string name, int cost, int attack, int defense) : name{name}, cost{cost}, attack{attack}, defense{defense}, ability_txt{""}, ability_cost{0} {}
Card::Card(string name, int cost, string ability_txt) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{0} {}
Card::Card(string name, int cost, string ability_txt, int ability_cost) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{ability_cost} {}
Card::Card(string name, int cost, int attack, int defense, string ability_txt, int ability_cost) : name{name}, cost{cost}, attack{attack}, defense{defense}, ability_txt{ability_txt}, ability_cost{ability_cost} {}

string Card::display() {
	return name + " " + to_string(cost) + " " + getType();

}

string Card::getName() { return name; }
int Card::getCost() { return cost; }
int Card::getStrength() { return attack; }
int Card::getDefense() { return defense; }
string Card::getAbility() { return ability_txt; }
int Card::getAbilityCost() { return ability_cost; }
// string Card::getType() { return "Generic"; }
