#ifndef _CARD_H_
#define _CARD_H_

#include <string>

using namespace std;
class Card {
	string name;
	int cost;
	public:
		Card(string name, int cost);
		string display();
};

#endif
