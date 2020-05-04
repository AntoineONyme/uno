// Uno.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Fichier.h"

using namespace std;

const string _DOSSIER_ = "";

int main()
{
	cout << "Hello Thibault!\n";

	vector<string> lignes;
	lignes.push_back("Ligne1");
	lignes.push_back("Ligne2");

	// Test de la classe "Fichier"
	Fichier fichier("test.txt", "../");


	cout << "Essais ecriture: " << fichier.ecritureLignes(lignes) << endl;	//Retourne 1 si l'écriture s'est bien passée
	cout << "Erreur: " << fichier.erreur() << endl; //Doit afficher 0


	cout << "\nEssais lecture: changement " << fichier.detecteChangement() << endl;	//Doit afficher 1 (car un changement vient d'être fait)
	vector<string>* lignesl;
	lignesl = fichier.lectureLignes();

	for (int i = 0; i < lignesl->size(); i++)
	{
		cout << lignesl->operator[](i) << " - ";
		//cout << (&lignesl)[i] << " - ";
	}
	cout << "\nErreur: " << fichier.erreur() << endl;
	cout << "\nEssais lecture: changement " << fichier.detecteChangement() << endl;	//Doit afficher 0 (car la lecture a déja été faite)
}