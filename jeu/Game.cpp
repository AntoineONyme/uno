#include "Game.h"





Game::Game()
{
	deck_ = new Deck("Deck");
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
		cout << "Selectionnez une carte dans votre main en indiquant sa position dans cette derniere ou 0 pour piocher." << endl;
		positionCardinHand = Menu::lectureInt("carte", 0, l.size());

		//	Si le joueur décide de piocher
		if (positionCardinHand == 0)
		{
			selection = false;
		}
		else
		{
			positionCardinHand--;

			advance(it, positionCardinHand);
			return *it;
		}
	} 
	while (selection != false);
	return -1;
}

int Game::playCard(int lastPlayedCard)
{
	int numCard = selectCard();
	//Cas Cheat-Code, permet d'activer un code de triche pour faciliter l'implémentation de certaines méthodes.

	if (numCard == 666 || numCard == -666)
	{
		CheatHandToOne();
		return 108;
	}
	//Cas  ou l'on décide de ne pas jouer de cartes.
	if (numCard == -1)
	{
		return -1;
	}
	else
	{
		if (checkCard(numCard, lastPlayedCard) == true)
		{
			return numCard;
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
				return -1;
			}
		}
	}


}

void Game::CheatHandToOne()
{
	list<int> hand = draw_->getHand();
	list<int>::iterator it = hand.begin();
	it++;
	for (it; it != hand.end(); it++)
		draw_->pullOutCard(*it,1);
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
	

}

StructAction Game::play(int lastPlayedCardId, bool cardAlreadyPlayed)
{
	StructAction structAction;
	structAction.drawnCards = new vector<int>;

	/*
		Permet de gérer les différents cas possible des actions permises selon la dernière carte jouée

		action < 0 : le joueur subit la dernière carte et peut jouer une carte de sa main (par défault : action == -1 si carte standard)
		action == 0: le joueur subit un +2, il pioche donc deux cartes et passe son tour
		action > 0 : le joueur subit la dernière car et ne peut pas jouer (ex: passe tour, inv-tour)
	*/

	StructPossibilities structPossibilities = applyAction(lastPlayedCardId, cardAlreadyPlayed);

	//	Si carte spéciale qui fait piocher (+2, +4)
	if (structPossibilities.nbCartsToDraw>0)
	{
		cout << "Vous piochez " << structPossibilities.nbCartsToDraw << " cartes.\n";
	}
	for (int i = 0; i < structPossibilities.nbCartsToDraw; i++)
	{
		int drawnCard = DrawCardtoHand();
		structAction.drawnCards->push_back(drawnCard);
		cout << "Vous avez pioché la carte ";
		showCardName(drawnCard);
		cout << endl;
	}

	//	le joueur peut jouer
	if (structPossibilities.allowedToPlay)
	{
		if (lastPlayedCardId != -1) {
			cout << "Derniere carte: ";
			showCardName(lastPlayedCardId);
			cout << endl;
		}

		show();
		int cartePlayed = playCard(lastPlayedCardId);

		//	le joueur a joué une carte
		if (cartePlayed != -1)
		{
			cartePlayed = placeCard(cartePlayed);
			structAction.playedCardId = cartePlayed;
		}

		//	le joueur ne peut pas jouer de carte : il pioche
		else
		{
			//	Le joueur pioche une carte
			int cardDrawn = DrawCardtoHand();
			structAction.drawnCards->push_back(cardDrawn);
			cout << "Vous avez pioché la carte ";
			showCardName(cardDrawn);
			cout << "." << endl;

			if (checkCard(cardDrawn, lastPlayedCardId) == true)
			{
				//	Le joueur peut jouer la carte piochée
				cardDrawn = placeCard(cardDrawn);	// éventuellement cardDrawn peut être remplécée par un subtitu le cas échéant (carte spéciale)
				structAction.playedCardId = cardDrawn;
			}
			else {
				structAction.playedCardId = lastPlayedCardId;
				structAction.cardAlreadyPlayed = true;
			}
		}
	}
	//	Le joueur ne peut pas jouer
	else {
		show();
		cout << "Vous ne pouvez pas jouer !" << endl;

		structAction.playedCardId = lastPlayedCardId;
		structAction.cardAlreadyPlayed = true;
	}

	return structAction;
}

vector<int>* Game::counterUno(bool tokenUno, int idUno)
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
	return nullptr;
}

vector<int>* Game::sayUno()
{
	vector<int>* penaltyDrawnCards = new vector<int>;
	list<int> hand = draw_->getHand();
	if (hand.size() != 1)
	{
		for (int i = 0; i < 2; i++)
		{
			penaltyDrawnCards->push_back(DrawCardtoHand());
		}
		return penaltyDrawnCards;
	}
	else
		return penaltyDrawnCards;
}

vector<int>* Game::cardsInHand()
{
	list<int> hand = draw_->getHand();
	vector<int>* cardsToSend = new vector<int>;
	list<int>::iterator it = hand.begin();
	for (it; it != hand.end(); it++)
		cardsToSend->push_back(*it);

	return cardsToSend;
}

vector<int>* Game::generateHand()
{
	draw_->generateHand();

	return cardsInHand();
}

void Game::removeDrawnCards(vector<int>* cardsToSend)
{
	for (int i = 0; i < cardsToSend->size(); i++)
		draw_->pullOutCard(cardsToSend->operator[](i), 0);
}

StructPossibilities Game::applyAction(int idPlayedCard, bool cardAlreadyPlayed)
{
	StructPossibilities structPossibilities;

	vector<Card*> deck = deck_->getDeck();

	//	Aucune carte n'a encore été jouée : le joueur joue celle qu'il veut
	if (idPlayedCard < 0) {
		return structPossibilities;
	}
	//	Si c'est une carte qui a déjà été jouée, aucun effet ne peut s'appliquer
	if (cardAlreadyPlayed) {
		return structPossibilities;
	}
	//	Sinon on regarde si un effet éventuel peut s'appliquer
	else
	{
		int specialType = deck[idPlayedCard]->getSpecialType();
		

		//	Carte de couleur (pas jocker / +4)
		
		
			//	+2
			if (specialType == 0)
			{
				structPossibilities.nbCartsToDraw = 2;
				structPossibilities.allowedToPlay = false;
				return structPossibilities;
			}

			//	Passe-tour
			if (specialType == 1)
			{
				if (cardAlreadyPlayed)
				{
					return structPossibilities;
				}
				else {
					structPossibilities.allowedToPlay = false;
					return structPossibilities;
				}
			}

			//	Inv-tour
			if (specialType == 2)
			{
				if (cardAlreadyPlayed)
				{
					return structPossibilities;
				}
				else {
					structPossibilities.allowedToPlay = false;
					return structPossibilities;
				}
			}
		

		//	Carte spéciales (jocker / +4)
		
		
			//	Carte +4
			if (deck[idPlayedCard]->getNumber() == -2)
			{
				structPossibilities.nbCartsToDraw = 4;
				return structPossibilities;
			}
			//	Jocker
			else {
				return structPossibilities;
			}
		
	}
}



int Game::placeCard(int cardValue)
{
	vector<Card*> deck = deck_->getDeck();
	if (cardValue < deck.size() - 8)
		draw_->pullOutCard(cardValue, 1);

	cout << " Vous avez joue la carte suivante : ";
	showCardName(cardValue);
	//	Cartes spéciale (jocker / +4)
	if (cardValue < 8)
	{
		int colorChoice;
		//	Jocker
		if (cardValue < 4)
		{
			cout << "Voici le tableau de couleur : [R,B,J,V]" << endl;
			colorChoice = Menu::lectureInt("Selectionnez une couleur pour la carte svp (1 = rouge par exemple)", 1, 4);
			
			if (colorChoice == 1)
			{
				int carte = 108;
				return carte;
			}
			if (colorChoice == 2)
			{
				int carte = 109;
				return carte;
			}
			if (colorChoice == 3)
			{
				int carte = 110;
				return carte;
			}
			else
			{
				int carte = 111;
				return carte;
			}

		}
		//	+4
		else
		{
			cout << "Voici le tableau de couleur : [R,B,J,V]" << endl;

			colorChoice = Menu::lectureInt("Selectionnez une couleur pour la carte svp (1 = rouge par exemple)", 1, 4);
			if (colorChoice == 1)
			{
				int carte = 112;
				return carte;
			}
			if (colorChoice == 2)
			{
				int carte = 113;
				return carte;
			}
			if (colorChoice == 3)
			{
				int carte = 114;
				return carte;
			}
			else
			{
				int carte = 115;
				return carte;
			}

		}
	}
	return cardValue;
}