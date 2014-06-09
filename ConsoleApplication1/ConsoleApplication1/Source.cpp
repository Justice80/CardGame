#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUMPLAYERS = 2;
const int NUMCARDS = 5;

class Card {
private:
	int suit;
	int value;

public:
	static const int SPADES = 1;
	static const int DIAMONDS = 2;
	static const int CLUBS = 3;
	static const int HEARTS = 4;
	Card(int s, int v) {
		setSuit(s);
		setValue(v);
	}

	int getSuit() { return suit; }
	void setSuit(int s) {
		suit = (s >= SPADES && s <= HEARTS) ? s : SPADES;
	}
	int getValue() { return value; }
	void setValue(int v) {
		value = (v >= 1 && v <= 13) ? v : 1;
	}

	friend ostream& operator<<(ostream& str, const Card& c) {
		if (c.value == 13) str << "King";
		else if (c.value == 12) str << "Queen";
		else if (c.value == 11) str << "Jack";
		else if (c.value == 1) str << "Ace";
		else str << c.value;

		str << " of ";

		switch (c.suit) {
		case SPADES:
			str << "Spades";
			break;
		case DIAMONDS:
			str << "Diamonds";
			break;
		case CLUBS:
			str << "Clubs";
			break;
		case HEARTS:
			str << "Hearts";
			break;
		}

		return str;
	}
};

class PlayerHand {
private:
	vector<Card*> cards;

public:
	int size() { return cards.size(); }

	void discard(int i) {
		for (; i < cards.size(); i++) {
			cards[i] = cards[i + 1];
		}
		cards.pop_back();
	}

	PlayerHand& operator+(Card* c) {
		cards.push_back(c);

		return *this;
	}

	PlayerHand& operator+=(Card* c) {
		return *this + c;
	}

	Card* operator[](int i) {
		return cards[i];
	}

	friend ostream& operator<<(ostream& str, PlayerHand& hand) {
		for (int c = 0; c < hand.size(); c++)
			str << (*hand[c]) << endl;

		return str;
	}
};

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
