#pragma once
#include "Card.h"
#include "OpalCard.h"
#include "ColoredCard.h"
#include "SpecialCard.h"
#include"Draw.h"
#include <algorithm>
#include<vector>
using namespace std;

/*==================================
header de la classe Deck gérant ici la génération des cartes nécessaires pour jouer au UNO
====================================*/

class Deck
{	vector<Card *> deck_ ; // vector dans lequel seront stockées toutes les cartes du jeu
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

