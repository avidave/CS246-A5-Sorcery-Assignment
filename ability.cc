#include <vector>
#include <string>
#include "ability.h"


Ability::Ability(vector<string> targets) : targets{targets} {}
vector<string> Ability::get_targets() { return targets; }

bool Ability::activate(Owner &p, int pos) { return false; }
bool Ability::activate(Owner *p) { return false; }
bool Ability::activate(Card *c, int pos, Owner *p) { return false; }
bool Ability::activate(Card *c) { return false; }

Damage::Damage(vector<string> targets, int damage) : Ability{targets}, damage{damage} {}
string Damage::getType() { return "Damage"; }
bool Damage::activate(Owner &p, int pos) {
	p.damage_minion(pos, damage);
	return true;
}

DamageAll::DamageAll(vector<string> targets, int damage) : Ability{targets}, damage{damage} {}
string DamageAll::getType() { return "DamageAll"; }
bool DamageAll::activate(Owner *p) {
	p->damage_all_minions(damage);
	return true;
}

Move::Move(vector<string> targets) : Ability{targets} {}
string Move::getType() { return "Move"; }
bool Move::activate(Card *c, int pos, Owner *p) {
	if (!c) return false;
	if (targets[1] == "Graveyard" && targets[2] == "Board") {
		if (p->resurrect()) return true;
		else return false;
	}

	if (targets[1] == "Board" && targets[2] == "Hand") {
		if (p->move(c, pos, p->get_board(), p->get_hand())) {
			// cout << "Moved to Hand" << endl;
			return true;
		}
		else {
			p->move(c, pos, p->get_board(), p->get_graveyard()); 
			return true;
		}
	}

	return false;
}

Destroy::Destroy(vector<string> targets) : Ability{targets} {}
string Destroy::getType() { return "Destroy"; }
bool Destroy::activate(Card *c, int pos, Owner *p) {
	if (!c) return false;
	if (c->getType() == "Minion") {
		p->move(c, pos, p->get_board(), p->get_graveyard());
		return true;
	}

	if (c->getType() == "Ritual") {
		p->get_board().set_ritual(nullptr);
		return true;
	}

	return false;
}

Charge::Charge(vector<string> targets, int num) : Ability{targets}, num{num} {}
string Charge::getType() { return "Charge"; }
bool Charge::activate(Card *c) {
	if (c) {
		c->set_actions(c->get_actions() + num);
		return true;
	}

	return false;
}

Add::Add(vector<string> targets, int atk, int def) : Ability{targets}, atk{atk}, def{def} {}
string Add::getType() { return "Add"; }
bool Add::activate(Card *c) {
	if (c->getType() == "Minion") {
		c->add_attack(atk);
		c->add_defense(def);
		return true;
	}
	return false;
}

Magic::Magic(vector<string> targets, int num) : Ability{targets}, num{num} {}
string Magic::getType() { return "Magic"; }
bool Magic::activate(Owner *p) {
	p->add_magic(num);
	return true;
}
