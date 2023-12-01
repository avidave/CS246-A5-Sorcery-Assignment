#ifndef _CARD_H_
#define _CARD_H_

#include <string>

using namespace std;
class Card {
	string name;
	int cost, attack, defense;
	public:
		Card(string name, int cost);
		string display();
		int getCost();
		virtual int getStrength();
		virtual int getDefense();
		//virtual bool activate();
		//virtual void setActions(int a);
};

#endif
