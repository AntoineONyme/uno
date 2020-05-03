#include "CommJeu.h"

CommJeu::CommJeu(Salon* salon)
{
	_salon = salon;
}

bool CommJeu::ajoutCartePioche(int id)
{
	// Vérification que la phase de jeu permet de piocher
	if (_etat != jeu_joueur) {
		return false;
	}
	_cartesPiochees.push_back(id);
	return true;
}

bool CommJeu::declareUno() {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}
	_declareUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}

	// Vérification que le joueur existe et est un adversaire
	if (!_salon->joueurEstAdversaire(idJoueur)) {
		return false;
	}

	_joueurContreUno = idJoueur;
	return true;
}

bool CommJeu::finTourAtt() {
	//to do 1 : on envoit les données

	do
	{
		//to do 2 : on attend une réponse

	} while (true);
	return true;
}