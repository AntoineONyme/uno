#pragma once
#include "Card.h"
#include "OpalCard.h"
#include "ColoredCard.h"
#include "SpecialCard.h"
#include"Draw.h"
#include <algorithm>
#include<vector>


using namespace std;

class Deck
{	vector<Card *> deck_ ;
	string name_ ;
	Draw *draw_ ;
public :
	Deck(const string& name);
	void addCard(Card *c);
	void showDeck();
	void generateOpalCards();
	void generateColoredCards();
	vector<Card *> getDeck();
};

