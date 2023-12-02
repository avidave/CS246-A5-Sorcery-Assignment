#ifndef _CARD_H_
#define _CARD_H_

#include <string>

using namespace std;
class Card {
	protected:
		string name;
		int cost, attack, defense;
		string ability_txt;
		int ability_cost;
	public:
		Card(string name, int cost);
		Card(string name, int cost, int attack, int defense);
		Card(string name, int cost, string ability_txt);
		Card(string name, int cost, string ability_txt, int ability_cost);
		Card(string name, int cost, int attack, int defense, string ability_txt, int ability_cost);
		string getName();
		int getCost();
		string getAbility();
		int getAbilityCost();
		virtual string display();
		virtual int getStrength();
		virtual int getDefense();
		virtual string getType() = 0;
		//virtual bool activate();
		//virtual void setActions(int a);
};

#endif
