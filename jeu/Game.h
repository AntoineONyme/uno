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
Classe gerant toute la phase de jeu d'une partie de uno
====================================*/

typedef struct StructAction {
	int playedCardId = -1;
	bool cardAlreadyPlayed = false;
	vector<int>* drawnCards = nullptr;
	bool endRound = false;
} StructAction;

typedef struct StructPossibilities {
	int nbCartsToDraw = 0;
	bool allowedToPlay = true;
} StructPossibilities;

class Game
{
	Draw* draw_;
	Deck* deck_;
	bool sayUno_ = false;

	vector<int>* cardsInHand(); //Renvoie un vecteur int* des cartes se trouvant dans la main du joueur.
	int DrawCardtoHand(); // M�thode appelant la m�thode de la classe Draw. Renvoie l'identifiant de la carte pioch�e.
	bool checkCard(int cardValue, int lastPlayedCard); //Prend en entr�e l'identifiant de la carte que le joueur souhaite jouer et derni�re carte jou�. Renvoie un bool�en true si cela est possible, non sinon.
	int placeCard(int cardValue); //Renvoie en int l'identifiant de la carte jou�e par le joueur. Permet de renvoyer un substitut de couleur pour les cartes joker et +4. 
	void regenCards(); // Permet de r�g�n�rer la pioche si cette derni�re � moins de 5 cartes.
	int selectCard(); //Permet de s�lectionner une carte dans la main. Renvoie en int l'identifiant de la carte choisie.
	int playCard(int lastPlayedCard); // Macro m�thode g�rant toute l'action de jouer une carte. Prenant en entr�e l'identifiant de la derni�re carte en jeu. Renvoie l'int de la carte jou�e.
	void CheatHandToOne(); // Code de triche permettant de vider instantan�ment une main au cours de la partie. 

	
	StructPossibilities applyAction(int idPlayedCard, bool cardAlreadyPlayed); //Prend en entr�e l'identifiant de la derni�re carte en jeu en int et un bool�en pour savoir si cette carte a d�j� �t� jou�. 
	//Permet d'appliquer l'effet d'une carte � un joueur si cette derni�re en poss�de une. Renvoie une StructPossibilities mise � jour si besoin.

public :
	Game();
	~Game();
	
	virtual void show(); // Permet d'afficher les cartes par leur nom plut�t qu'un identifiant num�rique.
	vector<int>* generateHand(); // M�thode appelant la m�thode de la classe Draw pour g�n�rer une main. Les cartes pioch�es sont stock�es dans un vecteur int * renvoy� par la m�thode.
	void removeDrawnCards(vector<int>* cardsToSend); // Prend en entr�e un vecteur int* correspondant � la main du joueur pr�c�dent et retire les valeurs du vecteur de la pioche.
	StructAction play(int lastPlayedCardId, bool cardAlreadyPlayed); //Macro m�thode prenant en entr�e l'identifiant de la derni�re carte jou�e, le bool�en de si la carte a d�j� �t� jou�e. G�re toute l'instance de jeu ou le joueur de s�lectionner une carte ou en piocher une. Renvoie une StructAction mise � jour. 
	vector<int>* counterUno(); // Revoie un vecteur int * et permet d'emp�cher un uno si utilis� au bon moment. 
	vector<int>* sayUno(); //V�rifie la taille de la main de joueur et lui fait piocher deux cartes s'il n'a pas 1 ou 0 carte. Renvoie un vecteur int* des cartes piocher. Sinon sayUno\_ passe en true. 

};

