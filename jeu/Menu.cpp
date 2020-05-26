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
	for (int i = 0; i < _optionsText.size(); i++)
	{
		cout << std::string(3, ' ') << i << ": " << _optionsText[i] << endl;
	}
	cout << "\n";

	choix = lectureInt("Votre choix", 0, _optionsNoms.size() - 1);
	return _optionsNoms[choix];
}

void Menu::ajoutOption(string nom, string text)
{
	_optionsNoms.push_back(nom);
	_optionsText.push_back(text);
}

string Menu::lectureString(string label, int min, int max, string vdefault)
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

		getline(cin, data);

		if (data.size() == 0 and vdefault != "-333")
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

int Menu::lectureInt(string label, int min, int max, int vdefault)
{
	string valeur;
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

		getline(cin, valeur);

		// code de triche
		if (valeur == "motherlode")
		{
			return -666;
		}
		if (valeur.size() != 0){
			data = stoi(valeur);
		}
		else if (vdefault != -333) {
			return vdefault;
		}
		else {
			cout << "Erreur, la valeur doit etre non nulle.\n";
			continue;
		}
		
		if (data < min or data > max) {
			cout << "Erreur, la valeur doit etre comprise entre " << min << " et " << max << ".\n";
		}
		else {
			return data;
		}
	}
}

bool Menu::lectureBool(string label, bool vdefault)
{
	string valeur;

	while (true)
	{
		if (vdefault == true)
		{
			cout << label << " [oui]: ";
		}
		else {
			cout << label << " [non]: ";
		}

		getline(cin, valeur);

		if (valeur.size() == 0) {
			return vdefault;
		}
		if (valeur == "oui" or valeur == "yes" or valeur == "1")
		{
			return true;
		}
		if (valeur == "non" or valeur == "no" or valeur == "0")
		{
			return false;
		}
		cout << "Erreur, les valeurs acceptées sont oui et non.\n";
	}
}