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
	int DrawCardtoHand(); // Méthode appelant la méthode de la classe Draw. Renvoie l'identifiant de la carte piochée.
	bool checkCard(int cardValue, int lastPlayedCard); //Prend en entrée l'identifiant de la carte que le joueur souhaite jouer et dernière carte joué. Renvoie un booléen true si cela est possible, non sinon.
	int placeCard(int cardValue); //Renvoie en int l'identifiant de la carte jouée par le joueur. Permet de renvoyer un substitut de couleur pour les cartes joker et +4. 
	void regenCards(); // Permet de régénérer la pioche si cette dernière à moins de 5 cartes.
	int selectCard(); //Permet de sélectionner une carte dans la main. Renvoie en int l'identifiant de la carte choisie.
	int playCard(int lastPlayedCard); // Macro méthode gérant toute l'action de jouer une carte. Prenant en entrée l'identifiant de la dernière carte en jeu. Renvoie l'int de la carte jouée.
	void CheatHandToOne(); // Code de triche permettant de vider instantanément une main au cours de la partie. 

	
	StructPossibilities applyAction(int idPlayedCard, bool cardAlreadyPlayed); //Prend en entrée l'identifiant de la dernière carte en jeu en int et un booléen pour savoir si cette carte a déjà été joué. 
	//Permet d'appliquer l'effet d'une carte à un joueur si cette dernière en possède une. Renvoie une StructPossibilities mise à jour si besoin.

public :
	Game();
	~Game();
	
	virtual void show(); // Permet d'afficher les cartes par leur nom plutôt qu'un identifiant numérique.
	vector<int>* generateHand(); // Méthode appelant la méthode de la classe Draw pour générer une main. Les cartes piochées sont stockées dans un vecteur int * renvoyé par la méthode.
	void removeDrawnCards(vector<int>* cardsToSend); // Prend en entrée un vecteur int* correspondant à la main du joueur précédent et retire les valeurs du vecteur de la pioche.
	StructAction play(int lastPlayedCardId, bool cardAlreadyPlayed); //Macro méthode prenant en entrée l'identifiant de la dernière carte jouée, le booléen de si la carte a déjà été jouée. Gère toute l'instance de jeu ou le joueur de sélectionner une carte ou en piocher une. Renvoie une StructAction mise à jour. 
	vector<int>* counterUno(); // Revoie un vecteur int * et permet d'empêcher un uno si utilisé au bon moment. 
	vector<int>* sayUno(); //Vérifie la taille de la main de joueur et lui fait piocher deux cartes s'il n'a pas 1 ou 0 carte. Renvoie un vecteur int* des cartes piocher. Sinon sayUno\_ passe en true. 

};

