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
	static void affichageImageConsole(string fichier);
	static void affichageSection(string nom);

	Menu(string nom);
	string affichageMenu();

	void ajoutOption(string nom, string text);


	static string lectureString(string label, int min, int max, string vdefault = "-333");
	static int lectureInt(string label, int min, int max, int vdefault = -333);
	static bool lectureBool(string label, bool vdefault = false);
};