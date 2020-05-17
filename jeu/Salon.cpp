#include "Salon.h"

Salon::Salon()
{
	//Fichier _fichier("XXpussyEmpalle", "/", true);
}

Salon::~Salon()
{
	if (_etat != 0) {
		CommSalon comm;
		comm.supprimerSalon(_nom);
	}
}

//	Crée un menu pour choisir son salon puis s'y connecter
bool Salon::choixSalon(string pseudo)
{
	Menu menu("Choix du salon");
	menu.ajoutOption("new", "Nouveau Salon");
	menu.ajoutOption("join", "Rejoindre un salon");
	menu.ajoutOption("delete", "Supprimer un salon");
	menu.ajoutOption("quitter", "Quitter le Jeu");
	string choix = menu.affichageMenu();

	if (choix == "quitter") {
		return false;
	}

	CommSalon comm;
	Struct_Parametres_Salon parametres_salon;
	parametres_salon.nbJoueurs = 2;	//TO DO : adapter pour que plusieurs joueurs puissent jouer

	// On crée le salon
	if (choix == "new") {
		Menu::affichageSection("Creation de salon");

		cout << "nom: ";
		cin >> parametres_salon.nom;

		cout << "Nombre de manches: ";
		cin >> parametres_salon.nbManches;

		cout << "Nombre de joueurs: ";
		cin >> parametres_salon.nbJoueurs;

		if (!comm.creation(parametres_salon, pseudo)) {
			cout << "Erreur de creation de salon\n";
			return false;
		}
		cout << "Partie cree !" << endl;
		_etat = 1;

		_nom = parametres_salon.nom;
		_nbManches = parametres_salon.nbManches;
		_idJoueurActuel = 0;
		_joueurs = new vector<string>;
		parametres_salon.joueurs = _joueurs;

		Menu::affichageSection("Attente debut");
		if (!comm.attenteSalonComplet(parametres_salon, true)) {
			cout << "Problème de salon\n";
			return false;
		}

		cout << "La partie peut maintenant commencer !\n";
		_etat = 2;

		return true;
	}

	// On rejoint un salon
	else if (choix == "join") {
		Menu::affichageSection("Rejoindre un salon");
		cout << "nom: ";
		cin >> parametres_salon.nom;
		parametres_salon = comm.join(parametres_salon.nom, pseudo);
		if (parametres_salon.erreur != "") {
			cout << "Erreur pour rejoindre un salon: " << parametres_salon.erreur << endl;
			return false;
		}

		_nom = parametres_salon.nom;
		_nbManches = parametres_salon.nbManches;
		_idJoueurActuel = parametres_salon.idJoueurActuel;
		_joueurs = parametres_salon.joueurs;
		cout << "Partie rejointe !" << endl;
		_etat = 1;

		Menu::affichageSection("Attente debut");
		if (!comm.attenteSalonComplet(parametres_salon, true)) {
			cout << "Problème de salon\n";
			return false;
		}
		cout << "La partie peut maintenant commencer !\n";
		_etat = 2;

		return true;
	}
	else if (choix == "delete")
	{
		Menu::affichageSection("Supprimer un salon");
		cout << "nom: ";
		cin >> parametres_salon.nom;
		comm.supprimerSalon(parametres_salon.nom);
	}
	return false;
}

int Salon::idNextPlayer()
{
	return _joueurs->size() >= _idJoueurActuel + 1 ? 0 : _idJoueurActuel + 1;	//Condition binaire de vérification
}
