#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include "observer.h"
#include "trigger.h"
#include "ascii_graphics.h"

using namespace std;
class Card : public Observer {
	protected:
		string name;
		int cost, attack, defense;
		string ability_txt;
		int ability_cost;
		int actions;
		bool active = false;
		vector<string> triggers;
	public:
		Card(string name, int cost);
		Card(string name, int cost, int attack, int defense);
		Card(string name, int cost, string ability_txt);
		Card(string name, int cost, string ability_txt, int ability_cost);
		Card(string name, int cost, int attack, int defense, string ability_txt, int ability_cost);
		Card(string name, int cost, string ability_txt, int ability_cost, int actions);
		Card(string name, int cost, string ability_txt, int ability_cost, int actions, vector<string> triggers);
		Card(string name, int cost, int attack, int defense, string ability_txt, vector<string> triggers);

		string getName();
		int getCost();
		string getAbility();
		int getAbilityCost();
		void attach(Trigger &t);
		virtual int getStrength();
		virtual int getDefense();
		int get_actions();
		int take_damage(int d);
		void set_actions(int a);
		void use_action();
		virtual string getType() = 0;
		void notify() override;
		void notify(int n) override;
		virtual card_template_t display() = 0;
		vector<string> &getTriggers();
		void toggleActive();
		//virtual bool activate();
		//virtual void setActions(int a);
};

#endif
