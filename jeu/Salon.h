#pragma once
#include "../communication/CommSalon.h"
#include "Menu.h"

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

	bool choixSalon(string pseudo);

	string getJoueur(int id) const { return _joueurs->operator[](id); };
	bool joueurEstAdversaire(int id) const { return id != _idJoueurActuel and 0 <= id < _joueurs->size(); };

	int idNextPlayer();
	int getJoueurActuel() const { return _idJoueurActuel; };
	int getNbJoueurs() const { return _joueurs->size(); };
	int getNbManches() const { return _nbManches; };
};