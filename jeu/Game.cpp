#include "Game.h"

Game::Game(Deck* deck, Draw* dr)
{
	deck_ = deck;
	draw_ = dr;
	deck_->generateOpalCards();
	deck_->generateColoredCards();
	deck_->showDeck();
	cout << "Boup" << endl;
	draw_->generateHand();
	cout << "Boup" << endl;

}

void Game::show() 
{
	cout << "Affichage de votre main : " << endl;
	list<int> l = draw_->getHand();
	list<int>::iterator it;
	for (it = l.begin(); it != l.end(); it++) 
	{
		cout << *it << " | ";
	}


}

int Game::selectCard() 
{	
	int numberCardInHand;
	char answer;
	bool selection = true;
	
	list<int> l = draw_->getHand();
	//--------------------------------//

	do
	{
		cout << "Selectionnez une carte dans votre main svp : ";
		cin >> numberCardInHand;
		bool found = (find(l.begin(), l.end(), numberCardInHand) != l.end());
		if (found == true)
		{
			cout << "Votre carte a bien ete selectionnee." << endl;
			return numberCardInHand;
		}
		else 
		{	
			
			cout << "Cette carte n'existe pas ou ne fait pas partie de votre main." << endl;
			cout << "Voulez reessayez ? (y pour oui, autre sinon)" << endl;
			cin >> answer;
			if (answer != 'y')
			{
				selection = false;
			}
				
		}
	} while (selection != false);
	return -1;
}	

void Game::playCard()
{	
	int numCard = selectCard();
	if (numCard == -1)
		cout << "Aucune carte selectionnee" << endl;
	else
	{	
		if (checkCard(numCard) == true)
		{
			usedCards_.push_back(numCard);
			vector<Card*> deck = deck_->getDeck();
			cout << " Vous avez jouer la carte suivant : " << endl;
			deck[numCard]->show();
		}
		else
		{
			cout << "Vous ne pouvez pas jouer cette carte" << endl;
			Game::playCard();
		}
	}	


}

list<int> Game::DrawCardtoHand()
{
	list<int> hand = draw_->getHand();
	hand.push_back(draw_->drawCard());
	return hand;
}

bool Game::checkCard(int cardValue)
{	
	vector<Card*> deck = deck_->getDeck();
	int lastCard = usedCards_.front();
	list<int>::iterator it;
	if (usedCards_.size() == 1)
		return true;
	for (it = usedCards_.begin(); it != usedCards_.end(); it++)
	{
		if (*it == cardValue)
			return false;
	}
	if (deck[cardValue]->getType() != "no")
		return true;
	else 
	{
		if (deck[cardValue]->getColor() != deck[lastCard]->getColor() && deck[cardValue]->getNumber() != deck[lastCard]->getNumber())
			return false;
		else
			return true;
	}
	

}