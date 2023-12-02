#include <iostream>
#include "subject.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"

using namespace std;

Controller::Controller(Owner p1, Owner p2) : p1{move(p1)}, p2{move(p2)} {

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
}

void Controller::play(istream &in, bool testing) {
	string command;
	while (in >> command) {
		if (command == "help") {
			cout << "Commands: ";
			cout << "help -- Display this message." << endl;
			cout << "\t  end -- End the current player’s turn." << endl;
			cout << "\t  quit -- End the game." << endl;
			cout << "\t  attack minion other-minion -- Orders minion to attack other-minion." << endl;
			cout << "\t  attack minion -- Orders minion to attack the opponent." << endl;
			cout << "\t  play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
			cout << "\t  use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
			cout << "\t  inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
			cout << "\t  hand -- Describe all cards in your hand." << endl;
			cout << "\t  board -- Describe all cards on the board." << endl;
		} else if (command == "end") {
			cout << command << endl;
		} else if (command == "quit") {
			//cout << command << endl;
			return;
		} else if (command == "draw") {
			if (testing) cout << command << endl;
		} else if (command == "discard") {
			if (testing) cout << command << endl;
		} else if (command == "attack") {
			cout << command << endl;
		} else if (command == "play") {
			cout << command << endl;
		} else if (command == "use") {
			cout << command << endl;
		} else if (command == "inspect") {
			cout << command << endl;
		} else if (command == "describe") {
			cout << command << endl;
		} else if (command == "hand") {
			cout << command << endl;
		} else if (command == "board") {
			cout << command << endl;
		} else {
			continue;
		}
	}

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
