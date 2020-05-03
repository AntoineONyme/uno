#pragma once
#include "Salon.h"

class CommJeu
{
	Salon* _salon;
	int _etat = 0;
	vector<int> _cartesPiochees;
	bool _declareUno = false;
	int _joueurContreUno = 0;

public:
	static const int non_initialise = 0;
	static const int attente_autres_joueurs = 1;
	static const int jeu_joueur = 2;

	CommJeu(Salon* salon);
	bool ajoutCartePioche(int id);
	bool declareUno();
	bool declareContreUno(int idJoueur);
	bool finTourAtt();
};

