#include <iostream>
#include "subject.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"
#include "spell.h"

using namespace std;

Controller::Controller(Owner p1, Owner p2) : p1{move(p1)}, p2{move(p2)} {

	for (int i = 0; i < 4; ++i) {
		triggers.emplace_back(Trigger{i});
	}

	tv = make_unique<TextView>(TextView{&this->p1, &this->p2});

	attach(tv.get());
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

	p1.setTrigger(triggers);
	p2.setTrigger(triggers);
	//for (Trigger t : triggers) t.notifyObservers();

	p1.draw(5);
	p2.draw(5);
}

void Controller::play(istream &in, bool testing) {
	string line;
	while (getline(in, line)) {
		vector<string> commands;
		string temp = "";
		for (int i = 0; i < line.length(); ++i) {
			if (line[i] == ' ') {
				commands.emplace_back(temp);
				temp = "";
			}
			else {
				temp += line[i];
			}
		}
		commands.emplace_back(temp);
		string command;
		if (commands.size() > 0) command = commands[0];
		else continue;

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
			// cout << command << endl;
			triggers[3].notifyObservers();
			flip_active();
			turn();
		} else if (command == "quit") {
			//cout << command << endl;
			return;
		} else if (command == "draw") {
			if (testing) {
				// cout << command << endl;
				active->draw(1);
			}

		} else if (command == "discard") {
			if (testing) {
				int pos = stoi(commands[1]);
				Card *c = active->get_hand().find(pos);
				// if (c->getType() == "Minion") {
				// 	active->move(c, pos, active->get_hand(), active->get_graveyard());
				// } else {
				// 	active->get_hand().remove(pos);
				// }
				c->toggleActive();
				active->get_hand().remove(pos);
			}
		} else if (command == "attack") {
			// cout << command << endl;
			int pos1, pos2;
			pos1 = stoi(commands[1]);
			Card *m1 = active->get_board().find(pos1);
			if (m1->get_actions() > 0 || testing) {
				if (commands.size() == 3) {
					pos2 = stoi(commands[2]);
					Card *m2 = non_active->get_board().find(pos2);
					non_active->damage_minion(pos2, m1->getStrength());
					active->damage_minion(pos1, m2->getStrength());

					//m2->take_damage(m1->getStrength());
					//m1->take_damage(m2->getStrength());

					if (m1->getDefense() <= 0) {
						triggers[2].notifyObservers();
						m1->toggleActive();
						active->move(m1, pos1, active->get_board(), active->get_graveyard());
					}
					if (m2->getDefense() <= 0) {
						triggers[2].notifyObservers();
						m2->toggleActive();
						non_active->move(m2, pos2, non_active->get_board(), non_active->get_graveyard());
					}
				

				} else if (commands.size() == 2) {
					if (non_active->take_damage(m1->getStrength())) {
						return;
					}
				}

				if (!testing) m1->use_action();
			}
		} else if (command == "play") {
			// cout << command << endl;
			int pos = stoi(commands[1]);
			int pos2, p;
			Owner *target;
			if (commands.size() == 4) {
				if (commands[3] == "r") pos2 = -1;
				else pos2 = stoi(commands[3]);
				p = stoi(commands[2]);
				cout << p << " " << pos2;
				if (p == 1) target = &p1;
				else target = &p2;
			}
			Card *c = active->get_hand().find(pos);
			if (c->getType() == "Minion" && (c->getCost() <= active->get_magic() || testing)) {
				bool moved = active->move(c, pos, active->get_hand(), active->get_board());
				if (!testing) active->spend_magic(c->getCost());
				if (moved) triggers[1].notifyObservers();
			}
			if (c->getType() == "Ritual" && (c->getCost() <= active->get_magic() || testing)) {
				
				active->get_board().set_ritual(c);
				active->get_hand().remove(pos);
				if (!testing) active->spend_magic(c->getCost());
			}

			if (c->getType() == "Spell" && (c->getCost() <= active->get_magic() || testing)) {
				Spell *s = dynamic_cast<Spell*>(c);
			        Ability *a = s->get_ability();
				if (a->get_targets()[0] == "AllMinion") {
					if (a->activate(active) && a->activate(non_active)) {
						active->get_hand().remove(pos);
						if (!testing) {
							active->spend_magic(c->getCost());
						}
					}	
				}
				if (a->getType() == "Move") {
					if (a->get_targets()[1] == "Graveyard" && a->get_targets()[2] == "Board") {
						if (a->activate(nullptr, 0, active)) {
							active->get_hand().remove(pos);
							if (!testing) {
								active->spend_magic(c->getCost());
							}
						}
					}

					if (a->get_targets()[1] == "Board" && a->get_targets()[2] == "Hand") {
						a->activate(target->get_board().find(pos2), pos2, target);
						active->get_hand().remove(pos);
						if (!testing) {
							active->spend_magic(c->getCost());
						}
					}
				}
				if (a->getType() == "Destroy") {
					cout << "Destroy" << endl;
					if (pos2 != -1) {
						Card *mr = target->get_board().find(pos2);
						if (a->activate(mr, pos2, target)) {
							active->get_hand().remove(pos);
							if (!testing) active->spend_magic(c->getCost());
						}
					} else if (pos2 == -1) {
						Card *r = target->get_board().get_ritual();
						if (a->activate(r, pos2, target)) {
							active->get_hand().remove(pos);
							if (!testing) active->spend_magic(c->getCost());
						}
					}

				}
				if (a->getType() == "Charge") {
					Card *rtc = active->get_board().get_ritual();
					Ritual *r = dynamic_cast<Ritual*>(rtc);
					if (a->activate(r)) {
						active->get_hand().remove(pos);
						if (!testing) active->spend_magic(c->getCost());
					}
				}	
			}
		} else if (command == "use") {
			cout << command << endl;
		} else if (command == "inspect") {
			cout << command << endl;
		} else if (command == "describe") {
			cout << command << endl;
		} else if (command == "hand") {
			// cout << command << endl;
			cout << active->get_life() << endl;
			cout << active->get_magic() << endl;
			notifyObservers(active->getNum());
			//active->display_hand();
		} else if (command == "board") {
			// cout << command << endl;
			notifyObservers();
			//active->display_board();
			//notifyObservers();
		} else if (command == "graveyard") {
			active->display_graveyard();
		}	
		else {
			continue;
		}
	}

}

void Controller::turn() {
	triggers[0].notifyObservers();
	active->add_magic(1);
	active->draw(1);
	active->reset_minion_actions();
	//notifyObservers(active->getNum());
	//active->display_hand();
	// notifyObservers(active->getNum());
	// cout << endl << endl << endl;
	//active->display_deck();
	// notifyObservers(active->getNum());
	//cout << endl << endl << endl;
}

void Controller::flip_active() {
	if (active == &p1) {
		active = &p2;
		non_active = &p1;
	} else {
		active = &p1;
		non_active = &p2;
	}
}
