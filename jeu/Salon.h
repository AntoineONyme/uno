#pragma once
#include "../communication/Fichier.h"

class Salon
{
	string _nom;
	Fichier _fichier;

	int _etat = 0;
	int _manche;
	int _nbManches;
	vector<string*> _joueurs;
	int _idJoueurActuel;	// Joueur de ce client

public:
	Salon(string nom);

	string * getJoueur(int id) const { return _joueurs[id]; };
	bool joueurEstAdversaire(int id) const { return id != _idJoueurActuel and 0 <= id < _joueurs.size(); };
};