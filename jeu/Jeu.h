#pragma once
#include "Salon.h"
#include "Menu.h"
#include "../communication/CommJeu.h"
#include "Game.h"
//#include "../cartes/Deck.h"

class Jeu
{
	Salon* _salon = nullptr;
	//Deck* _deck = nullptr;

public:
	Jeu(Salon* psalon);
	void lancementPartie();
};

