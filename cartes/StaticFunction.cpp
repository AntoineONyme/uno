#include "StaticFunction.h"

// Tableau de valeur char ou string à afficher dans la console 
char colors[4] = { 'R','B','J','V' };
vector<string> actions = { "+2", "InvSens", "PasseTour" };


// Methode permettant de convertir les id des cartes jouées / affichées en nom compréhensible par le joueur
void showCardName(int cardId)
{	
	Deck d("d");
	d.generateOpalCards();
	d.generateColoredCards(); // on génère un deck 
	char color;
	string action;
	
	vector<Card*> deck = d.getDeck();
	int num = deck.size();
	if (deck[cardId]->getType() != "no") // s'il s'agit d'un joker ou d'un +4 on ne rentre pas dans la boucle.
		cout << deck[cardId]->getType();
	else
	{
		if (cardId < deck.size() - 8) // taille - 8 correspond au n cartes du jeu initial
		{
			if (deck[cardId]->getNumber() < 10) // si la valeur d'une carte est inférieur à 10 on sait qu'elle n'aura pas d'effet
			{
				color = colors[deck[cardId]->getColor() - 1];
				num = deck[cardId]->getNumber();
				cout << color << num;
			}
			else // sinon on sait qu'elle a une faculté spéciale.
			{
				color = colors[deck[cardId]->getColor() - 1];
				cout << color << actions[deck[cardId]->getSpecialType()];
			}
		}
		else // si on touche au cartes supérieur à n - 8 on affiche les subsituts de couleur des cartes +4 et joker 
		{
			if (cardId == deck.size()-1)
				cout << "+4 vert";
			if (cardId == deck.size()-2)
				cout << "+4 jaune";
			if (cardId == deck.size()-3)
				cout << "+4 bleu";
			if (cardId == deck.size()-4)
				cout << "+4 rouge";
			if (cardId == deck.size()-5)
				cout << "joker vert";
			if (cardId == deck.size()-6)
				cout << "joker jaune";
			if (cardId == deck.size()-7)
				cout << "joker bleu";
			if (cardId == deck.size()-8)
				cout << "joker rouge";
			

		}
	}
}