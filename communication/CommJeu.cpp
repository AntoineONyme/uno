#include "CommJeu.h"
#include "../cartes/StaticFunction.h"


bool CommJeu::initialiserTour()
{
	_cartesPiochees->clear();
	_cartesPiocheesAdversaire->clear();
	_carteJouee = -1;
	_carteJoueeAdversaire = -1;
	_joueurContreUno = -1;
	_declarerUno = false;
	_message = "";
	_carteDejaSubie = false;
	_finManche = FinManche::manche_en_cours;

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

	_cartesPiochees = new vector<int>;
	_cartesPiocheesAdversaire = new vector<int>;
}

//	On supprime les aggrégations
CommJeu::~CommJeu()
{
	if (_cartesPiochees != nullptr)
		delete _cartesPiochees;
	if (_cartesPiocheesAdversaire != nullptr)
		delete _cartesPiocheesAdversaire;
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
		if (lignes->size() > 8) {

			//	On regarde si celui qui a envoyé ça n'est pas le même joueur
			if (lignes->operator[](1) != std::to_string(_salon->getJoueurActuel()))
			{

				string nomJoueur = _salon->getJoueur(lignes->operator[](1));

				//	Carte Jouée
				if (lignes->operator[](2).size() > 0)
				{
					_carteJoueeAdversaire = std::stoi(lignes->operator[](2));
					cout <<endl;
				}
				//	Carte déja subie
				if (lignes->operator[](3).size() > 0)
				{
					_carteDejaSubie = true;
					cout << nomJoueur << " n'a pas joue de carte.\n";
				}
				else {
					_carteDejaSubie = false;
					if (_carteJoueeAdversaire>=0)
					{
						cout << nomJoueur << " vient de jouer la carte ";
						showCardName(_carteJoueeAdversaire);
						cout << "\n";
					}					
				}
				//	Uno
				if (lignes->operator[](4).size() > 0)
				{
					cout << nomJoueur << " declare un Uno." << endl;
				}
				//	Contre-Uno
				if (lignes->operator[](5).size() > 0)
				{
					cout << nomJoueur << " declare un contre uno contre " << _salon->getJoueur(lignes->operator[](4)) << "." << endl;
				}
				//	Si c'est la fin de la manche
				if (lignes->operator[](6).size() > 0)
				{
					if (lignes->operator[](6) == "abandon")
					{
						cout << nomJoueur << " a abandonne la partie. Vous avez donc gagne !" << endl;
						_finManche = FinManche::manche_abandonnee;
					}
					else {
						cout << nomJoueur << " vient de jouer sa dernière carte, il remporte donc la manche !" << endl;
						_finManche = FinManche::manche_terminee;
					}
				}
				//	Si pioche
				if (lignes->operator[](7).size() > 0)
				{
					cout << nomJoueur << " vient de piocher " << lignes->operator[](7) << endl;
				}
				//	Si pioche
				if (lignes->operator[](8).size() > 0)
				{
					cout << "[" << nomJoueur << "] " << lignes->operator[](8) << endl;
				}
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
bool CommJeu::finTourAtt(FinManche finManche) {
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

	//Ligne 4 : si les effets de la carte ont déja été subits
	if (_carteDejaSubie)
		lignes.push_back("Deja subi");
	else
		lignes.push_back("");

	//Ligne 5 : si un uno est déclaré
	if (_declarerUno)
		lignes.push_back("Uno");
	else
		lignes.push_back("");

	//Ligne 6 : si un contre-uno est déclaré
	if (_joueurContreUno != -1)
		lignes.push_back(std::to_string(_joueurContreUno));
	else
		lignes.push_back("");

	//Ligne 7 : si fin tour ou abandon
	if (finManche == FinManche::manche_terminee)
		lignes.push_back("fin");
	else if (finManche == FinManche::manche_abandonnee)
		lignes.push_back("abandon");
	else
		lignes.push_back("");

	//Ligne 8 :
	string cartesTirees = "";
	for (int i = 0; i < _cartesPiochees->size(); i++)
	{
		cartesTirees += std::to_string(_cartesPiochees->operator[](i)) + " ";
	}
	lignes.push_back(cartesTirees);

	//Ligne 9 : si message à transmettre
	lignes.push_back(_message);

	//	On essaye d'écrire les lignes et on teste si il y a une erreur
	if (!_fichier->ecritureLignes(lignes)) {
		cout << "Erreur de transmission :(\n";
		return false;
	}
	cout << "Informations transmises !" << endl;

	//On réinitialiser les attribus de jeu
	initialiserTour();

	//On va maintenant attendre que ce soit notre tour avant de débloquer, sauf si abandon
	if (finManche != FinManche::manche_abandonnee)
	{
		attenteTour();
	}	

	return true;
}

bool CommJeu::declarerCarteJouee(int idCarte, bool carteDejaSubie)
{
	if (_carteJouee != -1)
	{
		return false;
	}
	_carteDejaSubie = carteDejaSubie;
	_carteJouee = idCarte;		//On stocke cet id sous forme de string car c'est plus pratique
	return true;
}
