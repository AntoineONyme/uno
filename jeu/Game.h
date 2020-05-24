#pragma once
#include<list>
#include <iostream>
#include <algorithm>
#include<vector>
#include"../cartes/Deck.h"
#include"../cartes/Draw.h"
#include"../cartes/StaticFunction.h"
#include "Menu.h"

class Game
{
	Draw* draw_;
	Deck* deck_;
	list<int> usedCards_ = { -1 };
public :
	Game();
	virtual void show();
	int placeCard(int cardValue);
	int selectCard();
	int playCard(int lastPlayedCard);
	int DrawCardtoHand();
	bool checkCard(int cardValue, int lastPlayedCard);
	//void showCardName(int cardId);
	void regenCards();
	void counterUno(bool tokenUno, int idUno);
	bool sayUno();
	//vector<int>* cardsToSend(int sizeHandBeginTurn, int sendChoice = 1 );
	vector<int>* cardsToSend();
	void removeDrawnCards(vector<int>* cardsToSend);
	void generateHand() {draw_->generateHand(); }
	int applyAction(int idPlayedCard);
	
};

