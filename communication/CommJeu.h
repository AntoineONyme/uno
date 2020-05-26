#pragma once
/*
#include <vector>
#include <string>
#include <iostream>

#include "Fichier.h"*/

#include "../jeu/Salon.h"

enum FinManche {
	manche_en_cours,
	manche_terminee,
	manche_abandonnee
};

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
	enum FinManche _finManche = FinManche::manche_en_cours;

	bool _declarerUno = false;
	int _joueurContreUno = -1;
	string _message;

	bool initialiserTour();

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.1";

public:

	CommJeu(Salon* psalon);
	~CommJeu();
	void attenteTour();
	void setCartesPiochees(vector<int>* cartesPiochees);
	bool finTourAtt(FinManche finManche = FinManche::manche_en_cours);

	bool ajoutCartePioche(int id);
	bool declarerUno();
	bool declareContreUno(int idJoueur);
	bool declarerCarteJouee(int idCarte, bool carteDejaSubie);
	void declareMessage(string message) { _message = message; };

	int getCarteJoueeAdversaire() const { return _carteJoueeAdversaire; };
	vector<int>* getCartePiocheesAdversaire() const { return _cartesPiocheesAdversaire; };
	int carteJouee() const { return _carteJouee; };
	bool getCarteDejaSubie() const { return _carteDejaSubie; };
	FinManche getStatusManche() const { return _finManche; };
};
