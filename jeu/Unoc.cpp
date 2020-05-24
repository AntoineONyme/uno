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
	cout << endl;
	string pseudo = Menu::lectureString("Merci de choisir un pseudo", 3, 10, "Titi");

	bool continuer = true;

	//	Boucle pour redémarer une partie une fois qu'elle est finie
	while (continuer)
	{
		//	La classe salon permet de gérer la mise en relation des joueurs (création ou rejoindre un salon existant)
		_salon = new Salon();
		if (!_salon->choixSalon(pseudo)) {
			continuer = false;
		}
		else {
			//	A cette étape, les joueurs sont mis en relation et la partie peut commencer
			_jeu = new Jeu(_salon);
			_jeu->lancementPartie();
			delete _jeu;
		}
		delete _salon;
	}

	// A ce stade le jeu est termine donc on arrete tout :(
	cout << endl << "A bientot !" << endl;
	return;
}

Unoc::~Unoc()
{
}
