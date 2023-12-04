#include "spell.h"
#include "ability.h"
#include <string>

using namespace std;

Spell::Spell(string name, int cost) : Card{name, cost} {
	vector<string> t = {"AllMinion"};
	ability = make_unique<DamageAll>(DamageAll{t, 0});
}
Spell::Spell(string name, int cost, string ability_txt) : Card{name, cost, ability_txt} {
	vector<string> t = {"AllMinion"};
	ability = make_unique<DamageAll>(DamageAll{t, 0});
}
Spell::Spell(string name, int cost, string ability_txt, vector<string> ability_type, vector<string> targets) : Card{name, cost, ability_txt} {
	if (ability_type[0] == "Damage") {
		if (targets[0] == "AllMinion") {
			ability = make_unique<DamageAll>(DamageAll{targets, stoi(ability_type[1])});
		} else {
			ability = make_unique<Damage>(Damage{targets, stoi(ability_type[1])});
		}
	} else if (ability_type[0] == "Move"){
		ability = make_unique<Move>(Move{targets});
	} else if (ability_type[0] == "Destroy") {
		ability = make_unique<Destroy>(Destroy{targets});
	}
}
string Spell::getType() { return "Spell"; }

card_template_t Spell::display() {
	
	return display_spell(getName(), getCost(), getAbility());;
}

Ability* Spell::get_ability() {
	return ability.get();
}
