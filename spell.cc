#include "spell.h"
#include <string>

using namespace std;

Spell::Spell(string name, int cost) : Card{name, cost} {}
Spell::Spell(string name, int cost, string ability_txt) : Card{name, cost, ability_txt} {}
string Spell::getType() { return "Spell"; }

card_template_t Spell::display() {
	
	return display_spell(getName(), getCost(), getAbility());;
}