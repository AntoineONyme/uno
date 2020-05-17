#pragma once
#include "Menu.h"
#include "Salon.h"
#include "Jeu.h"

/*
	Permet de choisir un salon, vérifier qu'il convient et alors de lancer le jeu
*/
class Unoc
{
	Jeu* _jeu = nullptr;
	Salon* _salon = nullptr;

public:
	Unoc();
	void lancementApplication();
	~Unoc();
};


