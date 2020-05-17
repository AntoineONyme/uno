#include "Menu.h"

/*
	Affiche dans la console le contenu d'un fichier, ex: aide ou image
*/
void Menu::affichageImageConsole(string fichier)
{
	ifstream file(fichier);
	file.good();
	if (!file.good()) {
		exit(EXIT_FAILURE);
		return;
	}

	string ligne;
	while (getline(file, ligne))
	{
		if (ligne.size() > 0)
			cout << ligne << endl;
	}

	file.close();
	return;
}

void Menu::affichageSection(string nom) {
	cout << "\n\n" << std::string(30, '=') << "\n  " << nom << "\n\n";
}

Menu::Menu(string nom) {
	_nom = nom;
}

string Menu::affichageMenu()
{
	int choix = 0;
	affichageSection(_nom);
	cout << "Choix possibles: \n";
	do {
		for (int i = 0; i < _optionsText.size(); i++)
		{
			cout << std::string(3, ' ') << i << ": " << _optionsText[i] << endl;
		}
		cout << "\n";

		cout << "Votre choix: ";
		cin >> choix;
	} while (choix < 0 and choix >= _optionsNoms.size());
	return _optionsNoms[choix];
}

void Menu::ajoutOption(string nom, string text)
{
	_optionsNoms.push_back(nom);
	_optionsText.push_back(text);
}
