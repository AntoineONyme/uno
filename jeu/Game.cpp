#include "Game.h"

Game::Game()
{
	deck_ = new Deck("Deck");
	draw_ = new Draw();
	deck_->generateOpalCards();
	deck_->generateColoredCards();
	//deck_->showDeck();

}

Game::~Game()
{
	delete deck_;
	delete draw_;
}
//Permet d'afficher les cartes de la main dans la console
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

//permet de selectionner une carte dans la main et la retourne 
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
		// positionCardinHand est compris entre 0 et l.size(), sachant que j'ai laiss� 0 pour permettre au joueur de ne rien s�lectionner (pour piocher par exemple ?)
		cout << "Selectionnez une carte dans votre main en indiquant sa position dans cette derniere ou 0 pour piocher." << endl;
		positionCardinHand = Menu::lectureInt("carte", 0, l.size());
		if (positionCardinHand == -666)
		{
			//Cas Cheat-Code, permet d'activer un code de triche pour faciliter l'impl�mentation de certaines m�thodes.
			cout << "Motherlode" << endl;
			CheatHandToOne();
			return 0;
		}
		//	Si le joueur d�cide de piocher
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
	} while (selection != false);
	return -1;
}


// macro m�thode appelant checkCard, placeCard et selectCard.
int Game::playCard(int lastPlayedCard) // prend entr�e l'id de la derni�re carte jou�e
{
	int numCard = selectCard();


	//Cas  ou l'on d�cide de ne pas jouer de cartes.
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

// permet de mettre la main du joueur � une carte en supprimant les cartes de position > 0 et revoie l'un des substituts du joker.
void Game::CheatHandToOne()
{
	draw_->clearHand();

	/*
	list<int> hand = draw_->getHand();
	list<int>::iterator it = hand.begin();
	it++;
	for (it; it != hand.end(); it++)
		draw_->pullOutCard(*it,1);*/
}

// permet de piocher une carte et de la mettre dans la main
int Game::DrawCardtoHand()
{
	int drawCard = draw_->DrawCardtoHand();
	sayUno_ = false;

	cout << "Vous avez pioche la carte ";
	showCardName(drawCard);
	cout << endl;

	return drawCard;
}

// v�rifie que la carte selectionne peut etre jouer au dessus de la carte precedente en renvoyant un booleen
bool Game::checkCard(int cardValue, int lastPlayedCard) //prend en entr�e l'id de la carte qu'on a selectionn� ainsi que l'id de la carte jou�e avant
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

// regen la pioche du joueur 
void Game::regenCards()
{
	list<int> draw = draw_->getDraw();
	if (draw.size() <= 4)
	{
		delete draw_;
		draw_ = new Draw();
		removeDrawnCards(cardsInHand());
	}
}

//	selon les cartes pr�c�dentes, am�ne le joueur � piocher / choisir une carte et la jouer
StructAction Game::play(int lastPlayedCardId, bool cardAlreadyPlayed) // prend en entr�e l'id de la derni�re carte jou�e ainsi que le bool indiquant si la carte a d�j� �t� jou�e
{
	//	Si on est le premier � jouer, on retourne la premi�re carte de la pioche
	if (lastPlayedCardId == -1)
	{
		lastPlayedCardId = draw_->drawCard();
	}

	regenCards();
	StructAction structAction;
	structAction.drawnCards = new vector<int>;

	/*
		Permet de g�rer les diff�rents cas possible des actions permises selon la derni�re carte jou�e

		action < 0 : le joueur subit la derni�re carte et peut jouer une carte de sa main (par d�fault : action == -1 si carte standard)
		action == 0: le joueur subit un +2, il pioche donc deux cartes et passe son tour
		action > 0 : le joueur subit la derni�re car et ne peut pas jouer (ex: passe tour, inv-tour)
	*/

	StructPossibilities structPossibilities = applyAction(lastPlayedCardId, cardAlreadyPlayed);

	//	Si carte sp�ciale qui fait piocher (+2, +4)
	if (structPossibilities.nbCartsToDraw > 0)
	{
		cout << "Vous piochez " << structPossibilities.nbCartsToDraw << " cartes.\n";
	}
	for (int i = 0; i < structPossibilities.nbCartsToDraw; i++)
	{
		int drawnCard = DrawCardtoHand();
		structAction.drawnCards->push_back(drawnCard);
	}

	cout << "Derniere carte: ";
	showCardName(lastPlayedCardId);
	cout << endl;

	//	le joueur peut jouer
	if (structPossibilities.allowedToPlay)
	{

		show();
		int cartePlayed = playCard(lastPlayedCardId);

		//	le joueur a jou� une carte
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

			if (checkCard(cardDrawn, lastPlayedCardId) == true and Menu::lectureBool("Voulez-vous jouer la carte pioch�e ?", true))
			{
				cardDrawn = placeCard(cardDrawn);	// �ventuellement cardDrawn peut �tre rempl�c�e par un subtitu le cas �ch�ant (carte sp�ciale)
				structAction.playedCardId = cardDrawn;
			}
			else {
				structAction.drawnCards->push_back(cardDrawn);
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

	if (draw_->getHand().size() == 0)
	{
		structAction.endRound = true;
		cout << "Vous avez gagn� la manche, bravo !" << endl;
	}
	return structAction;
}

//permet d'emp�cher un Uno si il a �tait dit et revoie vector<int>* des cartes pioch�es en cas de p�nalit�
vector<int>* Game::counterUno()
{

	list<int> hand = draw_->getHand();
	if (hand.size() == 1 && !sayUno_) //si la condition du uno n'est pas respect�e, pioche de deux cartes
	{
		vector<int>* penaltyDrawnCards = new vector<int>;
		for (int i = 0; i < 2; i++)
		{
			cout << " PAS DE CHANCE  NUL NUL NUL NUL >:( " << endl;
			penaltyDrawnCards->push_back(DrawCardtoHand());
		}
		return penaltyDrawnCards;
	}
	else // sinon il s'en sort sans rien. 
	{
		cout << " Habile BIL o:) " << endl;

		return nullptr;
	}
}

//permet d'envoyer l'�tat uno si le joueur le peut revoie vector<int>* des cartes pioch�es en cas de p�nalit�
vector<int>* Game::sayUno()
{

	list<int> hand = draw_->getHand();
	if (hand.size() != 1) //si le joueur a plus d'une carte dans sa main, il pioche deux cartes. 
	{
		vector<int>* penaltyDrawnCards = new vector<int>;
		cout << "D�sol�, MENTEUR >:( " << endl;
		for (int i = 0; i < 2; i++)
		{
			penaltyDrawnCards->push_back(DrawCardtoHand());
		}
		return penaltyDrawnCards;
	}
	else // sinon on change l'�tat de uno en true.
	{
		cout << "Uno, OUA o:) " << endl;
		sayUno_ = true;
		return nullptr;
	}
}

//Permet d'envoyer les cartes dans sa main au joueur adverse sous la forme d'un vector<int>*
vector<int>* Game::cardsInHand()
{
	list<int> hand = draw_->getHand();
	vector<int>* cardsToSend = new vector<int>;
	list<int>::iterator it = hand.begin();
	for (it; it != hand.end(); it++)
		cardsToSend->push_back(*it);

	return cardsToSend;
}

//G�n�re la main de d�part d'un joueur et la revoie sous la forme d'un vector<int>*
vector<int>* Game::generateHand()
{
	draw_->generateHand();

	return cardsInHand();
}

//Permet de supprimer de la pioche les cartes re�us par un joueur
void Game::removeDrawnCards(vector<int>* cardsToSend) //prend un entr�e un vector<int>* des cartes jou�es par la joueur pr�c�dent.
{
	for (int i = 0; i < cardsToSend->size(); i++) {
		draw_->pullOutCard(cardsToSend->operator[](i), 0);
	}
}


//Permet d'interpr�ter et d'appliquer l'effet d'une carte si elle en a un et met � jour la struct 
StructPossibilities Game::applyAction(int idPlayedCard, bool cardAlreadyPlayed) // 
{
	StructPossibilities structPossibilities;

	vector<Card*> deck = deck_->getDeck();

	//	Aucune carte n'a encore �t� jou�e : le joueur joue celle qu'il veut
	if (idPlayedCard < 0) {
		return structPossibilities;
	}
	//	Si c'est une carte qui a d�j� �t� jou�e, aucun effet ne peut s'appliquer
	if (cardAlreadyPlayed) {
		return structPossibilities;
	}
	//	Sinon on regarde si un effet �ventuel peut s'appliquer
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


		//	Carte sp�ciales (jocker / +4)


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


// place la carte sur dans le jeu, effectue un switch de carte lorsqu'il s'agit d'un joker ou d'un +4
int Game::placeCard(int cardValue)
{
	vector<Card*> deck = deck_->getDeck();
	if (cardValue < deck.size() - 8)
		draw_->pullOutCard(cardValue, 1);

	cout << "Vous avez joue la carte :";
	showCardName(cardValue);
	cout << endl;

	//	Cartes sp�ciale (jocker / +4)
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