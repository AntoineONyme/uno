#include "Salon.h"

Salon::Salon(string nom)
{
	_nom = nom;
	Fichier _fichier(_nom, "/", true);
}

Salon::Salon()
{
}

int Salon::idNextPlayer()
{
	return _joueurs.size()>= _idJoueurActuel+1 ? 0 : _idJoueurActuel +1;	//Condition binaire de vérification
}
