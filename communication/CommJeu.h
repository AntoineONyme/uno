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

typedef struct {
	int carteJouee = -1;
	bool carteDejaSubie = false;
	bool declareUno = false;
	int joueurContreUno = -1;
	string message = "";
	vector<int>* cartesPiochees = new vector<int>;
} DonneesCommJeu;

class CommJeu
{
	Fichier* _fichier = nullptr;
	Salon* _salon = nullptr;

	//	attributs concernant le joueur actuel
	DonneesCommJeu _donneesJoueur;

	//	attributs concernant le(s) adversaire(s)
	DonneesCommJeu _donneesAdversaires;

	enum FinManche _finManche = FinManche::manche_en_cours;

	bool initialiserTour();

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.1";

public:

	CommJeu(Salon* psalon);
	~CommJeu();

	//	Permet d'attendre que ce soit à son tour au début de la partie (car rien à transmettre initialement)
	void attenteTour();

	//	Fonctions pour paramétrer les infos à transmettre, qui seront transmises avec l'appel de finTourAtt()
	void declareCartesPiochees(vector<int>* cartesPiochees);
	bool declarerUno();
	bool declareContreUno(int idJoueur);
	bool declarerCarteJouee(int idCarte, bool carteDejaSubie);
	void declareMessage(string message) { _donneesJoueur.message = message; };

	//	Permet d'envoyer les infos "déclarées" puis attend que ce soit à son tour de jouer
	bool finTourAtt(FinManche finManche = FinManche::manche_en_cours);

	//	Fonctions pour récupérer les infos de l'adversaire, récupérées avec
	int getCarteJoueeAdversaire() const { return _donneesAdversaires.carteJouee; };
	bool getCarteDejaSubie() const { return _donneesAdversaires.carteDejaSubie; };
	vector<int>* getCartePiocheesAdversaire() const { return _donneesAdversaires.cartesPiochees; };
	int carteJouee() const { return _donneesAdversaires.carteJouee; };
	bool getASubitContreUno() const { return _donneesAdversaires.joueurContreUno; };
	FinManche getStatusManche() const { return _finManche; };
	bool isContreUno() const { return _donneesAdversaires.joueurContreUno == 1; };
};
