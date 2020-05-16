#include "Game.h"
char colors[4] = { 'R','B','J','V' };
vector<string> actions = { "+2", "InvSens", "PasseTour" };
Game::Game()
{	
	deck_= new Deck("Deck");
	draw_ = new Draw();
	deck_->generateOpalCards();
	deck_->generateColoredCards();
	deck_->showDeck();
	cout << "Boup" << endl;
	draw_->generateHand();
	cout << "Boup" << endl;

}

void Game::show() 
{
	cout <<"\n" << "Affichage de votre main : " << endl;
	list<int> l = draw_->getHand();
	list<int>::iterator it;
	cout << "| ";
	for (it = l.begin(); it != l.end(); it++) 
	{
		showCardName(*it);
	}
	cout << "\n";

}

int Game::selectCard() 
{	
	int positionCardinHand;
	char answer;
	bool selection = true;

	list<int> l = draw_->getHand();
	list<int>::iterator it = l.begin();
	//--------------------------------//

	do
	{
		cout << "Selectionnez une carte dans votre main en indiquant sa position dans cette derniere svp : ";
		cin >> positionCardinHand;
		positionCardinHand--;
		if (positionCardinHand < 0 || positionCardinHand > l.size())
		{	
			cout << "\n" << "Cette carte n'existe pas " << "\n" << endl;
			cout << "Voulez reessayez ? (y pour oui, autre sinon)" << endl;
			cin >> answer;
			if (answer != 'y')
			{
				selection = false;
			}
				
		}
		else
		{
			advance(it, positionCardinHand);
			cout << "\n" <<"Votre carte a bien etee selectionnee." << endl;
			return *it;
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
			
			draw_->pullOutCard(numCard,1);
			vector<Card*> deck = deck_->getDeck();
			cout << " Vous avez jouer la carte suivant : " << endl;
			deck[numCard]->show();
		}
		else
		{
			char answer;
			cout << "Vous ne pouvez pas jouer cette carte" << endl;
			cout << "Voulez vous reselectionner une carte ? (y pour oui, autre sinon) : ";
			cin >> answer;
			if (answer == 'y')
				Game::playCard();
			else
				cout << "Aucune carte selectionnee" << endl;
		}
	}	


}

void Game::DrawCardtoHand()
{
	draw_->DrawCardtoHand();
}

bool Game::checkCard(int cardValue)
{	
	vector<Card*> deck = deck_->getDeck();
	
	int lastCard = usedCards_.back();
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
		if ((deck[cardValue]->getColor() != deck[lastCard]->getColor()) && (deck[cardValue]->getNumber() != deck[lastCard]->getNumber()))
			return false;
		else
			return true;
	}
	

}

void Game::showCardName(int cardId)
{
	char color;
	string action;
	int num;
	vector<Card*> deck = deck_->getDeck();
	if (deck[cardId]->getType() != "no")
		cout << deck[cardId]->getType() << " | ";
	else
	{
		
		if (deck[cardId]->getNumber() < 10)
		{
			color = colors[deck[cardId]->getColor()];
			num = deck[cardId]->getNumber();
			cout << color << num << " | ";
		}
		else
		{
			color = colors[deck[cardId]->getColor()];
			cout << color << actions[deck[cardId]->getSpecialType()] << " | ";
		}
			
	}
}

