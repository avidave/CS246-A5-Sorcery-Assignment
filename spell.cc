#include "spell.h"
#include <string>
#include <vector>

using namespace std;

Spell::Spell(string name, int cost) : Card{name, cost} {}
Spell::Spell(string name, int cost, string ability_txt) : Card{name, cost, ability_txt} {}
Spell::Spell(string name, int cost, string ability_txt, vector<string> ability) : Card{name, cost, ability_txt}, ability{ability} {}
string Spell::getType() { return "Spell"; }

card_template_t Spell::display() {
	
	return display_spell(getName(), getCost(), getAbility());;
}

vector<string> Spell::ability_type() { 
	if (ability.size() > 0) return ability; 
	else return {"None"};
}
