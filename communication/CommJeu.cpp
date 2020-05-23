#include "CommJeu.h"

bool CommJeu::initialiserTour()
{
	_cartesPiochees->clear();
	_cartesPiocheesAdversaire->clear();
	_carteJouee = -1;
	_carteJoueeAdversaire = -1;
	_joueurContreUno = -1;
	_declarerUno = false;

	return true;
}

CommJeu::CommJeu(Salon* psalon)
{
	_salon = psalon;
	string nfic = _salon->getNomSalon() + ".jeu.txt";

	_fichier = new Fichier(nfic, REPERTOIRE, false);

	if (!_fichier->fichierExiste(nfic, REPERTOIRE)) {
		cout << "Ce salon n'existe pas !\n";
	}

	vector<int>* _cartesPiochees = new vector<int>;
}

//	On supprime les aggrégations
CommJeu::~CommJeu()
{
	if (_cartesPiochees != nullptr)
		delete _cartesPiochees;
	if (_fichier != nullptr)
		delete _fichier;
}

//	Cette fonction attend que ce soit au joueur actuel de jouer
void CommJeu::attenteTour()
{
	_fichier->synchroniser(REPERTOIRE);

	//system("pause");
	while (true)
	{
		cout << "attente...";

		vector<string>* lignes = _fichier->lectureLignes();
		if (lignes->size() >= 7) {
			string nomJoueur = _salon->getJoueur(lignes->operator[](1));

			//	Carte Jouée
			if (lignes->operator[](2).size() > 0)
			{
				cout << nomJoueur << " vient de jouer la carte " << lignes->operator[](2) << endl;
				_carteJoueeAdversaire = std::stoi(lignes->operator[](2));
			}
			//	Uno
			if (lignes->operator[](3).size() > 0)
			{
				cout << nomJoueur << " déclare un Uno." << endl;
			}
			//	Contre-Uno
			if (lignes->operator[](4).size() > 0)
			{
				cout << nomJoueur << " déclare un contre uno contre " << _salon->getJoueur(lignes->operator[](4)) << "." << endl;
			}
			//	Si c'est la fin de la manche
			if (lignes->operator[](5).size() > 0)
			{
				cout << nomJoueur << " vient de jouer sa dernière carte, il remporte donc la manche !" << endl;
			}
			//	Si c'est la fin de la manche
			if (lignes->operator[](6).size() > 0)
			{
				cout << nomJoueur << " vient de piocher " << lignes->operator[](6) << endl;
			}


			//	On regarde si le joueur précédent appelle le joueur actuel à jouer
			if (lignes->operator[](0) == std::to_string(_salon->getJoueurActuel()))
			{
				//	Dans ce cas, attente initiale terminée : c'est au joueur de jouer
				return;
			}
		}

		_fichier->detecteChangement();
	}
}

void CommJeu::setCartesPiochees(vector<int>* cartesPiochees)
{
	if (_cartesPiochees != nullptr)
	{
		delete _cartesPiochees;
	}
	_cartesPiochees = cartesPiochees;
}

bool CommJeu::ajoutCartePioche(int id)
{
	// Vérification que la phase de jeu permet de piocher
	if (_etat != 1) {
		return false;
	}
	_cartesPiochees->push_back(id);
	return true;
}

bool CommJeu::declarerUno() {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != 1) {
		return false;
	}
	_declarerUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != 1) {
		return false;
	}
	/*
	// Vérification que le joueur existe et est un adversaire
	if (!_salon->joueurEstAdversaire(idJoueur)) {
		return false;
	}*/

	_joueurContreUno = idJoueur;
	return true;
}

//	Permet d'envoyer les actions du tour
bool CommJeu::finTourAtt(bool finPartie) {
	vector<string> lignes;

	//Ligne 1 : on donne l'id du joueur suivant
	lignes.push_back(std::to_string(_salon->idNextPlayer()));

	//Ligne 2 : on donne l'id du joueur actuel
	lignes.push_back(std::to_string(_salon->getJoueurActuel()));

	//Ligne 3 : id carte jouée, vide si passé son tour (+ pioche dans ce cas)
	if (_carteJouee != -1)
		lignes.push_back(std::to_string(_carteJouee));
	else
		lignes.push_back("");

	//Ligne 4 : si un uno est déclaré
	if (_declarerUno)
		lignes.push_back("Uno");
	else
		lignes.push_back("");

	//Ligne 5 : si un contre-uno est déclaré
	if (_joueurContreUno != -1)
		lignes.push_back(std::to_string(_joueurContreUno));
	else
		lignes.push_back("");

	//Ligne 6 : si fin tour
	if (finPartie)
		lignes.push_back("fin");
	else
		lignes.push_back("");

	//Ligne 7 :
	string cartesTirees = "";
	for (int i = 0; i < _cartesPiochees->size(); i++)
	{
		cartesTirees += std::to_string(_cartesPiochees->operator[](i)) + " ";
	}
	lignes.push_back(cartesTirees);

	//	On essaye d'écrire les lignes et on teste si il y a une erreur
	if (!_fichier->ecritureLignes(lignes)) {
		cout << "Erreur de transmission :(\n";
		return false;
	}
	cout << "Informations transmises !" << endl;

	//On réinitialiser les attribus de jeu
	initialiserTour();

	//On va maintenant attendre que ce soit notre tour avant de débloquer
	attenteTour();

	return true;
}

bool CommJeu::declarerCarteJouee(int idCarte)
{
	if (_carteJouee != -1)
	{
		return false;
	}
	_carteJouee = idCarte;		//On stocke cet id sous forme de string car c'est plus pratique
	return true;
}
