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
header de la classe Deck g�rant ici la g�n�ration des cartes n�cessaires pour jouer au UNO
====================================*/

class Deck
{	vector<Card *> deck_ ; // vector dans lequel seront stock�es toutes les cartes du jeu
	string name_ ;
	Draw *draw_ ;
public :
	Deck(const string& name);
	void addCard(Card *c); // permet d'ajouter une carte au vecteur deck_ en prenant en entr�e une carte.
	void showDeck(); // permet d'afficher la totalit� du des cartes ainsi que leurs caract�ristiques.
	void generateOpalCards(); // permet de g�n�rer toutes les cartes de classe OpalCard.
	void generateColoredCards(); // permet de g�n�rer toutes les cartes de classe
	vector<Card *> getDeck(); // getter du deck.
};

