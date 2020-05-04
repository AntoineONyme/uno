#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

class Fichier
{
	string _nom;
	string _chemin;
	int _lastTimestamp = 0;
	bool _erreur = true;

public:
	Fichier(string nom, string chemin);
	Fichier() { return; };	//Permet de déclarer des attribus Fichier dans les classes

	bool erreur() const { return _erreur; };

	bool detecteChangement();
	vector<string>* lectureLignes();

	bool ecritureLignes(vector<string>& lignes);
};

