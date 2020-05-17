#include "Jeu.h"

Jeu::Jeu(Salon* psalon)
{
	_salon = psalon;
	//_deck = new Deck();
}

void Jeu::lancementPartie()
{
	int nbJoueurs = _salon->getNbJoueurs();
	Menu::affichageSection("Partie");
	cout << "Bienvenue dans le jeu :)\n" << endl;
	cout << "Il y a " << nbJoueurs << " joueurs presents: ";
	for (int i = 0; i < nbJoueurs; i++) {
		cout << "[" << _salon->getJoueur(i) << "] ";
	}
	cout << endl;

	while (_numManche != _salon->getNbManches())
	{
		// to do : mettre en place la routine de jeu
		break;
	}

	system("pause");
	cout << "Partie terminee ! merci d'avoir participe <3" << endl;
	return;
}
