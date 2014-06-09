#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>
using namespace std;

class Card {
private:
	int suit;
	int value;

public:
	static const int SPADES = 1;
	static const int DIAMONDS = 2;
	static const int CLUBS = 3;
	static const int HEARTS = 4;
	Card(int s, int v);

	int getSuit();
	void setSuit(int s);
	int getValue();
	void setValue(int v);

	friend ostream& operator<<(ostream& str, const Card& c);
};

#endif