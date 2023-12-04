//#include "card.h"
#include "ritual.h"
//#include "ability.h"
#include <string>
#include <memory>

using namespace std;

Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions) : Card{name, cost, ability_txt, ability_cost, actions} {
	vector<string> t = {"AllMinion"};
	ability = make_unique<DamageAll>(DamageAll{t, 0});
}
Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers) : Card{name, cost, ability_txt, ability_cost, actions, triggers} {
	vector<string> t = {"AllMinion"};
	ability = make_unique<DamageAll>(DamageAll{t, 0});
}
Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers, vector<string> ability_type, vector<string> targets) : Card{name, cost, ability_txt, ability_cost, actions, triggers} {
	if (ability_type[0] == "Magic") {
		ability = make_unique<Magic>(Magic{targets, stoi(ability_type[1])});
	} else if (ability_type[0] == "Add") {
		ability = make_unique<Add>(Add{targets, stoi(ability_type[1]), stoi(ability_type[2])});
	} else if (ability_type[0] == "Destroy") {
		ability = make_unique<Destroy>(Destroy{targets});
	}
}

string Ritual::getType() {
    return "Ritual";
}

card_template_t Ritual::display() {
    return display_ritual(getName(), getCost(), getAbilityCost(), getAbility(), get_actions());
}

Ability* Ritual::get_ability() {
	return ability.get();
}
