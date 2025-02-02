#include "Salon.h"

Salon::Salon()
{
	//Fichier _fichier("XXpussyEmpalle", "/", true);
}

Salon::~Salon()
{
	//	Si on a abouti à la création d'un salon, on peut le supprimer
	if (_etat != Etat::indefini) {
		CommSalon comm;
		comm.supprimerSalon(_nom);
	}
}

//	Cr�e un menu pour choisir son salon puis s'y connecter
StatuSalon Salon::choixSalon(string pseudo)
{
	Menu menu("Choix du salon");
	menu.ajoutOption("new", "Nouveau Salon");
	menu.ajoutOption("join", "Rejoindre un salon");
	menu.ajoutOption("delete", "Supprimer un salon");
	menu.ajoutOption("quitter", "Quitter le Jeu");
	string choix = menu.affichageMenu();

	if (choix == "quitter") {
		return StatuSalon::quitter;
	}

	CommSalon comm;
	Struct_Parametres_Salon parametres_salon;
	parametres_salon.nbJoueurs = 2;	

	// On cr�e le salon
	if (choix == "new") {
		Menu::affichageSection("Creation de salon");

		parametres_salon.nom = Menu::lectureString("nom", 3, 10, "test");

		parametres_salon.nbManches = Menu::lectureInt("Nombre de manches", 1, 10, 2);

		parametres_salon.nbJoueurs = Menu::lectureInt("Nombre de joueurs", 1, 3, 2);

		if (!comm.creation(parametres_salon, pseudo)) {
			cout << "Erreur de creation de salon\n";
			return StatuSalon::erreur;
		}
		cout << "Partie cree !" << endl;
		_etat = Etat::en_attente;

		_nom = parametres_salon.nom;
		_nbManches = parametres_salon.nbManches;
		_idJoueurActuel = 0;
		_joueurs = new vector<string>;
		parametres_salon.joueurs = _joueurs;

		Menu::affichageSection("Attente debut");
		if (!comm.attenteSalonComplet(parametres_salon, true)) {
			cout << "Probl�me de salon\n";
			return StatuSalon::erreur;
		}

		cout << "La partie peut maintenant commencer !\n";
		_etat = Etat::en_jeu;

		return StatuSalon::rejoindre_salon;
	}

	// On rejoint un salon
	else if (choix == "join") {
		Menu::affichageSection("Rejoindre un salon");

		parametres_salon.nom = Menu::lectureString("nom", 3, 10, "test");

		parametres_salon = comm.join(parametres_salon.nom, pseudo);
		if (parametres_salon.erreur != "") {
			cout << "Erreur pour rejoindre un salon: " << parametres_salon.erreur << endl;
			return StatuSalon::erreur;
		}

		_nom = parametres_salon.nom;
		_nbManches = parametres_salon.nbManches;
		_idJoueurActuel = parametres_salon.idJoueurActuel;
		_joueurs = parametres_salon.joueurs;
		cout << "Partie rejointe !" << endl;
		_etat = Etat::en_attente;

		Menu::affichageSection("Attente debut");
		if (!comm.attenteSalonComplet(parametres_salon, false)) {
			cout << "Probl�me de salon\n";
			return StatuSalon::erreur;
		}
		cout << "La partie peut maintenant commencer !\n";
		_etat = Etat::en_jeu;

		return StatuSalon::rejoindre_salon;
	}
	else if (choix == "delete")
	{
		Menu::affichageSection("Supprimer un salon");
		string nom = Menu::lectureString("nom", 3, 10, "test");
		comm.supprimerSalon(nom);
	}
	return StatuSalon::erreur;
}

int Salon::idNextPlayer()
{
	return _joueurs->size() <= _idJoueurActuel + 1 ? 0 : _idJoueurActuel + 1;	//Condition binaire de v�rification
}

int Salon::idNextPlayerFirst()
{

	return _numMancheActuelle%_joueurs->size();
}
