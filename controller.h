#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include "subject.h"
#include "owner.h"
#include "deck.h"
#include "trigger.h"

using namespace std;

class Controller : public Subject {
	Owner p1;
	Owner p2;
	Owner *active = &p1;
	vector<Trigger> triggers;

	public:
		Controller(Owner p1, Owner p2);
		~Controller();

		void echoName(int n);
		Owner* getActive();

		void start();
		void turn();
		void flip_active();
		void play(istream &in, bool testing);
		void trigger(int n);
};

#endif
