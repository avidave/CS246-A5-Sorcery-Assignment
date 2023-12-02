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
			gameFile = ifstream{argv[i + 1]};
			if (!gameFile.is_open()) {
				cerr << "Provided game file cannot be found" << endl;
			}
			++i;
			isInit = true;
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
	//Player1.shuffle_deck();
	Player2.import_deck(deck2);
	//Player2.shuffle_deck();

	Controller control{cin, move(Player1), move(Player2)};
	control.start();

	// for (int i = 1; i < 3; i++) {
	// 	control.echoName(i);
	// }

	//cout << control.getActive().getName() << endl;

	//Card c1{"Card 1", 1};
	//Card c2{"Card 2", 2};
	//Deck deck;
	//deck.add(&c1);
	//deck.add(&c2);
	//cout << deck.display();
	//control.getActive().import_deck();
	//control.getActive().display_deck();

	string command;

	while (isInit) {
		if (!(gameFile >> command)) break;//cin >> command;
		//if (!(cin >> command)) break;

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
			return 0;
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
