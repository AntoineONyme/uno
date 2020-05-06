// Uno.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#pragma once
#include <iostream>
#include <thread>
#include"cartes/Deck.h"
#include"jeu/Salon.h"

const string _DOSSIER_ = "";
const string _VERSION_ = "1.0.0";
void fctTestTiti() {
	Deck d;
	std::cout << "Generation automatiques des cartes\n";
	d.generateOpalCards();
	d.generateColoredCards();
	d.generateHand();
}

void fctTestClem() {
	vector<string> lignes;
	lignes.push_back("Ligne1");
	lignes.push_back("Ligne2");

	// Test de la classe "Fichier"
	Fichier fichier("testiti.txt", "Test", true);


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

int main()
{
	fctTestClem();
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
