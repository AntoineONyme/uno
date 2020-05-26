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
	vector<int>* cardsInHand();

	// permet de piocher une carte et de la mettre dans la main
	int DrawCardtoHand(); 
	// v�rifie que la carte selectionne peut etre jouer au dessus de la carte precedente
	bool checkCard(int cardValue, int lastPlayedCard); 
	// place la carte sur dans le jeu, effectue un switch de carte lorsqu'il s'agit d'un joker ou d'un +4
	int placeCard(int cardValue); 
	// regen la pioche du joueur 
	void regenCards(); 
	//permet de selectionner une carte dans la main 
	int selectCard(); 
	// macro m�thode appelant checkCard, placeCard et selectCard.
	int playCard(int lastPlayedCard); 
	// permet de mettre la main du joueur � une carte en supprimant les cartes de position > 0
	void CheatHandToOne(); 

	//	d�termine les actions � r�aliser et le substitu � la derni�re carte
	StructPossibilities applyAction(int idPlayedCard, bool cardAlreadyPlayed);

public :
	Game();
	virtual void show();

	vector<int>* generateHand();

	void removeDrawnCards(vector<int>* cardsToSend);

	//	selon les cartes pr�c�dentes, am�ne le joueur � piocher / choisir une carte et la jouer
	StructAction play(int lastPlayedCardId, bool cardAlreadyPlayed);

	vector<int>* counterUno(bool tokenUno, int idUno);
	vector<int>* sayUno();


	//void showCardName(int cardId);
	//vector<int>* cardsToSend(int sizeHandBeginTurn, int sendChoice = 1 );
};

