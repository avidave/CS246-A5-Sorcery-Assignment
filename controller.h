#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include "subject.h"
#include "owner.h"
#include "deck.h"

using namespace std;

class Controller : public Subject {
	istream &in;
	Owner p1;
	Owner p2;
	Owner &active = p1;

	public:
		Controller(istream &in, Owner p1, Owner p2);
		~Controller();

		void echoName(int n);
		Owner& getActive();

		void start();
};

#endif
