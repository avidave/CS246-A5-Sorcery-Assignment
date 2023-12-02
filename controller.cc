#include <iostream>
#include "subject.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"

using namespace std;

Controller::Controller(istream &in, Owner p1, Owner p2) : in{in}, p1{move(p1)}, p2{move(p2)} {

	for (int i = 0; i < 4; ++i) {
		triggers.emplace_back(Trigger{i});
	}
}
Controller::~Controller() {}

void Controller::echoName(int n) {
	if (p1.getNum() == n) {
		cout << p1.getName() << endl;
	} else {
		cout << p2.getName() << endl;
	}
}

void Controller::trigger(int n) {
	for (Trigger t : triggers) {
		if (t.getState() == n) t.notifyObservers();
		break;
	}
}

Owner* Controller::getActive() { return active; }

void Controller::start() {
	p1.shuffle_deck();
	p2.shuffle_deck();

	//p1.display_deck();
	//cout << endl << endl << endl;
	// p2.display_deck();

	for (int i = 0; i < 4; ++i) {
		p1.setTrigger(triggers.at(i));
		p2.setTrigger(triggers.at(i));
		triggers.at(i).notifyObservers();
	}

	p1.draw(5);
	p2.draw(5);

	p2.display_hand();
	cout << endl << endl << endl;
	p2.display_deck();
	cout << endl << endl << endl;
}

void Controller::turn() {
	active->add_magic(1);
	active->draw(1);
	active->display_hand();
	cout << endl << endl << endl;
	active->display_deck();
}

void Controller::flip_active() {
	if (active == &p1) {
		active = &p2;
	} else {
		active = &p1;
	}
}
