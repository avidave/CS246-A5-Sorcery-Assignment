#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include "observer.h"
using namespace std;

class Subject {

	vector<Observer*> observers;

	public:
		Subject();
		void attach(Observer *o);
		void detach(Observer *o);
		void notifyObservers();
		void notifyObservers(int n);
		vector<Observer*> getObservers();
		virtual ~Subject() = 0;
};


#endif
