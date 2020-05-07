#include "Game.h"

Game::Game(Deck& deck, Draw& draw)
{
	
	deck.generateOpalCards();
	deck.generateColoredCards();
	deck.generateHand(hand_);
}

void Game::show() 
{
	cout << "Affichage de votre main : " << endl;
	list <int> ::iterator it;
	for (it = hand_.begin(); it != hand_.end(); ++it)
		cout <<*it << " ";

}