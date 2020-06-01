#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdio>
#include "odrive.h"

using namespace std;

class Fichier
{
	//	Données sur le fichier actuel
	string _nom;
	string _repertoir;
	int _lastTimestamp = 0;
	bool _erreur = true;
	bool _nouveau = true;

	//	Agrégat
	ODrive _odrive;

	//	Méthode privée pour obtenir le chemin absolu du fichier
	string getFilePath() { return _odrive.getFullName(_repertoir + "/" + _nom); };

public:
	Fichier(string nom, string repertoir, bool createIfNonExist);
	//Fichier() { return; };	//Permet de d�clarer des attribus Fichier dans les classes

	bool erreur() const { return _erreur; };

	//	Méthode bloquante qui attent que le fichier soit modifié par un autre joueur
	bool detecteChangement();
	//	Méthode qui retourne un vector<string> de toutes les lignes du fichier
	vector<string>* lectureLignes();

	//	Méthodes d'écriture dans le fichier, puis de de synchronisation
	bool ecritureLignes(vector<string>& lignes);	//	Celle-ci remplace le contenu précédent
	bool ajoutLignes(vector<string>& lignes);	//		Celle-ci ajoute les lignes au fichier
	bool ajoutLigne(string ligne);

	static bool fichierExiste(string nom, string repertoir);
	bool supprimerFichier();

	//	Méthodes pour forcer la synchronisation (notemment au début, lors de la création du salon)
	static void synchroniser(string repertoir, bool bloquant = true);
};

