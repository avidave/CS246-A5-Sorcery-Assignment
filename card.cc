#include "card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string name, int cost) : name{name}, cost{cost} {}

string Card::display() {
	return name + " " + to_string(cost);

}
