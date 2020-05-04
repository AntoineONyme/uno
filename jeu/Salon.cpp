#include "Salon.h"

Salon::Salon(string nom)
{
	Fichier _fichier(_nom, "/");
	_nom = nom;
}

int Salon::idNextPlayer()
{
	return _joueurs.size()>= _idJoueurActuel+1 ? 0 : _idJoueurActuel +1;	//Condition binaire de vérification
}
