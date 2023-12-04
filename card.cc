#include "card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string name, int cost) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{""}, ability_cost{0}, actions{1} {}
Card::Card(string name, int cost, int attack, int defense) : name{name}, cost{cost}, attack{attack}, defense{defense}, ability_txt{""}, ability_cost{0}, actions{1} {}
Card::Card(string name, int cost, string ability_txt) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{0}, actions{1} {}
Card::Card(string name, int cost, string ability_txt, int ability_cost) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{ability_cost}, actions{1} {}
Card::Card(string name, int cost, int attack, int defense, string ability_txt, int ability_cost) : name{name}, cost{cost}, attack{attack}, defense{defense}, ability_txt{ability_txt}, ability_cost{ability_cost}, actions{1} {}
Card::Card(string name, int cost, string ability_txt, int ability_cost, int actions) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{ability_cost}, actions{actions} {}
Card::Card(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{ability_cost}, actions{actions}, triggers{triggers} {}
Card::Card(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers) : name{name}, cost{cost}, attack{0}, defense{0}, ability_txt{ability_txt}, ability_cost{0}, actions{actions}, triggers{triggers} {};

// string Card::display() {
// 	return name + " " + to_string(cost) + " " + getType();

// }

string Card::getName() { return name; }
int Card::getCost() { return cost; }
int Card::getStrength() { return attack; }
int Card::getDefense() { return defense; }
int Card::take_damage(int d) {
	defense -= d;
	return defense;
}

void Card::set_actions(int a) {
	actions = a;
}

void Card::use_action() {
	actions--;
}

int Card::get_actions() { return actions; }
string Card::getAbility() { return ability_txt; }
int Card::getAbilityCost() { return ability_cost; }
// string Card::getType() { return "Generic"; }
void Card::attach(Trigger &t) {
	t.attach(this);
}
void Card::notify() {
	if (active) cout << getName() << " " << "Triggered" << endl;
}

void Card::toggleActive() { active = !active; }

void Card::notify(int n) {
	// This function should only have code for view, not card.
}

vector<string> &Card::getTriggers() { return triggers; }