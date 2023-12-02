#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include "observer.h"
#include "trigger.h"

using namespace std;
class Card : public Observer {
	protected:
		string name;
		int cost, attack, defense;
		string ability_txt;
		int ability_cost;
		int actions = 1;
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
		void attach(Trigger &t);
		virtual string display();
		virtual int getStrength();
		virtual int getDefense();
		int get_actions();
		int take_damage(int d);
		void set_actions(int a);
		void use_action();
		virtual string getType() = 0;
		void notify() override;
		//virtual bool activate();
		//virtual void setActions(int a);
};

#endif
