#include <iostream>
#include "subject.h"
#include "controller.h"
#include "owner.h"

using namespace std;

Controller::Controller(istream &in, Owner p1, Owner p2) : in{in}, p1{p1}, p2{p2} {}
Controller::~Controller() {}

void Controller::echoName(int n) {
	if (p1.getNum() == n) {
		cout << p1.getName() << endl;
	} else {
		cout << p2.getName() << endl;
	}
}

Owner& Controller::getActive() { return active; }
