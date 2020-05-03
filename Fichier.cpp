#include "Fichier.h"

Fichier::Fichier(string nom, string chemin)
{
	_nom = nom;
	_chemin = chemin;
}

bool Fichier::detecteChangement()
{
	ifstream fileEchange(_chemin + _nom);

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	int timestamp;
	fileEchange >> timestamp;	//Lecture de la première ligne et vérification

	fileEchange.close();

	return timestamp != _lastTimestamp;	//Retourne vrai si les timestamp sont différents => il y a un changement
}

vector<string>* Fichier::lectureLignes()
{
	vector<string>* lignes = new vector<string>;

	ifstream fileEchange(_chemin + _nom);

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return lignes;	//Si il n'a pas été possible d'ouvrir le fichier, on retourne une liste vide
	}

	fileEchange >> _lastTimestamp;	//Lecture de la première ligne

	// Lecture ligne par ligne jusqu'à la fin du fichier
	string ligne;
	while (getline(fileEchange, ligne))
	{
		// Si la ligne est de longueur non nulle, alors on l'ajoute
		if (ligne.size() > 0)
			lignes->push_back(ligne);
	}

	fileEchange.close();

	return lignes;
}

bool Fichier::ecritureLignes(vector<string>& lignes)
{
	ofstream fileEchange(_chemin + _nom);

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	time_t t = time(0);
	fileEchange << t << endl;	//Remplie la première ligne avec le timestamp actuel (ici une approche apparament pas cross compatible mais bon)

	for (int i = 0; i < lignes.size(); i++)
	{
		fileEchange << lignes[i] << endl;
	}

	fileEchange.close();
	return true;
}
