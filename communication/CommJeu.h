#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Fichier.h"

class CommJeu
{
	int _etat = 0;
	string _nomSalon = "";

	Fichier* _fichier = nullptr;

	vector<int> _cartesPiochees;
	string _carteJouee = "";
	bool _declareUno = false;
	string _joueurContreUno = "";

	bool initialiserTour();

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.0";

public:

	CommJeu(string nomSalon);
	bool ajoutCartePioche(int id);
	bool declareUno();
	bool declareContreUno(int idJoueur);
	bool finTourAtt();
	bool declareCarteJouee(int idCarte);
	string carteJouee() const { return _carteJouee; };
};
