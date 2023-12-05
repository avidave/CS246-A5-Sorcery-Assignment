#include "enchantment.h"
#include <iostream>
using namespace std;

Enchantment::Enchantment(Card *e, string name, int cost, string ability_txt) : EnchantmentDec{e, name, cost, ability_txt} {
    //cout << "DOESTHISWORK";
    silence = true;
}
Enchantment::Enchantment(Card *e, string name, int cost, int attack, int defense, string mod_type) : EnchantmentDec{e, name, cost, attack, defense, mod_type} {}
Enchantment::Enchantment(Card *e, string name, int cost, int attack, int defense, string ability_txt, string mod_type) : EnchantmentDec{e, name, cost, attack, defense, ability_txt, mod_type} {}
Enchantment::Enchantment(Card *e, string name, int cost, string ability_txt, int num, string type) : EnchantmentDec{e, name, cost, ability_txt, 0, 0} {
    if (type == "AbilityCost") ability_cost = num;
    else actions = num;
}
//Enchantment::Enchantment(Minion *m, string name, int cost, string ability_txt, int ability_cost) : EnchantmentDec{m, name, cost, ability_txt, ability_cost} {}

int Enchantment::change_actions(int a) {
    if (silence) return a;
    if (!component) return this->actions + a;
    Enchantment *e = dynamic_cast<Enchantment *>(component);
    return this->actions + e->change_actions(a);
}

int Enchantment::change_strength(int a) {
    if (silence) return a;
    if (!component){
        if (mod_type == "Multiply") return this->attack * a;
        else return this->attack + a;
    }
    Enchantment *e = dynamic_cast<Enchantment *>(component);
    if (mod_type == "Multiply") return e->change_strength(this->attack * a);
    return e->change_strength(this->attack + a);
}

int Enchantment::change_defense(int a) {
    if (silence) return a;
    if (!component){
        if (mod_type == "Multiply") return this->defense * a;
        else return this->defense + a;
    }
    Enchantment *e = dynamic_cast<Enchantment *>(component);
    if (mod_type == "Multiply") return e->change_strength(this->defense * a);
    return e->change_strength(this->defense + a);
}

int Enchantment::change_ability_cost(int a) {
    if (silence) return a;
    if (!component) return this->ability_cost + a;
    Enchantment *e = dynamic_cast<Enchantment *>(component);
    return e->change_ability_cost(a) + this->ability_cost;
}

void Enchantment::setEnchantment(Card *e) {
    // if (!e) {
    //     if (getEnchantment()) {
    //         //cout << component->getName();
    //         delete component;
    //     }
	// 	else dynamic_cast<Enchantment *>(component)->setEnchantment(e);
    // }
    if (!component) component = e;
    else dynamic_cast<Enchantment *>(component)->setEnchantment(e);
}

Enchantment *Enchantment::getEnchantment() {
    if (!component) return nullptr;
    else return dynamic_cast<Enchantment *>(component);
}

string Enchantment::getType() { return "Enchantment"; }

card_template_t Enchantment::display() {
    //cout << "DOESTHISWORK" << getStrength();
    if (getStrength() > 0 || getDefense() > 0) {
        if (mod_type == "Multiply") return display_enchantment_attack_defence(name, cost, ability_txt, "*"+to_string(attack), "*"+to_string(defense));
        else return display_enchantment_attack_defence(name, cost, ability_txt, "+"+to_string(attack), "+"+to_string(defense));
    } else {
        return display_enchantment(name, cost, ability_txt);
    }
}

bool Enchantment::removeEnchantment() {
    if (!component) {
        return false;
    }
	if (!dynamic_cast<Enchantment *>(component)->removeEnchantment()) {
        component = nullptr;
        return false;
    }
	return true;
}