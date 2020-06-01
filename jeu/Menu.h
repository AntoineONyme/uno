#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "../communication/Fichier.h"

using namespace std;

class Menu
{
	string _nom;
	vector<string> _optionsNoms;
	vector<string> _optionsText;

public:

	//	Méthodes de classe pour gérer la création d'un menu et son affichage
	Menu(string nom);
	void ajoutOption(string nom, string text);
	string affichageMenu();

	//	Méthodes d'aides pour effectuer des affichages formatés
	static void affichageImageConsole(string fichier);
	static void affichageSection(string nom);

	//	Méthodes statiques d'aides pour gérer les inputs utilisateurs
	static string lectureString(string label, int min, int max, string vdefault = "-333");
	static int lectureInt(string label, int min, int max, int vdefault = -333);
	static bool lectureBool(string label, bool vdefault = false);
};