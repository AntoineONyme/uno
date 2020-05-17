#include "Unoc.h"

/*
	Lancement de la partie
*/
Unoc::Unoc()
{
	// https://text-image.com/convert/ascii.html
	Menu::affichageImageConsole("jeu/logo.txt");
}

void Unoc::lancementApplication()
{
	cout << "\nMerci de choisir un pseudo (longueur entre 5 et 20): ";

	string pseudo;
	cin >> pseudo;

	bool continuer = true;
	while (continuer)
	{
		_salon = new Salon();
		if (!_salon->choixSalon(pseudo)) {
			continuer = false;
		}
		else {
			_jeu = new Jeu(_salon);
			_jeu->lancementPartie();
			delete _jeu;
		}
		delete _salon;
	}

	// A ce stade le jeu est termine donc on arrete tout :(
	cout << endl << "A bientôt !" << endl;
	return;
}

Unoc::~Unoc()
{
}
