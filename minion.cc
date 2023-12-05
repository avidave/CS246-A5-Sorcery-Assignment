#include "card.h"
#include "minion.h"
#include <string>
#include <iostream>

using namespace std;

Minion::Minion(string name, int cost, int attack, int defense) : Card{name, cost, attack, defense}, enchantment{nullptr} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt) : Card{name, cost, attack, defense, ability_txt, 0}, enchantment{nullptr} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost) : Card{name, cost, attack, defense, ability_txt, ability_cost}, enchantment{nullptr} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers) : Card{name, cost, attack, defense, ability_txt, triggers}, enchantment{nullptr} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost, vector<string> ability) : Card{name, cost, attack, defense, ability_txt, ability_cost}, ability{ability}, enchantment{nullptr} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers, vector<string> ability) : Card{name, cost, attack, defense, ability_txt, triggers}, ability{ability}, enchantment{nullptr} {}



int Minion::getStrength() {
	if (!enchantment) return attack;
	enchantment->change_strength(attack);
}
int Minion::getDefense() {
	if (!enchantment) return defense;
	enchantment->change_defense(defense);
}
int Minion::get_actions() {
	if (!enchantment) return actions;
	enchantment->change_actions(actions);
}
int Minion::getAbilityCost() {
	if (!enchantment) return ability_cost;
	enchantment->change_ability_cost(ability_cost);
}
string Minion::getType() { return "Minion"; }

card_template_t Minion::display() {

	if (ability_txt == "") {
		return display_minion_no_ability(getName(), getCost(), getStrength(), getDefense());
	} else if (ability_cost == 0) {
		return display_minion_triggered_ability(getName(), getCost(), getStrength(), getDefense(), ability_txt);
	} else {
		return display_minion_activated_ability(getName(), getCost(), getStrength(), getDefense(), ability_cost, ability_txt);
	}
}

vector<string> Minion::ability_type() {
	if (ability.size() > 0) return ability;
	else return {"None"};
}

void Minion::setEnchantment(Enchantment *e) {
	// if (!e) {
    //     if (getEnchantment()) {
    //         //cout << component->getName();
    //         delete component;
    //     }
	// 	else dynamic_cast<Enchantment *>(component)->setEnchantment(e);
    // }
    if (!enchantment) enchantment = e;
    else enchantment->setEnchantment(e);
}