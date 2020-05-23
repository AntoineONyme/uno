#include "Game.h"





Game::Game()
{	
	deck_= new Deck("Deck");
	draw_ = new Draw();
	deck_->generateOpalCards();
	deck_->generateColoredCards();
	// deck_->showDeck();

}

void Game::show() 
{
	cout << "Affichage de votre main : " << endl;
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
		if ((positionCardinHand < 0) || (positionCardinHand >= l.size()))
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

int Game::playCard()
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
			return numCard;
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

char colors[4] = { 'R','B','J','V' };
vector<string> actions = { "+2", "InvSens", "PasseTour" };

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
			color = colors[deck[cardId]->getColor()-1];
			num = deck[cardId]->getNumber();
			cout << color << num << " | ";
		}
		else
		{
			color = colors[deck[cardId]->getColor()-1];
			cout << color << actions[deck[cardId]->getSpecialType()] << " | ";
		}
			
	}
}

void Game::regenCards()
{
	list<int> draw = draw_->getHand();
	int lastPlayedCard = usedCards_.back();
	list<int>::iterator it = draw.begin();
	draw_->genDraw();
	
	usedCards_.clear();
	usedCards_.push_back(-1);
	usedCards_.push_back(lastPlayedCard);
	for (it; it != draw.end(); it++)
	{
		draw_->pullOutCard(*it,0);
	}

}

void Game::counterUno(bool tokenUno, int idUno)
{
	int idCounterUno;
	if (tokenUno == false)
	{
		cout << "Pas de chance il ne reste qu'une carte � aucun joueur...";
		DrawCardtoHand();
	}
	else 
	{
		cout << "Contre qui voulez vous faire un contre-Uno ? (postition dans la liste de joueur) : ";
		cin >> idCounterUno;
		idCounterUno--;
		if (idCounterUno == idUno)
		{
			cout << "Habile Bil ! Le joueur " << idUno + 1 << "doit piocher une carte !";
		}
		else
		{
			cout << "Pas de chance ce n'est pas le bon joueur...";
			DrawCardtoHand();
		}
	}
}

bool Game::sayUno()
{
	list<int> hand = draw_->getHand();
	if (hand.size() != 1)
	{
		DrawCardtoHand();
		return false;
	}
	else
		return true;
}

vector<int>* Game::cardsToSend()
{
	list<int> hand = draw_->getHand();
	vector<int>* cardsToSend = new vector<int>;
	list<int>::iterator it = hand.begin();
	for (it; it != hand.end(); it++)
		cardsToSend->push_back(*it);
	return cardsToSend;
}

void Game::removeDrawCards(vector<int>* cardsToSend)
{
	for (int i = 0; i < cardsToSend->size(); i++)
		draw_->pullOutCard(cardsToSend->operator[](i), 0);
}

void Game::applyAction(int idPlayedCard)
{
	vector<Card*> deck = deck_->getDeck();
	int specialType = deck[idPlayedCard]->getSpecialType();
	string Type = deck[idPlayedCard]->getType();
	if (Type == "no")
	{
		switch (specialType)
		{
		case 0:
			DrawCardtoHand();
			DrawCardtoHand();
			
		case 1:
			endTurn();
			
		case 2:
			endTurn();
		
		default:
			break;
		}
	}
	else
	{
		if (Type == "joker")
			;
		else
		{
			DrawCardtoHand();
			DrawCardtoHand();
			DrawCardtoHand();
			DrawCardtoHand();
		}
	}
	
}

void Game::endTurn()
{
	;
}