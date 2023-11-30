#ifndef _OWNER_H_
#define _OWNER_H_

#include <string>
using namespace std;

class Owner {
	string name;
	int num;
	public:
		Owner(string name, int num);
		~Owner();
		string getName();
		int getNum();
};

#endif
