#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Fichier.h"

using namespace std;

typedef struct {
	string nom;
	int nbManches;
	int nbJoueurs;
	string erreur = "";
	vector<string>* joueurs = nullptr;
	int idJoueurActuel = 0;
} Struct_Parametres_Salon;

class CommSalon
{
	int _etat = 0;
	string _nom = "";

	Fichier* _fichier = nullptr;

public:
	static const int non_initialise = 0;
	static const int attente_autres_joueurs = 1;
	static const int jeu_joueur = 2;

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.0";

	CommSalon();
	bool creation(Struct_Parametres_Salon parametres_salon, string pseudo);
	Struct_Parametres_Salon join(string nom, string pseudo);
	bool attenteSalonComplet(Struct_Parametres_Salon parametres_salon, bool heberge);
	bool supprimerSalon(string nom);
};