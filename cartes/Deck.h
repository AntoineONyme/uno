#pragma once
#include <iostream>
#include<vector>
#include"Card.h"

using namespace std;

class Deck
{	vector<Card *> deck_;
	vector<Card*> hand_;
	vector<int> usedId_;
	string name_;

public :
	Deck(const string& name = "Deck");
	void addCard(Card*c);
	void showDeck();
	void generateOpalCards();
	void generateColoredCards();
	void generateHand();
};

