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
	Game(Deck* deck, Draw* dr);
	virtual void show();
	int selectCard();
	void playCard();
	list<int> DrawCardtoHand();
	bool checkCard(int cardValue);
};

