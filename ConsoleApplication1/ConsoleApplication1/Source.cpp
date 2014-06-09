#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "card.h"
#include "PlayerHand.h"
using namespace std;

const int NUMPLAYERS = 2;
const int NUMCARDS = 5;

void filldeck(stack<Card*>& cards) {
	vector<Card*> tmp;
	Card* c;
	bool found;
	while (tmp.size() < 52) {
		c = new Card(rand() % 4 + 1, rand() % 13 + 1);
		found = false;
		for (int i = 0; !found && i < tmp.size(); i++) {
			found = (tmp[i]->getSuit() == c->getSuit() && tmp[i]->getValue() == c->getValue());
		}
		if (!found)
			tmp.push_back(c);
	}

	for (int i = tmp.size() - 1; i >= 0; i--)
		cards.push(tmp[i]);
}

void deal(stack<Card*>& deck, PlayerHand players[], int numplayers) {
	for (int c = 0; c < NUMCARDS; c++) {
		for (int p = 0; p < numplayers; p++) {
			players[p] += deck.top();
			deck.pop();
		}
	}
}

void cleanup(PlayerHand& cards) {
	for (int i = 0; i < cards.size(); i++)
		delete cards[i];
}

void cleanup(stack<Card*>& cards) {
	while (!cards.empty()) {
		delete cards.top();
		cards.pop();
	}
}

int main()
{
	srand(time(NULL));
	stack<Card*> deck, discardpile;
	PlayerHand players[NUMPLAYERS];

	filldeck(deck);
	deal(deck, players, NUMPLAYERS);

	for (int p = 0; p < NUMPLAYERS; p++) {
		cout << "player " << p << ":\n" << players[p];
	}

	cleanup(deck);
	cleanup(discardpile);
	for (int p = 0; p < NUMPLAYERS; p++)
		cleanup(players[p]);
}
