#include "jeu/Unoc.h"

#include <thread>

#include"jeu/Game.h"
#include <iostream>
/*void fctTestTiti() {


	std::cout << "Generation automatiques des cartes\n";

	Game g;
	g.generateHand();
	g.show();
	g.playCard(18);

}*/ // 

int main()
{
	
	//Lancement du jeu

	Unoc unoc; 

	unoc.lancementApplication();
	
	system("pause");
	//fctTestTiti();
}
