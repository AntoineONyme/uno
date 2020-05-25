#include "Jeu.h"
#include"../cartes/StaticFunction.h"

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
		cout << "[";
		if (_salon->getJoueurActuel() == i)
		{
			cout << "*";
		}
		cout << _salon->getJoueur(i) << "] ";
	}
	cout << endl;

	// Instanciation de l'objet de communication
	CommJeu commJeu(_salon);

	while (_numManche != _salon->getNbManches())
	{
		Game g;

		//	étape 1: on génère les mains des joueurs, chacun son tour
		if (_salon->getJoueurActuel() != 0)
		{
			commJeu.attenteTour();
			g.removeDrawnCards(commJeu.getCartePiocheesAdversaire());
		}		
		vector<int>* mainDepart = g.generateHand();

		commJeu.setCartesPiochees(mainDepart);
		commJeu.finTourAtt();

		//	étape 2: on joue, boucle de jeu de la manche
		while (true)
		{
			//	D'abord récupérer les infos sur ce qui a été fait durant l'attente
			g.removeDrawnCards(commJeu.getCartePiocheesAdversaire());	//	Prise en compte des cartes piochées
			int derniereCarteJouee = commJeu.getCarteJoueeAdversaire();	//	Puis la dernière carte jouée

			//	permet au joueur de subir l'effet de la carte précédente (pioche...), puis joue ou pioche si il ne peut pas jouer
			StructAction structAction = g.play(derniereCarteJouee);

<<<<<<< HEAD
				g.show();
				int carte = g.playCard(derniereCarteJouee);
				if (carte != -1)
				{
					commJeu.declarerCarteJouee(carte);
				}
				else
				{
					int cartePiochee = 0; //Ici il faut le remplir avec une fonction de Game, par exemple :
					cartePiochee = g.DrawCardtoHand();
					commJeu.ajoutCartePioche(cartePiochee);
					if (g.checkCard(cartePiochee, derniereCarteJouee) == true)
					{
						g.placeCard(cartePiochee);
						commJeu.declarerCarteJouee(cartePiochee);
					}
					else
						commJeu.declarerCarteJouee(derniereCarteJouee);
				}
=======
			if (structAction.drawnCards->size()>0)
			{
				commJeu.setCartesPiochees(structAction.drawnCards);
>>>>>>> 09e1421116468dcf60af5f0f0acf8aacfd2b22ae
			}
			commJeu.declarerCarteJouee(structAction.playedCardId);
			
			while (true) {
				Menu menu("Choix de l'action");
				menu.ajoutOption("uno", "Uno");
				menu.ajoutOption("contreUno", "Contre-Uno");
				menu.ajoutOption("msg", "Envoyer un message");
				menu.ajoutOption("exit", "Terminer son tour");
				string choix = menu.affichageMenu();
				if (choix == "uno")
				{
					g.sayUno();
					commJeu.declarerUno();
				}
				else if (choix == "contreUno")
				{
					int idJoueur = Menu::lectureInt("joueur", 0, _salon->getNbJoueurs() - 1);
					commJeu.declareContreUno(idJoueur);
				}
				if (choix == "msg")
				{
					string msg = Menu::lectureString("message", 1, 30);
					commJeu.declareMessage(msg);
				}
				else
				{
					break;
				}
			}

			//	On termine par transmettre les infos et attendre
			commJeu.finTourAtt();
		}

		//Ici on ne joue qu'une manche, pas encore fini
		break;
	}

	cout << "Partie terminee ! merci d'avoir participe <3" << endl;
	system("pause");
	return;
}
