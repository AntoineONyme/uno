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
	int cardData = -1;
	vector<int>* drawnCards = nullptr;
} StructAction;

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
	vector<int>* cardsToSend();
	int applyAction(int idPlayedCard);

public :
	Game();
	virtual void show();

	vector<int>* generateHand();

	void removeDrawnCards(vector<int>* cardsToSend);

	//	selon les cartes précédentes, amène le joueur à piocher / choisir une carte et la jouer
	StructAction play(int lastPlayedCardId, int lastPlayedCardData = -1);

	void counterUno(bool tokenUno, int idUno);
	bool sayUno();


	//void showCardName(int cardId);
	//vector<int>* cardsToSend(int sizeHandBeginTurn, int sendChoice = 1 );
};

