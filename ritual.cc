#include "card.h"
#include "ritual.h"
#include <string>

using namespace std;

Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions) : Card{name, cost, ability_txt, ability_cost, actions} {}
Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers) : Card{name, cost, ability_txt, ability_cost, actions, triggers} {}
Ritual::Ritual(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers, vector<string> ability) : Card{name, cost, ability_txt, ability_cost, actions, triggers}, ability{ability} {}

string Ritual::getType() {
    return "Ritual";
}

card_template_t Ritual::display() {
    return display_ritual(getName(), getCost(), getAbilityCost(), getAbility(), get_actions());
}

vector<string> Ritual::ability_type() {
	if (ability.size() > 0) return ability;
	else return {"None"};
}
