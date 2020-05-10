#include"Deck.h"
#pragma once



Deck::Deck(const string& name, Draw *dr) {
	
	name_ = name;
	dr = draw_;
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

/*void Deck::generateHand() {
	//Dec var
	int rd;
	Card* a;
	vector<int>::iterator it;
	
	//Def var
	rd = rand() % 108;
	a = deck_[rd];
	it = find(usedId_.begin(), usedId_.end(), a->getId());
	
	while (hand_.size() < 7) 
	{
		rd = rand() % 108;
		a = deck_[rd];
		it = find(usedId_.begin(), usedId_.end(), a->getId());
		
		if (it == usedId_.end())
		{
			hand_.push_back(deck_[rd]);
			usedId_.push_back(a->getId());
		}
		else
			cout << " BIIIIP " << endl;
	}
		
			

	
	cout << "Voici votre main :\n" << endl;
	for (int i = 0; i < hand_.size(); i++)
	{	
		hand_[i]->show();
		cout << "      " << endl;
		
	}
	cout << "Voici les cartes utilisees :\n" << endl;
	for (int i = 0; i < usedId_.size(); i++)
	{
		cout << usedId_[i];
		cout << "      " << endl;

	}
}*/

vector<Card*> Deck::getDeck()
{
	return deck_;
}