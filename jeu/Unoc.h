#pragma once
#include "Menu.h"
#include "Salon.h"
#include "Jeu.h"

/*
	Permet de choisir un salon, v�rifier qu'il convient et alors de lancer le jeu
*/
class Unoc
{
	Jeu* _jeu = nullptr;
	Salon* _salon = nullptr;

public:
	//	Gère l'affichage de l'image de lancement présente une seule fois
	Unoc();

	//	Gère le menu principal
	void lancementApplication();

	//	Non utilisé car les agrégats sont déjà supprimé dans lancementApplication() 
	~Unoc();
};


