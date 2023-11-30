#include <iostream>
#include <string>
#include "observer.h"
#include "controller.h"
#include "owner.h"
#include "deck.h"
#include "card.h"

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

	//Card c1{"Card 1", 1};
	//Card c2{"Card 2", 2};
	//Deck deck;
	//deck.add(&c1);
	//deck.add(&c2);
	//cout << deck.display();
	Player1.import_deck();
	Player1.display_deck();
}
