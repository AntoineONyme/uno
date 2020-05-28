#include"Deck.h"
#pragma once



Deck::Deck(const string& name) {
	
	name_ = name;
}
void Deck::addCard(Card* c) {
	deck_.push_back(c);
}
//méthode permettant d'afficher le deck complet de carte 
void Deck::showDeck() {
	for (int i = 0; i < deck_.size() - 8 ; i++)
	{
		deck_[i]->show();
		cout << "      " << endl;
	}
}

//Généer tous les joker et +4 
void Deck::generateOpalCards() {
	for (int i = 0; i < 4; i++) // utilise une boucle pour générer automatiquement des cartes
		addCard(new OpalCard(i, "joker")); 
		
	for(int j = 4; j < 8;j++)
		addCard(new OpalCard(j, "+4"));
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
	//on génére des substituts de cartes joker et +4 que l'on paramètre manuellement car ayant des propriétés spécifiques.
	// substituts jocker
	addCard(new ColoredCard(n, 1, -1));
	n++;
	addCard(new ColoredCard(n, 2, -1));
	n++;
	addCard(new ColoredCard(n, 3, -1));
	n++;
	addCard(new ColoredCard(n, 4, -1));
	n++;
	// substituts +4
	addCard(new ColoredCard(n, 1, -2));
	n++;
	addCard(new ColoredCard(n, 2, -2));
	n++;
	addCard(new ColoredCard(n, 3, -2));
	n++;
	addCard(new ColoredCard(n, 4, -2));
}


vector<Card*> Deck::getDeck()
{
	return deck_; //retourne le deck de carte
}