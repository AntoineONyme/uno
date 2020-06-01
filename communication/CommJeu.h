#pragma once

#include "../jeu/Salon.h"

typedef struct DonneesCommJeu {
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


	bool initialiserTour();

	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.1";

public:
	enum FinManche { manche_en_cours, manche_terminee, manche_abandonnee };

	CommJeu(Salon* psalon);
	~CommJeu();

	//	Permet d'attendre que ce soit � son tour au d�but de la partie (car rien � transmettre initialement)
	void attenteTour();

	//	Fonctions pour param�trer les infos � transmettre, qui seront transmises avec l'appel de finTourAtt()
	void declareCartesPiochees(vector<int>* cartesPiochees);
	bool declarerUno();
	bool declareContreUno(int idJoueur);
	bool declarerCarteJouee(int idCarte, bool carteDejaSubie);
	void declareMessage(string message) { _donneesJoueur.message = message; };

	//	Permet d'envoyer les infos "d�clar�es" puis attend que ce soit � son tour de jouer
	bool finTourAtt(FinManche finManche = manche_en_cours);

	//	Fonctions pour r�cup�rer les infos de l'adversaire, r�cup�r�es avec
	int getCarteJoueeAdversaire() const { return _donneesAdversaires.carteJouee; };
	bool getCarteDejaSubie() const { return _donneesAdversaires.carteDejaSubie; };
	vector<int>* getCartePiocheesAdversaire() const { return _donneesAdversaires.cartesPiochees; };
	int carteJouee() const { return _donneesAdversaires.carteJouee; };
	bool getASubitContreUno() const { return _donneesAdversaires.joueurContreUno; };
	FinManche getStatusManche();
	bool isContreUno() const { return _donneesAdversaires.joueurContreUno == 1; };

	//	Permet d'envoyer une confirmation avant de relancer la partie
	bool finTour(FinManche finManche = manche_en_cours);

private:
	//	Je red�clare ici ce champ priv� comme l'�num est public
	FinManche _finManche = manche_en_cours;
};
