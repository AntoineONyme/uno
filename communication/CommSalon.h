#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Fichier.h"

using namespace std;

//	Permet d'échanger les paramètres du salon
typedef struct Struct_Parametres_Salon {
	string nom;
	int nbManches;
	int nbJoueurs;
	string erreur = "";
	vector<string>* joueurs = nullptr;
	int idJoueurActuel = 0;
} Struct_Parametres_Salon;

class CommSalon
{
	Fichier* _fichier = nullptr;

	//	Utilisé pour générer le fichier utilisé par la classe Jeu
	void creationFichierJeu(Struct_Parametres_Salon parametres_salon);

public:
	enum class StatutSalon { non_initialise, attente_autres_joueurs, jeu_joueur };

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.1";

	CommSalon();

	//	Pour créer un nouveau salon
	bool creation(Struct_Parametres_Salon parametres_salon, string pseudo);
	//	Pour rejoindre un salon existant
	Struct_Parametres_Salon join(string nom, string pseudo);
	//	Pour attendre le début de la partie une fois le salon rejoint
	bool attenteSalonComplet(Struct_Parametres_Salon parametres_salon, bool heberge);
	//	Pour supprimer les fichiers du salon une fois la partie finie / nettoyage forcé
	bool supprimerSalon(string nom);

private:
	StatutSalon _etat = StatutSalon::non_initialise;
};