#include "view.h"
#include <iostream>

using namespace std;

View::View(Owner *p1, Owner *p2) : p1{p1}, p2{p2} {}

string View::hand(int p) {
    vector<card_template_t> cards;
    if (p == 1) cards = p1->display_hand();
    else cards = p2->display_hand();

    string s;

    int height = cards.at(0).size();

    for (int i = 0; i < height; ++i) {
        for (auto card : cards) {
            s += card.at(i);
        }

        s += "\n";
    }

    return s;
}

string View::inspect(int p, int n) {

    Card *m;
    if (p == p1->getNum() && p1->get_board().find(n)->getType() == "Minion") m = p1->get_board().find(n);
    else if (p2->get_board().find(n)->getType() == "Minion") m = p2->get_board().find(n);

    card_template_t mCard;

    if (m) card_template_t mCard = m->display();
    else return "AAAA";

    Enchantment *e = dynamic_cast<Minion *>(m)->getEnchantment();
    vector<card_template_t> eCards;

    while (e) {
        eCards.emplace_back(e->display());
        e = e->getEnchantment();
    }

    string s;
    int height = mCard.size();

    for (int i = 0; i < height; ++i) s += mCard.at(i) + "\n";

    int numCards = eCards.size() / 5;

    for (int i = 0; i < numCards; ++i) {

        for (int r = 0; r < height; ++r) {
            for (int v = 0; v < 5; ++v) s += eCards.at(v + i * 5).at(r);
            s += "\n";
        }
    }

    int remaining = eCards.size() - numCards * 5;

    for (int i = remaining; i < eCards.size(); ++i) {
        for (int r = 0; r < height; ++r) {
            for (int v = 0; v < 5; ++v) s += eCards.at(v + i * 5).at(r);
            s += "\n";
        }
    }

    return s;
}

string View::board() {
    auto deck1 = p1->get_board();
    auto deck2 = p2->get_board();
    card_template_t p1Card = display_player_card(1,p1->getName(),p1->get_life(),p1->get_magic());
    card_template_t p2Card = display_player_card(2,p2->getName(),p2->get_life(),p2->get_magic());

    auto gyard1 = p1->get_graveyard();
    auto gyard2 = p2->get_graveyard();


    card_template_t p1Dead;
    card_template_t p2Dead;
    if (gyard1.numCards() > 0) {
        Card *c = gyard1.find(gyard1.numCards() - 1);
        p1Dead = c->display();
    } else {
        p1Dead = CARD_TEMPLATE_BORDER;
    }
    if (gyard2.numCards() > 0) {
        Card *c = gyard2.find(gyard2.numCards() - 1);
        p2Dead = c->display();
    } else {
        p2Dead = CARD_TEMPLATE_BORDER;
    }

    Card *ritual_1 = deck1.get_ritual();
    Card *ritual_2 = deck2.get_ritual();

    card_template_t p1Ritual;
    card_template_t p2Ritual;
    if (!ritual_1) p1Ritual = CARD_TEMPLATE_BORDER;
    else p1Ritual = ritual_1->display();
    if (!ritual_2) p2Ritual = CARD_TEMPLATE_BORDER;
    else p2Ritual = ritual_2->display();

    vector<card_template_t> minions1;
    vector<card_template_t> minions2;

    for (int i = 0; i < 5; ++i) {
        if (i < deck1.numCards()) {
            Card *c = deck1.find(i);

            if (c->getType() == "Minion") minions1.emplace_back(c->display());
        } else {
            minions1.emplace_back(CARD_TEMPLATE_BORDER);
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (i < deck2.numCards()) {
            Card *c = deck2.find(i);

            if (c->getType() == "Minion") minions2.emplace_back(c->display());
        } else {
            minions2.emplace_back(CARD_TEMPLATE_BORDER);
        }
    }

    string s;

    s += EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < 165; ++i) s += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    s += EXTERNAL_BORDER_CHAR_TOP_RIGHT + "\n";

    int height = minions1.at(0).size();

    for (int i = 0; i < height; i++) {

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        for (int v = 0; v < 5; ++v) {
            if (v == 0) {
                s += p1Ritual.at(i);
            } else if (v == 1 || v == 3) {
                s += CARD_TEMPLATE_EMPTY.at(i);
            } else if (v == 2) {
                s += p1Card.at(i);
            } else if (v == 4) {
                s += p1Dead.at(i);
            }
        }

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        s += "\n";
    }

    for (int i = 0; i < height; i++) {

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        for (auto minion : minions1) {
            s += minion.at(i);
        }

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        s += "\n";
    }

    for (int i = 0; i < CENTRE_GRAPHIC.size(); i++) {

        s += CENTRE_GRAPHIC.at(i);

        s += "\n";
    }

    for (int i = 0; i < height; i++) {

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        for (auto minion : minions2) {
            s += minion.at(i);
        }

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        s += "\n";
    }

    for (int i = 0; i < height; i++) {

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        for (int v = 0; v < 5; ++v) {
            if (v == 0) {
                s += p2Ritual.at(i);
            } else if (v == 1 || v == 3) {
                s += CARD_TEMPLATE_EMPTY.at(i);
            } else if (v == 2) {
                s += p2Card.at(i);
            } else if (v == 4) {
                s += p2Dead.at(i);
            }
        }

        s += EXTERNAL_BORDER_CHAR_UP_DOWN;

        s += "\n";
    }

    s += EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 165; ++i) s += EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    s += EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT + "\n";

    return s;
}
