#pragma once
#include<list>
#include <iostream>
#include <algorithm>
#include<vector>
#include"../cartes/Deck.h"
#include"../cartes/Draw.h"
#include"../cartes/StaticFunction.h"
#include "Menu.h"

typedef struct {
	int playedCardId = -1;
	bool cardAlreadyPlayed = false;
	vector<int>* drawnCards = nullptr;
} StructAction;

typedef struct {
	int nbCartsToDraw = 0;
	bool allowedToPlay = true;
} StructPossibilities;

class Game
{
	Draw* draw_;
	Deck* deck_;
	list<int> usedCards_ = { -1 };

	int DrawCardtoHand();
	bool checkCard(int cardValue, int lastPlayedCard);
	int placeCard(int cardValue);
	void regenCards();
	int selectCard();
	int playCard(int lastPlayedCard);
	vector<int>* cardsInHand();

	//	détermine les actions à réaliser et le substitu à la dernière carte
	StructPossibilities applyAction(int idPlayedCard, bool cardAlreadyPlayed);

public :
	Game();
	virtual void show();

	vector<int>* generateHand();

	void removeDrawnCards(vector<int>* cardsToSend);

	//	selon les cartes précédentes, amène le joueur à piocher / choisir une carte et la jouer
	StructAction play(int lastPlayedCardId, bool cardAlreadyPlayed);

	void counterUno(bool tokenUno, int idUno);
	bool sayUno();


	//void showCardName(int cardId);
	//vector<int>* cardsToSend(int sizeHandBeginTurn, int sendChoice = 1 );
};

