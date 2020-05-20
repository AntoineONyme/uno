#include"Deck.h"
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
		addCard(new OpalCard(i, "joker"));
		
	for(int j = 4; j < 8;j++)
		addCard(new OpalCard(j, "plusFour"));
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
			else if (j > 9) {
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


vector<Card*> Deck::getDeck()
{
	return deck_;
}