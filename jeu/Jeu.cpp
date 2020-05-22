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

	// Instanciation du 
	CommJeu commJeu(_salon->getNomSalon());

	while (_numManche != _salon->getNbManches())/*
	{
		Game g;

		//	�tape 1: on pioche les cartes
		if (_salon->getJoueurActuel() != 0)
		{
			commJeu.attenteInitiale();
			removeDrawCards(commJeu.cartesPiochees());
		}
		vector<int>* mainDepart = g.generateHand();

		cout << "Vous avez comme main de d�part :";
		g.show();
		commJeu.ajoutCartePioche(mainDepart);


		//	�tape 2: on joue, boucle de jeu
		while (true)
		{
			break;
		}
		break;
	}*/

	cout << "Partie terminee ! merci d'avoir participe <3" << endl;
	system("pause");
	return;
}
