#ifndef _ENCHANTMENT_DEC_H_
#define _ENCHANTMENT_DEC_H_

#include "card.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class EnchantmentDec : public Card {
    protected:
        Card *component;
        string mod_type;

    public:
        EnchantmentDec(Card *e, string name, int cost, string ability_txt);
        EnchantmentDec(Card *e, string name, int cost, int attack, int defense, string mod_type);
        EnchantmentDec(Card *e, string name, int cost, int attack, int defense, string ability_txt, string mod_type);
        EnchantmentDec(Card *e, string name, int cost, string ability_txt, int ability_cost, int actions);

        virtual ~EnchantmentDec();
};

#endif
