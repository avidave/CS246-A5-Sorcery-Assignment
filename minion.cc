#include "card.h"
#include "minion.h"
#include <string>

using namespace std;

Minion::Minion(string name, int cost, int attack, int defense) : Card{name, cost, attack, defense} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt) : Card{name, cost, attack, defense, ability_txt, 0} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost) : Card{name, cost, attack, defense, ability_txt, ability_cost} {}

int Minion::getStrength() { return attack; }
int Minion::getDefense() { return defense; }
string Minion::getType() { return "Minion"; }

string Minion::display() {
	string s = name + " " + to_string(cost) + " " + getType() + " " + to_string(attack) + "/" + to_string(defense);
	if (ability_txt != "") s += "\n" + ability_txt;
	if (ability_cost > 0) s += " " + to_string(ability_cost);
	return s;
}
