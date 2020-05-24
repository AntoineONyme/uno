#include "CommJeu.h"
#include "CommSalon.h"

void CommSalon::creationFichierJeu(Struct_Parametres_Salon parametres_salon)
{
	string nfic = parametres_salon.nom + ".jeu.txt";

	Fichier fichier(nfic, REPERTOIRE, true);
	vector<string> lignes;

	// Ligne1 : ligne vide pour empécher les erreurs de fichies
	lignes.push_back("vide");

	fichier.ecritureLignes(lignes);
}

CommSalon::CommSalon()
{
}

bool CommSalon::creation(Struct_Parametres_Salon parametres_salon, string pseudo)
{
	string nfic = parametres_salon.nom + ".salon.txt";

	if (_fichier->fichierExiste(nfic, REPERTOIRE)) {
		cout << "Ce salon existe deja !\n";
		return false;
	}
	_fichier = new Fichier(nfic, REPERTOIRE, true);
	vector<string> lignes;

	// Ligne1 : version du programme
	lignes.push_back(VERSION);

	//ligne2 : nb Manches
	lignes.push_back(std::to_string(parametres_salon.nbManches));

	//ligne3 : nbJoueurs
	lignes.push_back(std::to_string(parametres_salon.nbJoueurs));

	//ligne4 : pseudo joueur qui crée la partie
	lignes.push_back(pseudo);

	if (_fichier->ecritureLignes(lignes)) {
		return true;
	}

	cout << "Impossible de creer le salon !\n";
	return false;
}

Struct_Parametres_Salon CommSalon::join(string nom, string pseudo)
{
	string nfic = nom + ".salon.txt";
	
	Fichier::synchroniser(REPERTOIRE);

	Struct_Parametres_Salon parametres_salon;
	vector<string>* lignes;
	_fichier = new Fichier(nfic, REPERTOIRE, false);

	if (!_fichier->fichierExiste(nfic, REPERTOIRE)) {
		parametres_salon.erreur = "Ce salon n'a pas ete trouve.";
		return parametres_salon;
	}

	lignes = _fichier->lectureLignes();
	parametres_salon.nom = nom;

	if (lignes->operator[](0) != VERSION) {
		parametres_salon.erreur = "Ce salon est incompatible car associe a une autre version du programme.";
		return parametres_salon;
	}

	// Il n'y a pas le nombre minimum de champs requis
	if (lignes->size() < 4)
	{
		parametres_salon.erreur = "La declaration de la partie est incorrecte.";
		return parametres_salon;
	}

	if (lignes->operator[](lignes->size() - 1) == "COMMENCE")
	{
		parametres_salon.erreur = "La partie a deja commence.";
		return parametres_salon;
	}

	parametres_salon.nbManches = std::stoi(lignes->operator[](1));
	cout << "Il y aura " << parametres_salon.nbManches << " manches et ";
	parametres_salon.nbJoueurs = std::stoi(lignes->operator[](2));
	cout << parametres_salon.nbJoueurs << " joueurs au total.\n";

	vector<string>* joueurs = new vector<string>;
	for (int i = 3; i < lignes->size(); i++) {
		joueurs->push_back(lignes->operator[](i));
	}

	//La déclaration est compatible, il reste à enregistrer ce nouveau joueur
	_fichier->ajoutLigne(pseudo);
	parametres_salon.joueurs = new vector<string>;
	parametres_salon.idJoueurActuel = lignes->size() - 3;

	return parametres_salon;
}

bool CommSalon::attenteSalonComplet(Struct_Parametres_Salon parametres_salon, bool heberge)
{
	if (_fichier == nullptr) {
		cout << "Fichier d'echange non trouve\n";
		return false;
	}

	//Premier affichage
	vector<string>* lignes = _fichier->lectureLignes();
	if (lignes->size() < 4) {
		cout << "Fichier incomplet\n";
		return false;
	}
	for (int i = 3; i < lignes->size(); i++)
	{
		// joueur actuel est le dernier joueur et a ete detecte
		if (lignes->operator[](i) == "COMMENCE") {
			return true;
		}
		if (lignes->operator[](i).size() > 0) {
			cout << lignes->operator[](i) << " attend dans le salon.\n";
			parametres_salon.joueurs->push_back(lignes->operator[](i));
		}
		
	}
	int nbLignes = lignes->size();

	while (true)
	{
		cout << "attente... ";
		_fichier->detecteChangement();

		// On va lire les données et attendre qu'il y ait assez de joueurs
		vector<string>* lignes = _fichier->lectureLignes();

		if (lignes->size() >= 4) {
			if (lignes->size() < nbLignes)
			{
				cout << "Probleme de lecture\n";
				return false;
			}

			// Modification du nb de lignes
			if (lignes->size() > nbLignes)
			{
				for (int i = nbLignes; i < lignes->size(); i++)
				{
					if (lignes->operator[](i) == "COMMENCE") {
						return true;
					}
					else if(lignes->operator[](i).size() > 0) {
						cout << lignes->operator[](i) << " a rejoint le salon.\n";
						parametres_salon.joueurs->push_back(lignes->operator[](i));
					}

				}
				nbLignes = lignes->size();

				// Si il y a assez de joueurs et le joueur héberge la partie
				if (parametres_salon.joueurs->size() >= parametres_salon.nbJoueurs and heberge)
				{
					creationFichierJeu(parametres_salon);
					_fichier->ajoutLigne("COMMENCE");
					return true;
				}
			}
		}
	}
}

bool CommSalon::supprimerSalon(string nom)
{
	string nfic = nom + ".salon.txt";
	Fichier _fichier(nfic, REPERTOIRE, false);

	return _fichier.supprimerFichier();
}
