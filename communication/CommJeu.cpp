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
	// Vérification que la phase de jeu permet de piocher
	if (_etat != jeu_joueur) {
		return false;
	}
	_cartesPiochees.push_back(id);
	return true;
}

bool CommJeu::declareUno() {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}
	_declareUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	// Vérification que la phase de jeu permet de déclarer un uno
	if (_etat != jeu_joueur) {
		return false;
	}

	// Vérification que le joueur existe et est un adversaire
	if (!_salon->joueurEstAdversaire(idJoueur)) {
		return false;
	}

	_joueurContreUno = idJoueur;
	return true;
}

bool CommJeu::finTourAtt() {
	//to do 1 : on envoit les données
	vector<string> lignes;

	//Ligne 1 : on donne l'id du joueur suivant
	lignes.push_back(_salon->idNextPlayer() + "");

	//Ligne 2 : on donne l'id du joueur actuel
	lignes.push_back(_salon->getJoueurActuel() + "");

	//Ligne 3 : id carte jouée, vide si passé son tour (+ pioche dans ce cas)
	lignes.push_back(_carteJouee);

	//Ligne 4 : si un uno est déclaré
	lignes.push_back(_declareUno + "");

	//Ligne 5 : si un contre-uno est déclaré
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

	//	On essaye d'écrire les lignes et on teste si il y a une erreur
	if (!_salon->getFichier()->ecritureLignes(lignes)) {
		cout << "Erreur de transmission :(\n";
		return false;
	}

	// on attend une réponse
	int it = 0;
		//to do 2 : on attend une réponse
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
			cout << "Erreur de lecture : temps d'attente écoulé :(\n";
			return false;
		}
		it++;

	} while (true);

	//On termine par réinitialiser les attribus de jeu
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
