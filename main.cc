#include <iostream>
#include <string>
#include "observer.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"
#include "card.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	string deck1 = "default.deck";
	string deck2 = "default.deck";
	string p1 = "Player 1";
	string p2 = "Player 2";
	ifstream gameFile;
	bool isInit = false, testing = false, graphics = false;
	for (int i = 0; i < argc; i++) {
		string arg = argv[i];
		if (arg == "-deck1") {
			cout << arg << argv[i + 1] << endl;
			deck1 = argv[i + 1];
			++i;
		} else if (arg == "-deck2") {
			cout << arg << argv[i + 1] << endl;
			deck2 = argv[i + 1];
			++i;
		} else if (arg == "-init") {
			cout << arg << argv[i + 1] << endl;
			gameFile = ifstream{argv[i + 1]};
			if (!gameFile.is_open()) {
				cerr << "Provided game file cannot be found" << endl;
			} else {
				isInit = true;
			}
			++i;
		} else if (arg == "-testing") {
			cout << arg << endl;
			testing = true;
		} else if (arg == "-graphics") {
			cout << arg << endl;
			graphics = true;
		}
	}

	gameFile >> p1;
	gameFile >> p2;

	cout << deck2 << endl;

	Owner Player1{p1, 1};
	Owner Player2{p2, 2};

	Player1.import_deck(deck1);
	Player2.import_deck(deck2);

	Controller control{move(Player1), move(Player2)};
	control.start(testing);
	control.turn();
	if (isInit) {
		control.play(gameFile, testing);
	} else {
		control.play(cin, testing);
	}
	cout << control.getActive()->getName() << " Wins" << endl;
	//control.turn();
	//control.flip_active();
	//control.turn();
}
