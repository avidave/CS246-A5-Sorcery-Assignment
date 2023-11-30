#include <iostream>
#include <string>
#include "observer.h"
#include "controller.h"
#include "owner.h"

using namespace std;

int main(int argc, char *argv[]) {
	Owner Player1{"Player 1", 1};
	Owner Player2{"Player 2", 2};
	Controller control{cin, Player1, Player2};
	for (int i = 1; i < argc; i++) {
		cout << argv[i] << endl;
	}

	for (int i = 1; i < 3; i++) {
		control.echoName(i);
	}

	cout << control.getActive().getName() << endl;
}
