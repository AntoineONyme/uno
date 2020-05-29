#pragma once
#include<list>
#include <iostream>
#include <algorithm>
#include<vector>
#include"../cartes/Deck.h"
#include"../cartes/Draw.h"
#include"../cartes/StaticFunction.h"
#include "Menu.h"

/*==================================
Classe gérant toute la phase de jeu d'une partie de uno
====================================*/

typedef struct {
	int playedCardId = -1;
	bool cardAlreadyPlayed = false;
	vector<int>* drawnCards = nullptr;
	bool endRound = false;
} StructAction;

typedef struct {
	int nbCartsToDraw = 0;
	bool allowedToPlay = true;
} StructPossibilities;

class Game
{
	Draw* draw_;
	Deck* deck_;
	bool sayUno_ = false;

	vector<int>* cardsInHand();
	int DrawCardtoHand(); 
	bool checkCard(int cardValue, int lastPlayedCard); 
	int placeCard(int cardValue); 
	void regenCards(); 
	int selectCard(); 
	int playCard(int lastPlayedCard); 
	void CheatHandToOne(); 

	
	StructPossibilities applyAction(int idPlayedCard, bool cardAlreadyPlayed);

public :
	Game();
	~Game();
	
	virtual void show();
	vector<int>* generateHand();
	void removeDrawnCards(vector<int>* cardsToSend);
	StructAction play(int lastPlayedCardId, bool cardAlreadyPlayed);
	vector<int>* counterUno();
	vector<int>* sayUno();

};

