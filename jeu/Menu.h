#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
};