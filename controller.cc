#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "subject.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"
#include "spell.h"
#include "minion.h"

using namespace std;

Controller::Controller(Owner p1, Owner p2, bool graphics) : p1{move(p1)}, p2{move(p2)}, graphics{graphics} {

	for (int i = 0; i < 4; ++i) {
		triggers.emplace_back(Trigger{i});
	}

	tv = make_unique<TextView>(TextView{&this->p1, &this->p2});

	if (graphics) {
		gv = make_unique<GraphicalView>(GraphicalView{&this->p1, &this->p2});

		attach(gv.get());
	}

	attach(tv.get());
}

Controller::~Controller() {}

void Controller::trigger(int n) {
	for (Trigger t : triggers) {
		if (t.getState() == n) t.notifyObservers();
		break;
	}
}

Owner* Controller::getActive() { return active; }

void Controller::start(bool testing) {
	if (!testing) {
		p1.shuffle_deck();
		p2.shuffle_deck();
	} else {
		p1.reverse_deck();
		p2.reverse_deck();
	}

	p1.draw(5);
	p2.draw(5);
}

void start_turn_ritual(Trigger t, Owner *p, Owner *active) {
	vector<Observer *> ob = t.getObservers();
	for (int i = 0; i < ob.size(); i++) {
		Card *obc = dynamic_cast<Card*>(ob[i]);
		if (obc->getType() == "Ritual") {
			Ritual *obcr = dynamic_cast<Ritual*>(obc);
			if (obcr == p->get_board().get_ritual()) {
				if (obcr->ability_type()[0] == "Magic" && obcr == active->get_board().get_ritual() && obcr->get_actions() >= obcr->getAbilityCost()) {
					p->add_magic(stoi(obcr->ability_type()[1]));
					obcr->set_actions(obcr->get_actions() - obcr->getAbilityCost());
				}
			}
		}
	}
}
			

void end_turn_minion(Trigger t, Owner *p, Owner *active) {
	vector<Observer*> ob = t.getObservers();
	for (int i = 0; i < ob.size(); i++) {
		Card *obc = dynamic_cast<Card*>(ob[i]);
		if (obc->getType() == "Minion") {
			Minion *obcm = dynamic_cast<Minion*>(obc);
			if (p->get_board().find(obcm)) {
				if (obcm->ability_type()[0] == "Add" && active->get_board().find(obcm)) {
					p->get_board().add_to_all(stoi(obcm->ability_type()[1]), stoi(obcm->ability_type()[2]));
				}
			}	
		}
	}
}

void minion_leave_minion(Trigger t, Owner *p) {
	vector<Observer*> ob = t.getObservers();
	for (int i = 0; i < ob.size(); ++i) {
		Card *obc = dynamic_cast<Card*>(ob[i]);
		if (obc->getType() == "Minion") {
			Minion *obcm = dynamic_cast<Minion*>(obc);
			if (p->get_board().find(obcm)) {
				if (obcm->ability_type()[0] == "Add") {
					obcm->add_attack(stoi(obcm->ability_type()[1]));
					obcm->add_defense(stoi(obcm->ability_type()[2]));
				}
			}
		}
	}
}

void minion_enter_ritual(vector<Trigger> t, Card *c, Owner *p, Owner *active, Owner *non_active) {
	vector<Observer *> ob = t[1].getObservers();
	for (int i = 0; i < ob.size(); i++) {
		Card *obc = dynamic_cast<Card*>(ob[i]);
		if (obc->getType() == "Ritual") {
			Ritual *obcr = dynamic_cast<Ritual*>(obc);
			if (obcr == p->get_board().get_ritual()) {
				if (obcr->ability_type()[0] == "Destroy" && obcr->get_actions() >= obcr->getAbilityCost()) {
					active->move(c, active->get_board().numCards() - 1, active->get_board(), active->get_graveyard());
					active->removeTrigger(t, c);
					t[2].notifyObservers();
					minion_leave_minion(t[2], active);
					minion_leave_minion(t[2], non_active);
					obcr->set_actions(obcr->get_actions() - obcr->getAbilityCost());
				}
				if (obcr->ability_type()[0] == "Add" && obcr == active->get_board().get_ritual() && obcr->get_actions() >= obcr->getAbilityCost()) {
					c->add_attack(stoi(obcr->ability_type()[1]));
					c->add_defense(stoi(obcr->ability_type()[2]));
					obcr->set_actions(obcr->get_actions() - obcr->getAbilityCost());
				}
			}
		}
	}
}

void minion_enter_minion(vector<Trigger> t, Card *c, Owner *p, Owner *active, Owner *non_active) {
	vector<Observer *> ob = t[1].getObservers();
	for (int i = 0; i < ob.size(); i++) {
		Card *obc = dynamic_cast<Card*>(ob[i]);
		if (obc->getType() == "Minion") {
			Minion *obcm = dynamic_cast<Minion*>(obc);
			if (p->get_board().find(obcm)) {
				if (obcm->ability_type()[0] == "Damage" && non_active->get_board().find(obcm)) {
					c->take_damage(stoi(obcm->ability_type()[1]));
					if (c->getDefense() <= 0) {
						active->removeTrigger(t, c);
						t[2].notifyObservers();
						minion_leave_minion(t[2], active);
					        minion_leave_minion(t[2], non_active);	
						active->move(c, active->get_board().numCards() - 1, active->get_board(), active->get_graveyard());
					}
				}
			}
		}
	}
}

void Controller::play(istream &in, bool testing) {
	string line;
	if (p1.get_life() <= 0 || p2.get_life() <= 0) return;
	if (graphics) gv->notify(p1.getNum());
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

		try {
			if (commands.size() > 1) {
				stoi(commands[1]);
			}
			if (commands.size() > 3 && commands[3] != "r") {
				stoi(commands[3]);
			}
		} catch (...) {
			continue;
		}

		if (commands.size() > 1) {
			if (stoi(commands[1]) > 5 || stoi(commands[1]) < 1) continue;
			commands[1] = to_string(stoi(commands[1]) - 1);
		}

		if (commands.size() > 3 && commands[3] != "r") {
			if (stoi(commands[3]) > 5 || stoi(commands[3]) < 1) continue;
			commands[3] = to_string(stoi(commands[3]) - 1);
		}

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
			triggers[3].notifyObservers();
			end_turn_minion(triggers[3], active, active);
			end_turn_minion(triggers[3], non_active, active);
			flip_active();
			if (graphics) gv->notify(active->getNum());
			turn();
		} else if (command == "quit") {
			return;
		} else if (command == "draw") {
			if (testing) {
				active->draw(1);
				if (graphics) gv->notify(active->getNum());
			}

		} else if (command == "discard") {
			if (testing) {
				int pos = stoi(commands[1]);
				Card *c = active->get_hand().find(pos);
				active->removeTrigger(triggers, c);
				active->get_hand().remove(pos);
				if (graphics) gv->notify(active->getNum());
			}
		} else if (command == "attack") {
			int pos1, pos2;
			pos1 = stoi(commands[1]);
			Card *m1 = active->get_board().find(pos1);
			
			if (m1->get_actions() > 0) {
				if (commands.size() == 3) {
					pos2 = stoi(commands[2]);
					Card *m2 = non_active->get_board().find(pos2);

					m2->take_damage(m1->getStrength());
					m1->take_damage(m2->getStrength());

					if (m1->getDefense() <= 0) {
						active->removeTrigger(triggers, m1);
						triggers[2].notifyObservers();
						minion_leave_minion(triggers[2], active);
						minion_leave_minion(triggers[2], non_active);
					}
					if (m2->getDefense() <= 0) {
						non_active->removeTrigger(triggers, m2);
						triggers[2].notifyObservers();
						minion_leave_minion(triggers[2], active);
						minion_leave_minion(triggers[2], non_active);
					}

					if (m1->getDefense() <= 0) {
						active->move(m1, pos1, active->get_board(), active->get_graveyard());
					}
					if (m2->getDefense() <= 0) {
						non_active->move(m2, pos2, non_active->get_board(), non_active->get_graveyard());
					}
				

				} else if (commands.size() == 2) {
					if (non_active->take_damage(m1->getStrength())) {
						cout << active->getName() << " Wins" << endl;
						return;
					}
				}

				m1->use_action();
				if (graphics) {
					gv->notify(active->getNum());
					gv->notify();
				}
			}
		} else if (command == "play") {
			int pos = stoi(commands[1]);
			int pos2 = -1;
			int target_int = -1;
			Owner *target;
			if (commands.size() > 2) {
				if (commands[3] == "r") pos2 = 5;
				else pos2 = stoi(commands[3]);
				try {
					target_int = stoi(commands[2]);
				} catch (...) {
					target_int = -1;
				}
				if (target_int == 1) target = &p1;
				else if (target_int == 2) target = &p2;
				else target_int = -1;
			}
			
			Card *c = active->get_hand().find(pos);
			if (c->getType() == "Minion" && (c->getCost() <= active->get_magic() || testing)) {
				bool moved = active->move(c, pos, active->get_hand(), active->get_board());
				if (moved) {
					active->spend_magic(c->getCost());
					if (testing && active->get_magic() < 0) active->set_magic(0);
				}
				if (moved) {
					triggers[1].notifyObservers();
					active->setTrigger(triggers, c);
					minion_enter_minion(triggers, c, active, active, non_active);
					minion_enter_ritual(triggers, c, active, active, non_active);
					minion_enter_minion(triggers, c, non_active, active, non_active);
					minion_enter_ritual(triggers, c, non_active, active, non_active);
					c->set_actions(0);
				}
			}
			if (c->getType() == "Ritual" && (c->getCost() <= active->get_magic() || testing)) {
				active->get_board().set_ritual(c);
				active->get_hand().remove(pos);
				active->spend_magic(c->getCost());
				active->setTrigger(triggers, c);
				if (testing && active->get_magic() < 0) active->set_magic(0);
			}

			if (c->getType() == "Enchantment" && (c->getCost() <= active->get_magic() || testing)) {
				Minion *m = nullptr;
				if (active->getNum() == target_int && active->get_board().find(pos2)->getType() == "Minion") m = dynamic_cast<Minion *>(active->get_board().find(pos2));
				else if (non_active->getNum() == target_int && non_active->get_board().find(pos2)->getType() == "Minion") m = dynamic_cast<Minion *>(non_active->get_board().find(pos2));

				if (m) {
					m->setEnchantment(dynamic_cast<Enchantment *>(c));
					active->get_hand().remove(pos);
					if (!testing) active->spend_magic(c->getCost());
				}
			}

			if (c->getType() == "Spell" && (c->getCost() <= active->get_magic() || testing)) {
				Spell *s = dynamic_cast<Spell*>(c);
				if (s->ability_type()[0] == "Destroy" && target_int != -1 && pos2 != -1) {
					Card *target_c;
					if (pos2 != 5) target_c = target->get_board().find(pos2);
					else target_c = target->get_board().get_ritual();
					if (target_c) {
						if (s->ability_type()[1] == "Enchantment") {
							dynamic_cast<Minion *>(target_c)->removeEnchantment();
							active->spend_magic(c->getCost());
							if (testing && active->get_magic() < 0) active->set_magic(0);
						} else if (target->move(target_c, pos2, target->get_board(), target->get_graveyard())) {
							target->removeTrigger(triggers, target_c);
							triggers[2].notifyObservers();
							minion_leave_minion(triggers[2], active);
							minion_leave_minion(triggers[2], non_active);
							active->spend_magic(c->getCost());
							active->get_hand().remove(pos);
							if (testing && active->get_magic() < 0) active->set_magic(0);
						} else if (target_c->getType() == "Ritual") {
							target->removeTrigger(triggers, target->get_board().get_ritual());
							target->get_board().set_ritual(nullptr);
							active->spend_magic(c->getCost());
							active->get_hand().remove(pos);
							if (testing && active->get_magic() < 0) active->set_magic(0);
						}
					}
				}
				if (s->ability_type()[0] == "DamageAll") {
					active->spend_magic(c->getCost());
					active->get_hand().remove(pos);
					if (testing && active->get_magic() < 0) active->set_magic(0);
					int i = 0;
					while (i < active->get_board().numCards()) {
						Card *m = active->get_board().find(i);
						m->take_damage(stoi(s->ability_type()[1]));
						if (m->getDefense() <= 0) {
							active->removeTrigger(triggers, m);
							triggers[2].notifyObservers();
							minion_leave_minion(triggers[2], active);
							minion_leave_minion(triggers[2], non_active);
							active->move(m, i, active->get_board(), active->get_graveyard());
							--i;
						}
						++i;

					}
					i = 0;
					while (i < non_active->get_board().numCards()) {
						Card *m = non_active->get_board().find(i);
						m->take_damage(stoi(s->ability_type()[1]));
						if (m->getDefense() <= 0) {
							non_active->removeTrigger(triggers, m);
							triggers[2].notifyObservers();
							minion_leave_minion(triggers[2], active);
							minion_leave_minion(triggers[2], non_active);
							non_active->move(m, i, non_active->get_board(), non_active->get_graveyard());
							--i;
						}
						++i;
					}
				}

				if (s->ability_type()[0] == "Move") {
					if (s->ability_type()[1] == "Board" && s->ability_type()[2] == "Hand" && target_int != -1 && pos2 >= 0 && pos2 < target->get_board().numCards()) {
						Card *target_c = target->get_board().find(pos2);
						target->removeTrigger(triggers, target_c);
						triggers[2].notifyObservers();
						minion_leave_minion(triggers[2], active);
						minion_leave_minion(triggers[2], non_active);
						active->spend_magic(c->getCost());
						if (testing && active->get_magic() < 0) active->set_magic(0);
						if (target->move(target_c, pos2, target->get_board(), target->get_hand())) {
						} else target->get_board().remove(pos2);
						active->get_hand().remove(pos);
					}

					if (s->ability_type()[1] == "Graveyard" && s->ability_type()[2] == "Board" && active->get_graveyard().numCards() > 0) {
						int p = active->get_graveyard().numCards() - 1;
						Card *rm = active->get_graveyard().find(p);
						if (active->move(rm, p, active->get_graveyard(), active->get_board())) {
							rm->take_damage(-1 * (1 - rm->getDefense()));
							rm->set_actions(0);
							triggers[1].notifyObservers();
							active->setTrigger(triggers, rm);
							minion_enter_minion(triggers, rm, active, active, non_active);
							minion_enter_ritual(triggers, rm, active, active, non_active);
							minion_enter_minion(triggers, rm, non_active, active, non_active);
							minion_enter_ritual(triggers, rm, non_active, active, non_active);
						} else {
							active->get_graveyard().remove(p);
						}
						active->spend_magic(c->getCost());
						active->get_hand().remove(pos);
						if (testing && active->get_magic() < 0) active->set_magic(0);
					}
				}

				if (s->ability_type()[0] == "Charge") {
					Card *rit = active->get_board().get_ritual();
					if (rit) {
						rit->set_actions(rit->get_actions() + stoi(s->ability_type()[1]));
						active->spend_magic(c->getCost());
						active->get_hand().remove(pos);
						if (testing && active->get_magic() < 0) active->set_magic(0);
					}
				}
			}

			if (graphics) {
				gv->notify(active->getNum());
				gv->notify();
			}
		} else if (command == "use") {
			int pos = stoi(commands[1]);
			int pos2 = -1;
			int target_int = -1;
			Owner *target;
			if (commands.size() > 2) {
				if (commands[3] == "r") pos2 = 5;
				else pos2 = stoi(commands[3]);
				try {
					target_int = stoi(commands[2]);
				} catch (...) {
					target_int = -1;
				}
				if (target_int == 1) target = &p1;
				else if (target_int == 2) target = &p2;
				else target_int = -1;
			}

			Minion *m = dynamic_cast<Minion*>(active->get_board().find(pos));
			if (m->ability_type()[0] == "Activated" && ((m->getAbilityCost() <= active->get_magic()) || testing)) {
				if (m->ability_type()[1] == "Damage") {
					Card *target_c = target->get_board().find(pos2);
					target_c->take_damage(stoi(m->ability_type()[2]));
					if (target_c->getDefense() <= 0) {
						target->removeTrigger(triggers, target_c);
						triggers[2].notifyObservers();
						minion_leave_minion(triggers[2], active);
						minion_leave_minion(triggers[2], non_active);
						target->move(target_c, pos2, target->get_board(), target->get_graveyard());

					}
					active->spend_magic(m->getAbilityCost());
					if (testing && active->get_magic() < 0) active->set_magic(0);

				}

				if (m->ability_type()[1] == "AddMinion") {
					bool activated = false;
					int num_summons = stoi(m->ability_type()[3]);
					while (active->get_board().numCards() < 5 && num_summons > 0) {
						ifstream summon {"./cards/Air Elemental.txt"};
						string info;
						vector<string> card_info;
						card_info.emplace_back("Air Elemental");
						while (getline(summon, info)) {
							card_info.emplace_back(info);
						}

						if (card_info.size() == 1) card_info.emplace_back("1");
						auto c = active->create_card(card_info);
						active->add_to_all_cards(std::move(c));
						Card *c_ptr = active->get_newly_added();
						active->get_board().add(c_ptr);
						triggers[1].notifyObservers();
						active->setTrigger(triggers, c_ptr);
						minion_enter_minion(triggers, c_ptr, active, active, non_active);
						minion_enter_ritual(triggers, c_ptr, active, active, non_active);
						minion_enter_minion(triggers, c_ptr, non_active, active, non_active);
						minion_enter_ritual(triggers, c_ptr, non_active, active, non_active);
						c_ptr->set_actions(0);
						activated = true;
						num_summons--;
					}

					if (activated) {
						active->spend_magic(m->getAbilityCost());
						if (testing && active->get_magic() < 0) active->set_magic(0);
					}
				}

				if (graphics) gv->notify();
			}
		} else if (command == "inspect") {
			int player = stoi(commands[1]);
			int pos  = stoi(commands[1]);
			notifyObservers(player, pos);
		} else if (command == "hand") {
			notifyObservers(active->getNum());
		} else if (command == "board") {
			notifyObservers();
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
	start_turn_ritual(triggers[0], active, active);
	start_turn_ritual(triggers[0], non_active, active);
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
