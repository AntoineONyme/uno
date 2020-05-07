#pragma once
#include <iostream>
#include<list>
#include<vector>
#include"Card.h"
#include"Draw.h"
#include"OpalCard.h"
#include"ColoredCard.h"
#include"SpecialCard.h"

using namespace std;

class Deck
{	vector<Card *> deck_;
	// vector<int> usedId_;
	string name_;
	//Draw Diderot_; // Jeu de mots avec un pointeur appelé au départ dDraw.

public :
	Deck(const string& name = "Deck");
	void addCard(Card*c);
	void showDeck();
	void generateOpalCards();
	void generateColoredCards();
	void generateHand(list<int>hand_);
};

