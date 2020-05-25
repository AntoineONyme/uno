#pragma once
/*
#include <vector>
#include <string>
#include <iostream>

#include "Fichier.h"*/

#include "../jeu/Salon.h"

typedef struct {
	int idCarte;
	bool alreadyPlayed = false;
} CarteJoueeStruct;

class CommJeu
{
	int _etat = 0;

	Fichier* _fichier = nullptr;
	Salon* _salon = nullptr;

	vector<int>* _cartesPiochees = nullptr;
	vector<int>* _cartesPiocheesAdversaire = nullptr;

	int _carteJouee = -1;
	int _carteJoueeAdversaire = -1;
	bool _carteDejaSubie = false;

	bool _declarerUno = false;
	int _joueurContreUno = -1;
	string _message;

	bool initialiserTour();

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.0";

public:

	CommJeu(Salon* psalon);
	~CommJeu();
	void attenteTour();
	void setCartesPiochees(vector<int>* cartesPiochees);
	bool finTourAtt(bool finPartie = false);

	bool ajoutCartePioche(int id);
	bool declarerUno();
	bool declareContreUno(int idJoueur);
	bool declarerCarteJouee(int idCarte);
	void declareMessage(string message) { _message = message; };

	int getCarteJoueeAdversaire() const { return _carteJoueeAdversaire; };
	vector<int>* getCartePiocheesAdversaire() const { return _cartesPiocheesAdversaire; };
	int carteJouee() const { return _carteJouee; };
};
