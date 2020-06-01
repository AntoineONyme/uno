#pragma once

#include "../jeu/Salon.h"

//	Permet de sauvegarder les données d'un joueur
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

	//	méthode privée pour réinitialiser les données des joueurs à chaque tour
	bool initialiserTour();

	//	constantes de stockage des fichiers
	const string REPERTOIRE = "XXpussyEmpalle";
	const string VERSION = "1.0.1";

public:
	//	Différents statuts possibles pour la manche
	enum class FinManche { manche_en_cours, manche_terminee, manche_abandonnee };

	//	Le constructeur a besoin d'un pointeur vers le salon comme ils sont associés
	CommJeu(Salon* psalon);
	~CommJeu();

	//	Permet d'attendre que ce soit à son tour au début de la partie (car rien à transmettre initialement)

	void attenteTour();

	//	Fonctions pour paramétrer les infos à transmettre, qui seront transmises avec l'appel de finTourAtt()

	void declareCartesPiochees(vector<int>* cartesPiochees);
	bool declarerUno();
	bool declareContreUno(int idJoueur);
	bool declarerCarteJouee(int idCarte, bool carteDejaSubie);
	//Ici c'est la fonctionalité qui permet au joueur d'envoyer un message textuel
	void declareMessage(string message) { _donneesJoueur.message = message; };

	//	Permet d'envoyer les infos "déclarées" puis attend que ce soit à son tour de jouer

	bool finTourAtt(FinManche finManche = FinManche::manche_en_cours);

	//	Fonctions pour recuperer les infos de l'adversaire, recuperees avec finTourAtt()

	//	Pour avoir la carte du dessus du packet
	int getCarteJoueeAdversaire() const { return _donneesAdversaires.carteJouee; };
	//	Pour savoir si on doit appliquer les effets de cette carte
	bool getCarteDejaSubie() const { return _donneesAdversaires.carteDejaSubie; };
	//	Cette fonction permet de mettre à jour la pioche du joueur actuel en retirant les cartes piochées
	vector<int>* getCartePiocheesAdversaire() const { return _donneesAdversaires.cartesPiochees; };
	//	Pour savoir si un joueur a abandonné / gagné
	FinManche getStatusManche();
	//	Permet de savoir si un joueur a lancé un contre-uno contre le joueur actuel
	bool isContreUno() const { return _donneesAdversaires.joueurContreUno == 1; };

	//	Permet d'envoyer une confirmation avant de relancer la partie
	bool finTour(FinManche finManche = FinManche::manche_en_cours);

private:
	//	On redeclare ici ce champ prive comme l'enum est public
	FinManche _finManche = FinManche::manche_en_cours;
};
