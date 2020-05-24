#include "jeu/Unoc.h"

#include <thread>
#include "jeu/Menu.h"
#include"jeu/Game.h"
#include <iostream>
/*void fctTestTiti() {


	std::cout << "Generation automatiques des cartes\n";

	Game g;
	g.show();
	int carte = g.placeCard(0);
	cout << carte;

} */// 

int main()
{
	
	//Lancement du jeu

	Unoc unoc; 

	unoc.lancementApplication();
	
	system("pause");
	//fctTestTiti();
}
