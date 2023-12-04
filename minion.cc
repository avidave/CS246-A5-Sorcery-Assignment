#include "card.h"
#include "minion.h"
#include <string>

using namespace std;

Minion::Minion(string name, int cost, int attack, int defense) : Card{name, cost, attack, defense} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt) : Card{name, cost, attack, defense, ability_txt, 0} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, int ability_cost) : Card{name, cost, attack, defense, ability_txt, ability_cost} {}
Minion::Minion(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers) : Card{name, cost, attack, defense, ability_txt, triggers} {}

int Minion::getStrength() { return attack; }
int Minion::getDefense() { return defense; }
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
