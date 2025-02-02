#include "Fichier.h"

Fichier::Fichier(string nom, string repertoir, bool createIfNonExist)
{
	_nom = nom;
	_repertoir = repertoir;
	_erreur = false;

	if (createIfNonExist && !_odrive.isDir(_repertoir)) {	//Cr�e le r�pertoir de jeu
		_odrive.mkDir(_repertoir);
	}

	_odrive.sync(_repertoir + "/" + _nom);	//Si le fichier existe il est synchronis� 

	if (!ifstream(getFilePath()).good() and createIfNonExist) {
		if (!createIfNonExist) {
			throw "Impossible de lire le fichier !";
		}

		// On cr�e le fichier comme on a le droit
		ofstream fichier(getFilePath());
		fichier.close();
	}
}

bool Fichier::detecteChangement()
{
	_odrive.waitForChange(_repertoir + "/" + _nom);	//Fct bloquante, pour attendre un changement du fichier

	ifstream fileEchange(getFilePath());

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	int timestamp;
	fileEchange >> timestamp;	//Lecture de la premi�re ligne et v�rification

	fileEchange.close();

	return timestamp != _lastTimestamp;	//Retourne vrai si les timestamp sont diff�rents => il y a un changement
}

vector<string>* Fichier::lectureLignes()
{
	vector<string>* lignes = new vector<string>;

	ifstream fileEchange(getFilePath());

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return lignes;	//Si il n'a pas �t� possible d'ouvrir le fichier, on retourne une liste vide
	}

	string ligne;

	getline(fileEchange, ligne);
	if (ligne.size()==0)
	{
		_erreur = true;
		return lignes;	//Si le fichier n'est pas nette, on arrete
	}
	_lastTimestamp = std::stoi(ligne);	//Lecture de la premi�re ligne

	// Lecture ligne par ligne jusqu'� la fin du fichier
	while (getline(fileEchange, ligne))
	{
		lignes->push_back(ligne);
	}

	fileEchange.close();

	return lignes;
}

bool Fichier::ecritureLignes(vector<string>& lignes)
{
	ofstream fileEchange(getFilePath());

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	time_t t = time(0);
	fileEchange << t << endl;	//Remplie la premi�re ligne avec le timestamp actuel (ici une approche apparament pas cross compatible mais bon)

	for (int i = 0; i < lignes.size(); i++)
	{
		fileEchange << lignes[i] << endl;
	}

	fileEchange.close();
	_odrive.refresh(_repertoir + "/" + _nom);
	return true;
}

bool Fichier::ajoutLignes(vector<string>& lignes)
{
	ofstream fileEchange(getFilePath(), ios::app);

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	for (int i = 0; i < lignes.size(); i++)
	{
		fileEchange << lignes[i] << endl;
	}

	fileEchange.close();
	_odrive.refresh(_repertoir + "/" + _nom);
	return true;
}

bool Fichier::ajoutLigne(string ligne)
{
	ofstream fileEchange(getFilePath(), ios::app);

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return false;
	}

	fileEchange << ligne << endl;

	fileEchange.close();
	_odrive.refresh(_repertoir + "/" + _nom);
	return true;
}

bool Fichier::fichierExiste(string nom, string repertoir)
{
	ODrive odrive;

	return ifstream(odrive.getFullName(repertoir + "/" + nom)).good();
}

bool Fichier::supprimerFichier()
{
	string chemin = getFilePath();
	const char *filename = chemin.c_str();
	remove(filename);
	return true;
}

void Fichier::synchroniser(string repertoir, bool bloquant) {
	ODrive odrive;
	if (bloquant)
	{
		odrive.refresh(repertoir + "/");
	}
	else {
		odrive.sync(repertoir + "/");
	}
	
}
