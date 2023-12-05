#include "enchantment_dec.h"
#include <iostream>
using namespace std;

EnchantmentDec::EnchantmentDec(Card *e, string name, int cost, string ability_txt) : Card{name, cost, ability_txt}, component{e} {}
EnchantmentDec::EnchantmentDec(Card *e, string name, int cost, int attack, int defense, string mod_type) : Card{name, cost, attack, defense}, component{e}, mod_type{mod_type} {}
EnchantmentDec::EnchantmentDec(Card *e, string name, int cost, int attack, int defense, string ability_txt, string mod_type) : Card{name, cost, attack, defense, ability_txt}, component{e}, mod_type{mod_type} {}
EnchantmentDec::EnchantmentDec(Card *e, string name, int cost, string ability_txt, int ability_cost, int actions) : Card{name, cost, ability_txt, ability_cost, actions}, component{e} {}

EnchantmentDec::~EnchantmentDec() { }