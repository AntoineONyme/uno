#include "CommJeu.h"

bool CommJeu::initialiserTour()
{
	_cartesPiochees.clear();
	_carteJouee = "";
	_declareUno = false;
	_joueurContreUno = "";

	return true;
}

CommJeu::CommJeu(Salon* salon)
{
	_salon = salon;
}

bool CommJeu::ajoutCartePioche(int id)
{
	// V�rification que la phase de jeu permet de piocher
	if (_etat != jeu_joueur) {
		return false;
	}
	_cartesPiochees.push_back(id);
	return true;
}

bool CommJeu::declareUno() {
	// V�rification que la phase de jeu permet de d�clarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}
	_declareUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	// V�rification que la phase de jeu permet de d�clarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}

	// V�rification que le joueur existe et est un adversaire
	if (!_salon->joueurEstAdversaire(idJoueur)) {
		return false;
	}

	_joueurContreUno = idJoueur;
	return true;
}

bool CommJeu::finTourAtt() {
	//to do 1 : on envoit les donn�es
	vector<string> lignes;

	//Ligne 1 : on donne l'id du joueur suivant
	lignes.push_back(_salon->idNextPlayer() + "");

	//Ligne 2 : on donne l'id du joueur actuel
	lignes.push_back(_salon->getJoueurActuel() + "");

	//Ligne 3 : id carte jou�e, vide si pass� son tour (+ pioche dans ce cas)
	lignes.push_back(_carteJouee);

	//Ligne 4 : si un uno est d�clar�
	lignes.push_back(_declareUno + "");

	//Ligne 5 : si un contre-uno est d�clar�
	lignes.push_back(_joueurContreUno + "");

	//Ligne 6 : 
	lignes.push_back("");

	//Ligne 7 :
	string cartesTirees = "";
	for (int i = 0; i < _cartesPiochees.size(); i++)
	{
		cartesTirees += _cartesPiochees[i] + " ";
	}
	lignes.push_back(cartesTirees);

	//	On essaye d'�crire les lignes et on teste si il y a une erreur
	if (!_salon->getFichier()->ecritureLignes(lignes)) {
		cout << "Erreur de transmission :(\n";
		return false;
	}

	// on attend une r�ponse
	int it = 0;
		//to do 2 : on attend une r�ponse
	do
	{
		chrono::milliseconds timespan(12);
		//this_thread::sleep_for(timespan);

		if (_salon->getFichier()->detecteChangement())
		{
			break;
		}
		if (it % 30 == 0) {
			cout << "Toujours aucune modification\n";
		}
		if (it > 123) {
			cout << "Erreur de lecture : temps d'attente �coul� :(\n";
			return false;
		}
		it++;

	} while (true);

	//On termine par r�initialiser les attribus de jeu
	initialiserTour();

	return true;
}

bool CommJeu::declareCarteJouee(int idCarte)
{
	if (_carteJouee != "")
	{
		return false;
	}
	_carteJouee = idCarte + "";		//On stocke cet id sous forme de string car c'est plus pratique
	return true;
}
