#pragma once
#include "Salon.h"
#include "Menu.h"
#include "../communication/CommJeu.h"
#include "Game.h"
//#include "../cartes/Deck.h"

class Jeu
{
	Salon* _salon = nullptr;

public:
	//	permet d'afficher l'image de lancement du jeu
	Jeu(Salon* psalon);

	//	Permet de lancer la boucle infinie de fonctionnement (menu principal)
	void lancementPartie();
};

