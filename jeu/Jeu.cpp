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

	while (_salon->getNumManche() != _salon->getNbManches())
	{
		cout << "Bienvenue dans la manche num " << _salon->getNumManche() + 1 << " !" << endl << endl;
		Game g;

		//	étape 1: on génère les mains des joueurs, chacun son tour
		if (_salon->getJoueurActuel() != _salon->idNextPlayerFirst())
		{
			commJeu.attenteTour();
			g.removeDrawnCards(commJeu.getCartePiocheesAdversaire());
		}
		vector<int>* mainDepart = g.generateHand();

		commJeu.declareCartesPiochees(mainDepart);
		commJeu.finTourAtt();

		//	étape 2: on joue, boucle de jeu de la manche
		while (true)
		{
			//	On commence par vérifier que le joueur précédent continue de jouer
			if (commJeu.getStatusManche() == CommJeu::manche_abandonnee)
			{
				cout << "Un abandon vient d'avoir lieu." << endl;
				return;
			}
			else if (commJeu.getStatusManche() == CommJeu::manche_terminee)
			{
				cout << "Manche terminee ! " << endl;
				break;
			}

			//	Ici la partie est tjs en cours et c'est au joueur actuel de jouer
			Menu::affichageSection("A vous de jouer !");
			//	D'abord récupérer les infos sur ce qui a été fait durant l'attente
			g.removeDrawnCards(commJeu.getCartePiocheesAdversaire());	//	Prise en compte des cartes piochées
			int derniereCarteJouee = commJeu.getCarteJoueeAdversaire();	//	Puis la dernière carte jouée
			if (commJeu.isContreUno())
			{
				commJeu.declareCartesPiochees(g.counterUno());
			}

			//	permet au joueur de subir l'effet de la carte précédente (pioche...), puis joue ou pioche si il ne peut pas jouer
			StructAction structAction = g.play(derniereCarteJouee, commJeu.getCarteDejaSubie());

			if (structAction.drawnCards->size() > 0)
			{
				commJeu.declareCartesPiochees(structAction.drawnCards);
			}

			commJeu.declarerCarteJouee(structAction.playedCardId, structAction.cardAlreadyPlayed);

			while (true) {
				Menu menu("Choix de l'action");
				menu.ajoutOption("uno", "Uno");
				menu.ajoutOption("contreUno", "Contre-Uno");
				menu.ajoutOption("msg", "Envoyer un message");
				menu.ajoutOption("abn", "Abandonner la partie");
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
				else if (choix == "msg")
				{
					string msg = Menu::lectureString("message", 1, 30);
					commJeu.declareMessage(msg);
				}
				else if (choix == "abn")
				{
					bool confirm = Menu::lectureBool("Voulez-vous reellemnt abandonner ? ");
					if (confirm)
					{
						cout << "Vous decidez d'abandonner la partie, a bientot !" << endl;
						commJeu.finTourAtt(CommJeu::manche_abandonnee);
						_salon->resetEtat();
						return;
					}
				}
				else
				{
					break;
				}
			}

			//	Si le joueur vient de jouer sa dernière carte, on termine la manche
			if (structAction.endRound)
			{
				commJeu.finTourAtt(CommJeu::manche_terminee);
				break;
			}

			//	On termine par transmettre les infos et attendre
			commJeu.finTourAtt();
		}

		//	Fin de la manche : le destructeur est automatiquement appelé
		_salon->nextManche();
	}

	cout << "Partie terminee ! merci d'avoir participe <3" << endl;
	system("pause");
	return;
}
