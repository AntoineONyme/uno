#pragma once
#include<list>
#include <iostream>
#include <algorithm>
#include<vector>
#include"cartes/Deck.h"
#include"cartes/Draw.h"
class Game
{
	Deck *deck;
	Draw *draw;
	list<int> hand_;
public :
	Game(Deck &deck,Draw &draw);
	virtual void show();

};

