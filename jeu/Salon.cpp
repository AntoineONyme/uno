#include "Salon.h"

Salon::Salon(string nom)
{
	Fichier _fichier(_nom, "/");
	_nom = nom;
}
