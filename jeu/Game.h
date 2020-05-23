#pragma once
#include<list>
#include <iostream>
#include <algorithm>
#include<vector>
#include"../cartes/Deck.h"
#include"../cartes/Draw.h"
class Game
{
	Draw* draw_;
	Deck* deck_;
	list<int> usedCards_ = { -1 };
public :
	Game();
	virtual void show();
	int selectCard();
	int playCard();
	void DrawCardtoHand();
	bool checkCard(int cardValue);
	void showCardName(int cardId);
	void regenCards();
	void counterUno(bool tokenUno, int idUno);
	bool sayUno();
	vector<int>* cardsToSend();
	void removeDrawCards(vector<int>* cardsToSend);
	void generateHand() {draw_->generateHand(); }
	void applyAction(int idPlayedCard);
	void endTurn();
};

