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
	void addCard(Card *c); // permet d'ajouter une carte au vecteur deck_ en prenant en entrée une carte.
	void showDeck(); // permet d'afficher la totalité du des cartes ainsi que leurs caractéristiques.
	void generateOpalCards(); // permet de générer toutes les cartes de classe OpalCard.
	void generateColoredCards(); // permet de générer toutes les cartes de classe
	vector<Card *> getDeck(); // getter du deck.
};

