#include "MenuSalon.h"

MenuSalon::MenuSalon(string nom) : Menu(nom)
{
	ajoutOption("choix", "Cr�er un salon ou en rejoindre un");
	ajoutOption("quitter", "Quitter");
}

bool MenuSalon::setAction(string nomMenu)
{
	if (nomMenu == "choix") {

	}
	return false;
}
