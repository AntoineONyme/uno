#include "Fichier.h"

Fichier::Fichier(string nom, string repertoir, bool createIfNonExist)
{
	_nom = nom;
	_repertoir = repertoir;
	_erreur = false;

	if (createIfNonExist && !_odrive.isDir(_repertoir)) {	//Crée le répertoir de jeu
		_odrive.mkDir(_repertoir);
	}

	_odrive.sync(_repertoir + "/" + _nom);	//Si le fichier existe il est synchronisé 

	if (!ifstream(getFilePath()).good() and createIfNonExist) {
		if (!createIfNonExist) {
			throw "Impossible de lire le fichier !";
		}

		// On crée le fichier comme on a le droit
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
	fileEchange >> timestamp;	//Lecture de la première ligne et vérification

	fileEchange.close();

	return timestamp != _lastTimestamp;	//Retourne vrai si les timestamp sont différents => il y a un changement
}

vector<string>* Fichier::lectureLignes()
{
	vector<string>* lignes = new vector<string>;

	ifstream fileEchange(getFilePath());

	if (!fileEchange.is_open() or !fileEchange) {
		_erreur = true;
		return lignes;	//Si il n'a pas été possible d'ouvrir le fichier, on retourne une liste vide
	}

	string ligne;

	getline(fileEchange, ligne);
	_lastTimestamp = std::stoi(ligne);	//Lecture de la première ligne

	// Lecture ligne par ligne jusqu'à la fin du fichier
	while (getline(fileEchange, ligne))
	{
		// Si la ligne est de longueur non nulle, alors on l'ajoute
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
	fileEchange << t << endl;	//Remplie la première ligne avec le timestamp actuel (ici une approche apparament pas cross compatible mais bon)

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
	_odrive.delFile(_repertoir + "/" + _nom);
	return true;
}

void Fichier::synchroniser(string repertoir) {
	ODrive odrive;
	odrive.refresh(repertoir + "/");
}

string Fichier::lectureString(string label, int min, int max, string vdefault)
{
	string data;
	while (true)
	{
		if (vdefault != "-333")
		{
			cout << label << " [" << vdefault << "]: ";
		}
		else {
			cout << label << " : ";
		}

		cin >> data;
		if (data == "0" and vdefault != "-333")
		{
			return vdefault;
		}
		if (data.size() < min or data.size() > max) {
			cout << "Erreur, la lougueur doit etre comprise entre " << min << " et " << max << ".\n";
		}
		else {
			return data;
		}
	}
}

int Fichier::lectureInt(string label, int min, int max, int vdefault)
{
	int data;
	while (true)
	{
		if (vdefault != -333)
		{
			cout << label << " [" << vdefault << "]: ";
		}
		else {
			cout << label << ": ";
		}

		cin >> data;
		if (data == 0 and vdefault != -333)
		{
			return vdefault;
		}
		if (data < min or data > max) {
			cout << "Erreur, la valeur doit etre comprise entre " << min << " et " << max << ".\n";
		}
		else {
			return data;
		}
	}
}
