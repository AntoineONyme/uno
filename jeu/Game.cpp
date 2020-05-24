#include "Game.h"





Game::Game()
{	
	deck_= new Deck("Deck");
	draw_ = new Draw();
	deck_->generateOpalCards();
	deck_->generateColoredCards();
	//deck_->showDeck();

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
		cout << " | ";
	}
	cout << "\n";

}

int Game::selectCard() 
{	
	int positionCardinHand;
	bool answer;
	bool selection = true;

	list<int> l = draw_->getHand();
	list<int>::iterator it = l.begin();
	//--------------------------------//

	do
	{
		// positionCardinHand est compris entre 0 et l.size(), sachant que j'ai laissé 0 pour permettre au joueur de ne rien sélectionner (pour piocher par exemple ?)
		positionCardinHand = Menu::lectureInt("Selectionnez une carte dans votre main en indiquant sa position dans cette derniere svp", 0, l.size());
		
		if (positionCardinHand == 0)
		{	
			// ici ça aurait plus de sens de piocher 
			cout << "\n" << "Cette carte n'existe pas " << "\n" << endl;
			answer = Menu::lectureBool("Voulez reessayez ? ");

			// answer est un booléen et vaut soit vrai, soit faux.
			if (!answer)
			{
				selection = false;
			}
				
		}
		else
		{
			positionCardinHand--;

			advance(it, positionCardinHand);
			//cout << "\n" <<"Votre carte a bien etee selectionnee." << endl;
			return *it;
		}
	} while (selection != false);
	return -1;
}	

int Game::playCard(int lastPlayedCard)
{	
	int numCard = selectCard();
	if (numCard == -1)
		cout << "Aucune carte selectionnee" << endl;
	else
	{	
		if (checkCard(numCard, lastPlayedCard) == true)
		{
			
			int cardToplay = placeCard(numCard);
			return cardToplay;
			
		}
		else
		{
			char answer;
			cout << "Vous ne pouvez pas jouer cette carte" << endl;
			answer = Menu::lectureBool("Voulez-vous reselectionner une carte ? ", true);

			if (answer)
				Game::playCard(lastPlayedCard);
			else
			{
				cout << "Aucune carte selectionnee" << endl;
				return lastPlayedCard;
			}
			
		}
	}	


}

int Game::DrawCardtoHand()
{
	int drawCard = draw_->DrawCardtoHand();
	
	return drawCard;
}

bool Game::checkCard(int cardValue, int lastPlayedCard)
{	
	vector<Card*> deck = deck_->getDeck();
	
	
	list<int>::iterator it;
	if (lastPlayedCard == -1)
		return true;
	/*for (it = usedCards_.begin(); it != usedCards_.end(); it++)
	{
		if (*it == cardValue)
			return false;
	}*/
	if (deck[cardValue]->getType() != "no")
		return true;
	else 
	{
		if ((deck[cardValue]->getColor() != deck[lastPlayedCard]->getColor()) && (deck[cardValue]->getNumber() != deck[lastPlayedCard]->getNumber()))
			return false;
		else
			return true;
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
		cout << "Pas de chance il ne reste qu'une carte à aucun joueur...";
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

/*vector<int>* Game::cardsToSend(int sizeHandBeginTurn, int sendChoice)
{
	vector<int>* cardsToSend = new vector<int>;
	list<int> hand = draw_->getHand();
	list<int>::iterator it = hand.begin();
	if (sendChoice == 0)
	{
		for (it; it != hand.end(); it++)
			cardsToSend->push_back(*it);
		return cardsToSend;
	}
	else
	{
		advance(it, sizeHandBeginTurn - 1);
		for (it; it != hand.end(); it++)
			cardsToSend->push_back(*it);
		return cardsToSend;
	}
}*/

vector<int>* Game::cardsToSend()
{
	list<int> hand = draw_->getHand();
	vector<int>* cardsToSend = new vector<int>;
	list<int>::iterator it = hand.begin();
	for (it; it != hand.end(); it++)
		cardsToSend->push_back(*it);
	return cardsToSend;
}

void Game::removeDrawnCards(vector<int>* cardsToSend)
{
	for (int i = 0; i < cardsToSend->size(); i++)
		draw_->pullOutCard(cardsToSend->operator[](i), 0);
}

int Game::applyAction(int idPlayedCard)
{
	vector<Card*> deck = deck_->getDeck();
	if (idPlayedCard < 0)
		return -1;
	if (idPlayedCard > deck.size() - 9)
		return -1;
	else
	{
		
		int specialType = deck[idPlayedCard]->getSpecialType();
		string Type = deck[idPlayedCard]->getType();
		if (Type == "no")
		{
			if (specialType == 0)
			{
				Game::DrawCardtoHand();
				Game::DrawCardtoHand();
				return -1;
			}

			if (specialType == 1)
			{
				int carte = 0;
				if (deck[idPlayedCard]->getColor() == 1)
					carte = placeCard(108);
				if (deck[idPlayedCard]->getColor() == 2)
					carte = placeCard(109);
				if (deck[idPlayedCard]->getColor() == 3)
					carte = placeCard(110);
				if (deck[idPlayedCard]->getColor() == 4)
					carte = placeCard(111);
				return carte;
			}


			if (specialType == 2)
			{ 
				int carte = 0;
				if (deck[idPlayedCard]->getColor() == 1)
				{
					carte = placeCard(108);
					return carte;
				}
				if (deck[idPlayedCard]->getColor() == 2)
				{
					carte = placeCard(109);
					return carte;
				}
				if (deck[idPlayedCard]->getColor() == 3)
				{
					carte = placeCard(110);
					return carte;
				}
				if (deck[idPlayedCard]->getColor() == 4) 
				{
					carte = placeCard(111);
					return carte;
				}
					
			}
			else
				return -1;
		}

		else
		{
			if (deck[idPlayedCard]->getNumber() == -2)
			{
				Game::DrawCardtoHand();
				Game::DrawCardtoHand();
				Game::DrawCardtoHand();
				Game::DrawCardtoHand();
				return -1;
			}
			else
				return -1;
		}
	}
}

void Game::endTurn()
{
	;
}

int Game::placeCard(int cardValue)
{
	vector<Card*> deck = deck_->getDeck();
	if (cardValue < deck.size() - 8)
		draw_->pullOutCard(cardValue, 1);
	
	cout << " Vous avez jouer la carte suivant : " << endl;
	deck[cardValue]->show();
	if (cardValue < 8) 
	{
		int colorChoice;
		if (cardValue < 4)
		{
		
			cout << "Voici le tableau de couleur : [R,B,J,V]" << endl;
			cout << "Choississez la couleur de votre joker (1 = rouge par exemple) : ";
			cin >> colorChoice;
			if (colorChoice == 1)
				return 108;
			if (colorChoice == 2)
				return 109;
			if (colorChoice == 3)
				return 110;
			if (colorChoice == 1)
				return 111;

		}
		else
		{
			cout << "Voici le tableau de couleur : [R,B,J,V]" << endl;
			cout << "Choississez la couleur de votre +4 (1 = rouge par exemple) : ";
			cin >> colorChoice;
			if (colorChoice == 1)
				return 112;
			if (colorChoice == 2)
				return 113;
			if (colorChoice == 3)
				return 114;
			if (colorChoice == 1)
				return 115;

		}
	}
	return cardValue;
}