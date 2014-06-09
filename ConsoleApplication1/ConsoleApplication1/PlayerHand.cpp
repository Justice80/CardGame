#include "PlayerHand.h"

int PlayerHand::size() { return cards.size(); }

void PlayerHand::discard(int i) {
	for (; i < cards.size(); i++) {
		cards[i] = cards[i + 1];
	}
	cards.pop_back();
}

PlayerHand& PlayerHand::operator+(Card* c) {
	cards.push_back(c);

	return *this;
}

PlayerHand& PlayerHand::operator+=(Card* c) {
	return *this + c;
}

Card* PlayerHand::operator[](int i) {
	return cards[i];
}

ostream& operator<<(ostream& str, PlayerHand& hand) {
	for (int c = 0; c < hand.size(); c++)
		str << (*hand[c]) << endl;

	return str;
}
