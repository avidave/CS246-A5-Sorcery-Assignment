#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_

#include "enchantment_dec.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Enchantment : public EnchantmentDec {
	//unique_ptr<Ability> ability;
    bool silence = false;

    public:
	    Enchantment(Card *e, string name, int cost, string ability_txt);
        Enchantment(Card *e, string name, int cost, int attack, int defense, string mod_type);
        Enchantment(Card *e, string name, int cost, int attack, int defense, string ability_txt, string mod_type);
        Enchantment(Card *e, string name, int cost, string ability_txt, int num, string type);
        //Enchantment(Minion *m, string name, int cost, string ability_txt, int ability_cost);

        //Ability* get_ability();
        // int get_actions() override;
        // int getStrength() override;
        // int getDefense() override;
        // //int getCost() override;
        // int getAbilityCost() override;
        //void setActions(int a);

        int change_actions(int actions);
        int change_strength(int strength);
        int change_defense(int defense);
        int change_ability_cost(int ability_cost);

        string getType() override;
        card_template_t display() override;

        void setEnchantment(Card *e);
        Enchantment *getEnchantment();
        bool removeEnchantment();
};

#endif