#include <iostream>
#include "subject.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"

using namespace std;

Controller::Controller(istream &in, Owner p1, Owner p2) : in{in}, p1{move(p1)}, p2{move(p2)} {}
Controller::~Controller() {}

void Controller::echoName(int n) {
	if (p1.getNum() == n) {
		cout << p1.getName() << endl;
	} else {
		cout << p2.getName() << endl;
	}
}

Owner& Controller::getActive() { return active; }

void Controller::start() {
	p1.shuffle_deck();
	p2.shuffle_deck();

	p1.display_deck();
	cout << endl << endl << endl;
	// p2.display_deck();

	p1.draw(5);
	p2.draw(5);

	p1.display_hand();
	cout << endl << endl << endl;
	p1.display_deck();
}
