#include "CommJeu.h"

CommJeu::CommJeu(Salon* salon)
{
	_salon = salon;
}

bool CommJeu::ajoutCartePioche(int id)
{
	// V�rification que la phase de jeu permet de piocher
	if (_etat != jeu_joueur) {
		return false;
	}
	_cartesPiochees.push_back(id);
	return true;
}

bool CommJeu::declareUno() {
	// V�rification que la phase de jeu permet de d�clarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}
	_declareUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	// V�rification que la phase de jeu permet de d�clarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}

	// V�rification que le joueur existe et est un adversaire
	if (!_salon->joueurEstAdversaire(idJoueur)) {
		return false;
	}

	_joueurContreUno = idJoueur;
	return true;
}

bool CommJeu::finTourAtt() {
	//to do 1 : on envoit les donn�es

	do
	{
		//to do 2 : on attend une r�ponse

	} while (true);
	return true;
}