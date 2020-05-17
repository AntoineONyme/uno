#pragma once/*
#include "../jeu/Salon.h"

class CommJeu
{
	Salon* _salon = nullptr;
	int _etat = 0;

	vector<int> _cartesPiochees;
	string _carteJouee = "";
	bool _declareUno = false;
	string _joueurContreUno = "";

	bool initialiserTour();

public:
	static const int non_initialise = 0;
	static const int attente_autres_joueurs = 1;
	static const int jeu_joueur = 2;

	CommJeu(Salon* salon);
	bool ajoutCartePioche(int id);
	bool declareUno();
	bool declareContreUno(int idJoueur);
	bool finTourAtt();
	bool declareCarteJouee(int idCarte);
	string carteJouee() const { return _carteJouee; };
};
*/
