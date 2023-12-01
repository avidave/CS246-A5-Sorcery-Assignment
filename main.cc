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
	for (int i = 1; i < argc; i++) {
		//cout << argv[i] << endl;
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
			try {
				gameFile = ifstream{argv[i + 1]};
				++i;
				isInit = true;
			} catch(...) {
				cerr << "Provided game file cannot be found" << endl;
			}
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

	Owner Player1{p1, 1};
	Owner Player2{p2, 2};
	Player1.import_deck(deck1);
	Player2.import_deck(deck2);
	Controller control{cin, move(Player1), move(Player2)};

	for (int i = 1; i < 3; i++) {
		control.echoName(i);
	}

	cout << control.getActive().getName() << endl;

	//Card c1{"Card 1", 1};
	//Card c2{"Card 2", 2};
	//Deck deck;
	//deck.add(&c1);
	//deck.add(&c2);
	//cout << deck.display();
	//control.getActive().import_deck();
	control.getActive().display_deck();

	string command;

	while (gameFile >> command) {
		if (command == "help") {
			cout << command << endl;
		} else if (command == "end") {
			cout << command << endl;
		} else if (command == "quit") {
			cout << command << endl;
		} else if (command == "draw") {
			cout << command << endl;
		} else if (command == "discard") {
			cout << command << endl;
		} else if (command == "attack") {
			cout << command << endl;
		} else if (command == "play") {
			cout << command << endl;
		} else if (command == "use") {
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
