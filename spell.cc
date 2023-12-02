#include "spell.h"
#include <string>

using namespace std;

Spell::Spell(string name, int cost) : Card{name, cost} {}
Spell::Spell(string name, int cost, string ability_txt) : Card{name, cost, ability_txt} {}
string Spell::getType() { return "Spell"; }

string Spell::display() {
	string s = name + " " + to_string(cost) + " " + getType();
	if (ability_txt != "") s += "\n" + ability_txt;
	if (ability_cost > 0) s += " " + to_string(ability_cost);
	return s;
}
//bool Spell::activate() {

//}

//void Spell::setActions(int a) {

//}
