#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "odrive.h"

using namespace std;

class Fichier
{
	string _nom;
	string _repertoir;
	int _lastTimestamp = 0;
	bool _erreur = true;
	bool _nouveau = true;

	ODrive _odrive;
	string getFilePath() { return _odrive.getFullName(_repertoir + "/" + _nom); };

public:
	Fichier(string nom, string repertoir, bool createIfNonExist);
	Fichier() { return; };	//Permet de déclarer des attribus Fichier dans les classes

	bool erreur() const { return _erreur; };

	bool detecteChangement();
	vector<string>* lectureLignes();

	bool ecritureLignes(vector<string>& lignes);
	bool ajoutLignes(vector<string>& lignes);
	bool ajoutLigne(string ligne);

	static bool fichierExiste(string nom, string repertoir);
	bool supprimerFichier();
	static void synchroniser(string repertoir);
};

