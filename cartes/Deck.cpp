#include "Deck.h"
#include "Card.h"
#include "OpalCard.h"
#include "ColoredCard.h"
#include "SpecialCard.h"
#include <stdlib.h>
#include <algorithm>
#pragma once



Deck::Deck(const string& name) {
	name_ = name;
}
void Deck::addCard(Card* c) {
	deck_.push_back(c);
}

void Deck::showDeck() {
	for (int i = 0; i < deck_.size(); i++)
	{
		deck_[i]->show();
		cout << "      " << endl;
	}
}

void Deck::generateOpalCards() {
	for (int i = 0; i < 4; i++)
	{
		addCard(new OpalCard(i, "joker"));
		addCard(new OpalCard(i+4, "plusFour"));
	}

}
void Deck::generateColoredCards() {
	int n = 8;
	int sp = 0;
	for (int i = 1; i < 5; i++) {sp = 0;
		for (int j = 0; j < 13; j++)
		{
			if (j == 0)
			{
				addCard(new ColoredCard(n, i, j));
				n++;
			}
			else if (j > 8) {
				addCard(new SpecialCard(n, i, j, sp));
				n++;
				addCard(new SpecialCard(n, i, j, sp));
				n++;
				sp++;
				
			}
			else
			{
				addCard(new ColoredCard(n, i, j));
				n++;
				addCard(new ColoredCard(n, i, j));
				n++;
			}
		}
		
	}
}

void Deck::generateHand() {
	int rd;
	/*
	rd = rand() % 108;
	hand_.push_back(deck_[rd]);
	usedCards_.push_back(deck_[rd]);
	while (hand_.size() < 7) {
		rd = rand() % 108;
		for (int i = 0; i < usedCards_.size();i++){
			
			hand_.push_back(deck_[rd]);
		}
		else
			cout << " BIIIIP " << endl;

	}
	cout << "Voici votre main :\n" << endl;
	for (int i = 0; i < hand_.size(); i++)
	{	
		hand_[i]->show();
		cout << "      " << endl;
		
	}*/

}