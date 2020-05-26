#pragma once
#include "../communication/CommSalon.h"
#include "Menu.h"

enum StatuSalon {
	quitter,
	erreur,
	rejoindre_salon
};

class Salon
{

	int _etat = 0;	//0: pas de salon, 1: en attente, 2: en jeu, 3: termine
	int _nbManches = 0;
	vector<string>* _joueurs;
	int _idJoueurActuel = 0;	// Joueur de ce client
	string _nom;

public:
	Salon();
	~Salon();

	StatuSalon choixSalon(string pseudo);

	string getJoueur(int id) const { return _joueurs->operator[](id); };
	string getJoueur(string id) const { return getJoueur(std::stoi(id)); };
	bool joueurEstAdversaire(int id) const { return id != _idJoueurActuel and 0 <= id < _joueurs->size(); };

	int idNextPlayer();
	int getJoueurActuel() const { return _idJoueurActuel; };
	int getNbJoueurs() const { return _joueurs->size(); };
	int getNbManches() const { return _nbManches; };
	string getNomSalon() const { return _nom; };
};