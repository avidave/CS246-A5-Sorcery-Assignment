#include <string>
#include "owner.h"

Owner::Owner(string name, int num): name{name}, num{num} {}
Owner::~Owner() {}

string Owner::getName() { return name; }
int Owner::getNum() { return num; }
