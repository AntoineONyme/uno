#include "jeu/Unoc.h"

/*

#include <iostream>
#include <thread>
#include"jeu/Game.h"



void fctTestTiti() {


	std::cout << "Generation automatiques des cartes\n";

	Game g;
	g.generateHand();
	g.show();
	g.DrawCardtoHand();
	g.show();
	g.playCard();
	g.show();
	g.playCard();
	g.show();

} // */

int main()
{
	
	//Lancement du jeu

	Unoc unoc;

	unoc.lancementApplication();
	
	system("pause");
	//fctTestTiti();
}
