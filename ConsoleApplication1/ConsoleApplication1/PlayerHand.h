#ifndef _PLAYERHAND_H_
#define _PLAYERHAND_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "card.h"
using namespace std;

class PlayerHand {
private:
	vector<Card*> cards;

public:
	int size();

	void discard(int i);

	PlayerHand& operator+(Card* c);
	PlayerHand& operator+=(Card* c);
	Card* operator[](int i);
	friend ostream& operator<<(ostream& str, PlayerHand& hand);
};


#endif